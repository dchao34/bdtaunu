#ifndef __RECOGRAPHVISITOR_H__
#define __RECOGRAPHVISITOR_H__

#include <iostream>
#include <cmath>
#include <cassert>
#include <vector>
#include <map>
#include <utility>
#include <boost/graph/depth_first_search.hpp>
#include <boost/graph/breadth_first_search.hpp>
#include "BDtaunuReader.h"
#include "bdtaunu_definitions.h"

template <typename LundMap>
class RecoGraphDfsVisitor : public boost::default_dfs_visitor {
  private:
    typedef typename BDtaunuReader::RecoGraph Graph;
    typedef typename BDtaunuReader::Vertex Vertex;
    typedef typename BDtaunuReader::YDecayProperties YDecayProperties;
    typedef typename boost::graph_traits<Graph>::adjacency_iterator AdjacencyIterator;

  public:
    RecoGraphDfsVisitor(LundMap &l, std::vector<YDecayProperties> &v) : 
      lund_map(l), upsilon_properties(v) {};
    void finish_vertex(Vertex u, const Graph &g);
    std::vector<YDecayProperties> get_upsilons() { return upsilon_properties; }

  private:
    LundMap lund_map;
    std::vector<YDecayProperties> &upsilon_properties;

    void ComputeY(const Vertex &u, const Graph &g);
    void ComputeB(const Vertex &u, const Graph &g);
    void ComputeDstar(const Vertex &u, const Graph &g);
    void ComputeD(const Vertex &u, const Graph &g);
    void ComputeRhoDaughters(Vertex &tau_pi_dau, Vertex &tau_pi0_dau, 
                             const Vertex &u, const Graph &g);

  private:
    struct D {
      int dec_mode;
      D() : dec_mode(bdtaunu::kUndefinedDMode) {};
      D(int mode) : dec_mode(mode) {};
    };

    struct Dstar {
      int dec_mode;
      Vertex D_dau;
      Dstar() : dec_mode(bdtaunu::kUndefinedDMode) {};
      Dstar(int mode, const Vertex &v) : dec_mode(mode), D_dau(v) {};
    };

    struct B {
      int bflavor;
      bool has_dstardau;

      bool is_tag;
      Vertex D_dau;
      Vertex lep_dau;

      int tau_mode;
      Vertex tau_pi_dau;
      Vertex tau_pi0_dau;

      B() {};
      B(int _bflavor, bool _has_dstardau,
        bool _is_tag, const Vertex &_D, 
        const Vertex &_lep, int _tau_mode, 
        const Vertex &_tau_pi, const Vertex &_tau_pi0) :
        bflavor(_bflavor), has_dstardau(_has_dstardau), 
        is_tag(_is_tag), D_dau(_D), lep_dau(_lep), 
        tau_mode(_tau_mode), tau_pi_dau(_tau_pi), 
        tau_pi0_dau(_tau_pi0) {};
    };

    std::map<Vertex, D> Dmap;
    std::map<Vertex, Dstar> Dstarmap;
    std::map<Vertex, B> Bmap;

};

template <typename LundMap>
void RecoGraphDfsVisitor<LundMap>::finish_vertex(Vertex u, const Graph &g) {
  int lund = std::abs(boost::get(lund_map, u));
  switch (lund) {
    case bdtaunu::UpsilonLund:
      ComputeY(u, g);
      break;
    case bdtaunu::B0Lund:
    case bdtaunu::BcLund:
      ComputeB(u, g);
      break;
    case bdtaunu::Dstar0Lund:
    case bdtaunu::DstarcLund:
      ComputeDstar(u, g);
      break;
    case bdtaunu::D0Lund:
    case bdtaunu::DcLund:
      ComputeD(u, g);
      break;
    default:
      return;
  }
}

