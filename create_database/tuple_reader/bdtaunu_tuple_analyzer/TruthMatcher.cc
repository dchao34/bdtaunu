#include <map>
#include <utility>
#include <cassert>

#include <boost/graph/depth_first_search.hpp>

#include "TruthMatcher.h"
#include "BDtaunuMcReader.h"
#include "GraphDef.h"

using namespace boost;

TruthMatcher::TruthMatcher() : reader(nullptr) {
}

TruthMatcher::TruthMatcher(BDtaunuMcReader *_reader) : reader(_reader) {
}

bool TruthMatcher::is_truth_matched(int reco_idx) const {
  std::map<int, bool>::const_iterator it = truth_match.find(reco_idx);
  assert(it != truth_match.end());
  return it->second;
}

void TruthMatcher::analyze() {
  truth_match.clear();
  depth_first_search((reader->reco_graph_manager).g, visitor(TruthMatchDfsVisitor(this)));
}

TruthMatchDfsVisitor::TruthMatchDfsVisitor() : tm(nullptr) {
}

TruthMatchDfsVisitor::TruthMatchDfsVisitor(TruthMatcher *_tm) : tm(_tm) {
  lund_pm = get(vertex_lund_id, (tm->reader->reco_graph_manager).g);
  reco_idx_pm = get(vertex_reco_index, (tm->reader->reco_graph_manager).g);
  block_idx_pm = get(vertex_block_index, (tm->reader->reco_graph_manager).g);
}

void TruthMatchDfsVisitor::finish_vertex(RecoGraph::Vertex u, const RecoGraph::Graph &g) {

  int reco_idx = get(reco_idx_pm, u);
  if ((tm->reader->reco_graph_manager).reco_indexer.is_h_candidate(reco_idx)) {
    bool is_tm = false;
    if (tm->reader->hMCIdx[get(block_idx_pm, u)] >= 0) is_tm = true;
    (tm->truth_match).insert(std::make_pair(reco_idx, is_tm));
  } else if ((tm->reader->reco_graph_manager).reco_indexer.is_l_candidate(reco_idx)) {
    bool is_tm = false;
    if (tm->reader->lMCIdx[get(block_idx_pm, u)] >= 0) is_tm = true;
    (tm->truth_match).insert(std::make_pair(reco_idx, is_tm));
  } else if ((tm->reader->reco_graph_manager).reco_indexer.is_gamma_candidate(reco_idx)) {
    bool is_tm = false;
    if (tm->reader->gammaMCIdx[get(block_idx_pm, u)] >= 0) is_tm = true;
    (tm->truth_match).insert(std::make_pair(reco_idx, is_tm));
  } else {
    bool is_tm = true;
    RecoGraph::AdjacencyIterator ai, ai_end;
    for (tie(ai, ai_end) = adjacent_vertices(u, g); ai != ai_end; ++ai) {
      if (!(tm->truth_match).find(get(reco_idx_pm, *ai))->second) {
        is_tm = false;
        break;
      }
    }
    (tm->truth_match).insert(std::make_pair(reco_idx, is_tm));
  }
}
