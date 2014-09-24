#ifndef _TRUTHMATCHER_H_
#define _TRUTHMATCHER_H_

#include <map>
#include <boost/graph/depth_first_search.hpp>

#include "GraphDef.h"

class BDtaunuMcReader;

class TruthMatcher {

  friend class TruthMatchDfsVisitor;

  public:
    TruthMatcher();
    TruthMatcher(BDtaunuMcReader *reader);
    TruthMatcher(const TruthMatcher&) = default;
    TruthMatcher &operator=(const TruthMatcher&) = default;

    bool is_truth_matched(int reco_idx) const;

    void analyze();

  private:

    std::map<int, bool> truth_match;

    BDtaunuMcReader *reader;
};

class TruthMatchDfsVisitor : public boost::default_dfs_visitor {

  public:
    TruthMatchDfsVisitor();
    TruthMatchDfsVisitor(TruthMatcher*);
    ~TruthMatchDfsVisitor() {};

    void finish_vertex(RecoGraph::Vertex u, const RecoGraph::Graph &g);

  private:
    TruthMatcher *tm;
    RecoGraph::LundIdPropertyMap lund_pm;
    RecoGraph::RecoIndexPropertyMap reco_idx_pm;
    RecoGraph::BlockIndexPropertyMap block_idx_pm;
};

#endif
