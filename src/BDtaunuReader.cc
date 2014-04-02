#include <TTree.h>

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <cmath>
#include <cassert>

#include "utilities.h"
#include "bdtaunu_definitions.h"
#include "BDtaunuReader.h"

const int BDtaunuReader::maximum_candidates_allowed = 100;
std::map<std::string, int> BDtaunuReader::lundIdMap = BDtaunuReader::build_lund_map();

std::map<std::string, int> BDtaunuReader::build_lund_map() {
  std::map<std::string, int> m;

  std::ifstream pdt_file;
  pdt_file.open(__PDT_FILE_PATHNAME);

  std::string line, lundId_string, particle_name;
  while (std::getline(pdt_file, line)) {

    for (std::string::size_type i = 0; i != line.size(); ++i) {
      if (std::isspace(line[i])) {
        lundId_string = line.substr(i + 1);
        particle_name = line.substr(0, i);
        m[particle_name] = to_int(lundId_string);
        break;
      }
    }
  }
  pdt_file.close();

  return m;
}

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

void BDtaunuReader::Initialize() {

  YBPairMmissPrime2 = new float[maximum_candidates_allowed];
  YBPairEextra50 = new float[maximum_candidates_allowed];
  YTagBlP3MagCM = new float[maximum_candidates_allowed];
  YSigBhP3MagCM = new float[maximum_candidates_allowed];
  YTagBCosBY = new float[maximum_candidates_allowed];
  YSigBCosBY = new float[maximum_candidates_allowed];
  YTagBCosThetaDlCM = new float[maximum_candidates_allowed];
  YSigBCosThetaDtauCM = new float[maximum_candidates_allowed];
  YSigBVtxProbB = new float[maximum_candidates_allowed];
  YBPairCosThetaT = new float[maximum_candidates_allowed];
  YTagBDMass = new float[maximum_candidates_allowed];
  YTagBDstarDeltaM = new float[maximum_candidates_allowed];
  YTagBCosThetaDSoftCM = new float[maximum_candidates_allowed];
  YTagBsoftP3MagCM = new float[maximum_candidates_allowed];
  YSigBDMass = new float[maximum_candidates_allowed];
  YSigBDstarDeltaM = new float[maximum_candidates_allowed];
  YSigBCosThetaDSoftCM = new float[maximum_candidates_allowed];
  YSigBsoftP3MagCM = new float[maximum_candidates_allowed];
  YSigBhMass = new float[maximum_candidates_allowed];
  YSigBVtxProbh = new float[maximum_candidates_allowed];

  Yd1Idx = new int[maximum_candidates_allowed];
  Yd2Idx = new int[maximum_candidates_allowed];
  Bd1Idx = new int[maximum_candidates_allowed];
  Bd2Idx = new int[maximum_candidates_allowed];
  Dd1Idx = new int[maximum_candidates_allowed];

  Yd2Lund = new int[maximum_candidates_allowed];
  Bd1Lund = new int[maximum_candidates_allowed];
  Dd1Lund = new int[maximum_candidates_allowed];
  Dd2Lund = new int[maximum_candidates_allowed];
  Dd3Lund = new int[maximum_candidates_allowed];
  Dd4Lund = new int[maximum_candidates_allowed];
  Dd5Lund = new int[maximum_candidates_allowed];
  taud1Lund = new int[maximum_candidates_allowed];

  SetBranchAddress();
  ClearColumnValues();
}

