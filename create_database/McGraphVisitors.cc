#include <cmath>
#include <cassert>
#include <vector>

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
    default:
      return;
  }
  return;
}


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
    daulund_list.push_back(get(lund_map, *ai));
  }
  mcB.mc_type = static_cast<int>(mcB_catalogue.search_catalogue(daulund_list));

  (manager->B_map).insert(std::make_pair(u, mcB));
}
