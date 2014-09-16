#include <cmath>
#include <cassert>

#include "GraphDef.h"
#include "Particles.h"
#include "RecoGraphVisitors.h"
#include "RecoGraphManager.h"

using namespace boost;
using namespace RecoGraph;

RecoGraphDfsVisitor::RecoGraphDfsVisitor(RecoGraphManager *_manager) 
  : manager(_manager) {
  lund_map = get(vertex_lund_id, manager->g);
  block_idx_map = get(vertex_block_index, manager->g);
}

void RecoGraphDfsVisitor::finish_vertex(Vertex u, const Graph &g) {
  int lund = std::abs(get(lund_map, u));
  switch (lund) {
    case bdtaunu::UpsilonLund:
      AnalyzeY(u, g);
      break;
    case bdtaunu::B0Lund:
    case bdtaunu::BcLund:
      AnalyzeB(u, g);
      break;
    case bdtaunu::Dstar0Lund:
    case bdtaunu::DstarcLund:
      AnalyzeDstar(u, g);
      break;
    case bdtaunu::D0Lund:
    case bdtaunu::DcLund:
      AnalyzeD(u, g);
      break;
    case bdtaunu::piLund:
    case bdtaunu::rhoLund:
    case bdtaunu::eLund:
    case bdtaunu::muLund:
      AnalyzeLepton(u, g);
      break;
    default:
      return;
  }
  return;
}

void RecoGraphDfsVisitor::AnalyzeD(const Vertex &u, const Graph &g) {

  RecoD recoD;

  int n_daughters, n_K, n_Ks, n_pi, n_pi0;
  n_daughters = n_K = n_Ks = n_pi = n_pi0 = 0;

  AdjacencyIterator ai, ai_end;
  for (tie(ai, ai_end) = adjacent_vertices(u, g); ai != ai_end; ++ai) {
    n_daughters += 1;
    int lund = abs(get(lund_map, *ai));
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
        assert(false);
        return;
    }
  }

  int mode;
  if (std::abs(get(lund_map, u)) == bdtaunu::DcLund) {
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

  recoD.D_mode = mode;

  (manager->D_map).insert(std::make_pair(u, recoD));
}

void RecoGraphDfsVisitor::AnalyzeDstar(const Vertex &u, const Graph &g) {

  RecoD recoD;

  int n_daughters, n_D0, n_Dc, n_pi, n_pi0, n_gamma;
  n_daughters = n_D0 = n_Dc = n_pi = n_pi0 = n_gamma = 0;

  AdjacencyIterator ai, ai_end;
  for (tie(ai, ai_end) = adjacent_vertices(u, g); ai != ai_end; ++ai) {
    n_daughters += 1;
    int lund = abs(get(lund_map, *ai));
    switch (lund) {
      case bdtaunu::D0Lund:
        n_D0 += 1;
        recoD.D_mode = (manager->D_map)[*ai].D_mode;
        break;
      case bdtaunu::DcLund:
        n_Dc += 1;
        recoD.D_mode = (manager->D_map)[*ai].D_mode;
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
        assert(false);
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

  recoD.Dstar_mode = mode;

  (manager->D_map).insert(std::make_pair(u, recoD));

}

void RecoGraphDfsVisitor::AnalyzeLepton(const Vertex &u, const Graph &g) {

  RecoLepton recoLepton;

  AdjacencyIterator ai, ai_end;
  int lund = abs(get(lund_map, u));
  switch (lund) {

    case bdtaunu::eLund:
      recoLepton.l_block_idx = block_idx_map[u];
      recoLepton.pi_block_idx = -1;
      recoLepton.tau_mode = bdtaunu::ktau_e;

    case bdtaunu::muLund:
      recoLepton.l_block_idx = block_idx_map[u];
      recoLepton.pi_block_idx = -1;
      recoLepton.tau_mode = bdtaunu::ktau_mu;
      break;

    case bdtaunu::piLund:
      recoLepton.l_block_idx = -1;
      recoLepton.pi_block_idx = block_idx_map[u];
      recoLepton.tau_mode = bdtaunu::ktau_pi;
      break;

    case bdtaunu::rhoLund:
      recoLepton.l_block_idx = -1;
      for (tie(ai, ai_end) = adjacent_vertices(u, g); ai != ai_end; ++ai) {
        if (abs(get(lund_map, *ai)) == bdtaunu::piLund) {
          recoLepton.pi_block_idx = (manager->Lepton_map)[*ai].pi_block_idx;
          break;
        }
      }
      recoLepton.tau_mode = bdtaunu::ktau_rho;
      break;

    default:
      assert(false);
      return;
  }

  (manager->Lepton_map).insert(std::make_pair(u, recoLepton));
}


void RecoGraphDfsVisitor::AnalyzeB(const Vertex &u, const Graph &g) {

  RecoB recoB;

  if (abs(get(lund_map, u)) == bdtaunu::B0Lund) {
    recoB.flavor = bdtaunu::kB0;
  } else {
    recoB.flavor = bdtaunu::kBc;
  }

  AdjacencyIterator ai, ai_end;
  for (tie(ai, ai_end) = adjacent_vertices(u, g); ai != ai_end; ++ai) {

    int lund = abs(get(lund_map, *ai));
    switch (lund) {
      case bdtaunu::D0Lund:
      case bdtaunu::DcLund:
      case bdtaunu::Dstar0Lund:
      case bdtaunu::DstarcLund:
        recoB.D = &(manager->D_map)[*ai];
        break;
      case bdtaunu::eLund:
      case bdtaunu::muLund:
      case bdtaunu::piLund:
      case bdtaunu::rhoLund:
        recoB.Lepton = &(manager->Lepton_map)[*ai];
        break;
      default:
        assert(false);
        return;
    }
  }

  (manager->B_map).insert(std::make_pair(u, recoB));
}



void RecoGraphDfsVisitor::AnalyzeY(const Vertex &u, const Graph &g) {

  RecoY recoY;

  AdjacencyIterator ai, ai_end;
  for (tie(ai, ai_end) = adjacent_vertices(u, g); ai != ai_end; ++ai) {

    int lund = abs(get(lund_map, *ai));
    switch (lund) {
      case bdtaunu::B0Lund:
      case bdtaunu::BcLund:
        if ((manager->B_map)[*ai].Lepton->l_block_idx >= 0) {
          recoY.tagB = &(manager->B_map)[*ai];
        } else {
          recoY.sigB = &(manager->B_map)[*ai];
        }
        break;
      default:
        assert(false);
        return;
    }
  }

  (manager->Y_map).insert(std::make_pair(u, recoY));
}

