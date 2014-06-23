#include <map>
#include <vector>
#include <utility>
#include <string>
#include <cmath>
#include <cassert>
#include <algorithm>

#include "BDtaunuMcReader.h"
#include "BDtaunuSigMcReader.h"
#include "utilities/helpers.h"
#include "bdtaunu_definitions.h"

BDtaunuSigMcReader::BDtaunuSigMcReader() : BDtaunuMcReader() {
  Initialize();
}

BDtaunuSigMcReader::BDtaunuSigMcReader(const char *root_fname) : 
  BDtaunuMcReader(root_fname) {
  Initialize();
}

BDtaunuSigMcReader::BDtaunuSigMcReader(
    const char *root_fname,
    const char *root_trname) : 
  BDtaunuMcReader(root_fname, root_trname) {
  Initialize();
}

BDtaunuSigMcReader::~BDtaunuSigMcReader() {
  delete[] hd1Lund;
  delete[] hd2Lund;
  delete[] hd3Lund;
  delete[] hd1Idx;
  delete[] hd2Idx;
  delete[] hd3Idx;
  delete[] ld1Lund;
  delete[] ld2Lund;
  delete[] ld3Lund;
  delete[] ld1Idx;
  delete[] ld2Idx;
  delete[] ld3Idx;
  delete[] hMCIdx;
  delete[] lMCIdx;
  delete[] gammaMCIdx;
}


void BDtaunuSigMcReader::Initialize() {
  hd1Lund = new int[maximum_h_candidates];
  hd2Lund = new int[maximum_h_candidates];
  hd3Lund = new int[maximum_h_candidates];
  hd1Idx = new int[maximum_h_candidates];
  hd2Idx = new int[maximum_h_candidates];
  hd3Idx = new int[maximum_h_candidates];
  ld1Lund = new int[maximum_l_candidates];
  ld2Lund = new int[maximum_l_candidates];
  ld3Lund = new int[maximum_l_candidates];
  ld1Idx = new int[maximum_l_candidates];
  ld2Idx = new int[maximum_l_candidates];
  ld3Idx = new int[maximum_l_candidates];
  hMCIdx = new int[maximum_h_candidates];
  lMCIdx = new int[maximum_l_candidates];
  gammaMCIdx = new int[maximum_gamma_candidates];
  SetBranchAddress();
  ClearColumnValues();
}

void BDtaunuSigMcReader::SetBranchAddress() {
  BDtaunuMcReader::SetBranchAddress();
  tr->SetBranchAddress("hd1Lund", hd1Lund);
  tr->SetBranchAddress("hd2Lund", hd2Lund);
  tr->SetBranchAddress("hd3Lund", hd3Lund);
  tr->SetBranchAddress("hd1Idx", hd1Idx);
  tr->SetBranchAddress("hd2Idx", hd2Idx);
  tr->SetBranchAddress("hd3Idx", hd3Idx);
  tr->SetBranchAddress("ld1Lund", ld1Lund);
  tr->SetBranchAddress("ld2Lund", ld2Lund);
  tr->SetBranchAddress("ld3Lund", ld3Lund);
  tr->SetBranchAddress("ld1Idx", ld1Idx);
  tr->SetBranchAddress("ld2Idx", ld2Idx);
  tr->SetBranchAddress("ld3Idx", ld3Idx);
  tr->SetBranchAddress("hMCIdx", hMCIdx);
  tr->SetBranchAddress("lMCIdx", lMCIdx);
  tr->SetBranchAddress("gammaMCIdx", gammaMCIdx);
}

void BDtaunuSigMcReader::ClearColumnValues() {
  BDtaunuMcReader::ClearColumnValues();
  truth_match.clear();
  dau_map.clear();
  hit_map.clear();
}

int BDtaunuSigMcReader::next_record() {
  ClearColumnValues();

  int next_record_idx = BDtaunuMcReader::next_record();
  if (next_record_idx > -1) {
    FillTruthMatchInfo();
  }

  return next_record_idx;
}

