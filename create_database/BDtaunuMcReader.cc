#include "BDtaunuReader.h"
#include "BDtaunuMcReader.h"
#include "utilities/helpers.h"
#include "bdtaunu_definitions.h"

#include <map>
#include <string>
#include <cmath>
#include <cassert>
#include <algorithm>

// Static methods to initialize the particle lundId arrays that are
// needed to determine MC B meson types. 
// Charged leptons. 
std::vector<int> BDtaunuMcReader::build_ell() {
  std::vector<int> ell_temp;
  ell_temp.push_back(abs(lundIdMap["e-"]));
  ell_temp.push_back(abs(lundIdMap["mu-"]));
  ell_temp.push_back(abs(lundIdMap["tau-"]));
  std::sort(ell_temp.begin(), ell_temp.end());
  return ell_temp;
}
const std::vector<int> BDtaunuMcReader::ell = build_ell();

// Neutrinos. 
std::vector<int> BDtaunuMcReader::build_nu() {
  std::vector<int> nu_temp;
  nu_temp.push_back(abs(lundIdMap["nu_e"]));
  nu_temp.push_back(abs(lundIdMap["nu_mu"]));
  nu_temp.push_back(abs(lundIdMap["nu_tau"]));
  std::sort(nu_temp.begin(), nu_temp.end());
  return nu_temp;
}
const std::vector<int> BDtaunuMcReader::nu = build_nu();

// D mesons. 
std::vector<int> BDtaunuMcReader::build_dmeson() {
  std::vector<int> dmeson_temp;
  dmeson_temp.push_back(abs(lundIdMap["D+"]));
  dmeson_temp.push_back(abs(lundIdMap["D0"]));
  std::sort(dmeson_temp.begin(), dmeson_temp.end());
  return dmeson_temp;
}
const std::vector<int> BDtaunuMcReader::dmeson = build_dmeson();

// D* mesons. 
std::vector<int> BDtaunuMcReader::build_dstar() {
  std::vector<int> dstar_temp;
  dstar_temp.push_back(abs(lundIdMap["D*+"]));
  dstar_temp.push_back(abs(lundIdMap["D*0"]));
  std::sort(dstar_temp.begin(), dstar_temp.end());
  return dstar_temp;
}
const std::vector<int> BDtaunuMcReader::dstar = build_dstar();

// D** mesons. 
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

// Ds(*) mesons.
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

// pion. 
std::vector<int> BDtaunuMcReader::build_pion() {
  std::vector<int> pion_temp;
  pion_temp.push_back(abs(lundIdMap["pi+"]));
  pion_temp.push_back(abs(lundIdMap["pi0"]));
  std::sort(pion_temp.begin(), pion_temp.end());
  return pion_temp;
}
const std::vector<int> BDtaunuMcReader::pion = build_pion();


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
  McB1.mc_idx = -1;
  McB1.bmctype = kUndefinedBMcType;
  McB1.dtau_max_photon_energy = -1;
  McB1.taumctype = ktau_undefined_mc;

  McB2.bflavor = kUndefinedBFlavor;
  McB2.mc_idx = -1;
  McB2.bmctype = kUndefinedBMcType;
  McB2.dtau_max_photon_energy = -1;
  McB2.taumctype = ktau_undefined_mc;
}

