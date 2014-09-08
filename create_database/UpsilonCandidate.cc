#include <string> 
#include <cassert> 

#include "bdtaunu_definitions.h"
#include "UpsilonCandidate.h"

UpsilonCandidate::UpsilonCandidate() : 
  eventId(""), event_candidate_index(-999),
  reco_index(-1), 
  eextra50(-999), mmiss_prime2(-999), 
  tag_lp3(-999), sig_hp3(-999),
  tag_cosBY(-999), sig_cosBY(-999), 
  tag_cosThetaDl(-999), sig_cosThetaDtau(-999), 
  sig_vtxB(-999), 
  cosThetaT(-999), 
  tag_Dmass(-999), tag_deltaM(-999), 
  tag_cosThetaDSoft(-999), tag_softP3MagCM(-999),
  sig_Dmass(-999), sig_deltaM(-999), 
  sig_cosThetaDSoft(-999), sig_softP3MagCM(-999), 
  sig_hmass(-999), sig_vtxh(-999), 
  bflavor(bdtaunu::kUndefinedBFlavor),
  tag_dstar_mode(bdtaunu::kUndefinedDstarMode), tag_d_mode(bdtaunu::kUndefinedDMode),
  sig_dstar_mode(bdtaunu::kUndefinedDstarMode), sig_d_mode(bdtaunu::kUndefinedDMode),
  sig_tau_mode(bdtaunu::kUndefinedTauMode), 
  l_ePidMap(0), l_muPidMap(0),
  h_ePidMap(0), h_muPidMap(0) {
}

UpsilonCandidate::UpsilonCandidate(
    std::string &event_id, int candidate_idx, 
    float eextra50, float mmiss_prime2, 
    float tag_lp3, float sig_hp3, 
    float tag_cosBY, float sig_cosBY, 
    float tag_cosThetaDl, float sig_cosThetaDtau, 
    float sig_vtxB, 
    float cosThetaT, 
    float tag_Dmass, float tag_deltaM, 
    float tag_cosThetaDSoft, float tag_softP3MagCM,
    float sig_Dmass, float sig_deltaM, 
    float sig_cosThetaDSoft, float sig_softP3MagCM, 
    float sig_hmass, float sig_vtxh, 
    int bflavor,
    int tag_dstar_mode, int tag_d_mode,
    int sig_dstar_mode, int sig_d_mode,
    int sig_tau_mode) :
  eventId(event_id), event_candidate_index(candidate_idx),
  reco_index(-1), 
  eextra50(eextra50), mmiss_prime2(mmiss_prime2),
  tag_lp3(tag_lp3), sig_hp3(sig_hp3),
  tag_cosBY(tag_cosBY), sig_cosBY(sig_cosBY),
  tag_cosThetaDl(tag_cosThetaDl), sig_cosThetaDtau(sig_cosThetaDtau),
  sig_vtxB(sig_vtxB),
  cosThetaT(cosThetaT),
  tag_Dmass(tag_Dmass), tag_deltaM(tag_deltaM),
  tag_cosThetaDSoft(tag_cosThetaDSoft), tag_softP3MagCM(tag_softP3MagCM),
  sig_Dmass(sig_Dmass), sig_deltaM(sig_deltaM),
  sig_cosThetaDSoft(sig_cosThetaDSoft), sig_softP3MagCM(sig_softP3MagCM),
  sig_hmass(sig_hmass), sig_vtxh(sig_vtxh),
  bflavor(bflavor),
  tag_dstar_mode(tag_dstar_mode), tag_d_mode(tag_d_mode),
  sig_dstar_mode(sig_dstar_mode), sig_d_mode(sig_d_mode),
  sig_tau_mode(sig_tau_mode),
  l_ePidMap(0), l_muPidMap(0),
  h_ePidMap(0), h_muPidMap(0) {
}