// Fill truth match status of each candidate of the event.  
void BDtaunuSigMcReader::FillTruthMatchInfo() {

  build_dau_map();
  build_hit_map();

  for (int i = 0; i < nY; i++) {

    // Truth match each reco B individually. 
    std::pair<int, int> recoB1(Yd1Lund[i], Yd1Idx[i]);
    bool cand_tag_match = BTruthMatches(recoB1);
    std::pair<int, int> recoB2(Yd2Lund[i], Yd2Idx[i]);
    bool cand_sig_match = BTruthMatches(recoB2);

    // The candidate is truth matched if both reco B's are also truth matched. 
    if (cand_tag_match && cand_sig_match) {
      truth_match.push_back(1);
    } else {
      truth_match.push_back(0);
    }
  }
}






// determine the candidate block a particle belongs to given its lund Id 
BDtaunuSigMcReader::CandBlocks BDtaunuSigMcReader::get_cand_block(int plund) {
  switch (abs(plund)) {
    case 70553:
      return Yblock;
    case 511:
    case 521: 
      return Bblock;
    case 411:
    case 421:
    case 413: 
    case 423:
      return Dblock;
    case 15: 
      return taublock;
    case 20213:
    case 310:
    case 321:
    case 213:
    case 111:
    case 211:
      return hblock;
    case 11:
    case 13: 
      return lblock;
    case 22:
      return gammablock;
    default: 
      return noblock;
  }
}


// build reco daughter map. there is one key per candidate block,
// with a vector of pairs as its corresponding value. the ith element
// of each vector cooresponds to the ith daughters of the candidate
// block. each pair is two arrays. the first array is the lundId of
// the daughters while the second is its index in its correspond
// candidate block. see reco_daughters below for example of its usage.
void BDtaunuSigMcReader::build_dau_map() {

  // Y(4S)
  std::pair<int*, int*> Yd1(Yd1Lund, Yd1Idx);
  std::pair<int*, int*> Yd2(Yd2Lund, Yd2Idx);
  std::vector<std::pair<int*, int*> > YDaus;
  YDaus.push_back(Yd1);
  YDaus.push_back(Yd2);
  dau_map[Yblock] = YDaus;

  
  // B meson
  std::pair<int*, int*> Bd1(Bd1Lund, Bd1Idx);
  std::pair<int*, int*> Bd2(Bd2Lund, Bd2Idx);
  std::vector<std::pair<int*, int*> > BDaus;
  BDaus.push_back(Bd1);
  BDaus.push_back(Bd2);
  dau_map[Bblock] = BDaus;

  
  // D meson 
  std::pair<int*, int*> Dd1(Dd1Lund, Dd1Idx);
  std::pair<int*, int*> Dd2(Dd2Lund, Dd2Idx);
  std::pair<int*, int*> Dd3(Dd3Lund, Dd3Idx);
  std::pair<int*, int*> Dd4(Dd4Lund, Dd4Idx);
  std::pair<int*, int*> Dd5(Dd5Lund, Dd5Idx);
  std::vector<std::pair<int*, int*> > DDaus;
  DDaus.push_back(Dd1);
  DDaus.push_back(Dd2);
  DDaus.push_back(Dd3);
  DDaus.push_back(Dd4);
  DDaus.push_back(Dd5);
  dau_map[Dblock] = DDaus;

  
  // tau lepton
  std::pair<int*, int*> taud1(taud1Lund, taud1Idx);
  std::vector<std::pair<int*, int*> > tauDaus;
  tauDaus.push_back(taud1);
  dau_map[taublock] = tauDaus;

  
  // hadrons; see hblock in cand_block()
  std::pair<int*, int*> hd1(hd1Lund, hd1Idx);
  std::pair<int*, int*> hd2(hd2Lund, hd2Idx);
  std::pair<int*, int*> hd3(hd3Lund, hd3Idx);
  std::vector<std::pair<int*, int*> > hDaus;
  hDaus.push_back(hd1);
  hDaus.push_back(hd2);
  hDaus.push_back(hd3);
  dau_map[hblock] = hDaus;

  
  // leptons
  std::pair<int*, int*> ld1(ld1Lund, ld1Idx);
  std::pair<int*, int*> ld2(ld2Lund, ld2Idx);
  std::pair<int*, int*> ld3(ld3Lund, ld3Idx);
  std::vector<std::pair<int*, int*> > lDaus;
  lDaus.push_back(ld1);
  lDaus.push_back(ld2);
  lDaus.push_back(ld3);
  dau_map[lblock] = lDaus;

}

