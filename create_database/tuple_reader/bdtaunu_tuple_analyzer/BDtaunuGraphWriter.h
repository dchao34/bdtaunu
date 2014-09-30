#ifndef __BDTAUNUGRAPHWRITER_H_
#define __BDTAUNUGRAPHWRITER_H_

#include <iostream> 
#include <fstream> 
#include <string> 

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphviz.hpp>

template <typename GraphT, typename LundMap,
          typename LundPM, typename IdxPM>
class BDtaunuGraphWriter {

  private:
    typedef typename boost::graph_traits<GraphT>::vertex_descriptor VertexT;

  public:
    BDtaunuGraphWriter(
        const GraphT &_graph, 
        const LundMap &_lund_map,
        const LundPM &_lund_pm, 
        const IdxPM &_idx_pm) : 
        g(_graph), 
        lund_map(_lund_map), 
        lund_pm(_lund_pm), 
        idx_pm(_idx_pm) {}

    void operator()(std::ostream &out, const VertexT &v) const;

  private:
    GraphT g;
    LundMap lund_map;
    LundPM lund_pm;
    IdxPM idx_pm;
};

template <typename GraphT, typename LundMap,
          typename LundPM, typename IdxPM>
void BDtaunuGraphWriter<GraphT, LundMap, LundPM, IdxPM>::operator() (
    std::ostream &out, const VertexT &v) const {

  typename LundMap::const_iterator it = lund_map.find(lund_pm[v]);
  if (it != lund_map.end()) {
    out << "[label=\"" << idx_pm[v] << ": " << it->second << "\",color=\"blue\"]";
  } else {
    out << "[label=\"" << idx_pm[v] << ": " << lund_pm[v] << "\",color=\"blue\"]";
  }

}

template <typename GraphT, typename LundMap,
          typename LundPM, typename IdxPM>
BDtaunuGraphWriter<GraphT, LundMap, LundPM, IdxPM>
make_graph_writer(const GraphT &g, const LundMap lund_map, 
                  const LundPM lund_pm, const IdxPM idx_pm) {

  return BDtaunuGraphWriter<GraphT, LundMap, LundPM, IdxPM>(g, lund_map, lund_pm, idx_pm);
}

template <typename GraphT, typename LundMap, typename TruthMatchMap, 
          typename LundPM, typename IdxPM>
class MyVertexWriter {

  private:
    typedef typename boost::graph_traits<GraphT>::vertex_descriptor VertexT;

  public:
    MyVertexWriter(
        const GraphT &_graph, 
        const LundMap &_lund_map,
        const TruthMatchMap &_tm_map,
        const LundPM &_lund_pm, 
        const IdxPM &_idx_pm) :
        g(_graph), 
        lund_map(_lund_map), 
        tm_map(_tm_map), 
        lund_pm(_lund_pm), 
        idx_pm(_idx_pm) {}

    void operator()(std::ostream &out, const VertexT &v) const;

  private:
    GraphT g;
    LundMap lund_map;
    TruthMatchMap tm_map;
    LundPM lund_pm;
    IdxPM idx_pm;
};

template <typename GraphT, typename LundMap, typename TruthMatchMap, 
          typename LundPM, typename IdxPM>
void MyVertexWriter<GraphT, LundMap, TruthMatchMap, LundPM, IdxPM>::operator() (
    std::ostream &out, const VertexT &v) const {

  typename LundMap::const_iterator it = lund_map.find(lund_pm[v]);
  typename TruthMatchMap::const_iterator tm_it = tm_map.find(idx_pm[v]);
  if (it != lund_map.end()) {
    if (tm_it != tm_map.end() && tm_it->second >= 0) {
      //out << "[label=\"" << idx_pm[v] << ": " << it->second << "\",color=\"blue\",penwidth=\"3\",fillcolor=\"cyan\",style=\"filled\"]";
      out << "[label=\"" << idx_pm[v] << ": " << it->second << "\",color=\"red\",penwidth=\"3\",fillcolor=\"lightskyblue\",style=\"filled\"]";
    } else {
      out << "[label=\"" << idx_pm[v] << ": " << it->second << "\",color=\"red\"]";
    }
  } else {
    out << "[label=\"" << idx_pm[v] << ": " << lund_pm[v] << "\",color=\"red\"]";
  }

}

template <typename GraphT, typename LundMap, typename TruthMatchMap, 
          typename LundPM, typename IdxPM>
MyVertexWriter<GraphT, LundMap, TruthMatchMap, LundPM, IdxPM>
make_myvertex_writer(const GraphT &g, const LundMap lund_map, const TruthMatchMap truthmatch_map,
                  const LundPM lund_pm, const IdxPM idx_pm) {

  return MyVertexWriter<GraphT, LundMap, TruthMatchMap, LundPM, IdxPM>(g, lund_map, truthmatch_map, lund_pm, idx_pm);
}

template <typename GraphT, typename LundMap, typename TruthMatchMap, 
          typename LundPM, typename IdxPM>
class MyEdgeWriter {

  private:
    typedef typename boost::graph_traits<GraphT>::edge_descriptor EdgeT;

  public:
    MyEdgeWriter(
        const GraphT &_graph, 
        const LundMap &_lund_map,
        const TruthMatchMap &_tm_map,
        const LundPM &_lund_pm, 
        const IdxPM &_idx_pm) : 
        g(_graph), 
        lund_map(_lund_map), 
        tm_map(_tm_map), 
        lund_pm(_lund_pm), 
        idx_pm(_idx_pm) {}

    void operator()(std::ostream &out, const EdgeT &v) const;

  private:
    GraphT g;
    LundMap lund_map;
    TruthMatchMap tm_map;
    LundPM lund_pm;
    IdxPM idx_pm;
};

template <typename GraphT, typename LundMap, typename TruthMatchMap, 
          typename LundPM, typename IdxPM>
void MyEdgeWriter<GraphT, LundMap, TruthMatchMap, LundPM, IdxPM>::operator() (
    std::ostream &out, const EdgeT &e) const {

  auto u = source(e, g);
  auto v = target(e, g);
  typename TruthMatchMap::const_iterator u_tm_it, v_tm_it;
  u_tm_it = tm_map.find(idx_pm[u]);
  v_tm_it = tm_map.find(idx_pm[v]);
  if (
      (u_tm_it != tm_map.end() && u_tm_it->second >= 0) &&
      (v_tm_it != tm_map.end() && v_tm_it->second >= 0) 
     ) {
    out << "[color=\"black\",weight=\"1\", penwidth=\"3\"]";
  } else {
    out << "[color=\"grey\"]";
  }

}

template <typename GraphT, typename LundMap, typename TruthMatchMap, 
          typename LundPM, typename IdxPM>
MyEdgeWriter<GraphT, LundMap, TruthMatchMap, LundPM, IdxPM>
make_myedge_writer(const GraphT &g, const LundMap lund_map, const TruthMatchMap truthmatch_map,
                  const LundPM lund_pm, const IdxPM idx_pm) {

  return MyEdgeWriter<GraphT, LundMap, TruthMatchMap, LundPM, IdxPM>(g, lund_map, truthmatch_map, lund_pm, idx_pm);
}

class MyGraphWriter {

  public:
    MyGraphWriter(std::string _title) : title(_title) {}
    void operator()(std::ostream &out) const {
      out << "graph[fontsize=\"32\"]" << std::endl;
      out << "labelloc=\"t\"" << std::endl;
      out << "label = " << "\"" << title << "\"" << std::endl;
    };
  private:
    std::string title;
};

#endif
