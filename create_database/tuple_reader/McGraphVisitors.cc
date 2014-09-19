#include <cmath>
#include <cassert>
#include <vector>

#include "BDtaunuDef.h"
#include "GraphDef.h"
#include "Particles.h"
#include "McGraphVisitors.h"
#include "McGraphManager.h"
#include "McBTypeCatalogue.h"

using namespace boost;
using namespace McGraph;

McGraphDfsVisitor::McGraphDfsVisitor(McGraphManager *_manager) 
  : manager(_manager) {
  lund_map = get(vertex_lund_id, manager->g);
}

const McBTypeCatalogue McGraphDfsVisitor::mcB_catalogue = McBTypeCatalogue();

// Determine whether to analyze a MC particle 
// when its vertex is colored black. 
void McGraphDfsVisitor::finish_vertex(Vertex u, const Graph &g) {
  int lund = std::abs(get(lund_map, u));
  switch (lund) {
    case bdtaunu::UpsilonLund:
      AnalyzeY(u, g);
      break;
    case bdtaunu::B0Lund:
    case bdtaunu::BcLund:
      AnalyzeB(u, g);
      break;
    case bdtaunu::tauLund:
      AnalyzeTau(u, g);
      break;
    default:
      return;
  }
  return;
}


// Analyze Y(4S). The quantities computed are:
// 1. Pointers to the daughter B mesons.
void McGraphDfsVisitor::AnalyzeY(const Vertex &u, const Graph &g) {

  McY mcY;

  AdjacencyIterator ai, ai_end;
  for (tie(ai, ai_end) = adjacent_vertices(u, g); ai != ai_end; ++ai) {

    int lund = abs(get(lund_map, *ai));
    switch (lund) {
      case bdtaunu::B0Lund:
      case bdtaunu::BcLund:
        (mcY.B1 == nullptr) ? 
          (mcY.B1 = &(manager->B_map)[*ai]) : 
          (mcY.B2 = &(manager->B_map)[*ai]);
        break;
      default:
        mcY.isBBbar = false;
        return;
    }
  }

  (manager->Y_map).insert(std::make_pair(u, mcY));
}

// Analyze B meson. The quantities computed are:
// 1. B flavor. 
// 2. Pointer to daughter tau. 
// 3. MC type. See Particles.h.
void McGraphDfsVisitor::AnalyzeB(const Vertex &u, const Graph &g) {

  McB mcB;

  if (abs(get(lund_map, u)) == bdtaunu::B0Lund) {
    mcB.flavor = bdtaunu::kB0;
  } else {
    mcB.flavor = bdtaunu::kBc;
  }

  std::vector<int> daulund_list;
  AdjacencyIterator ai, ai_end;
  for (tie(ai, ai_end) = adjacent_vertices(u, g); ai != ai_end; ++ai) {
    int lund = get(lund_map, *ai);
    switch (abs(lund)) {
      case bdtaunu::tauLund:
        mcB.tau = &(manager->Tau_map)[*ai];
      default:
        daulund_list.push_back(lund);
    }
  }
  mcB.mc_type = static_cast<int>(mcB_catalogue.search_catalogue(daulund_list));

  (manager->B_map).insert(std::make_pair(u, mcB));
}

// Analyze tau. The quantities computed are:
// 1. MC type. See Particles.h.
void McGraphDfsVisitor::AnalyzeTau(const Vertex &u, const Graph &g) {

  McTau mcTau;

  AdjacencyIterator ai, ai_end;
  for (tie(ai, ai_end) = adjacent_vertices(u, g); ai != ai_end; ++ai) {
    int lund = abs(get(lund_map, *ai));
    if (lund == bdtaunu::eLund) {
      mcTau.mc_type = bdtaunu::ktau_e_mc;
      break;
    } else if (lund == bdtaunu::muLund) {
      mcTau.mc_type = bdtaunu::ktau_mu_mc;
      break;
    } else {
      mcTau.mc_type = bdtaunu::ktau_h_mc;
    }
  }

  (manager->Tau_map).insert(std::make_pair(u, mcTau));
}
