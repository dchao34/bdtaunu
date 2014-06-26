#include <TTree.h>

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <cmath>
#include <cassert>

#include "utilities/helpers.h"
#include "bdtaunu_definitions.h"
#include "RootReader.h"
#include "BDtaunuReader.h"

// The maximum number of candidates allowed in an event. This should
// be consistent with the number set in BtaTupleMaker. 
const int BDtaunuReader::maximum_Y_candidates = 800;
const int BDtaunuReader::maximum_B_candidates = 400;
const int BDtaunuReader::maximum_D_candidates = 200;
const int BDtaunuReader::maximum_tau_candidates = 100;
const int BDtaunuReader::maximum_h_candidates = 100;
const int BDtaunuReader::maximum_l_candidates = 100;
const int BDtaunuReader::maximum_gamma_candidates = 100;

// map<string, int> that associates particle name to its lundId. For
// example, "B0" : 511.
std::map<std::string, int> BDtaunuReader::lundIdMap = BDtaunuReader::build_lund_map();

// Reads in __PDT_FILE_PATHNAME which contains one particle type on
// each line in the format: "particle name" lundId, and puts the
// information in lundIdMap.
std::map<std::string, int> BDtaunuReader::build_lund_map() {
  std::map<std::string, int> m;

  std::ifstream pdt_file;
  pdt_file.open(__PDT_FILE_PATHNAME);

  // Scan each line from the first character until the first space for
  // the particle name. The remainder of the line is the lundId. 
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

  assert(!m.empty());
  assert(m["B0"] == 511);

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

  Yd1Idx = new int[maximum_Y_candidates];
  Yd2Idx = new int[maximum_Y_candidates];
  Bd1Idx = new int[maximum_B_candidates];
  Bd2Idx = new int[maximum_B_candidates];
  Dd1Idx = new int[maximum_D_candidates];
  Dd2Idx = new int[maximum_D_candidates];
  Dd3Idx = new int[maximum_D_candidates];
  Dd4Idx = new int[maximum_D_candidates];
  Dd5Idx = new int[maximum_D_candidates];
  taud1Idx = new int[maximum_tau_candidates];

  Yd1Lund = new int[maximum_Y_candidates];
  Yd2Lund = new int[maximum_Y_candidates];
  Bd1Lund = new int[maximum_B_candidates];
  Bd2Lund = new int[maximum_B_candidates];
  Dd1Lund = new int[maximum_D_candidates];
  Dd2Lund = new int[maximum_D_candidates];
  Dd3Lund = new int[maximum_D_candidates];
  Dd4Lund = new int[maximum_D_candidates];
  Dd5Lund = new int[maximum_D_candidates];
  taud1Lund = new int[maximum_tau_candidates];

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
  tr->SetBranchAddress("nY", &nY);
  tr->SetBranchAddress("nB", &nB);
  tr->SetBranchAddress("nD", &nD);
  tr->SetBranchAddress("ntau", &ntau);
  tr->SetBranchAddress("nh", &nh);
  tr->SetBranchAddress("nl", &nl);
  tr->SetBranchAddress("ngamma", &ngamma);
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
  tr->SetBranchAddress("Dd2Idx", Dd2Idx);
  tr->SetBranchAddress("Dd3Idx", Dd3Idx);
  tr->SetBranchAddress("Dd4Idx", Dd4Idx);
  tr->SetBranchAddress("Dd5Idx", Dd5Idx);
  tr->SetBranchAddress("taud1Idx", taud1Idx);
  tr->SetBranchAddress("Yd1Lund", Yd1Lund);
  tr->SetBranchAddress("Yd2Lund", Yd2Lund);
  tr->SetBranchAddress("Bd1Lund", Bd1Lund);
  tr->SetBranchAddress("Bd2Lund", Bd2Lund);
  tr->SetBranchAddress("Dd1Lund", Dd1Lund);
  tr->SetBranchAddress("Dd2Lund", Dd2Lund);
  tr->SetBranchAddress("Dd3Lund", Dd3Lund);
  tr->SetBranchAddress("Dd4Lund", Dd4Lund);
  tr->SetBranchAddress("Dd5Lund", Dd5Lund);
  tr->SetBranchAddress("taud1Lund", taud1Lund);

}

void BDtaunuReader::ClearColumnValues() {
  platform = -999;
  partition = -999;
  upperID = -999;
  upperID = -999;
  nTrk = -999;
  nY = -999;
  nB = -999;
  nD = -999;
  ntau = -999;
  nh = -999;
  nl = -999;
  ngamma = -999;
  R2All = -999;
  eventId = std::string();
  upsilon_candidates = UpsilonList();
}

