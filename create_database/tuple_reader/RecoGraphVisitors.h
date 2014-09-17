#ifndef __RECOGRAPHVISITOR_H__
#define __RECOGRAPHVISITOR_H__

#include <boost/graph/depth_first_search.hpp>

#include "GraphDef.h"
#include "RecoDTypeCatalogue.h"

class RecoGraphManager;

class RecoGraphDfsVisitor : public boost::default_dfs_visitor {

  public:
    RecoGraphDfsVisitor() = default;
    RecoGraphDfsVisitor(RecoGraphManager*);
    ~RecoGraphDfsVisitor() {};

    void finish_vertex(RecoGraph::Vertex u, const RecoGraph::Graph &g);

  private:
    static const RecoDTypeCatalogue recoD_catalogue;

  private:
    RecoGraphManager *manager = nullptr;
    RecoGraph::LundIdPropertyMap lund_map;
    RecoGraph::BlockIndexPropertyMap block_idx_map;

    void AnalyzeY(const RecoGraph::Vertex &u, const RecoGraph::Graph &g);
    void AnalyzeB(const RecoGraph::Vertex &u, const RecoGraph::Graph &g);
    void AnalyzeDstar(const RecoGraph::Vertex &u, const RecoGraph::Graph &g);
    void AnalyzeD(const RecoGraph::Vertex &u, const RecoGraph::Graph &g);
    void AnalyzeLepton(const RecoGraph::Vertex &u, const RecoGraph::Graph &g);
};

#endif