template<typename LundMap>
void RecoGraphDfsVisitor<LundMap>::ComputeY(const Vertex &u, const Graph &g) {

  YDecayProperties y;
  y.Y = u;

  AdjacencyIterator ai, ai_end;
  for (boost::tie(ai, ai_end) = adjacent_vertices(u, g);
       ai != ai_end; ++ai) {

    auto bi = Bmap.find(*ai);
    assert(bi != Bmap.end());
    B b = bi->second;

    if (b.is_tag) {
      y.bflavor = b.bflavor;
      y.l = b.lep_dau;
      if (b.has_dstardau) {
        auto dstari = Dstarmap.find(b.D_dau);
        assert(dstari != Dstarmap.end());
        y.tag_dstar_mode = (dstari->second).dec_mode;

        auto di = Dmap.find((dstari->second).D_dau);
        assert(di != Dmap.end());
        y.tag_d_mode = (di->second).dec_mode;
      } else {
        auto di = Dmap.find(b.D_dau);
        assert(di != Dmap.end());
        y.tag_dstar_mode = bdtaunu::kNoDstar;
        y.tag_d_mode = (di->second).dec_mode;
      }
    } else {
      y.tau_mode = b.tau_mode;
      y.tau_pi = b.tau_pi_dau;
      y.tau_pi0 = b.tau_pi0_dau;
      if (b.has_dstardau) {
        auto dstari = Dstarmap.find(b.D_dau);
        assert(dstari != Dstarmap.end());
        y.sig_dstar_mode = (dstari->second).dec_mode;

        auto di = Dmap.find((dstari->second).D_dau);
        assert(di != Dmap.end());
        y.sig_d_mode = (di->second).dec_mode;
      } else {
        auto di = Dmap.find(b.D_dau);
        assert(di != Dmap.end());
        y.sig_dstar_mode = bdtaunu::kNoDstar;
        y.sig_d_mode = (di->second).dec_mode;
      }
    }
  }

  upsilon_properties.push_back(y);
}

template<typename LundMap>
void RecoGraphDfsVisitor<LundMap>::ComputeB(const Vertex &u, const Graph &g) {

  assert(Bmap.find(u) == Bmap.end());

  int bflavor;
  if (abs(boost::get(lund_map, u)) == bdtaunu::B0Lund) {
    bflavor = bdtaunu::kB0;
  } else {
    bflavor = bdtaunu::kBc;
  }

  bool is_tag, has_dstardau;
  Vertex D_dau, lep_dau;
  int tau_mode;
  Vertex tau_pi_dau, tau_pi0_dau;
  AdjacencyIterator ai, ai_end;
  for (boost::tie(ai, ai_end) = adjacent_vertices(u, g);
       ai != ai_end; 
       ++ai) {

    int lund = abs(boost::get(lund_map, *ai));
    switch (lund) {
      case bdtaunu::D0Lund:
      case bdtaunu::DcLund:
        has_dstardau = false;
        D_dau = *ai;
        break;
      case bdtaunu::Dstar0Lund:
      case bdtaunu::DstarcLund:
        has_dstardau = true;
        D_dau = *ai;
        break;
      case bdtaunu::eLund:
      case bdtaunu::muLund:
        is_tag = true;
        lep_dau = *ai;
        tau_mode = bdtaunu::kUndefinedTauMode;
        break;
      case bdtaunu::piLund:
        is_tag = false;
        lep_dau = *ai;
        tau_mode = bdtaunu::ktau_pi;
        tau_pi_dau = *ai;
        break;
      case bdtaunu::rhoLund:
        is_tag = false;
        lep_dau = *ai;
        tau_mode = bdtaunu::ktau_rho;
        ComputeRhoDaughters(tau_pi_dau, tau_pi0_dau, *ai, g);
        break;
      default:
        assert(false);
        return;
    }
  }

  Bmap.insert(std::make_pair(
        u, B(bflavor, has_dstardau, is_tag, 
             D_dau, lep_dau, tau_mode, tau_pi_dau, tau_pi0_dau)));

}

template<typename LundMap>
void RecoGraphDfsVisitor<LundMap>::ComputeRhoDaughters(
    Vertex &tau_pi_dau, Vertex &tau_pi0_dau, 
    const Vertex &u, const Graph &g) {
  AdjacencyIterator ai, ai_end;
  for (boost::tie(ai, ai_end) = adjacent_vertices(u, g);
       ai != ai_end; 
       ++ai) {
    switch(abs(boost::get(lund_map, *ai))) {
      case bdtaunu::piLund:
        tau_pi_dau = *ai;
        break;
      case bdtaunu::pi0Lund:
        tau_pi0_dau = *ai;
        break;
      default:
        assert(false);
    }
  }
}

