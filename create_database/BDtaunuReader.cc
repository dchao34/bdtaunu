#include <TTree.h>

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <functional>
#include <cmath>
#include <cassert>

#include "bdtaunu_definitions.h"
#include "RootReader.h"
#include "BDtaunuReader.h"
#include "RecoIndexer.h"
#include "UpsilonCandidate.h"
#include "RecoGraphVisitors.h"
#include "utilities/helpers.h"

#include <boost/graph/depth_first_search.hpp>
#include <boost/graph/breadth_first_search.hpp>

using namespace boost;

// The maximum number of candidates allowed in an event. This should
// be consistent with the number set in BtaTupleMaker. 
const int BDtaunuReader::maximum_Y_candidates = 800;
const int BDtaunuReader::maximum_B_candidates = 400;
const int BDtaunuReader::maximum_D_candidates = 200;
const int BDtaunuReader::maximum_C_candidates = 100;
const int BDtaunuReader::maximum_h_candidates = 100;
const int BDtaunuReader::maximum_l_candidates = 100;
const int BDtaunuReader::maximum_gamma_candidates = 100;

std::map<std::string, int> BDtaunuReader::lundIdMap = bdtaunu::NameToLundMap();

BDtaunuReader::BDtaunuReader() : RootReader() {
  Initialize();
}

BDtaunuReader::BDtaunuReader(const char *root_fname) : RootReader(root_fname) {
  Initialize();
}

BDtaunuReader::BDtaunuReader(
    const char *root_fname, 
    const char *root_trname) : RootReader(root_fname, root_trname) {
  Initialize();
}


// All constructors call this function to initialize the class members.
void BDtaunuReader::Initialize() {

  // Allocate space to read in arrays from ntuples. 
  YBPairMmissPrime2 = new float[maximum_Y_candidates];
  YBPairEextra50 = new float[maximum_Y_candidates];
  YTagBlP3MagCM = new float[maximum_Y_candidates];
  YSigBhP3MagCM = new float[maximum_Y_candidates];
  YTagBCosBY = new float[maximum_Y_candidates];
  YSigBCosBY = new float[maximum_Y_candidates];
  YTagBCosThetaDlCM = new float[maximum_Y_candidates];
  YSigBCosThetaDtauCM = new float[maximum_Y_candidates];
  YSigBVtxProbB = new float[maximum_Y_candidates];
  YBPairCosThetaT = new float[maximum_Y_candidates];
  YTagBDMass = new float[maximum_Y_candidates];
  YTagBDstarDeltaM = new float[maximum_Y_candidates];
  YTagBCosThetaDSoftCM = new float[maximum_Y_candidates];
  YTagBsoftP3MagCM = new float[maximum_Y_candidates];
  YSigBDMass = new float[maximum_Y_candidates];
  YSigBDstarDeltaM = new float[maximum_Y_candidates];
  YSigBCosThetaDSoftCM = new float[maximum_Y_candidates];
  YSigBsoftP3MagCM = new float[maximum_Y_candidates];
  YSigBhMass = new float[maximum_Y_candidates];
  YSigBVtxProbh = new float[maximum_Y_candidates];

  lTrkIdx = new int[maximum_l_candidates];
  hTrkIdx = new int[maximum_h_candidates];
  eSelectorsMap = new int[maximum_h_candidates + maximum_l_candidates];
  muSelectorsMap = new int[maximum_h_candidates + maximum_l_candidates];
  KSelectorsMap = new int[maximum_h_candidates + maximum_l_candidates];
  piSelectorsMap = new int[maximum_h_candidates + maximum_l_candidates];

  YLund = new int[maximum_Y_candidates];
  BLund = new int[maximum_B_candidates];
  DLund = new int[maximum_D_candidates];
  CLund = new int[maximum_C_candidates];
  hLund = new int[maximum_h_candidates];
  lLund = new int[maximum_l_candidates];
  gammaLund = new int[maximum_gamma_candidates];

  Yd1Idx = new int[maximum_Y_candidates];
  Yd2Idx = new int[maximum_Y_candidates];
  Bd1Idx = new int[maximum_B_candidates];
  Bd2Idx = new int[maximum_B_candidates];
  Bd3Idx = new int[maximum_B_candidates];
  Bd4Idx = new int[maximum_B_candidates];
  Dd1Idx = new int[maximum_D_candidates];
  Dd2Idx = new int[maximum_D_candidates];
  Dd3Idx = new int[maximum_D_candidates];
  Dd4Idx = new int[maximum_D_candidates];
  Dd5Idx = new int[maximum_D_candidates];
  Cd1Idx = new int[maximum_C_candidates];
  Cd2Idx = new int[maximum_C_candidates];
  hd1Idx = new int[maximum_h_candidates];
  hd2Idx = new int[maximum_h_candidates];
  ld1Idx = new int[maximum_l_candidates];
  ld2Idx = new int[maximum_l_candidates];
  ld3Idx = new int[maximum_l_candidates];
  Yd1Lund = new int[maximum_Y_candidates];
  Yd2Lund = new int[maximum_Y_candidates];
  Bd1Lund = new int[maximum_B_candidates];
  Bd2Lund = new int[maximum_B_candidates];
  Bd3Lund = new int[maximum_B_candidates];
  Bd4Lund = new int[maximum_B_candidates];
  Dd1Lund = new int[maximum_D_candidates];
  Dd2Lund = new int[maximum_D_candidates];
  Dd3Lund = new int[maximum_D_candidates];
  Dd4Lund = new int[maximum_D_candidates];
  Dd5Lund = new int[maximum_D_candidates];
  Cd1Lund = new int[maximum_C_candidates];
  Cd2Lund = new int[maximum_C_candidates];
  hd1Lund = new int[maximum_h_candidates];
  hd2Lund = new int[maximum_h_candidates];
  ld1Lund = new int[maximum_l_candidates];
  ld2Lund = new int[maximum_l_candidates];
  ld3Lund = new int[maximum_l_candidates];

  YdauIdx = { Yd1Idx, Yd2Idx };
  YdauLund = { Yd1Lund, Yd2Lund };
  BdauIdx = { Bd1Idx, Bd2Idx, Bd3Idx, Bd4Idx };
  BdauLund = { Bd1Lund, Bd2Lund, Bd3Lund, Bd4Lund };
  DdauIdx = { Dd1Idx, Dd2Idx, Dd3Idx, Dd4Idx, Dd5Idx };
  DdauLund = { Dd1Lund, Dd2Lund, Dd3Lund, Dd4Lund, Dd5Lund };
  CdauIdx = { Cd1Idx, Cd2Idx };
  CdauLund = { Cd1Lund, Cd2Lund };
  hdauIdx = { hd1Idx, hd2Idx };
  hdauLund = { hd1Lund, hd2Lund };
  ldauIdx = { ld1Idx, ld2Idx, ld3Idx };
  ldauLund = { ld1Lund, ld2Lund, ld3Lund };

  // Specify the variables where each ntuple branch should be read into. 
  SetBranchAddress();
  
  // Zero out variables where ntuple data are read into. 
  ClearColumnValues();
}

