#include <cmath>
#include <vector>
#include <cassert>

#include "GraphDef.h"
#include "Particles.h"
#include "RecoGraphVisitors.h"
#include "RecoGraphManager.h"
#include "RecoDTypeCatalogue.h"

using namespace boost;
using namespace RecoGraph;

RecoGraphDfsVisitor::RecoGraphDfsVisitor(RecoGraphManager *_manager) 
  : manager(_manager) {
  lund_map = get(vertex_lund_id, manager->g);
  block_idx_map = get(vertex_block_index, manager->g);
}

const RecoDTypeCatalogue RecoGraphDfsVisitor::recoD_catalogue = RecoDTypeCatalogue();

void RecoGraphDfsVisitor::finish_vertex(Vertex u, const Graph &g) {
  int lund = std::abs(get(lund_map, u));
  switch (lund) {
    case bdtaunu::UpsilonLund:
      AnalyzeY(u, g);
      break;
    case bdtaunu::B0Lund:
    case bdtaunu::BcLund:
      AnalyzeB(u, g);
      break;
    case bdtaunu::Dstar0Lund:
    case bdtaunu::DstarcLund:
      AnalyzeDstar(u, g);
      break;
    case bdtaunu::D0Lund:
    case bdtaunu::DcLund:
      AnalyzeD(u, g);
      break;
    case bdtaunu::piLund:
    case bdtaunu::rhoLund:
    case bdtaunu::eLund:
    case bdtaunu::muLund:
      AnalyzeLepton(u, g);
      break;
    default:
      return;
  }
  return;
}

void RecoGraphDfsVisitor::AnalyzeD(const Vertex &u, const Graph &g) {

  RecoD recoD;

  std::vector<int> lund_list;
  lund_list.push_back(get(lund_map, u));

  AdjacencyIterator ai, ai_end;
  for (tie(ai, ai_end) = adjacent_vertices(u, g); ai != ai_end; ++ai) {
    lund_list.push_back(get(lund_map, *ai));
  }
  recoD.D_mode = static_cast<int>(recoD_catalogue.search_d_catalogue(lund_list));

  (manager->D_map).insert(std::make_pair(u, recoD));

}

void RecoGraphDfsVisitor::AnalyzeDstar(const Vertex &u, const Graph &g) {

  RecoD recoD;

  std::vector<int> lund_list;
  lund_list.push_back(get(lund_map, u));

  AdjacencyIterator ai, ai_end;
  for (tie(ai, ai_end) = adjacent_vertices(u, g); ai != ai_end; ++ai) {

    int lund = get(lund_map, *ai);
    switch (abs(lund)) {
      case bdtaunu::D0Lund:
      case bdtaunu::DcLund:
        recoD.D_mode = (manager->D_map)[*ai].D_mode;
      case bdtaunu::piLund:
      case bdtaunu::pi0Lund:
      case bdtaunu::gammaLund:
        lund_list.push_back(get(lund_map, *ai));
        break;
      default:
        assert(false);
        return;
    }
  }
  recoD.Dstar_mode = static_cast<int>(recoD_catalogue.search_dstar_catalogue(lund_list));

  (manager->D_map).insert(std::make_pair(u, recoD));

}

void RecoGraphDfsVisitor::AnalyzeLepton(const Vertex &u, const Graph &g) {

  RecoLepton recoLepton;

  AdjacencyIterator ai, ai_end;
  int lund = abs(get(lund_map, u));
  switch (lund) {

    case bdtaunu::eLund:
      recoLepton.l_block_idx = block_idx_map[u];
      recoLepton.pi_block_idx = -1;
      recoLepton.tau_mode = bdtaunu::ktau_e;

    case bdtaunu::muLund:
      recoLepton.l_block_idx = block_idx_map[u];
      recoLepton.pi_block_idx = -1;
      recoLepton.tau_mode = bdtaunu::ktau_mu;
      break;

    case bdtaunu::piLund:
      recoLepton.l_block_idx = -1;
      recoLepton.pi_block_idx = block_idx_map[u];
      recoLepton.tau_mode = bdtaunu::ktau_pi;
      break;

    case bdtaunu::rhoLund:
      recoLepton.l_block_idx = -1;
      for (tie(ai, ai_end) = adjacent_vertices(u, g); ai != ai_end; ++ai) {
        if (abs(get(lund_map, *ai)) == bdtaunu::piLund) {
          recoLepton.pi_block_idx = (manager->Lepton_map)[*ai].pi_block_idx;
          break;
        }
      }
      recoLepton.tau_mode = bdtaunu::ktau_rho;
      break;

    default:
      assert(false);
      return;
  }

  (manager->Lepton_map).insert(std::make_pair(u, recoLepton));
}


void RecoGraphDfsVisitor::AnalyzeB(const Vertex &u, const Graph &g) {

  RecoB recoB;

  if (abs(get(lund_map, u)) == bdtaunu::B0Lund) {
    recoB.flavor = bdtaunu::kB0;
  } else {
    recoB.flavor = bdtaunu::kBc;
  }

  AdjacencyIterator ai, ai_end;
  for (tie(ai, ai_end) = adjacent_vertices(u, g); ai != ai_end; ++ai) {

    int lund = abs(get(lund_map, *ai));
    switch (lund) {
      case bdtaunu::D0Lund:
      case bdtaunu::DcLund:
      case bdtaunu::Dstar0Lund:
      case bdtaunu::DstarcLund:
        recoB.D = &(manager->D_map)[*ai];
        break;
      case bdtaunu::eLund:
      case bdtaunu::muLund:
      case bdtaunu::piLund:
      case bdtaunu::rhoLund:
        recoB.Lepton = &(manager->Lepton_map)[*ai];
        break;
      default:
        assert(false);
        return;
    }
  }

  (manager->B_map).insert(std::make_pair(u, recoB));
}



void RecoGraphDfsVisitor::AnalyzeY(const Vertex &u, const Graph &g) {

  RecoY recoY;

  AdjacencyIterator ai, ai_end;
  for (tie(ai, ai_end) = adjacent_vertices(u, g); ai != ai_end; ++ai) {

    int lund = abs(get(lund_map, *ai));
    switch (lund) {
      case bdtaunu::B0Lund:
      case bdtaunu::BcLund:
        if ((manager->B_map)[*ai].Lepton->l_block_idx >= 0) {
          recoY.tagB = &(manager->B_map)[*ai];
        } else {
          recoY.sigB = &(manager->B_map)[*ai];
        }
        break;
      default:
        assert(false);
        return;
    }
  }

  (manager->Y_map).insert(std::make_pair(u, recoY));
}

