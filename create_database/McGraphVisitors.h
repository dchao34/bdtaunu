#ifndef __MCGRAPHVISITOR_H__
#define __MCGRAPHVISITOR_H__

#include <boost/graph/depth_first_search.hpp>

#include "GraphDef.h"
#include "McBTypeCatalogue.h"

class McGraphManager;

class McGraphDfsVisitor : public boost::default_dfs_visitor {

  public:
    McGraphDfsVisitor() = default;
    McGraphDfsVisitor(McGraphManager*);
    ~McGraphDfsVisitor() {};

    void finish_vertex(McGraph::Vertex u, const McGraph::Graph &g);

  private:
    static const McBTypeCatalogue mcB_catalogue;

  private:
    McGraphManager *manager = nullptr;
    McGraph::LundIdPropertyMap lund_map;

    void AnalyzeY(const McGraph::Vertex &u, const McGraph::Graph &g);
    void AnalyzeB(const McGraph::Vertex &u, const McGraph::Graph &g);
    void AnalyzeTau(const McGraph::Vertex &u, const McGraph::Graph &g);
};

#endif