// This function takes the decay tree information read from the ntuple
// (which are read into the arrays new'd in Initialize()), and creates
// the UpsilonList of the event. It constructs an UpsilonCandidate
// object for each candidate and fills it with correctly computed
// higher level features.
void BDtaunuReader::FillUpsilonList() {

  for (int cand_idx = 0; cand_idx < nY; cand_idx++) {

    // Compute reconstructed decay tree information. 
    int bflavor;
    int tag_dstar_mode, tag_d_mode;
    int sig_dstar_mode, sig_d_mode, sig_tau_mode;
    ComputeCandidateDecay(cand_idx, 
        bflavor, tag_dstar_mode, tag_d_mode,
        sig_dstar_mode, sig_d_mode, sig_tau_mode);

    // Construct an UpsilonCandidate object and fill in its features.
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

    // Add it to the UpsilonList. 
    upsilon_candidates.add_candidate(cand);
  }
}

void BDtaunuReader::ComputeCandidateDecay(
    int cand_idx,
    int &bflavor, int &tag_dstar_mode, int &tag_d_mode, 
    int &sig_dstar_mode, int &sig_d_mode, int &sig_tau_mode) {

    // B flavor of the this Y(4S) candidate.
    assert(
      abs(Yd2Lund[cand_idx]) == abs(lundIdMap["B0"]) ||
      abs(Yd2Lund[cand_idx]) == abs(lundIdMap["B+"])
    );
    bflavor = DetermineBFlavor(Yd2Lund[cand_idx]);
  
    // Determine whether the tag B has a D* decay, and determine the
    // modes in which the D* and D decay. 
    int tagBIdx = Yd1Idx[cand_idx];
    assert(
      abs(Bd1Lund[tagBIdx]) == abs(lundIdMap["D+"]) ||
      abs(Bd1Lund[tagBIdx]) == abs(lundIdMap["D0"]) ||
      abs(Bd1Lund[tagBIdx]) == abs(lundIdMap["D*0"]) ||
      abs(Bd1Lund[tagBIdx]) == abs(lundIdMap["D*+"])
    );

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

    // Determine whether the sig B has a D* decay, and determine the
    // modes in which the D* and D decay. Also determine which mode
    // the tau decays in. 
    int sigBIdx = Yd2Idx[cand_idx];
    assert(
      abs(Bd1Lund[sigBIdx]) == abs(lundIdMap["D+"]) ||
      abs(Bd1Lund[sigBIdx]) == abs(lundIdMap["D0"]) ||
      abs(Bd1Lund[sigBIdx]) == abs(lundIdMap["D*0"]) ||
      abs(Bd1Lund[sigBIdx]) == abs(lundIdMap["D*+"])
    );
    
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
    assert(abs(Bd2Lund[sigBIdx]) == abs(lundIdMap["tau+"]));
    assert(
      abs(taud1Lund[tauIdx]) == abs(lundIdMap["pi+"]) ||
      abs(taud1Lund[tauIdx]) == abs(lundIdMap["rho+"])
    );

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
  delete[] Dd2Idx;
  delete[] Dd3Idx;
  delete[] Dd4Idx;
  delete[] Dd5Idx;
  delete[] taud1Idx;
  delete[] Yd1Lund;
  delete[] Yd2Lund;
  delete[] Bd1Lund;
  delete[] Bd2Lund;
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
    return kUndefinedBFlavor;
  }
}

int BDtaunuReader::DetermineDstarMode(
    int Dd1_lundId, int Dd2_lundId, 
    int Dd3_lundId, int Dd4_lundId, int Dd5_lundId) {

  int dau_abslund[] = { abs(Dd1_lundId), abs(Dd2_lundId), 
                        abs(Dd3_lundId), abs(Dd4_lundId), 
                        abs(Dd5_lundId) };

  // Count the daughter particle types
  int n_daughters, n_D0, n_Dc, n_pi, n_pi0, n_gamma;
  n_daughters = n_D0 = n_Dc = n_pi = n_pi0 = n_gamma = 0;
  for (int i = 0; i < 5; i++) {
    if (dau_abslund[i] == 0) {
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

  // Determine the decay mode based on the daughter counts. 
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

  // Count the daughter particle types
  int n_daughters, n_K, n_Ks, n_pi, n_pi0;
  n_daughters = n_K = n_Ks = n_pi = n_pi0 = 0;
  for (int i = 0; i < 5; i++) {
    if (dau_abslund[i] == 0) {
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

  // Determine the decay mode based on the daughter counts. 
  if (abs(D_lundId) == abs(lundIdMap["D+"])) {
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

// Determine whether the maximum number of allowed candidates 
// have been exceeded. Events that exceed the maximum are not 
// well behaved and should be skipped.
bool BDtaunuReader::IsMaxCandidateExceeded() const {
    if ( 
        (nY < maximum_Y_candidates) &&
        (nB < maximum_B_candidates) &&
        (nD < maximum_D_candidates) &&
        (ntau < maximum_tau_candidates) &&
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
  if (next_record_idx > -1) {
    eventId = to_string(platform) + ":" 
              + to_string(partition) + ":" 
              + to_string(upperID) + "/" 
              + to_string(lowerID);

    // Construct the Y(4S) candidate list for this event. 
    // Maximum number of candidates must not be exceeded.
    if (!IsMaxCandidateExceeded()) { 
      FillUpsilonList();
    }
  }

  return next_record_idx;
}