void BDtaunuReader::SetBranchAddress() {

  tr->SetBranchAddress("platform", &platform);
  tr->SetBranchAddress("partition", &partition);
  tr->SetBranchAddress("upperID", &upperID);
  tr->SetBranchAddress("lowerID", &lowerID);
  tr->SetBranchAddress("nTRK", &nTrk);
  tr->SetBranchAddress("R2All", &R2All);

  tr->SetBranchAddress("YBPairMmissPrime2", YBPairMmissPrime2);
  tr->SetBranchAddress("YBPairEextra50", YBPairEextra50);
  tr->SetBranchAddress("YTagBlP3MagCM", YTagBlP3MagCM);
  tr->SetBranchAddress("YSigBhP3MagCM", YSigBhP3MagCM);
  tr->SetBranchAddress("YTagBCosBY", YTagBCosBY);
  tr->SetBranchAddress("YSigBCosBY", YSigBCosBY);
  tr->SetBranchAddress("YTagBCosThetaDlCM", YTagBCosThetaDlCM);
  tr->SetBranchAddress("YSigBCosThetaDtauCM", YSigBCosThetaDtauCM);
  tr->SetBranchAddress("YSigBVtxProbB", YSigBVtxProbB);
  tr->SetBranchAddress("YBPairCosThetaT", YBPairCosThetaT);
  tr->SetBranchAddress("YTagBDMass", YTagBDMass);
  tr->SetBranchAddress("YTagBDstarDeltaM", YTagBDstarDeltaM);
  tr->SetBranchAddress("YTagBCosThetaDSoftCM", YTagBCosThetaDSoftCM);
  tr->SetBranchAddress("YTagBsoftP3MagCM", YTagBsoftP3MagCM);
  tr->SetBranchAddress("YSigBDMass", YSigBDMass);
  tr->SetBranchAddress("YSigBDstarDeltaM", YSigBDstarDeltaM);
  tr->SetBranchAddress("YSigBCosThetaDSoftCM", YSigBCosThetaDSoftCM);
  tr->SetBranchAddress("YSigBsoftP3MagCM", YSigBsoftP3MagCM);
  tr->SetBranchAddress("YSigBhMass", YSigBhMass);
  tr->SetBranchAddress("YSigBVtxProbh", YSigBVtxProbh);

  tr->SetBranchAddress("lTrkIdx", lTrkIdx);
  tr->SetBranchAddress("hTrkIdx", hTrkIdx);
  tr->SetBranchAddress("eSelectorsMap", eSelectorsMap);
  tr->SetBranchAddress("muSelectorsMap", muSelectorsMap);
  tr->SetBranchAddress("KSelectorsMap", KSelectorsMap);
  tr->SetBranchAddress("piSelectorsMap", piSelectorsMap);

  tr->SetBranchAddress("nY", &nY);
  tr->SetBranchAddress("nB", &nB);
  tr->SetBranchAddress("nD", &nD);
  tr->SetBranchAddress("nC", &nC);
  tr->SetBranchAddress("nh", &nh);
  tr->SetBranchAddress("nl", &nl);
  tr->SetBranchAddress("ngamma", &ngamma); 
  tr->SetBranchAddress("YLund", YLund);
  tr->SetBranchAddress("BLund", BLund);
  tr->SetBranchAddress("DLund", DLund);
  tr->SetBranchAddress("CLund", CLund);
  tr->SetBranchAddress("hLund", hLund);
  tr->SetBranchAddress("lLund", lLund);
  tr->SetBranchAddress("gammaLund", gammaLund);
  tr->SetBranchAddress("Yd1Idx", Yd1Idx);
  tr->SetBranchAddress("Yd2Idx", Yd2Idx);
  tr->SetBranchAddress("Bd1Idx", Bd1Idx);
  tr->SetBranchAddress("Bd2Idx", Bd2Idx);
  tr->SetBranchAddress("Bd3Idx", Bd3Idx);
  tr->SetBranchAddress("Bd4Idx", Bd4Idx);
  tr->SetBranchAddress("Dd1Idx", Dd1Idx);
  tr->SetBranchAddress("Dd2Idx", Dd2Idx);
  tr->SetBranchAddress("Dd3Idx", Dd3Idx);
  tr->SetBranchAddress("Dd4Idx", Dd4Idx);
  tr->SetBranchAddress("Dd5Idx", Dd5Idx);
  tr->SetBranchAddress("Cd1Idx", Cd1Idx);
  tr->SetBranchAddress("Cd2Idx", Cd2Idx);
  tr->SetBranchAddress("hd1Idx", hd1Idx);
  tr->SetBranchAddress("hd2Idx", hd2Idx);
  tr->SetBranchAddress("ld1Idx", ld1Idx);
  tr->SetBranchAddress("ld2Idx", ld2Idx);
  tr->SetBranchAddress("ld3Idx", ld3Idx);
  tr->SetBranchAddress("Yd1Lund", Yd1Lund);
  tr->SetBranchAddress("Yd2Lund", Yd2Lund);
  tr->SetBranchAddress("Bd1Lund", Bd1Lund);
  tr->SetBranchAddress("Bd2Lund", Bd2Lund);
  tr->SetBranchAddress("Bd3Lund", Bd3Lund);
  tr->SetBranchAddress("Bd4Lund", Bd4Lund);
  tr->SetBranchAddress("Dd1Lund", Dd1Lund);
  tr->SetBranchAddress("Dd2Lund", Dd2Lund);
  tr->SetBranchAddress("Dd3Lund", Dd3Lund);
  tr->SetBranchAddress("Dd4Lund", Dd4Lund);
  tr->SetBranchAddress("Dd5Lund", Dd5Lund);
  tr->SetBranchAddress("Cd1Lund", Cd1Lund);
  tr->SetBranchAddress("Cd2Lund", Cd2Lund);
  tr->SetBranchAddress("hd1Lund", hd1Lund);
  tr->SetBranchAddress("hd2Lund", hd2Lund);
  tr->SetBranchAddress("ld1Lund", ld1Lund);
  tr->SetBranchAddress("ld2Lund", ld2Lund);
  tr->SetBranchAddress("ld3Lund", ld3Lund);

}