UpsilonCandidate::UpsilonCandidate(
    std::string &event_id, int candidate_idx, 
    float eextra50, float mmiss_prime2, 
    float tag_lp3, float sig_hp3, 
    float tag_cosBY, float sig_cosBY, 
    float tag_cosThetaDl, float sig_cosThetaDtau, 
    float sig_vtxB, 
    float cosThetaT, 
    float tag_Dmass, float tag_deltaM, 
    float tag_cosThetaDSoft, float tag_softP3MagCM,
    float sig_Dmass, float sig_deltaM, 
    float sig_cosThetaDSoft, float sig_softP3MagCM, 
    float sig_hmass, float sig_vtxh, 
    int bflavor,
    int tag_dstar_mode, int tag_d_mode,
    int sig_dstar_mode, int sig_d_mode,
    int sig_tau_mode, 
    int l_ePidMap, int l_muPidMap) :
  eventId(event_id), event_candidate_index(candidate_idx),
  reco_index(-1), 
  eextra50(eextra50), mmiss_prime2(mmiss_prime2),
  tag_lp3(tag_lp3), sig_hp3(sig_hp3),
  tag_cosBY(tag_cosBY), sig_cosBY(sig_cosBY),
  tag_cosThetaDl(tag_cosThetaDl), sig_cosThetaDtau(sig_cosThetaDtau),
  sig_vtxB(sig_vtxB),
  cosThetaT(cosThetaT),
  tag_Dmass(tag_Dmass), tag_deltaM(tag_deltaM),
  tag_cosThetaDSoft(tag_cosThetaDSoft), tag_softP3MagCM(tag_softP3MagCM),
  sig_Dmass(sig_Dmass), sig_deltaM(sig_deltaM),
  sig_cosThetaDSoft(sig_cosThetaDSoft), sig_softP3MagCM(sig_softP3MagCM),
  sig_hmass(sig_hmass), sig_vtxh(sig_vtxh),
  bflavor(bflavor),
  tag_dstar_mode(tag_dstar_mode), tag_d_mode(tag_d_mode),
  sig_dstar_mode(sig_dstar_mode), sig_d_mode(sig_d_mode),
  sig_tau_mode(sig_tau_mode),
  l_ePidMap(l_ePidMap), l_muPidMap(l_muPidMap),
  h_ePidMap(0), h_muPidMap(0) {
}

UpsilonCandidate::UpsilonCandidate(
    std::string &event_id, int candidate_idx, 
    int reco_idx,
    float eextra50, float mmiss_prime2, 
    float tag_lp3, float sig_hp3, 
    float tag_cosBY, float sig_cosBY, 
    float tag_cosThetaDl, float sig_cosThetaDtau, 
    float sig_vtxB, 
    float cosThetaT, 
    float tag_Dmass, float tag_deltaM, 
    float tag_cosThetaDSoft, float tag_softP3MagCM,
    float sig_Dmass, float sig_deltaM, 
    float sig_cosThetaDSoft, float sig_softP3MagCM, 
    float sig_hmass, float sig_vtxh, 
    int bflavor,
    int tag_dstar_mode, int tag_d_mode,
    int sig_dstar_mode, int sig_d_mode,
    int sig_tau_mode, 
    int l_ePidMap, int l_muPidMap,
    int h_ePidMap, int h_muPidMap) :
  eventId(event_id), event_candidate_index(candidate_idx),
  reco_index(reco_idx), 
  eextra50(eextra50), mmiss_prime2(mmiss_prime2),
  tag_lp3(tag_lp3), sig_hp3(sig_hp3),
  tag_cosBY(tag_cosBY), sig_cosBY(sig_cosBY),
  tag_cosThetaDl(tag_cosThetaDl), sig_cosThetaDtau(sig_cosThetaDtau),
  sig_vtxB(sig_vtxB),
  cosThetaT(cosThetaT),
  tag_Dmass(tag_Dmass), tag_deltaM(tag_deltaM),
  tag_cosThetaDSoft(tag_cosThetaDSoft), tag_softP3MagCM(tag_softP3MagCM),
  sig_Dmass(sig_Dmass), sig_deltaM(sig_deltaM),
  sig_cosThetaDSoft(sig_cosThetaDSoft), sig_softP3MagCM(sig_softP3MagCM),
  sig_hmass(sig_hmass), sig_vtxh(sig_vtxh),
  bflavor(bflavor),
  tag_dstar_mode(tag_dstar_mode), tag_d_mode(tag_d_mode),
  sig_dstar_mode(sig_dstar_mode), sig_d_mode(sig_d_mode),
  sig_tau_mode(sig_tau_mode),
  l_ePidMap(l_ePidMap), l_muPidMap(l_muPidMap),
  h_ePidMap(h_ePidMap), h_muPidMap(h_muPidMap) {
}

