#ifndef __RECOGRAPH_H_
#define __RECOGRAPH_H_

#include <boost/graph/adjacency_list.hpp>

namespace boost {
  enum vertex_reco_index_t { vertex_reco_index };
  enum vertex_block_index_t { vertex_block_index };
  enum vertex_lund_id_t { vertex_lund_id };

  BOOST_INSTALL_PROPERTY(vertex, reco_index);
  BOOST_INSTALL_PROPERTY(vertex, block_index);
  BOOST_INSTALL_PROPERTY(vertex, lund_id);
}

namespace RecoGraph {

typedef boost::adjacency_list<
  boost::vecS, boost::vecS, boost::directedS,
  boost::property<boost::vertex_reco_index_t, int,
  boost::property<boost::vertex_block_index_t, int,
  boost::property<boost::vertex_lund_id_t, int>>>,
  boost::property<boost::edge_index_t, int>
> Graph;

typedef typename boost::graph_traits<Graph>::vertex_descriptor Vertex;

typedef typename boost::graph_traits<Graph>::adjacency_iterator AdjacencyIterator;

typedef typename boost::property_map<Graph, boost::vertex_lund_id_t>::type LundIdPropertyMap;
typedef typename boost::property_map<Graph, boost::vertex_reco_index_t>::type RecoIndexPropertyMap;
typedef typename boost::property_map<Graph, boost::vertex_block_index_t>::type BlockIndexPropertyMap;

}

#endif