// Find the MC B meson's from the mcLund array of the event. Determine
// its flavor along the way. 
void BDtaunuMcReader::FindBMesons() {

  // Scan through the mcLund array. Store B mesons that are found.
  for (int i = 0; i < mcLen; i++) {
    if (abs(mcLund[i]) == lundIdMap["B0"] ||
        abs(mcLund[i]) == lundIdMap["B+"] ) {

      // Error if we find more than two B mesons. 
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

  // Error if we find only one B meson. 
  assert(
      (McB1.mc_idx == -1 && McB2.mc_idx == -1) ||
      (McB1.mc_idx > -1 && McB2.mc_idx > -1)
  );

  // Error if the two B meson's flavor don't agree. Note the condition
  // is also true for continuum events. 
  assert(McB1.bflavor == McB2.bflavor);

}

// Determine the B MC types. 
void BDtaunuMcReader::DetermineBMcType(McBMeson &mcB) {

  // Return if no MC B mesons are in the event. 
  if (mcB.mc_idx == -1) {
    mcB.bmctype = kCont;
    return;
  }

  // Count the number of daughters of the first generation B daughters
  // and record the lundId of relevant daughters.
  int n_daughters = 0;
  int ell_lund, nu_lund;
  ell_lund = nu_lund = 0;
  int n_ell, n_nu, n_d, n_dstar, n_dstarstar, n_dstrange, n_pi, n_other;
  n_ell = n_nu = n_d = n_dstar = n_dstarstar = n_dstrange = n_pi = n_other = 0;

  int ell_idx = -1;

  // Scan through the entire first generation daughter. 
  int begin_dauIdx = dauIdx[mcB.mc_idx];
  int end_dauIdx = begin_dauIdx + dauLen[mcB.mc_idx];
  for (int i = begin_dauIdx; i < end_dauIdx; i++) {

    // Note down max photon energy, but don't use it to classify B type.
    if (mcLund[i] == lundIdMap["gamma"]) {
      if (mcenergy[i] > mcB.dtau_max_photon_energy) {
        mcB.dtau_max_photon_energy = mcenergy[i];
      }
      continue;
    }
    n_daughters += 1;

    // Determine the identity of each daughter. 
    if (std::binary_search(ell.begin(), ell.end(), abs(mcLund[i]))) {
      n_ell += 1;
      ell_lund = abs(mcLund[i]);
      ell_idx = i;
    } else if (std::binary_search(nu.begin(), nu.end(), abs(mcLund[i]))) {
      n_nu += 1;
      nu_lund = abs(mcLund[i]);
    } else if (std::binary_search(dmeson.begin(), dmeson.end(), abs(mcLund[i]))) {
      n_d += 1;
    } else if (std::binary_search(dstar.begin(), dstar.end(), abs(mcLund[i]))) {
      n_dstar += 1;
    } else if (std::binary_search(dstarstar.begin(), dstarstar.end(), abs(mcLund[i]))) {
      n_dstarstar += 1;
    } else if (std::binary_search(dstrange.begin(), dstrange.end(), abs(mcLund[i]))) {
      n_dstrange += 1;
    } else if (std::binary_search(pion.begin(), pion.end(), abs(mcLund[i]))) {
      n_pi += 1;
    } else {
      n_other += 1;
    }
  }

  // Determine the B MC Type. See bdtaunu_definitions.h for the
  // definitions. 
  if (n_ell == 1 && n_nu == 1) {
    if (n_d == 1) {
      if (n_daughters == 3) {
        if (ell_lund == abs(lundIdMap["tau-"])) {
          mcB.bmctype = kDtau;
        } else {
          mcB.bmctype = kDl;
        }
      } else if (n_pi > 0) {
        mcB.bmctype = kDstarstar_nonres;
      } else {
        mcB.bmctype = kD_SL;
      }
    } else if (n_dstar == 1) {
      if (n_daughters == 3) {
        if (ell_lund == abs(lundIdMap["tau-"])) {
          mcB.bmctype = kDstartau;
        } else {
          mcB.bmctype = kDstarl;
        }
      } else if (n_pi > 0) {
        mcB.bmctype = kDstarstar_nonres;
      } else {
        mcB.bmctype = kD_SL;
      }
    } else if (n_dstarstar == 1) {
      mcB.bmctype = kDstarstar_res;
    } else if (n_d + n_dstar + n_dstarstar == 0) {
      mcB.bmctype = k0D_SL;
    } else {
      mcB.bmctype = kUndefinedBMcType;
    }
  } else if (n_ell == 0 && n_nu == 0) {
    int nD = n_dstarstar + n_dstrange + n_d;
    if (nD == 0)  {
      mcB.bmctype = k0Charm_Had;
    } else if (nD == 1) {
      mcB.bmctype = k1Charm_Had;
    } else if (nD == 2) {
      mcB.bmctype = k2Charm_Had;
    } else {
      mcB.bmctype = kUndefinedBMcType;
    }
  } else {
    mcB.bmctype = kUndefinedBMcType;
  }

  // Determine tau mc type
  if (mcB.bmctype == kDtau || mcB.bmctype == kDstartau) {
    mcB.taumctype = ktau_had_mc;

    int begin_dauIdx = dauIdx[ell_idx];
    int end_dauIdx = begin_dauIdx + dauLen[ell_idx];
    for (int i = begin_dauIdx; i < end_dauIdx; i++) {
      if (abs(mcLund[i]) == lundIdMap["e-"]) {
        mcB.taumctype = ktau_e_mc;
      } else if (abs(mcLund[i]) == lundIdMap["mu-"]) {
        mcB.taumctype = ktau_mu_mc;
      } else {
        continue;
      }
    }
  }
}

// Main method that fills MC information.
void BDtaunuMcReader::FillMCInformation() {

  // Find the MC B mesons. 
  FindBMesons();

  // Determine B MC types. 
  DetermineBMcType(McB1);
  DetermineBMcType(McB2);

}

// get the next event
int BDtaunuMcReader::next_record() {
  ClearColumnValues();

  int next_record_idx = BDtaunuReader::next_record();
  if (next_record_idx > -1) {
    if (!IsMaxCandidateExceeded()) {
      FillMCInformation();
    }
  }

  return next_record_idx;
}
