#include <cassert>
#include <vector>
#include <map>
#include <iostream>

#include <boost/graph/depth_first_search.hpp>
#include <boost/graph/graphviz.hpp>

#include "BDtaunuReader.h"
#include "RecoGraph.h"
#include "RecoGraphManager.h"
#include "BDtaunuGraphWriter.h"

using namespace boost;
using namespace RecoGraph;

RecoGraphManager::RecoGraphManager() : reader(nullptr) { 
}

RecoGraphManager::RecoGraphManager(BDtaunuReader *_reader) : reader(_reader) { 
}

void RecoGraphManager::clear() {
  ClearGraph();
  ClearAnalysis();
}

void RecoGraphManager::analyze() {
  ConstructGraph();
  AnalyzeGraph();
  return;
}

const RecoY* RecoGraphManager::get_recoY(int i) const { 

  std::map<int, RecoGraph::Vertex>::const_iterator reco_vertex_it;
  reco_vertex_it = reco_vertex_map.find(reco_indexer(bdtaunu::UpsilonLund, i));
  assert(reco_vertex_it != reco_vertex_map.end());

  std::map<Vertex, RecoY>::const_iterator y_it;
  y_it = Y_map.find(reco_vertex_it->second);
  assert(y_it != Y_map.end());

  return &y_it->second;
}

void RecoGraphManager::print(std::ostream &os) const {
  boost::write_graphviz(
      os, g, 
      make_graph_writer(g, BDtaunuReader::lund_to_name, 
                        get(vertex_lund_id, g),
                        get(vertex_reco_index, g)));
}


void RecoGraphManager::ClearGraph() {
  reco_vertex_map.clear();
  reco_indexer.clear();
  g.clear();
}

void RecoGraphManager::ConstructGraph() {

  ClearGraph();

  assert(reader != nullptr);
  reco_indexer.set({reader->nY, reader->nB, reader->nD, reader->nC, 
                    reader->nh, reader->nl, reader->ngamma});

  std::vector<int*> YdauIdx{ reader->Yd1Idx, reader->Yd2Idx };
  std::vector<int*> YdauLund{ reader->Yd1Lund, reader->Yd2Lund };
  std::vector<int*> BdauIdx{ reader->Bd1Idx, reader->Bd2Idx, reader->Bd3Idx, reader->Bd4Idx };
  std::vector<int*> BdauLund{ reader->Bd1Lund, reader->Bd2Lund, reader->Bd3Lund, reader->Bd4Lund };
  std::vector<int*> DdauIdx{ reader->Dd1Idx, reader->Dd2Idx, reader->Dd3Idx, reader->Dd4Idx, reader->Dd5Idx };
  std::vector<int*> DdauLund{ reader->Dd1Lund, reader->Dd2Lund, reader->Dd3Lund, reader->Dd4Lund, reader->Dd5Lund };
  std::vector<int*> CdauIdx{ reader->Cd1Idx, reader->Cd2Idx };
  std::vector<int*> CdauLund{ reader->Cd1Lund, reader->Cd2Lund };
  std::vector<int*> hdauIdx{ reader->hd1Idx, reader->hd2Idx };
  std::vector<int*> hdauLund{ reader->hd1Lund, reader->hd2Lund };
  std::vector<int*> ldauIdx{ reader->ld1Idx, reader->ld2Idx, reader->ld3Idx };
  std::vector<int*> ldauLund{ reader->ld1Lund, reader->ld2Lund, reader->ld3Lund };

  AddCandidates(reader->nY, reader->YLund, YdauIdx, YdauLund);
  AddCandidates(reader->nB, reader->BLund, BdauIdx, BdauLund);
  AddCandidates(reader->nD, reader->DLund, DdauIdx, DdauLund);
  AddCandidates(reader->nC, reader->CLund, CdauIdx, CdauLund);
  AddCandidates(reader->nh, reader->hLund, hdauIdx, hdauLund);
  AddCandidates(reader->nl, reader->lLund, ldauIdx, ldauLund);

}

void RecoGraphManager::ClearAnalysis() {
  Y_map.clear();
  B_map.clear();
  D_map.clear();
  Lepton_map.clear();
}

void RecoGraphManager::AnalyzeGraph() {

  ClearAnalysis();
  depth_first_search(g, visitor(RecoGraphDfsVisitor(this)));

  return;
}

void RecoGraphManager::AddCandidates(
    int nCand,
    int *CandLund,
    std::vector<int*> &CandDauIdx,
    std::vector<int*> &CandDauLund) {

  RecoIndexPropertyMap reco_index = get(vertex_reco_index, g);
  BlockIndexPropertyMap block_index = get(vertex_block_index, g);
  LundIdPropertyMap lund_id = get(vertex_lund_id, g);

  Vertex u, v;
  std::map<int, Vertex>::iterator pos;
  bool inserted;

  for (int i = 0; i < nCand; i++) {

    int u_idx = reco_indexer(CandLund[i], i);
    tie(pos, inserted) = reco_vertex_map.insert(std::make_pair(u_idx, Vertex()));
    if (inserted) {
      u = add_vertex(g);
      reco_index[u] = u_idx;
      block_index[u] = i;
      lund_id[u] = CandLund[i];
      reco_vertex_map[u_idx] = u;
    } else {
      u = reco_vertex_map[u_idx];
    }

    for (std::vector<int*>::size_type j = 0; j < CandDauIdx.size(); j++) {
      if (CandDauIdx[j][i] == -1) {
        break;
      } else {

        int v_idx = reco_indexer(CandDauLund[j][i], CandDauIdx[j][i]);
        tie(pos, inserted) = reco_vertex_map.insert(std::make_pair(v_idx, Vertex()));
        if (inserted) {
          v = add_vertex(g);
          reco_index[v] = v_idx;
          block_index[v] = CandDauIdx[j][i];
          lund_id[v] = CandDauLund[j][i];
          reco_vertex_map[v_idx] = v;
        } else {
          v = reco_vertex_map[v_idx];
        }

        add_edge(u, v, g);
      }
    }
  }
}
