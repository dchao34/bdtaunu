#ifndef _TRUTHMATCHMANAGER_H_
#define _TRUTHMATCHMANAGER_H_

#include <map>
#include <boost/graph/depth_first_search.hpp>

#include "GraphDef.h"
#include "RecoGraphManager.h"
#include "McGraphManager.h"

class BDtaunuMcReader;

class TruthMatchManager {

  friend class TruthMatchDfsVisitor;

  public:
    TruthMatchManager();
    TruthMatchManager(BDtaunuMcReader *reader);
    TruthMatchManager(const TruthMatchManager&) = default;
    TruthMatchManager &operator=(const TruthMatchManager&) = default;

    int get_truth_match_status(int reco_idx) const;
    std::map<int, int> get_truth_map() const { return truth_match; }

    void update_graph(const RecoGraphManager&, const McGraphManager&);
    void analyze_graph();
    void print_mc(std::ostream &os) const;
    void print_reco(std::ostream &os) const;

  private:

    std::map<int, int> truth_match;

    BDtaunuMcReader *reader;
    const int *hMCIdx;
    const int *lMCIdx;
    const int *gammaMCIdx;
    RecoGraph::Graph reco_graph;
    RecoGraph::RecoIndexer reco_indexer;
    McGraph::Graph mc_graph;

    void contract_mc_graph();
    bool is_cleave_vertex(
        const McGraph::Vertex &v, 
        const McGraph::Graph &g, 
        const McGraph::LundIdPropertyMap &lund_id_pm,
        const McGraph::McIndexPropertyMap &mc_idx_pm) const;
};

class TruthMatchDfsVisitor : public boost::default_dfs_visitor {

  public:
    TruthMatchDfsVisitor();
    TruthMatchDfsVisitor(TruthMatchManager*);
    ~TruthMatchDfsVisitor() {};

    void finish_vertex(RecoGraph::Vertex u, const RecoGraph::Graph &g);

  private:
    TruthMatchManager *manager;
    RecoGraph::LundIdPropertyMap reco_lund_pm;
    RecoGraph::RecoIndexPropertyMap reco_idx_pm;
    RecoGraph::BlockIndexPropertyMap block_idx_pm;
    McGraph::LundIdPropertyMap mc_lund_pm;
    McGraph::McIndexPropertyMap mc_idx_pm;

    void MatchFinalState(const RecoGraph::Vertex &u);
    void MatchCompositeState(const RecoGraph::Vertex &u, const RecoGraph::Graph &g);
};

#endif
