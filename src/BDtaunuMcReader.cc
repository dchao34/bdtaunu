#include "BDtaunuReader.h"
#include "BDtaunuMcReader.h"
#include "utilities.h"
#include "bdtaunu_definitions.h"

#include <map>
#include <string>
#include <cmath>
#include <cassert>
#include <algorithm>

std::vector<int> BDtaunuMcReader::build_ell() {
  std::vector<int> ell_temp;
  ell_temp.push_back(abs(lundIdMap["e-"]));
  ell_temp.push_back(abs(lundIdMap["mu-"]));
  ell_temp.push_back(abs(lundIdMap["tau-"]));
  std::sort(ell_temp.begin(), ell_temp.end());
  return ell_temp;
}
const std::vector<int> BDtaunuMcReader::ell = build_ell();

std::vector<int> BDtaunuMcReader::build_nu() {
  std::vector<int> nu_temp;
  nu_temp.push_back(abs(lundIdMap["nu_e"]));
  nu_temp.push_back(abs(lundIdMap["nu_mu"]));
  nu_temp.push_back(abs(lundIdMap["nu_tau"]));
  std::sort(nu_temp.begin(), nu_temp.end());
  return nu_temp;
}
const std::vector<int> BDtaunuMcReader::nu = build_nu();

std::vector<int> BDtaunuMcReader::build_dmeson() {
  std::vector<int> dmeson_temp;
  dmeson_temp.push_back(abs(lundIdMap["D+"]));
  dmeson_temp.push_back(abs(lundIdMap["D0"]));
  dmeson_temp.push_back(abs(lundIdMap["D*+"]));
  dmeson_temp.push_back(abs(lundIdMap["D*0"]));
  std::sort(dmeson_temp.begin(), dmeson_temp.end());
  return dmeson_temp;
}
const std::vector<int> BDtaunuMcReader::dmeson = build_dmeson();

std::vector<int> BDtaunuMcReader::build_dstarstar() {
  std::vector<int> dstarstar_temp;
  dstarstar_temp.push_back(abs(lundIdMap["D_0*+"]));
  dstarstar_temp.push_back(abs(lundIdMap["D_0*0"]));
  dstarstar_temp.push_back(abs(lundIdMap["D_1+"]));
  dstarstar_temp.push_back(abs(lundIdMap["D_10"]));
  dstarstar_temp.push_back(abs(lundIdMap["D_2*+"]));
  dstarstar_temp.push_back(abs(lundIdMap["D_2*0"]));
  dstarstar_temp.push_back(abs(lundIdMap["D'_1+"]));
  dstarstar_temp.push_back(abs(lundIdMap["D'_10"]));
  dstarstar_temp.push_back(abs(lundIdMap["D(2S)+"]));
  dstarstar_temp.push_back(abs(lundIdMap["D(2S)0"]));
  dstarstar_temp.push_back(abs(lundIdMap["D*(2S)+"]));
  dstarstar_temp.push_back(abs(lundIdMap["D*(2S)0"]));
  std::sort(dstarstar_temp.begin(), dstarstar_temp.end());
  return dstarstar_temp;
}
const std::vector<int> BDtaunuMcReader::dstarstar = build_dstarstar();

std::vector<int> BDtaunuMcReader::build_dstrange() {
  std::vector<int> dstrange_temp;
  dstrange_temp.push_back(abs(lundIdMap["D_s+"]));
  dstrange_temp.push_back(abs(lundIdMap["D_s*+"]));
  dstrange_temp.push_back(abs(lundIdMap["D_s0*+"]));
  dstrange_temp.push_back(abs(lundIdMap["D_s1+"]));
  dstrange_temp.push_back(abs(lundIdMap["D_s2*+"]));
  dstrange_temp.push_back(abs(lundIdMap["D'_s1+"]));
  std::sort(dstrange_temp.begin(), dstrange_temp.end());
  return dstrange_temp;
}
const std::vector<int> BDtaunuMcReader::dstrange = build_dstrange();


BDtaunuMcReader::BDtaunuMcReader() : BDtaunuReader() {
  Initialize();
}

BDtaunuMcReader::BDtaunuMcReader(const char *root_fname) : 
  BDtaunuReader(root_fname) {
  Initialize();
}

BDtaunuMcReader::BDtaunuMcReader(
    const char *root_fname,
    const char *root_trname) : 
  BDtaunuReader(root_fname, root_trname) {
  Initialize();
}

BDtaunuMcReader::~BDtaunuMcReader() {
  delete[] mcLund;
  delete[] mothIdx;
  delete[] dauIdx;
  delete[] dauLen;
  delete[] mcenergy;
}


void BDtaunuMcReader::Initialize() {
  mcLund = new int[max_mc_length];
  mothIdx = new int[max_mc_length];
  dauIdx = new int[max_mc_length];
  dauLen = new int[max_mc_length];
  mcenergy = new float[max_mc_length];
  SetBranchAddress();
  ClearColumnValues();
}

void BDtaunuMcReader::SetBranchAddress() {
  BDtaunuReader::SetBranchAddress();
  tr->SetBranchAddress("mcLen", &mcLen);
  tr->SetBranchAddress("mcLund", mcLund);
  tr->SetBranchAddress("mothIdx", mothIdx);
  tr->SetBranchAddress("dauIdx", dauIdx);
  tr->SetBranchAddress("dauLen", dauLen);
  tr->SetBranchAddress("mcenergy", mcenergy);
}

void BDtaunuMcReader::ClearColumnValues() {
  BDtaunuReader::ClearColumnValues();
  mcLen = 0;
  McB1.bflavor = kUndefinedBFlavor;
  McB1.bmctype = kUndefinedBMcType;
  McB1.mc_idx = -1;
  McB2.bflavor = kUndefinedBFlavor;
  McB2.bmctype = kUndefinedBMcType;
  McB2.mc_idx = -1;
  mc_evttype = kUndefinedMcEventType;
}