void BDtaunuReader::ClearColumnValues() {
  platform = -999;
  partition = -999;
  upperID = -999;
  lowerID = -999;
  nTrk = -999;
  R2All = -999;
  nY = -999;
  nB = -999;
  nD = -999;
  nC = -999;
  nh = -999;
  nl = -999;
  ngamma = -999;

  eventId.clear();
  upsilon_candidates.clear();
  reco_indexer.clear();
  reco_vertex_map.clear();
  g.clear();
}

BDtaunuReader::~BDtaunuReader() {

  delete[] YBPairMmissPrime2;
  delete[] YBPairEextra50;
  delete[] YTagBlP3MagCM;
  delete[] YSigBhP3MagCM;
  delete[] YTagBCosBY;
  delete[] YSigBCosBY;
  delete[] YTagBCosThetaDlCM;
  delete[] YSigBCosThetaDtauCM;
  delete[] YSigBVtxProbB;
  delete[] YBPairCosThetaT;
  delete[] YTagBDMass;
  delete[] YTagBDstarDeltaM;
  delete[] YTagBCosThetaDSoftCM;
  delete[] YTagBsoftP3MagCM;
  delete[] YSigBDMass;
  delete[] YSigBDstarDeltaM;
  delete[] YSigBCosThetaDSoftCM;
  delete[] YSigBsoftP3MagCM;
  delete[] YSigBhMass;
  delete[] YSigBVtxProbh;

  delete[] lTrkIdx;
  delete[] hTrkIdx;
  delete[] eSelectorsMap;
  delete[] muSelectorsMap;
  delete[] KSelectorsMap;
  delete[] piSelectorsMap;

  delete[] YLund;
  delete[] BLund;
  delete[] DLund;
  delete[] CLund;
  delete[] hLund;
  delete[] lLund;
  delete[] gammaLund;

  delete[] Yd1Idx;
  delete[] Yd2Idx;
  delete[] Bd1Idx;
  delete[] Bd2Idx;
  delete[] Bd3Idx;
  delete[] Bd4Idx;
  delete[] Dd1Idx;
  delete[] Dd2Idx;
  delete[] Dd3Idx;
  delete[] Dd4Idx;
  delete[] Dd5Idx;
  delete[] Cd1Idx;
  delete[] Cd2Idx;
  delete[] hd1Idx;
  delete[] hd2Idx;
  delete[] ld1Idx;
  delete[] ld2Idx;
  delete[] ld3Idx;
  delete[] Yd1Lund;
  delete[] Yd2Lund;
  delete[] Bd1Lund;
  delete[] Bd2Lund;
  delete[] Bd3Lund;
  delete[] Bd4Lund;
  delete[] Dd1Lund;
  delete[] Dd2Lund;
  delete[] Dd3Lund;
  delete[] Dd4Lund;
  delete[] Dd5Lund;
  delete[] Cd1Lund;
  delete[] Cd2Lund;
  delete[] hd1Lund;
  delete[] hd2Lund;
  delete[] ld1Lund;
  delete[] ld2Lund;
  delete[] ld3Lund;

}

