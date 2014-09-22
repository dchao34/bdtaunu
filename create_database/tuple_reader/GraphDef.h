#ifndef __GRAPHDEF_H_
#define __GRAPHDEF_H_

#include <initializer_list>
#include <boost/graph/adjacency_list.hpp>

#include "BDtaunuDef.h"

namespace boost {
  enum vertex_lund_id_t { vertex_lund_id };
  BOOST_INSTALL_PROPERTY(vertex, lund_id);
}

namespace boost {
  enum vertex_reco_index_t { vertex_reco_index };
  enum vertex_block_index_t { vertex_block_index };
  BOOST_INSTALL_PROPERTY(vertex, reco_index);
  BOOST_INSTALL_PROPERTY(vertex, block_index);
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

struct RecoLepton {
  int l_block_idx = -1;
  int pi_block_idx = -1;
  int tau_mode = static_cast<int>(bdtaunu::TauType::null);
};

struct RecoD {
  RecoD() = default;
  int D_mode = static_cast<int>(bdtaunu::RecoDTypeCatalogue::DType::null);
  int Dstar_mode = static_cast<int>(bdtaunu::RecoDTypeCatalogue::DstarType::NoDstar);
};

struct RecoB {
  RecoB() = default;
  int flavor = static_cast<int>(bdtaunu::BFlavor::null);
  RecoD *D = nullptr;
  RecoLepton *Lepton = nullptr;
};

struct RecoY {
  RecoY() = default;
  RecoB *tagB = nullptr;
  RecoB *sigB = nullptr;
};

/** @brief This class assigns a unique index to each reconstructed particle.
 *
 * @detail 
 * # Motivation
 * The need for every reconstructed particle of the event to have a unique
 * index arises primarily in accessessing vertex information in the BGL graph. 
 * However, such an indexing is more convenient to use than the existing 
 * BtaTupleMaker indexing. 
 *
 * # Implementation
 * This class builds a hash function from the reco particle's index in the 
 * BtaTupleMaker block to a unique index. 
 *
 * See RecoIndexer.cc for details.
 */
class RecoIndexer {

  private:
    int nY, nB, nD, nC, nh, nl, ngamma;

  public:
    RecoIndexer();
    RecoIndexer(int _nY, int _nB, int _nD, 
                int _nC, int _nh, int _nl, int _ngamma);
    RecoIndexer(const RecoIndexer &r) = default;
    RecoIndexer &operator=(const RecoIndexer &r) = default;
    ~RecoIndexer() {};

    //! Given the lundId and block index, return the unique reco index.
    int operator()(int lund, int idx) const;

    //! Return total number of reco particles in this event. 
    int total() const { return nY + nB + nD + nC + nh + nl + ngamma; }

    //! Set the total number of each type of reco particle.
    /*! The list order is { nY, nB, nD, nC, nh, nl, ngamma } */
    void set(std::initializer_list<int> l);

    //! Clear cache.
    void clear();
};

}











namespace boost {
  enum vertex_mc_index_t { vertex_mc_index };
  BOOST_INSTALL_PROPERTY(vertex, mc_index);
}

namespace McGraph {

typedef boost::adjacency_list<
  boost::vecS, boost::vecS, boost::directedS,
  boost::property<boost::vertex_mc_index_t, int,
  boost::property<boost::vertex_lund_id_t, int>>,
  boost::property<boost::edge_index_t, int>
> Graph;

typedef typename boost::graph_traits<Graph>::vertex_descriptor Vertex;

typedef typename boost::graph_traits<Graph>::adjacency_iterator AdjacencyIterator;

typedef typename boost::property_map<Graph, boost::vertex_lund_id_t>::type LundIdPropertyMap;
typedef typename boost::property_map<Graph, boost::vertex_mc_index_t>::type McIndexPropertyMap;

struct McTau {
  McTau() = default;
  int mc_type = static_cast<int>(bdtaunu::TauMcType::null);
};

struct McB {
  McB() = default;
  int flavor = static_cast<int>(bdtaunu::BFlavor::null);
  int mc_type = static_cast<int>(bdtaunu::McBTypeCatalogue::BMcType::null);
  McTau *tau = nullptr;
};

struct McY {
  McY() = default;
  bool isBBbar = true;
  McB *B1 = nullptr;
  McB *B2 = nullptr;
};

}

#endif