UpsilonCandidate::UpsilonCandidate(const UpsilonCandidate &cand) {
  copy_candidate(cand);
}

void UpsilonCandidate::copy_candidate(const UpsilonCandidate &cand) {
  eventId = cand.eventId;
  event_candidate_index = cand.event_candidate_index;
  reco_index = cand.reco_index;
  eextra50 = cand.eextra50;
  mmiss_prime2 = cand.mmiss_prime2;
  tag_lp3 = cand.tag_lp3;
  sig_hp3 = cand.sig_hp3;
  tag_cosBY = cand.tag_cosBY;
  sig_cosBY = cand.sig_cosBY;
  tag_cosThetaDl = cand.tag_cosThetaDl;
  sig_cosThetaDtau = cand.sig_cosThetaDtau;
  sig_vtxB = cand.sig_vtxB;
  cosThetaT = cand.cosThetaT;
  tag_Dmass = cand.tag_Dmass;
  tag_deltaM = cand.tag_deltaM;
  tag_cosThetaDSoft = cand.tag_cosThetaDSoft;
  tag_softP3MagCM = cand.tag_softP3MagCM;
  sig_Dmass = cand.sig_Dmass;
  sig_deltaM = cand.sig_deltaM;
  sig_cosThetaDSoft = cand.sig_cosThetaDSoft;
  sig_softP3MagCM = cand.sig_softP3MagCM;
  sig_hmass = cand.sig_hmass;
  sig_vtxh = cand.sig_vtxh;
  bflavor = cand.bflavor;
  tag_dstar_mode = cand.tag_dstar_mode;
  tag_d_mode = cand.tag_d_mode;
  sig_dstar_mode = cand.sig_dstar_mode;
  sig_d_mode = cand.sig_d_mode;
  sig_tau_mode = cand.sig_tau_mode;
  l_ePidMap = cand.l_ePidMap;
  l_muPidMap = cand.l_muPidMap;
  h_ePidMap = cand.h_ePidMap;
  h_muPidMap = cand.h_muPidMap;
}

UpsilonCandidate & UpsilonCandidate::operator=(const UpsilonCandidate &cand) {
  if (this != &cand) {
    copy_candidate(cand);
  }
  return *this;
}

// Examine the D, D*, and tau modes to determine the candidate type. 
int UpsilonCandidate::get_cand_type() const {

  assert(sig_tau_mode != bdtaunu::kUndefinedTauMode);
  assert(tag_dstar_mode != bdtaunu::kUndefinedDstarMode);
  assert(sig_dstar_mode != bdtaunu::kUndefinedDstarMode);

  int cand_type = 0;
  if (sig_tau_mode == bdtaunu::ktau_rho)
    cand_type += (1 << 2);
  if (tag_dstar_mode != bdtaunu::kNoDstar)
    cand_type += (1 << 1);
  if (sig_dstar_mode != bdtaunu::kNoDstar)
    cand_type += 1;

  return cand_type;
}


// Examine the bflavor and D* decay mode on the signal to determine
// sample type. 
int UpsilonCandidate::get_sample_type() const {

  assert(bflavor != bdtaunu::kUndefinedBFlavor);
  assert(sig_dstar_mode != bdtaunu::kUndefinedDstarMode);

  int sample_type = 0;
  if (bflavor == bdtaunu::kB0) 
    sample_type += (1 << 1);
  if (sig_dstar_mode != bdtaunu::kNoDstar) 
    sample_type += 1;

  return sample_type;
}
