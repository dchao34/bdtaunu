#include <vector>
#include <map>
#include <algorithm>
#include <utility>
#include <fstream>
#include <cassert>

#include <boost/graph/depth_first_search.hpp>
#include <boost/graph/graphviz.hpp>

#include "BDtaunuDef.h"
#include "TruthMatchManager.h"
#include "BDtaunuMcReader.h"
#include "GraphDef.h"
#include "RecoGraphManager.h"
#include "McGraphManager.h"
#include "BDtaunuGraphWriter.h"

using namespace boost;
using namespace bdtaunu;

// TruthMatchMananger
// ------------------

TruthMatchManager::TruthMatchManager() : reader(nullptr) {
}

TruthMatchManager::TruthMatchManager(BDtaunuMcReader *_reader) : reader(_reader) {
}

int TruthMatchManager::get_truth_match_status(int reco_idx) const {
  std::map<int, int>::const_iterator it = truth_match.find(reco_idx);
  assert(it != truth_match.end());
  return it->second;
}

void TruthMatchManager::update_graph(
    const RecoGraphManager &reco_graph_manager, 
    const McGraphManager &mc_graph_manager) {
  hMCIdx = reader->hMCIdx;
  lMCIdx = reader->lMCIdx;
  gammaMCIdx = reader->gammaMCIdx;
  reco_graph = reco_graph_manager.get_reco_graph();
  reco_indexer = reco_graph_manager.get_reco_indexer();
  mc_graph = mc_graph_manager.get_mc_graph();
  contract_mc_graph();
}

void TruthMatchManager::analyze_graph() {
  truth_match.clear();
  depth_first_search(reco_graph, visitor(TruthMatchDfsVisitor(this)));
}

bool TruthMatchManager::is_cleave_vertex(
    const McGraph::Vertex &v, 
    const McGraph::Graph &g, 
    const McGraph::LundIdPropertyMap &lund_id_pm,
    const McGraph::McIndexPropertyMap &mc_idx_pm) const {

  // neutrinos, tau, and K0
  switch (abs(lund_id_pm[v])) {
    case nu_eLund:
    case nu_muLund:
    case nu_tauLund:
    case tauLund:
    case K0Lund:
      return true;
  }

  // initial e+e- beam particles
  switch (mc_idx_pm[v]) {
    case 0:
    case 1:
      return true;
  }

  // elimimate final state particles' daughters
  graph_traits<McGraph::Graph>::in_edge_iterator ie, ie_end;
  tie(ie, ie_end) = in_edges(v, g);
  if ((ie != ie_end) && (lund_id_pm[v] != UpsilonLund)) {
    assert(ie + 1 == ie_end);
    if (is_final_state_particle(lund_id_pm[source(*ie, g)])) {
      return true;
    }
  }

  // eliminate MC added photons
  if ((ie != ie_end) && (lund_id_pm[v] == gammaLund)) {
    assert(ie + 1 == ie_end);
    if (lund_id_pm[source(*ie, g)] != pi0Lund) {
      return true;
    }
  }

  return false;

}

void TruthMatchManager::contract_mc_graph() {

  McGraph::Graph &g = mc_graph;
  McGraph::McIndexPropertyMap mc_idx_pm = get(vertex_mc_index, g);
  McGraph::LundIdPropertyMap lund_id_pm = get(vertex_lund_id, g);

  std::vector<int> to_cleave;
  graph_traits<McGraph::Graph>::vertex_iterator vi, vi_end;
  for (tie(vi, vi_end) = vertices(g); vi != vi_end; ++vi)
    if (is_cleave_vertex(*vi, g, lund_id_pm, mc_idx_pm)) to_cleave.push_back(mc_idx_pm[*vi]);

  for (auto i : to_cleave) {

    graph_traits<McGraph::Graph>::vertex_iterator vi_begin, vi_end;
    tie(vi_begin, vi_end) = vertices(g);
    McGraph::Vertex v = *std::find_if(vi_begin, vi_end, 
        [i, mc_idx_pm] (const McGraph::Vertex &v) { return (i == mc_idx_pm[v]); });

    McGraph::Vertex m;
    graph_traits<McGraph::Graph>::in_edge_iterator ie, ie_end;
    tie(ie, ie_end) = in_edges(v, g);
    if (ie != ie_end) {
      assert(ie + 1 == ie_end);
      m = source(*ie, g);
      McGraph::Vertex d;
      graph_traits<McGraph::Graph>::out_edge_iterator oe, oe_end;
      for (tie(oe, oe_end) = out_edges(v, g); oe != oe_end; ++oe) {
        d = target(*oe, g);
        add_edge(m, d, g);
      }
    }

    clear_vertex(v, g);
    remove_vertex(v, g);
    
  }

}

