#ifndef __MCGRAPHMANAGER_H_
#define __MCGRAPHMANAGER_H_

#include <iostream>
#include <set>
#include <map>

#include "GraphManager.h"
#include "GraphDef.h"
#include "Particles.h"
#include "McGraphVisitors.h"

class BDtaunuMcReader;

class McGraphManager : public GraphManager {

  friend bool is_final_state_particle(int lund);
  friend class McGraphDfsVisitor;

  public:
    McGraphManager();
    McGraphManager(BDtaunuMcReader*);
    McGraphManager(const McGraphManager&) = default;
    McGraphManager &operator=(const McGraphManager&) = default;
    ~McGraphManager() {};

    void construct_graph();
    void analyze_graph();
    void print(std::ostream &os) const;
    void clear();

    const McY* get_mcY() const;
    const McB* get_mcB1() const;
    const McB* get_mcB2() const;

  private:
    static const std::set<int> final_state_particles;

  private:
    BDtaunuMcReader *reader;
    McGraph::Graph g;

    // graph construction
    std::map<int, McGraph::Vertex> mc_vertex_map;
    void ClearGraph();

    // graph analysis
    std::map<McGraph::Vertex, McY> Y_map;
    std::map<McGraph::Vertex, McB> B_map;
    void ClearAnalysis();

};

bool is_final_state_particle(int lund);

#endif
