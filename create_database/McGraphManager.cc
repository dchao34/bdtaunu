#include <iostream>
#include <cmath>
#include <cassert>
#include <map>

#include <boost/graph/depth_first_search.hpp>
#include <boost/graph/graphviz.hpp>

#include "bdtaunu_definitions.h"
#include "GraphDef.h"
#include "Particles.h"
#include "BDtaunuMcReader.h"
#include "McGraphManager.h"
#include "BDtaunuGraphWriter.h"

using namespace boost;
using namespace McGraph;

const std::set<int> McGraphManager::final_state_particles = { 
  bdtaunu::eLund, bdtaunu::muLund, bdtaunu::piLund, bdtaunu::KLund,
  bdtaunu::gammaLund, bdtaunu::protonLund, bdtaunu::neutronLund,
};

bool is_final_state_particle(int lund) {
  return 
    (McGraphManager::final_state_particles.find(std::abs(lund)) == 
     McGraphManager::final_state_particles.end()) ? false : true;
}

McGraphManager::McGraphManager() : reader(nullptr) { 
}

McGraphManager::McGraphManager(BDtaunuMcReader *_reader) : reader(_reader) { 
}

void McGraphManager::clear() {
  ClearGraph();
  ClearAnalysis();
}

void McGraphManager::ClearGraph() {
  mc_vertex_map.clear();
  g.clear();
}

void McGraphManager::construct_graph() {

  ClearGraph();

  assert(reader != nullptr);

  McIndexPropertyMap mc_index = get(vertex_mc_index, g);
  LundIdPropertyMap lund_id = get(vertex_lund_id, g);

  Vertex u, v;
  std::map<int, Vertex>::iterator pos;
  bool inserted;

  for (int i = 0; i < reader->mcLen; i++) {

    int u_idx = i;
    tie(pos, inserted) = mc_vertex_map.insert(std::make_pair(u_idx, Vertex()));
    if (inserted) {
      u = add_vertex(g);
      mc_index[u] = u_idx;
      lund_id[u] = (reader->mcLund)[i];
      mc_vertex_map[u_idx] = u;
    } else {
      u = mc_vertex_map[u_idx];
    }

    int first_dau_idx = (reader->dauIdx)[i];
    for (int j = 0; j < (reader->dauLen)[i]; j++) {

      int v_idx = first_dau_idx + j;
      tie(pos, inserted) = mc_vertex_map.insert(std::make_pair(v_idx, Vertex()));
      if (inserted) {
        v = add_vertex(g);
        mc_index[v] = v_idx;
        lund_id[v] = (reader->mcLund)[v_idx];
        mc_vertex_map[v_idx] = v;
      } else {
        v = mc_vertex_map[v_idx];
      }

      add_edge(u, v, g);
    }
  }
}

void McGraphManager::ClearAnalysis() {
  Y_map.clear();
  B_map.clear();
}

void McGraphManager::analyze_graph() {
  ClearAnalysis();
  depth_first_search(g, visitor(McGraphDfsVisitor(this)));
  assert(Y_map.size() == 0 || Y_map.size() == 1);
  assert(B_map.size() == 0 || B_map.size() == 2);
  return;
}

const McY* McGraphManager::get_mcY() const {
  if (Y_map.size()) {
    return &Y_map.begin()->second;
  } else {
    return nullptr;
  }
}

const McB* McGraphManager::get_mcB1() const {
  if (B_map.size()) {
    return &B_map.begin()->second;
  } else {
    return nullptr;
  }
}

const McB* McGraphManager::get_mcB2() const {
  if (B_map.size()) {
    return &(++B_map.begin())->second;
  } else {
    return nullptr;
  }
}

void McGraphManager::print(std::ostream &os) const {
  boost::write_graphviz(
      os, g, 
      make_graph_writer(g, BDtaunuMcReader::lund_to_name, 
                        get(vertex_lund_id, g),
                        get(vertex_mc_index, g)));
}