void BDtaunuReader::SetBranchAddress() {
  tr->SetBranchAddress("platform", &platform);
  tr->SetBranchAddress("partition", &partition);
  tr->SetBranchAddress("upperID", &upperID);
  tr->SetBranchAddress("lowerID", &lowerID);
  tr->SetBranchAddress("nTRK", &nTrk);
  tr->SetBranchAddress("nY", &nY);
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
  tr->SetBranchAddress("Yd1Idx", Yd1Idx);
  tr->SetBranchAddress("Yd2Idx", Yd2Idx);
  tr->SetBranchAddress("Bd1Idx", Bd1Idx);
  tr->SetBranchAddress("Bd2Idx", Bd2Idx);
  tr->SetBranchAddress("Dd1Idx", Dd1Idx);
  tr->SetBranchAddress("Yd2Lund", Yd2Lund);
  tr->SetBranchAddress("Bd1Lund", Bd1Lund);
  tr->SetBranchAddress("Dd1Lund", Dd1Lund);
  tr->SetBranchAddress("Dd2Lund", Dd2Lund);
  tr->SetBranchAddress("Dd3Lund", Dd3Lund);
  tr->SetBranchAddress("Dd4Lund", Dd4Lund);
  tr->SetBranchAddress("Dd5Lund", Dd5Lund);
  tr->SetBranchAddress("taud1Lund", taud1Lund);

}

void BDtaunuReader::ClearColumnValues() {
  platform = 0;
  partition = 0;
  upperID = 0;
  upperID = 0;
  nTrk = 0;
  nY = 0;
  R2All = 0.0;
  eventId = std::string();
  upsilon_candidates = UpsilonList();
}

void BDtaunuReader::FillUpsilonList() {

  for (int cand_idx = 0; cand_idx < nY; cand_idx++) {

    int bflavor;
    int tag_dstar_mode, tag_d_mode;
    int sig_dstar_mode, sig_d_mode, sig_tau_mode;
    ComputeCandidateDecay(cand_idx, 
        bflavor, tag_dstar_mode, tag_d_mode,
        sig_dstar_mode, sig_d_mode, sig_tau_mode);

    // build upsilon candidate
    UpsilonCandidate cand(eventId, cand_idx, 
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
        bflavor,
        tag_dstar_mode, tag_d_mode, 
        sig_dstar_mode, sig_d_mode, 
        sig_tau_mode);
    upsilon_candidates.add_candidate(cand);
  }
}

void BDtaunuReader::ComputeCandidateDecay(
    int cand_idx,
    int &bflavor, int &tag_dstar_mode, int &tag_d_mode, 
    int &sig_dstar_mode, int &sig_d_mode, int &sig_tau_mode) {

    bflavor = DetermineBFlavor(Yd2Lund[cand_idx]);
  

    // tagB
    int tagBIdx = Yd1Idx[cand_idx];

    if (abs(Bd1Lund[tagBIdx]) == abs(lundIdMap["D+"]) ||
        abs(Bd1Lund[tagBIdx]) == abs(lundIdMap["D0"])) {
      int DIdx = Bd1Idx[tagBIdx];
      
      tag_dstar_mode = kNoDstar;
      tag_d_mode = DetermineDMode(Bd1Lund[tagBIdx], Dd1Lund[DIdx], Dd2Lund[DIdx],
                                  Dd3Lund[DIdx], Dd4Lund[DIdx], Dd5Lund[DIdx]);
    } else {
      int DsIdx = Bd1Idx[tagBIdx];
      int DIdx = Dd1Idx[DsIdx];
      
      tag_dstar_mode = DetermineDstarMode(Dd1Lund[DsIdx], Dd2Lund[DsIdx],
                                          Dd3Lund[DsIdx], Dd4Lund[DsIdx], Dd5Lund[DsIdx]);
      tag_d_mode = DetermineDMode(Dd1Lund[DsIdx], Dd1Lund[DIdx], Dd2Lund[DIdx],
                                  Dd3Lund[DIdx], Dd4Lund[DIdx], Dd5Lund[DIdx]);
    }

    // sigB
    int sigBIdx = Yd2Idx[cand_idx];
    
    if (abs(Bd1Lund[sigBIdx]) == abs(lundIdMap["D+"]) ||
        abs(Bd1Lund[sigBIdx]) == abs(lundIdMap["D0"])) {
      int DIdx = Bd1Idx[sigBIdx];

      sig_dstar_mode = kNoDstar;
      sig_d_mode = DetermineDMode(Bd1Lund[sigBIdx], Dd1Lund[DIdx], Dd2Lund[DIdx],
                                  Dd3Lund[DIdx], Dd4Lund[DIdx], Dd5Lund[DIdx]);
    } else {
      int DsIdx = Bd1Idx[sigBIdx];
      int DIdx = Dd1Idx[DsIdx];

      sig_dstar_mode = DetermineDstarMode(Dd1Lund[DsIdx], Dd2Lund[DsIdx],
                                          Dd3Lund[DsIdx], Dd4Lund[DsIdx], Dd5Lund[DsIdx]);
      sig_d_mode = DetermineDMode(Dd1Lund[DsIdx], Dd1Lund[DIdx], Dd2Lund[DIdx],
                                  Dd3Lund[DIdx], Dd4Lund[DIdx], Dd5Lund[DIdx]);
    }
    
    int tauIdx = Bd2Idx[sigBIdx];
    sig_tau_mode = DetermineTauMode(taud1Lund[tauIdx]);
    
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
  delete[] Yd1Idx;
  delete[] Yd2Idx;
  delete[] Bd1Idx;
  delete[] Bd2Idx;
  delete[] Dd1Idx;
  delete[] Yd2Lund;
  delete[] Bd1Lund;
  delete[] Dd1Lund;
  delete[] Dd2Lund;
  delete[] Dd3Lund;
  delete[] Dd4Lund;
  delete[] Dd5Lund;
  delete[] taud1Lund;

}