template<typename LundMap>
void RecoGraphDfsVisitor<LundMap>::ComputeDstar(const Vertex &u, const Graph &g) {

  assert(Dstarmap.find(u) == Dstarmap.end());

  int n_daughters, n_D0, n_Dc, n_pi, n_pi0, n_gamma;
  n_daughters = n_D0 = n_Dc = n_pi = n_pi0 = n_gamma = 0;

  Vertex v;
  AdjacencyIterator ai, ai_end;
  for (boost::tie(ai, ai_end) = adjacent_vertices(u, g);
       ai != ai_end; 
       ++ai) {
    n_daughters += 1;
    int lund = abs(boost::get(lund_map, *ai));
    switch (lund) {
      case bdtaunu::D0Lund:
        n_D0 += 1;
        v = *ai;
        break;
      case bdtaunu::DcLund:
        n_Dc += 1;
        v = *ai;
        break;
      case bdtaunu::piLund:
        n_pi += 1;
        break;
      case bdtaunu::pi0Lund:
        n_pi0 += 1;
        break;
      case bdtaunu::gammaLund:
        n_gamma += 1;
        break;
      default:
        Dstarmap.insert(std::make_pair(u, Dstar()));
        return;
    }
  }

  int mode;
  if (n_daughters == 2 && n_D0 == 1 && n_pi0 == 1) {
    mode = bdtaunu::kDstar0_D0pi0;
  } else if (n_daughters == 2 && n_D0 == 1 && n_gamma == 1) {
    mode = bdtaunu::kDstar0_D0gamma;
  } else if (n_daughters == 2 && n_D0 == 1 && n_pi == 1) {
    mode = bdtaunu::kDstarc_D0pi;
  } else if (n_daughters == 2 && n_Dc == 1 && n_pi0 == 1) {
    mode = bdtaunu::kDstarc_Dcpi0;
  } else if (n_daughters == 2 && n_Dc == 1 && n_gamma == 1) {
    mode = bdtaunu::kDstarc_Dcgamma;
  } else {
    mode = bdtaunu::kUndefinedDstarMode;
  }

  Dstarmap.insert(std::make_pair(u, Dstar(mode, v)));

}


template<typename LundMap>
void RecoGraphDfsVisitor<LundMap>::ComputeD(const Vertex &u, const Graph &g) {

  assert(Dmap.find(u) == Dmap.end());

  int n_daughters, n_K, n_Ks, n_pi, n_pi0;
  n_daughters = n_K = n_Ks = n_pi = n_pi0 = 0;

  AdjacencyIterator ai, ai_end;
  for (boost::tie(ai, ai_end) = adjacent_vertices(u, g);
       ai != ai_end; 
       ++ai) {
    n_daughters += 1;
    int lund = abs(boost::get(lund_map, *ai));
    switch (lund) {
      case bdtaunu::KLund:
        n_K += 1;
        break;
      case bdtaunu::KSLund:
        n_Ks += 1;
        break;
      case bdtaunu::piLund:
        n_pi += 1;
        break;
      case bdtaunu::pi0Lund:
        n_pi0 += 1;
        break;
      default:
        Dmap.insert(std::make_pair(u, D()));
        return;
    }
  }

  int mode;
  if (std::abs(boost::get(lund_map, u)) == bdtaunu::DcLund) {
    if (n_daughters == 3 && n_K == 1 && n_pi == 2) {
      mode = bdtaunu::kDc_Kpipi;
    } else if (n_daughters == 4 && n_K == 1 && n_pi == 2 && n_pi0 == 1) {
      mode = bdtaunu::kDc_Kpipipi0;
    } else if (n_daughters == 2 && n_K == 1 && n_Ks == 1) {
      mode = bdtaunu::kDc_KsK;
    } else if (n_daughters == 2 && n_Ks == 1 && n_pi == 1) {
      mode = bdtaunu::kDc_Kspi;
    } else if (n_daughters == 3 && n_Ks == 1 && n_pi == 1 && n_pi0 == 1) {
      mode = bdtaunu::kDc_Kspipi0;
    } else if (n_daughters == 4 && n_Ks == 1 && n_pi == 3) {
      mode = bdtaunu::kDc_Kspipipi;
    } else if (n_daughters == 3 && n_K == 2 && n_pi == 1) {
      mode = bdtaunu::kDc_KKpi;
    } else {
      mode = bdtaunu::kUndefinedDMode;
    }
  } else {
    if (n_daughters == 2 && n_K == 1 && n_pi == 1) {
      mode = bdtaunu::kD0_Kpi;
    } else if (n_daughters == 3 && n_K == 1 && n_pi == 1 && n_pi0 == 1) {
      mode = bdtaunu::kD0_Kpipi0;
    } else if (n_daughters == 4 && n_K == 1 && n_pi == 3) {
      mode = bdtaunu::kD0_Kpipipi;
    } else if (n_daughters == 5 && n_K == 1 && n_pi == 3 && n_pi0 == 1) {
      mode = bdtaunu::kD0_Kpipipipi0;
    } else if (n_daughters == 3 && n_Ks == 1 && n_pi == 2) {
      mode = bdtaunu::kD0_Kspipi;
    } else if (n_daughters == 4 && n_Ks == 1 && n_pi == 2 && n_pi0 == 1) {
      mode = bdtaunu::kD0_Kspipipi0;
    } else if (n_daughters == 2 && n_Ks == 1 && n_pi0 == 1) {
      mode = bdtaunu::kD0_Kspi0;
    } else if (n_daughters == 2 && n_K == 2) {
      mode = bdtaunu::kD0_KK;
    } else {
      mode = bdtaunu::kUndefinedDMode;
    }
  }

  Dmap.insert(std::make_pair(u, D(mode)));
}