// Determine whether the maximum number of allowed candidates 
// have been exceeded. Events that exceed the maximum are not 
// well behaved and should be skipped.
bool BDtaunuReader::IsMaxCandidateExceeded() const {
    if ( 
        (nY < maximum_Y_candidates) &&
        (nB < maximum_B_candidates) &&
        (nD < maximum_D_candidates) &&
        (nC < maximum_C_candidates) &&
        (nh < maximum_h_candidates) &&
        (nl < maximum_l_candidates) &&
        (ngamma < maximum_gamma_candidates) 
       ) {
      return false;
    } else {
      return true;
    }
}

// Read in the next event in the ntuple. It computes all relevant
// information as a side effect. 
int BDtaunuReader::next_record() {

  // Zero out garbage information from the previous event. 
  ClearColumnValues();

  // Read in the next event in the ntuple. The variables now contain
  // information from the new event. 
  int next_record_idx = RootReader::next_record();

  // Compute higher level information that is not directly avaible. 
  if ((next_record_idx > -1) && (!IsMaxCandidateExceeded())) {

    eventId = std::to_string(platform) + ":" 
              + std::to_string(partition) + ":" 
              + std::to_string(upperID) + "/" 
              + std::to_string(lowerID);

    reco_indexer.set({nY, nB, nD, nC, nh, nl, ngamma});

    ConstructRecoGraph();

    // Construct the Y(4S) candidate list for this event. 
    // Maximum number of candidates must not be exceeded.
    FillUpsilonList();
  }

  return next_record_idx;
}