int BDtaunuReader::DetermineBFlavor(int lundId) {
  if (abs(lundId) == abs(lundIdMap["B0"])) {
    return kB0;
  } else if (abs(lundId) == abs(lundIdMap["B+"])) {
    return kBc;
  } else {
    return kUndefinedBFlav;
  }
}

int BDtaunuReader::DetermineDstarMode(
    int Dd1_lundId, int Dd2_lundId, 
    int Dd3_lundId, int Dd4_lundId, int Dd5_lundId) {

  int dau_abslund[] = { abs(Dd1_lundId), abs(Dd2_lundId), 
                        abs(Dd3_lundId), abs(Dd4_lundId), 
                        abs(Dd5_lundId) };

  int n_daughters, n_D0, n_Dc, n_pi, n_pi0, n_gamma;
  n_daughters = n_D0 = n_Dc = n_pi = n_pi0 = n_gamma = 0;
  for (int i = 0; i < 5; i++) {
    if (dau_abslund[i] < 0) {
      break;
    } else {
      n_daughters += 1;
      if (dau_abslund[i] == abs(lundIdMap["D0"])) {
        n_D0 += 1;
      } else if (dau_abslund[i] == abs(lundIdMap["D+"])) {
        n_Dc += 1;
      } else if (dau_abslund[i] == abs(lundIdMap["pi+"])) {
        n_pi += 1;
      } else if (dau_abslund[i] == abs(lundIdMap["pi0"])) {
        n_pi0 += 1;
      } else if (dau_abslund[i] == abs(lundIdMap["gamma"])) {
        n_gamma += 1;
      } else {
        return kUndefinedDstarMode;
      }
    }
  }

  if (n_daughters == 2 && n_D0 == 1 && n_pi0 == 1) {
    return kDstar0_D0pi0;
  } else if (n_daughters == 2 && n_D0 == 1 && n_gamma == 1) {
    return kDstar0_D0gamma;
  } else if (n_daughters == 2 && n_D0 == 1 && n_pi == 1) {
    return kDstarc_D0pi;
  } else if (n_daughters == 2 && n_Dc == 1 && n_pi0 == 1) {
    return kDstarc_Dcpi0;
  } else if (n_daughters == 2 && n_Dc == 1 && n_gamma == 1) {
    return kDstarc_Dcgamma;
  } else {
    return kUndefinedDstarMode;
  }
}