// build truth hitmap (GHit) for h, l, and gammas
void BDtaunuSigMcReader::build_hit_map() {
  hit_map[hblock] = hMCIdx;
  hit_map[lblock] = lMCIdx;
  hit_map[gammablock] = gammaMCIdx;
}


// Entry point for truth matching a recoB. 
bool BDtaunuSigMcReader::BTruthMatches(std::pair<int, int> &recoB) {

  // does not truth match if mctruth is non-BBbar
  if (McB1.mc_idx == -1 || McB2.mc_idx == -1)
    return false;

  // determine if recoB truth matches to either mctruth B mesons
  std::pair<int, int> B1(mcLund[McB1.mc_idx], McB1.mc_idx);
  std::pair<int, int> B2(mcLund[McB2.mc_idx], McB2.mc_idx);
  bool matchB1 = TruthMatchesTo(B1, recoB);
  bool matchB2 = TruthMatchesTo(B2, recoB);

  // recoB truth matches if it truth matches to exactly one mctruth B
  if (matchB1 ^ matchB2) {
    return true;
  } else {
    return false;
  }
}

// determine if an mctruth particle truth matches to a reco particle
bool BDtaunuSigMcReader::TruthMatchesTo(std::pair<int, int> &mcParticle, 
                                        std::pair<int, int> &recoParticle) {

  // the lundId must agree 
  if (mcParticle.first != recoParticle.first)
    return false;

  // if the particle type is a final state particle, then the hit
  // pattern of the reco particle must correspond to the mc particle
  if (IsMcFinalState(mcParticle)) {
    if (!HitTruthMatches(mcParticle, recoParticle))
      return false;

  // if the particle type is not a final state, then all relevant mc
  // daughters, "mc targets", must truth match to all relevant 
  // reco daughter particles, "reco targets", 1-to-1 and onto
  } else {

    // find the mc and reco targets
    std::vector<std::pair<int, int> > mcDau_targets, recoDau_targets;
    McTargetDaughters(mcParticle, mcDau_targets);
    RecoTargetDaughters(recoParticle, recoDau_targets);

    // check that each mc target truth matches to a unique reco target
    std::vector<std::pair<int, int> > matched_recoDaus;
    std::vector<std::pair<int, int> >::iterator mc_it = mcDau_targets.begin();
    while (mc_it != mcDau_targets.end()) {

      // cycle through all reco targets to see if any truth matches
      // this particular mc target
      bool found_match = false;
      std::vector<std::pair<int, int> >::iterator reco_it = recoDau_targets.begin();
      while (reco_it != recoDau_targets.end()) {

        if (TruthMatchesTo(*mc_it, *reco_it)) {

          // the matched reco target must be unique and keep track of all
          // those that have been matched
          if (find(matched_recoDaus.begin(), 
                   matched_recoDaus.end(), 
                   *reco_it) != matched_recoDaus.end()) {
            return false;
          } else {
            found_match = true;
            matched_recoDaus.push_back(*reco_it);
            break;
          }
        }
        ++reco_it;
      }
      if (!found_match)
        return false;

      ++mc_it;
    }

    // check that all reco targets have been matched
    if (matched_recoDaus.size() != recoDau_targets.size())
      return false;
  }

  // passed all tests; the two particles truth match to each other
  return true;
}



