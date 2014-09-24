#ifndef _TRUTHMATCHMANAGER_H_
#define _TRUTHMATCHMANAGER_H_

#include <map>
#include <boost/graph/depth_first_search.hpp>

#include "GraphDef.h"
#include "RecoGraphManager.h"

class BDtaunuMcReader;

class TruthMatchManager {

  friend class TruthMatchDfsVisitor;

  public:
    TruthMatchManager();
    TruthMatchManager(BDtaunuMcReader *reader);
    TruthMatchManager(const TruthMatchManager&) = default;
    TruthMatchManager &operator=(const TruthMatchManager&) = default;

    bool is_truth_matched(int reco_idx) const;

    void update_graph(const RecoGraphManager&);
    void analyze_graph();

  private:

    std::map<int, bool> truth_match;

    BDtaunuMcReader *reader;
    const int *hMCIdx;
    const int *lMCIdx;
    const int *gammaMCIdx;
    RecoGraph::Graph reco_graph;
    RecoGraph::RecoIndexer reco_indexer;
};

class TruthMatchDfsVisitor : public boost::default_dfs_visitor {

  public:
    TruthMatchDfsVisitor();
    TruthMatchDfsVisitor(TruthMatchManager*);
    ~TruthMatchDfsVisitor() {};

    void finish_vertex(RecoGraph::Vertex u, const RecoGraph::Graph &g);

  private:
    TruthMatchManager *manager;
    RecoGraph::LundIdPropertyMap lund_pm;
    RecoGraph::RecoIndexPropertyMap reco_idx_pm;
    RecoGraph::BlockIndexPropertyMap block_idx_pm;
};

#endif