void BDtaunuMcReader::FindBMesons() {

  for (int i = 0; i < mcLen; i++) {
    if (abs(mcLund[i]) == lundIdMap["B0"] ||
        abs(mcLund[i]) == lundIdMap["B+"] ) {
      assert(!(McB1.mc_idx > -1 && McB2.mc_idx > -1));

      if (McB1.mc_idx == -1) {
        McB1.mc_idx = i;
        if (abs(mcLund[i]) == lundIdMap["B0"]) {
          McB1.bflavor = kB0;
        } else {
          McB1.bflavor = kBc;
        }
      } else {
        McB2.mc_idx = i;
        if (abs(mcLund[i]) == lundIdMap["B0"]) {
          McB2.bflavor = kB0;
        } else {
          McB2.bflavor = kBc;
        }    
      }
    }
  }
  assert(
      (McB1.mc_idx == -1 && McB2.mc_idx == -1) ||
      (McB1.mc_idx > -1 && McB2.mc_idx > -1)
  );
  assert(McB1.bflavor == McB2.bflavor);

}

int BDtaunuMcReader::DetermineBMcType(int bmc_idx) {

  if (bmc_idx == -1) 
    return kNoB;

  int n_daughters = 0;
  int ell_lund, nu_lund, d_lund;
  ell_lund = nu_lund = d_lund = 0;
  int n_ell, n_nu, n_d, n_dstarstar, n_dstrange, n_other;
  n_ell = n_nu = n_d = n_dstarstar = n_dstrange = n_other = 0;

  int begin_dauIdx = dauIdx[bmc_idx];
  int end_dauIdx = begin_dauIdx + dauLen[bmc_idx];
  for (int i = begin_dauIdx; i < end_dauIdx; i++) {

    if (mcLund[i] == lundIdMap["gamma"] && 
        mcenergy[i] < min_photon_energy) {
      continue;
    }
    n_daughters += 1;

    if (std::binary_search(ell.begin(), ell.end(), abs(mcLund[i]))) {
      n_ell += 1;
      ell_lund = abs(mcLund[i]);
    } else if (std::binary_search(nu.begin(), nu.end(), abs(mcLund[i]))) {
      n_nu += 1;
      nu_lund = abs(mcLund[i]);
    } else if (std::binary_search(dmeson.begin(), dmeson.end(), abs(mcLund[i]))) {
      n_d += 1;
      d_lund = abs(mcLund[i]);
    } else if (std::binary_search(dstarstar.begin(), dstarstar.end(), abs(mcLund[i]))) {
      n_dstarstar += 1;
    } else if (std::binary_search(dstrange.begin(), dstrange.end(), abs(mcLund[i]))) {
      n_dstrange += 1;
    } else {
      n_other += 1;
    }
  }

  if (n_ell == 1 && n_nu == 1) {
    if (n_d == 1) {
      if (n_daughters == 3) {
        if (ell_lund == abs(lundIdMap["tau-"])) {
          return kDtau;
        } else {
          return kDl;
        }
      } else {
        return kD_SL;
      }
    } else if (n_dstarstar == 1) {
      return kDstarstar_SL;
    } else if (n_d + n_dstarstar == 0) {
      return k0Charm_SL;
    } else {
      return kUndefinedBMcType;
    }
  } else if (n_ell == 0 && n_nu == 0) {
    int nD = n_dstarstar + n_dstrange + n_d;
    if (nD == 0)  {
      return k0Charm_Had;
    } else if (nD == 1) {
      return k1Charm_Had;
    } else if (nD == 2) {
      return k2Charm_Had;
    } else {
      return kUndefinedBMcType;
    }
  } else {
    return kUndefinedBMcType;
  }
}

int BDtaunuMcReader::DetermineMcEventType() {
  if (McB1.bmctype == kNoB && McB2.bmctype == kNoB) {
    return kContinuum_Bkg;
  } else if (McB1.bmctype == kDtau || McB2.bmctype == kDtau) {
    return kSignal;
  } else if (McB1.bmctype == kDl || McB2.bmctype == kDl) {
    return kNormalization;
  } else {
    int b1_dectype, b2_dectype;
    b1_dectype = b2_dectype = -2;

    switch (McB1.bmctype) {
      case kD_SL:
      case kDstarstar_SL:
      case k0Charm_SL:
        b1_dectype = 0;
        break;
      case k0Charm_Had:
      case k1Charm_Had:
      case k2Charm_Had:
        b1_dectype = 1;
        break;
    }

    switch (McB2.bmctype) {
      case kD_SL:
      case kDstarstar_SL:
      case k0Charm_SL:
        b2_dectype = 0;
        break;
      case k0Charm_Had:
      case k1Charm_Had:
      case k2Charm_Had:
        b2_dectype = 1;
        break;
    }

    int dectype_sum = b1_dectype + b2_dectype;
    switch (dectype_sum) {
      case 0:
        return kSLSL_Bkg;
      case 1:
        return kSLHad_Bkg;
      case 2:
        return kHadHad_Bkg;
      default: 
        return kUndefinedMcEventType;
    }
  }
}

void BDtaunuMcReader::FillMCInformation() {
  FindBMesons();
  McB1.bmctype = DetermineBMcType(McB1.mc_idx);
  McB2.bmctype = DetermineBMcType(McB2.mc_idx);
  mc_evttype = DetermineMcEventType();
}

int BDtaunuMcReader::next_record() {
  ClearColumnValues();

  int next_record_idx = BDtaunuReader::next_record();
  if (next_record_idx > -1) {
    FillMCInformation();
  }

  return next_record_idx;
}