void TruthMatchManager::print_mc(std::ostream &os) const {
  boost::write_graphviz(
      os, mc_graph,
      make_graph_writer(mc_graph, BDtaunuMcReader::lund_to_name,
                        get(vertex_lund_id, mc_graph),
                        get(vertex_mc_index, mc_graph)),
      boost::default_writer(), 
      MyGraphWriter("MC Graph with Edge Contraction"));
}

void TruthMatchManager::print_reco(std::ostream &os) const {
  boost::write_graphviz(
      os, reco_graph,
      make_myvertex_writer(reco_graph, BDtaunuMcReader::lund_to_name,
                           truth_match,
                           get(vertex_lund_id, reco_graph),
                           get(vertex_reco_index, reco_graph)),
      make_myedge_writer(reco_graph, BDtaunuMcReader::lund_to_name,
                         truth_match,
                         get(vertex_lund_id, reco_graph),
                         get(vertex_reco_index, reco_graph)),
      MyGraphWriter("Reco Graph with Truth Match"));
}






// TruthMatchVisitor
// -----------------

TruthMatchDfsVisitor::TruthMatchDfsVisitor() : manager(nullptr) {
}

TruthMatchDfsVisitor::TruthMatchDfsVisitor(TruthMatchManager *_manager) : manager(_manager) {
  reco_lund_pm = get(vertex_lund_id, manager->reco_graph);
  reco_idx_pm = get(vertex_reco_index, manager->reco_graph);
  block_idx_pm = get(vertex_block_index, manager->reco_graph);
  mc_lund_pm = get(vertex_lund_id, manager->mc_graph);
  mc_idx_pm = get(vertex_mc_index, manager->mc_graph);
}

void TruthMatchDfsVisitor::finish_vertex(RecoGraph::Vertex u, const RecoGraph::Graph &g) {
  int lund = std::abs(reco_lund_pm[u]);
  switch (lund) {
    case bdtaunu::UpsilonLund:
    case bdtaunu::B0Lund:
    case bdtaunu::BcLund:
    case bdtaunu::Dstar0Lund:
    case bdtaunu::DstarcLund:
    case bdtaunu::D0Lund:
    case bdtaunu::DcLund:
    case bdtaunu::KSLund:
    case bdtaunu::rhoLund:
    case bdtaunu::pi0Lund:
      MatchCompositeState(u, g);
      break;
    case bdtaunu::eLund:
    case bdtaunu::muLund:
    case bdtaunu::piLund:
    case bdtaunu::KLund:
    case bdtaunu::gammaLund:
      MatchFinalState(u);
      break;
    default:
      assert(false);
      return;
  }
}

void TruthMatchDfsVisitor::MatchFinalState(const RecoGraph::Vertex &u) {
  const int *hitMap = nullptr;
  switch (abs(reco_lund_pm[u])) {
    case eLund:
    case muLund:
      hitMap = manager->lMCIdx;
      break;
    case piLund:
    case KLund:
      hitMap = manager->hMCIdx;
      break;
    case gammaLund:
      hitMap = manager->gammaMCIdx;
      break;
    default:
      assert(false);
  }

  manager->truth_match.insert(
      std::make_pair(reco_idx_pm[u], hitMap[block_idx_pm[u]]));

}

void TruthMatchDfsVisitor::MatchCompositeState(const RecoGraph::Vertex &u, const RecoGraph::Graph &g) {

  int tm_mc_idx = -1;

  std::vector<int> dau_tm_mc_idx;
  RecoGraph::AdjacencyIterator ai, ai_end;
  for (tie(ai, ai_end) = adjacent_vertices(u, g); ai != ai_end; ++ai) {
    dau_tm_mc_idx.push_back((manager->truth_match).find(reco_idx_pm[*ai])->second);
  }
  std::sort(dau_tm_mc_idx.begin(), dau_tm_mc_idx.end());

  if (dau_tm_mc_idx[0] < 0) {
    manager->truth_match.insert(
        std::make_pair(reco_idx_pm[u], tm_mc_idx));
    return; 
  }

  graph_traits<McGraph::Graph>::vertex_iterator vi, vi_end;
  for (tie(vi, vi_end) = vertices(manager->mc_graph); vi != vi_end; ++vi) {

    if (reco_lund_pm[u] == mc_lund_pm[*vi]) {

      std::vector<int> dau_mc_idx;

      McGraph::AdjacencyIterator bi, bi_end;
      for (tie(bi, bi_end) = adjacent_vertices(*vi, manager->mc_graph); bi != bi_end; ++bi) {
        dau_mc_idx.push_back(mc_idx_pm[*bi]);
      }
      std::sort(dau_mc_idx.begin(), dau_mc_idx.end());

      if (dau_tm_mc_idx == dau_mc_idx) {
        tm_mc_idx = mc_idx_pm[*vi];
        break;
      }
    }

  }

  manager->truth_match.insert(
      std::make_pair(reco_idx_pm[u], tm_mc_idx));

}