template <typename LundMap>
RecoGraphDfsVisitor<LundMap> reco_graph_dfs_visitor(
    LundMap m, std::vector<BDtaunuReader::YDecayProperties> &u) {
  return RecoGraphDfsVisitor<LundMap>(m, u);
}

/*
class RecoGraphBfsVisitor : public boost::default_bfs_visitor {
  private:
    typedef typename BDtaunuReader::RecoGraph Graph;
    typedef typename BDtaunuReader::Vertex Vertex;

  public:
    RecoGraphBfsVisitor(std::vector<Vertex> &v) : 
      subgraph_vertices(v) {};
    void discover_vertex(Vertex u, const Graph &g);
    std::vector<Vertex> get_subgraph_vertices() { return subgraph_vertices; }

  private:
    std::vector<Vertex> &subgraph_vertices;
};

void RecoGraphBfsVisitor::discover_vertex(Vertex u, const Graph &g) {
  subgraph_vertices.push_back(u);
}

RecoGraphBfsVisitor reco_graph_bfs_visitor(
    std::vector<BDtaunuReader::Vertex> &u) {
  return RecoGraphBfsVisitor(u);
}
*/

class RecoGraphBfsVisitor : public boost::default_bfs_visitor {
  private:
    typedef typename BDtaunuReader::RecoGraph Graph;
    typedef typename boost::graph_traits<Graph>::vertex_descriptor Vertex;
    typedef typename boost::graph_traits<Graph>::edge_descriptor Edge;
    typedef typename boost::graph_traits<Graph>::adjacency_iterator AdjacencyIterator;

  public:
    RecoGraphBfsVisitor(const Graph &g, Graph &subg) : 
      graph(g),
      subgraph(subg) { 
        reco_index = get(boost::vertex_reco_index, graph);
        block_index = get(boost::vertex_block_index, graph);
        lund_id = get(boost::vertex_lund_id, graph); 
      };
    void discover_vertex(Vertex u, const Graph &g);
    void tree_edge(Edge e, const Graph &g);

  private:
    Graph graph;
    Graph &subgraph;
    std::map<int, Vertex> inserted_vertices;
    typename boost::property_map<Graph, boost::vertex_reco_index_t>::type reco_index;
    typename boost::property_map<Graph, boost::vertex_block_index_t>::type block_index;
    typename boost::property_map<Graph, boost::vertex_lund_id_t>::type lund_id; 
};

void RecoGraphBfsVisitor::discover_vertex(Vertex u, const Graph &g) {
  if (inserted_vertices.find(reco_index[u]) == inserted_vertices.end()) {
    Vertex v = add_vertex(subgraph);
    put(get(boost::vertex_reco_index, subgraph), v, reco_index[u]);
    put(get(boost::vertex_block_index, subgraph), v, block_index[u]);
    put(get(boost::vertex_lund_id, subgraph), v, lund_id[u]);
    inserted_vertices[reco_index[u]] = v;
  }
}

void RecoGraphBfsVisitor::tree_edge(Edge e, const Graph &g) {

  Vertex u_bfs = source(e, g);
  Vertex v_bfs = target(e, g);
  if (inserted_vertices.find(reco_index[v_bfs]) == inserted_vertices.end()) {
    Vertex u = inserted_vertices[reco_index[u_bfs]];
    Vertex v = add_vertex(subgraph);
    put(get(boost::vertex_reco_index, subgraph), v, reco_index[v_bfs]);
    put(get(boost::vertex_block_index, subgraph), v, block_index[v_bfs]);
    put(get(boost::vertex_lund_id, subgraph), v, lund_id[v_bfs]);
    inserted_vertices[reco_index[v_bfs]] = v;
    add_edge(u, v, subgraph);
  } else {
    Vertex u = inserted_vertices[reco_index[u_bfs]];
    Vertex v = inserted_vertices[reco_index[v_bfs]];
    add_edge(u, v, subgraph);
  }
}

RecoGraphBfsVisitor reco_graph_bfs_visitor(
    const BDtaunuReader::RecoGraph &g,
    BDtaunuReader::RecoGraph &subg) {
  return RecoGraphBfsVisitor(g, subg);
}


#endif