void BDtaunuReader::ConstructRecoGraph() {
  AddCandidatesToGraph(nY, YLund, YdauIdx, YdauLund);
  AddCandidatesToGraph(nB, BLund, BdauIdx, BdauLund);
  AddCandidatesToGraph(nD, DLund, DdauIdx, DdauLund);
  AddCandidatesToGraph(nC, CLund, CdauIdx, CdauLund);
  AddCandidatesToGraph(nh, hLund, hdauIdx, hdauLund);
  AddCandidatesToGraph(nl, lLund, ldauIdx, ldauLund);
}

void BDtaunuReader::AddCandidatesToGraph(
    int nCand,
    int *CandLund,
    std::vector<int*> &CandDauIdx,
    std::vector<int*> &CandDauLund) {

  property_map<RecoGraph, vertex_reco_index_t>::type reco_index = get(vertex_reco_index, g);
  property_map<RecoGraph, vertex_block_index_t>::type block_index = get(vertex_block_index, g);
  property_map<RecoGraph, vertex_lund_id_t>::type lund_id = get(vertex_lund_id, g);

  Vertex u, v;
  std::map<int, Vertex>::iterator pos;
  bool inserted;

  for (int i = 0; i < nCand; i++) {

    int u_idx = reco_indexer(CandLund[i], i);
    boost::tie(pos, inserted) = reco_vertex_map.insert(std::make_pair(u_idx, Vertex()));
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
        boost::tie(pos, inserted) = reco_vertex_map.insert(std::make_pair(v_idx, Vertex()));
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


// This function takes the decay tree information read from the ntuple
// (which are read into the arrays new'd in Initialize()), and creates
// the UpsilonList of the event. It constructs an UpsilonCandidate
// object for each candidate and fills it with correctly computed
// higher level features.
void BDtaunuReader::FillUpsilonList() {

  auto lund_map = get(vertex_lund_id, g);
  std::vector<YDecayProperties> upsilon_decays;
  depth_first_search(g, visitor(reco_graph_dfs_visitor(lund_map, upsilon_decays)));

  auto block_idx_map = get(vertex_block_index, g);
  auto reco_idx_map = get(vertex_reco_index, g);
  for (auto y : upsilon_decays) {
    int cand_idx = get(block_idx_map, y.Y);
    int reco_idx = get(reco_idx_map, y.Y);
    int l_ePidMap = eSelectorsMap[lTrkIdx[get(block_idx_map, y.l)]];
    int l_muPidMap = muSelectorsMap[lTrkIdx[get(block_idx_map, y.l)]];

    UpsilonCandidate ups(eventId, cand_idx, reco_idx, 
        YBPairEextra50[cand_idx], YBPairMmissPrime2[cand_idx], 
        YTagBlP3MagCM[cand_idx], YSigBhP3MagCM[cand_idx], 
        YTagBCosBY[cand_idx], YSigBCosBY[cand_idx], 
        YTagBCosThetaDlCM[cand_idx], YSigBCosThetaDtauCM[cand_idx], 
        YSigBVtxProbB[cand_idx], 
        YBPairCosThetaT[cand_idx], 
        YTagBDMass[cand_idx], YTagBDstarDeltaM[cand_idx], 
        YTagBCosThetaDSoftCM[cand_idx], YTagBsoftP3MagCM[cand_idx],
        YSigBDMass[cand_idx], YSigBDstarDeltaM[cand_idx], 
        YSigBCosThetaDSoftCM[cand_idx], YSigBsoftP3MagCM[cand_idx],
        YSigBhMass[cand_idx], YSigBVtxProbh[cand_idx], 
        y.bflavor,
        y.tag_dstar_mode, y.tag_d_mode, 
        y.sig_dstar_mode, y.sig_d_mode, 
        y.tau_mode, 
        l_ePidMap, l_muPidMap); 
    upsilon_candidates.push_back(ups);
  }
}

BDtaunuReader::RecoGraph BDtaunuReader::get_reco_subgraph(int reco_idx) {
  RecoGraph subg;
  breadth_first_search(g, reco_vertex_map[reco_idx], visitor(reco_graph_bfs_visitor(g, subg)));
  return subg;
}
