#ifndef __BDTAUNUGRAPHWRITER_H_
#define __BDTAUNUGRAPHWRITER_H_

#include <iostream> 
#include <fstream> 

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
    out << "[label=\"" << idx_pm[v] << ": " << it->second << "\",color=\"red\"]";
  } else {
    out << "[label=\"" << idx_pm[v] << ": " << lund_pm[v] << "\",color=\"red\"]";
  }

}

template <typename GraphT, typename LundMap,
          typename LundPM, typename IdxPM>
BDtaunuGraphWriter<GraphT, LundMap, LundPM, IdxPM>
make_graph_writer(const GraphT &g, const LundMap lund_map, 
                  const LundPM lund_pm, const IdxPM idx_pm) {

  return BDtaunuGraphWriter<GraphT, LundMap, LundPM, IdxPM>(g, lund_map, lund_pm, idx_pm);
}

#endif
