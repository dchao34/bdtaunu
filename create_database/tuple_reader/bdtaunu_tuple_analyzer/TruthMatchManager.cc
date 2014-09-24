#include <map>
#include <utility>
#include <cassert>

#include <boost/graph/depth_first_search.hpp>

#include "TruthMatchManager.h"
#include "BDtaunuMcReader.h"
#include "GraphDef.h"
#include "RecoGraphManager.h"

using namespace boost;

// TruthMatchMananger
// ------------------

TruthMatchManager::TruthMatchManager() : reader(nullptr) {
}

TruthMatchManager::TruthMatchManager(BDtaunuMcReader *_reader) : reader(_reader) {
}

bool TruthMatchManager::is_truth_matched(int reco_idx) const {
  std::map<int, bool>::const_iterator it = truth_match.find(reco_idx);
  assert(it != truth_match.end());
  return it->second;
}

void TruthMatchManager::update_graph(const RecoGraphManager &reco_graph_manager) {
  hMCIdx = reader->hMCIdx;
  lMCIdx = reader->lMCIdx;
  gammaMCIdx = reader->gammaMCIdx;
  reco_graph = reco_graph_manager.get_reco_graph();
  reco_indexer = reco_graph_manager.get_reco_indexer();
}

void TruthMatchManager::analyze_graph() {
  truth_match.clear();
  depth_first_search(reco_graph, visitor(TruthMatchDfsVisitor(this)));
}

// TruthMatchVisitor
// -----------------

TruthMatchDfsVisitor::TruthMatchDfsVisitor() : manager(nullptr) {
}

TruthMatchDfsVisitor::TruthMatchDfsVisitor(TruthMatchManager *_manager) : manager(_manager) {
  lund_pm = get(vertex_lund_id, manager->reco_graph);
  reco_idx_pm = get(vertex_reco_index, manager->reco_graph);
  block_idx_pm = get(vertex_block_index, manager->reco_graph);
}

void TruthMatchDfsVisitor::finish_vertex(RecoGraph::Vertex u, const RecoGraph::Graph &g) {

  bool is_tm = false;

  int reco_idx = get(reco_idx_pm, u);

  if ((manager->reco_indexer).is_h_candidate(reco_idx)) {
    if (manager->hMCIdx[get(block_idx_pm, u)] >= 0) is_tm = true;
    (manager->truth_match).insert(std::make_pair(reco_idx, is_tm));

  } else if ((manager->reco_indexer).is_l_candidate(reco_idx)) {
    if (manager->lMCIdx[get(block_idx_pm, u)] >= 0) is_tm = true;
    (manager->truth_match).insert(std::make_pair(reco_idx, is_tm));

  } else if ((manager->reco_indexer).is_gamma_candidate(reco_idx)) {
    if (manager->gammaMCIdx[get(block_idx_pm, u)] >= 0) is_tm = true;
    (manager->truth_match).insert(std::make_pair(reco_idx, is_tm));

  } else {
    RecoGraph::AdjacencyIterator ai, ai_end;
    for (tie(ai, ai_end) = adjacent_vertices(u, g); ai != ai_end; ++ai) {
      if (!(manager->truth_match).find(get(reco_idx_pm, *ai))->second) is_tm = false; break;
    }
    (manager->truth_match).insert(std::make_pair(reco_idx, is_tm));
  }
}