int BDtaunuReader::DetermineDMode(
    int D_lundId, int Dd1_lundId, int Dd2_lundId, 
    int Dd3_lundId, int Dd4_lundId, int Dd5_lundId) {

  int dau_abslund[] = { abs(Dd1_lundId), abs(Dd2_lundId), 
                        abs(Dd3_lundId), abs(Dd4_lundId), 
                        abs(Dd5_lundId) };

  int n_daughters, n_K, n_Ks, n_pi, n_pi0;
  n_daughters = n_K = n_Ks = n_pi = n_pi0 = 0;
  for (int i = 0; i < 5; i++) {
    if (dau_abslund[i] < 0) {
      break;
    } else {
      n_daughters += 1;
      if (dau_abslund[i] == abs(lundIdMap["K+"])) {
        n_K += 1;
      } else if (dau_abslund[i] == abs(lundIdMap["K_S0"])) {
        n_Ks += 1;
      } else if (dau_abslund[i] == abs(lundIdMap["pi+"])) {
        n_pi += 1;
      } else if (dau_abslund[i] == abs(lundIdMap["pi0"])) {
        n_pi0 += 1;
      } else {
        return kUndefinedDMode;
      }
    }
  }

  if (abs(D_lundId) == abs(lundIdMap["Dc"])) {
    if (n_daughters == 3 && n_K == 1 && n_pi == 2) {
      return kDc_Kpipi;
    } else if (n_daughters == 4 && n_K == 1 && n_pi == 2 && n_pi0 == 1) {
      return kDc_Kpipipi0;
    } else if (n_daughters == 2 && n_K == 1 && n_Ks == 1) {
      return kDc_KsK;
    } else if (n_daughters == 2 && n_Ks == 1 && n_pi == 1) {
      return kDc_Kspi;
    } else if (n_daughters == 3 && n_Ks == 1 && n_pi == 1 && n_pi0 == 1) {
      return kDc_Kspipi0;
    } else if (n_daughters == 4 && n_Ks == 1 && n_pi == 3) {
      return kDc_Kspipipi;
    } else if (n_daughters == 3 && n_K == 2 && n_pi == 1) {
      return kDc_KKpi;
    } else {
      return kUndefinedDMode;
    }
  } else {
    if (n_daughters == 2 && n_K == 1 && n_pi == 1) {
      return kD0_Kpi;
    } else if (n_daughters == 3 && n_K == 1 && n_pi == 1 && n_pi0 == 1) {
      return kD0_Kpipi0;
    } else if (n_daughters == 4 && n_K == 1 && n_pi == 3) {
      return kD0_Kpipipi;
    } else if (n_daughters == 5 && n_K == 1 && n_pi == 3 && n_pi0 == 1) {
      return kD0_Kpipipipi0;
    } else if (n_daughters == 3 && n_Ks == 1 && n_pi == 2) {
      return kD0_Kspipi;
    } else if (n_daughters == 4 && n_Ks == 1 && n_pi == 2 && n_pi0 == 1) {
      return kD0_Kspipipi0;
    } else if (n_daughters == 2 && n_Ks == 1 && n_pi0 == 1) {
      return kD0_Kspi0;
    } else if (n_daughters == 2 && n_K == 2) {
      return kD0_KK;
    } else {
      return kUndefinedDMode;
    }
  }
}

int BDtaunuReader::DetermineTauMode(int tau_d1lundId) {
  if (abs(tau_d1lundId) == abs(lundIdMap["pi+"])) {
    return ktau_pi;
  } else if (abs(tau_d1lundId) == abs(lundIdMap["rho+"])) {
    return ktau_rho;
  } else {
    return kUndefinedTauMode;
  }
}


int BDtaunuReader::next_record() {

  ClearColumnValues();

  int next_record_idx = RootReader::next_record();
  if (next_record_idx > -1) {
    eventId = to_string(platform) + ":" 
              + to_string(partition) + ":" 
              + to_string(upperID) + "/" 
              + to_string(lowerID);
    //if (nY < 100) 
    FillUpsilonList();
  }

  return next_record_idx;
}
