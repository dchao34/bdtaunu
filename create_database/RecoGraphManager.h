#ifndef __RECOGRAPHMANAGER_H_
#define __RECOGRAPHMANAGER_H_

#include <iostream>
#include <vector>
#include <map>

#include "RecoGraph.h"
#include "RecoIndexer.h"
#include "RecoGraphVisitors.h"
#include "RecoParticles.h"

class BDtaunuReader;

class RecoGraphManager {

  friend class RecoGraphDfsVisitor;

  public:
    RecoGraphManager();
    RecoGraphManager(BDtaunuReader*);
    RecoGraphManager(const RecoGraphManager&) = default;
    RecoGraphManager &operator=(const RecoGraphManager&) = default;
    ~RecoGraphManager() {};

    void analyze();
    void clear();

    int get_reco_index(int lund, int i) const { return reco_indexer(lund, i); }
    const RecoY* get_recoY(int i) const;

    void print(std::ostream &os) const;

  private:
    BDtaunuReader *reader;
    RecoGraph::Graph g;

    // graph construction
    RecoIndexer reco_indexer;
    std::map<int, RecoGraph::Vertex> reco_vertex_map;
    void AddCandidates(
        int nCand, int *CandLund,
        std::vector<int*> &CandDauIdx, 
        std::vector<int*> &CandDauLund);
    void ConstructGraph();
    void ClearGraph();

    // graph analysis
    std::map<RecoGraph::Vertex, RecoY> Y_map;
    std::map<RecoGraph::Vertex, RecoB> B_map;
    std::map<RecoGraph::Vertex, RecoD> D_map;
    std::map<RecoGraph::Vertex, RecoLepton> Lepton_map;
    void AnalyzeGraph();
    void ClearAnalysis();
};

#endif