// determine if two particles truth match based on their hit pattern
bool BDtaunuSigMcReader::HitTruthMatches(std::pair<int, int> &mcParticle, 
                                         std::pair<int, int> &recoParticle) {
  int *truthmap = hit_map[get_cand_block(recoParticle.first)];
  if (truthmap[recoParticle.second] == mcParticle.second) {
    return true;
  } else {
    return false;
  }
}

// determine if the mcParticle is a final state
bool BDtaunuSigMcReader::IsMcFinalState(std::pair<int, int> &mcParticle) {
  int lundId = abs(mcParticle.first);
  if (lundId == 11 || lundId == 13 || lundId == 211 ||
      lundId == 321 || lundId == 2212 || lundId == 22 || lundId == 2112) {
    return true;
  } else {
    return false;
  }
}


// determine mc particle daughters that need to be truth matched to
// the corresponding reco daughters. these mc daughters are "mc
// targets"
void BDtaunuSigMcReader::McTargetDaughters(
  std::pair<int, int> &particle,
  std::vector<std::pair<int, int> > &pDaughters) {

  int mcIdx = particle.second;
  int d1Idx = dauIdx[mcIdx];
  int nDaus = dauLen[mcIdx];

  // check if each first generation daughter is a target
  for (int i = 0; i < nDaus; i++) {
    int dauLund = abs(mcLund[d1Idx + i]);
    std::pair<int, int> mcDau(mcLund[d1Idx + i], d1Idx + i);

    // ignore neutrinos
    if (dauLund == 12 || dauLund == 14 || dauLund == 16) {
      continue;

    // ignore low energy photons
    } else if (dauLund == 22 && mcenergy[d1Idx + i] <= 0.02) {
      continue;

    // K0's themselves are ignored, but its daughters should be
    // considered for "mc targets". these will be grand daughters for
    // the starting particle
    } else if (dauLund == 311) {
      McTargetDaughters(mcDau, pDaughters);

    // make final pions the mc targets for tau->rho decays. 
    } else if (dauLund == 213 && abs(particle.first) == 15) {
      McTargetDaughters(mcDau, pDaughters);

    // make final pions the mc targets for 3-prong tau->a1 decays. 
    } else if ((dauLund == 20213 && abs(particle.first) == 15) || 
               (dauLund == 113 && abs(particle.first) == 20213)) {
      McTargetDaughters(mcDau, pDaughters);

    // all other particles are considered targets
    } else {
      pDaughters.push_back(mcDau);
    } 
  }
}


// determine reco particle daughters that need to be truth matched to
// the corresponding mc targets. these reco daughters are "reco
// targets"
void BDtaunuSigMcReader::RecoTargetDaughters(
  std::pair<int, int> &particle,
  std::vector<std::pair<int, int> > &pDaughters) {

  // get all daughters of the corresponding candidate block.
  // each vector element i stores info on the ith daughter. 
  int pLund = particle.first;
  std::vector<std::pair<int*, int*> > block_daus = dau_map[get_cand_block(pLund)];

  // cycle through all potential daughter particles
  int pIdx = particle.second;
  std::vector<std::pair<int*, int*> >::iterator it = block_daus.begin();
  while (it != block_daus.end()) {

    // get the current daughter if it has one
    int dauLund = (it->first)[pIdx];
    int dauIdx = (it->second)[pIdx];
    if (dauIdx == -1)
      break;
    std::pair<int, int> recoDau(dauLund, dauIdx);

    // make final pions targets for a reco charged rho particle
    if (abs(dauLund) == 213) {
      RecoTargetDaughters(recoDau, pDaughters);
    
    // make final pions targets for a reco a1 particle
    } else if (abs(dauLund) == 20213) {
      RecoTargetDaughters(recoDau, pDaughters);

    // all other particles are considered targets
    } else {
      pDaughters.push_back(recoDau);
    }

    ++it;
  }
}
