#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <iostream>

#include "YCandFeatureExtractor.h"
#include "bdtaunu_definitions.h"

YCandFeatureExtractor::YCandFeatureExtractor() : 
  numeric_features(), 
  tagD_indicators(),
  sigD_indicators(), 
  tagDstar_indicators(), 
  sigDstar_indicators() {
  ClearCache();
  ClearFeatures();
}


YCandFeatureExtractor::YCandFeatureExtractor(
  int n_num, 
  int n_tagD, int n_sigD, 
  int n_tagDstar, int n_sigDstar) {

  if (n_num > 0) {
    numeric_features = std::vector<double>(n_num, 0);
  } else {
    numeric_features = std::vector<double>();
  }

  if (n_tagD > 0) {
    tagD_indicators = std::vector<int>(n_tagD, 0);
  } else {
    tagD_indicators = std::vector<int>();
  }

  if (n_sigD > 0) {
    sigD_indicators = std::vector<int>(n_sigD, 0);
  } else {
    sigD_indicators = std::vector<int>();
  }

  if (n_tagDstar > 0) {
    tagDstar_indicators = std::vector<int>(n_tagDstar, 0);
  } else {
    tagDstar_indicators = std::vector<int>();
  }

  if (n_sigDstar > 0) {
    sigDstar_indicators = std::vector<int>(n_sigDstar, 0);
  } else {
    sigDstar_indicators = std::vector<int>();
  }

  ClearCache();
  ClearFeatures();
}

void YCandFeatureExtractor::ClearCache() {

  id = 0;
  truth_match = 0;

  tag_lp3 = 0;
  tag_cosBY = 0;
  tag_cosThetaDl = 0;
  sig_hp3 = 0;
  sig_vtxB = 0;
  mmiss_prime2 = 0;
  eextra50 = 0;
  tag_Dmass = 0;
  sig_Dmass = 0;
  sig_cosBY = 0;
  tag_deltaM = 0;
  tag_cosThetaDSoft = 0;
  tag_softP3MagCM = 0;
  sig_deltaM = 0;
  sig_cosThetaDSoft = 0;
  sig_softP3MagCM = 0;
  sig_hmass = 0;
  sig_vtxh = 0;

  tag_Dtype = 0;
  sig_Dtype = 0;
  tag_Dstartype = 0;
  sig_Dstartype = 0;

}

void YCandFeatureExtractor::ClearFeatures() {

  std::vector<double>::iterator it_double = numeric_features.begin();
  while (it_double != numeric_features.end()) {
    *it_double = 0;
    ++it_double;
  }

  std::vector<int>::iterator it_int; 

  it_int = tagD_indicators.begin();
  while (it_int != tagD_indicators.end()) {
    *it_int = 0;
    ++it_int;
  }

  it_int = sigD_indicators.begin();
  while (it_int != sigD_indicators.end()) {
    *it_int = 0;
    ++it_int;
  }

  it_int = tagDstar_indicators.begin();
  while (it_int != tagDstar_indicators.end()) {
    *it_int = 0;
    ++it_int;
  }

  it_int = sigDstar_indicators.begin();
  while (it_int != sigDstar_indicators.end()) {
    *it_int = 0;
    ++it_int;
  }

}

bool YCandFeatureExtractor::passed_selection() const {

  // tag_lp3
  if (
      (tag_lp3 < 0.6)
     ) {
    return false;
  }

  // cosBY
  if (
      (tag_cosBY < -5.0) ||
      (tag_cosBY > 1.5)
     ) {
    return false;
  }

  if (
      (sig_cosBY < -20.0)
     ) {
    return false;
  }

  // mmiss_prime2
  if (
      (mmiss_prime2 < -20.0) ||
      (mmiss_prime2 > 20.0)
     ) {
    return false;
  }

  // eextra50
  if (
      (eextra50 > 2.5)
     ) {
    return false;
  }

  return true;
}


void YCandFeatureExtractor::extract_features(const UpsilonCandidate &cand) {

  ClearCache(); 

  tag_lp3 = cand.get_tag_lp3();
  tag_cosBY = cand.get_tag_cosBY();
  tag_cosThetaDl = cand.get_tag_cosThetaDl();
  sig_hp3 = cand.get_sig_hp3();
  sig_vtxB = cand.get_sig_vtxB();
  mmiss_prime2 = cand.get_mmiss_prime2();
  eextra50 = cand.get_eextra50();
  tag_Dmass = cand.get_tag_Dmass();
  sig_Dmass = cand.get_sig_Dmass();
  sig_cosBY = cand.get_sig_cosBY();
  tag_deltaM = cand.get_tag_deltaM();
  tag_cosThetaDSoft = cand.get_tag_cosThetaDSoft();
  tag_softP3MagCM = cand.get_tag_softP3MagCM();
  sig_deltaM = cand.get_sig_deltaM();
  sig_cosThetaDSoft = cand.get_sig_cosThetaDSoft();
  sig_softP3MagCM = cand.get_sig_softP3MagCM();
  sig_hmass = cand.get_sig_hmass();
  sig_vtxh = cand.get_sig_vtxh();
  tag_Dtype = cand.get_tag_d_mode();
  tag_Dstartype = cand.get_tag_dstar_mode();
  sig_Dtype = cand.get_sig_d_mode();
  sig_Dstartype = cand.get_sig_dstar_mode();

  extract_features();
}

std::string YCandFeatureExtractor::get_libsvm_line() const {

  std::stringstream libsvm_line;
  if (truth_match) {
    libsvm_line << "1";
  } else {
    libsvm_line << "-1";
  }

  int feature_counter = 1;

  std::vector<double>::const_iterator it_double = numeric_features.begin();
  while (it_double != numeric_features.end()) {
    libsvm_line << " ";
    libsvm_line << feature_counter;
    libsvm_line << ":";
    libsvm_line << *it_double;
    ++feature_counter;
    ++it_double;
  }


  std::vector<int>::const_iterator it_int;

  it_int = tagD_indicators.begin();
  while (it_int != tagD_indicators.end()) {
    libsvm_line << " ";
    libsvm_line << feature_counter;
    libsvm_line << ":";
    libsvm_line << *it_int;
    ++feature_counter;
    ++it_int;
  }

  it_int = sigD_indicators.begin();
  while (it_int != sigD_indicators.end()) {
    libsvm_line << " ";
    libsvm_line << feature_counter;
    libsvm_line << ":";
    libsvm_line << *it_int;
    ++feature_counter;
    ++it_int;
  }

  it_int = tagDstar_indicators.begin();
  while (it_int != tagDstar_indicators.end()) {
    libsvm_line << " ";
    libsvm_line << feature_counter;
    libsvm_line << ":";
    libsvm_line << *it_int;
    ++feature_counter;
    ++it_int;
  }

  it_int = sigDstar_indicators.begin();
  while (it_int != sigDstar_indicators.end()) {
    libsvm_line << " ";
    libsvm_line << feature_counter;
    libsvm_line << ":";
    libsvm_line << *it_int;
    ++feature_counter;
    ++it_int;
  }

  return libsvm_line.str();
}

void DDpiFeatureExtractor::extract_features() {

  ClearFeatures(); 

  numeric_features[0] = tag_lp3;
  numeric_features[1] = tag_cosBY;
  numeric_features[2] = tag_cosThetaDl;
  numeric_features[3] = sig_hp3;
  numeric_features[4] = sig_vtxB;
  numeric_features[5] = mmiss_prime2;
  numeric_features[6] = eextra50;
  numeric_features[7] = tag_Dmass;
  numeric_features[8] = sig_Dmass;

  switch (tag_Dtype) {
    case bdtaunu::kDc_Kpipi:
      tagD_indicators[0] = 1;
      break;
    case bdtaunu::kDc_Kpipipi0:
      tagD_indicators[1] = 1; 
      break;
    case bdtaunu::kDc_KsK:
      tagD_indicators[2] = 1;
      break;
    case bdtaunu::kDc_Kspi:
      tagD_indicators[2] = 2;
      break;
    case bdtaunu::kDc_Kspipi0:
      tagD_indicators[3] = 1;
      break;
    case bdtaunu::kDc_Kspipipi:
      // do nothing
      break;
    case bdtaunu::kDc_KKpi:
      tagD_indicators[4] = 1;
      break;
    case bdtaunu::kD0_Kpi:
      tagD_indicators[5] = 1;
      break;
    case bdtaunu::kD0_Kpipi0:
      tagD_indicators[6] = 1;
      break;
    case bdtaunu::kD0_Kpipipi:
      tagD_indicators[7] = 1;
      break;
    case bdtaunu::kD0_Kpipipipi0:
      // do nothing
      break;
    case bdtaunu::kD0_Kspipi:
      tagD_indicators[8] = 1;
      break;
    case bdtaunu::kD0_Kspipipi0:
      tagD_indicators[8] = 2;
      break;
    case bdtaunu::kD0_Kspi0:
      tagD_indicators[8] = 3;
      break;
    case bdtaunu::kD0_KK:
      tagD_indicators[9] = 1;
      break;
  }

  switch (sig_Dtype) {
    case bdtaunu::kDc_Kpipi:
      sigD_indicators[0] = 1;
      break;
    case bdtaunu::kDc_Kpipipi0:
      sigD_indicators[1] = 1; 
      break;
    case bdtaunu::kDc_KsK:
      sigD_indicators[2] = 1;
      break;
    case bdtaunu::kDc_Kspi:
      sigD_indicators[2] = 2;
      break;
    case bdtaunu::kDc_Kspipi0:
      sigD_indicators[2] = 3;
      break;
    case bdtaunu::kDc_Kspipipi:
      // do nothing
      break;
    case bdtaunu::kDc_KKpi:
      sigD_indicators[3] = 1;
      break;
    case bdtaunu::kD0_Kpi:
      sigD_indicators[4] = 1;
      break;
    case bdtaunu::kD0_Kpipi0:
      sigD_indicators[5] = 1;
      break;
    case bdtaunu::kD0_Kpipipi:
      sigD_indicators[6] = 1;
      break;
    case bdtaunu::kD0_Kpipipipi0:
      // do nothing
      break;
    case bdtaunu::kD0_Kspipi:
      sigD_indicators[7] = 1;
      break;
    case bdtaunu::kD0_Kspipipi0:
      sigD_indicators[7] = 2;
      break;
    case bdtaunu::kD0_Kspi0:
      sigD_indicators[7] = 3;
      break;
    case bdtaunu::kD0_KK:
      sigD_indicators[8] = 1;
      break;
  }

  return;
}

bool DDpiFeatureExtractor::passed_selection() const {

  if (!YCandFeatureExtractor::passed_selection()) {
    return false;
  }

  // tag_Dmass
  if (
      (tag_Dmass < 1.84) ||
      (tag_Dmass > 1.9)
     ) {
    return false;
  }

  // sig_Dmass
  if (
        (sig_Dmass < 1.84) ||
        (sig_Dmass > 1.9)
       ) {
      return false;
  }

  // tag_Dtype
  if (
      (sig_Dtype == bdtaunu::kDc_Kspipipi) ||
      (tag_Dtype == bdtaunu::kD0_Kpipipipi0)
     ) {
    return false;
  }

  // sig_Dtype
  if (
      (sig_Dtype == bdtaunu::kDc_Kspipipi) ||
      (sig_Dtype == bdtaunu::kD0_Kpipipipi0)
     ) {
    return false;
  }

  return true;
}

void DDstarpiFeatureExtractor::extract_features() {

  ClearFeatures(); 

  numeric_features[0] = tag_lp3;
  numeric_features[1] = tag_cosBY;
  numeric_features[2] = tag_cosThetaDl;
  numeric_features[3] = sig_hp3;
  numeric_features[4] = sig_vtxB;
  numeric_features[5] = mmiss_prime2;
  numeric_features[6] = eextra50;
  numeric_features[7] = tag_Dmass;
  numeric_features[8] = sig_deltaM;
  numeric_features[9] = sig_cosThetaDSoft;
  numeric_features[10] = sig_softP3MagCM;

  switch (tag_Dtype) {
    case bdtaunu::kDc_Kpipi:
      tagD_indicators[0] = 1;
      break;
    case bdtaunu::kDc_Kpipipi0:
      tagD_indicators[1] = 1; 
      break;
    case bdtaunu::kDc_KsK:
      tagD_indicators[2] = 1;
      break;
    case bdtaunu::kDc_Kspi:
      tagD_indicators[2] = 2;
      break;
    case bdtaunu::kDc_Kspipi0:
      tagD_indicators[2] = 3;
      break;
    case bdtaunu::kDc_Kspipipi:
      // do nothing
      break;
    case bdtaunu::kDc_KKpi:
      tagD_indicators[3] = 1;
      break;
    case bdtaunu::kD0_Kpi:
      tagD_indicators[4] = 1;
      break;
    case bdtaunu::kD0_Kpipi0:
      tagD_indicators[5] = 1;
      break;
    case bdtaunu::kD0_Kpipipi:
      tagD_indicators[6] = 1;
      break;
    case bdtaunu::kD0_Kpipipipi0:
      // do nothing
      break;
    case bdtaunu::kD0_Kspipi:
      tagD_indicators[7] = 1;
      break;
    case bdtaunu::kD0_Kspipipi0:
      tagD_indicators[7] = 2;
      break;
    case bdtaunu::kD0_Kspi0:
      tagD_indicators[7] = 3;
      break;
    case bdtaunu::kD0_KK:
      tagD_indicators[8] = 1;
      break;
  }

  switch (sig_Dtype) {
    case bdtaunu::kDc_Kpipi:
      sigD_indicators[0] = 1;
      break;
    case bdtaunu::kDc_Kpipipi0:
      sigD_indicators[1] = 1; 
      break;
    case bdtaunu::kDc_KsK:
      // do nothing
      break;
    case bdtaunu::kDc_Kspi:
      // do nothing
      break;
    case bdtaunu::kDc_Kspipi0:
      // do nothing
      break;
    case bdtaunu::kDc_Kspipipi:
      // do nothing
      break;
    case bdtaunu::kDc_KKpi:
      // do nothing
      break;
    case bdtaunu::kD0_Kpi:
      sigD_indicators[2] = 1;
      break;
    case bdtaunu::kD0_Kpipi0:
      sigD_indicators[3] = 1;
      break;
    case bdtaunu::kD0_Kpipipi:
      sigD_indicators[4] = 1;
      break;
    case bdtaunu::kD0_Kpipipipi0:
      // do nothing
      break;
    case bdtaunu::kD0_Kspipi:
      sigD_indicators[5] = 1;
      break;
    case bdtaunu::kD0_Kspipipi0:
      sigD_indicators[5] = 2;
      break;
    case bdtaunu::kD0_Kspi0:
      sigD_indicators[5] = 3;
      break;
    case bdtaunu::kD0_KK:
      sigD_indicators[6] = 1;
      break;
  }

  switch (sig_Dstartype) {
    case bdtaunu::kDstar0_D0pi0:
      sigDstar_indicators[0] = 1;
      break;
    case bdtaunu::kDstar0_D0gamma:
      sigDstar_indicators[1] = 1;
      break;
    case bdtaunu::kDstarc_D0pi:
      sigDstar_indicators[2] = 1;
      break;
    case bdtaunu::kDstarc_Dcpi0:
      sigDstar_indicators[3] = 1;
      break;
    case bdtaunu::kDstarc_Dcgamma:
      // do nothing
      break;
  }

  return;
}

bool DDstarpiFeatureExtractor::passed_selection() const {

  if (!YCandFeatureExtractor::passed_selection()) {
    return false;
  }

  // tag_Dmass
  if (
      (tag_Dmass < 1.84) ||
      (tag_Dmass > 1.9) 
     ) {
    return false;
  }

  // deltaM
  if (sig_Dstartype == bdtaunu::kDstar0_D0pi0) {
    if (
        (sig_deltaM < 0.135) ||
        (sig_deltaM > 0.15)
       ) {
      return false;
    }
  }

  if (sig_Dstartype == bdtaunu::kDstar0_D0gamma) {
    if (
        (sig_deltaM < 0.13) ||
        (sig_deltaM > 0.155)
       ) {
      return false;
    }
  }

  if (sig_Dstartype == bdtaunu::kDstarc_D0pi) {
    if (
        (sig_deltaM < 0.14) ||
        (sig_deltaM > 0.15)
       ) {
      return false;
    }
  }

  if (sig_Dstartype == bdtaunu::kDstarc_Dcpi0) {
    if (
        (sig_deltaM < 0.1375) ||
        (sig_deltaM > 0.145)
       ) {
      return false;
    }
  }

  // tag_Dtype
  if (
      (tag_Dtype == bdtaunu::kDc_Kspipipi) ||
      (tag_Dtype == bdtaunu::kD0_Kpipipipi0)
     ) {
    return false;
  }

  // sig_Dtype
  if (
      (sig_Dtype == bdtaunu::kDc_KsK) ||
      (sig_Dtype == bdtaunu::kDc_Kspi) ||
      (sig_Dtype == bdtaunu::kDc_Kspipi0) ||
      (sig_Dtype == bdtaunu::kDc_Kspipipi) ||
      (sig_Dtype == bdtaunu::kDc_KKpi) ||
      (sig_Dtype == bdtaunu::kD0_Kpipipipi0)
     ) {
    return false;
  }

  // sig_Dstartype
  if (
      (sig_Dstartype == bdtaunu::kDstarc_Dcgamma)
     ) {
    return false;
  }

  return true;
}


void DstarDpiFeatureExtractor::extract_features() {

  ClearFeatures(); 

  numeric_features[0] = tag_lp3;
  numeric_features[1] = tag_cosBY;
  numeric_features[2] = tag_cosThetaDl;
  numeric_features[3] = sig_hp3;
  numeric_features[4] = sig_vtxB;
  numeric_features[5] = mmiss_prime2;
  numeric_features[6] = eextra50;
  numeric_features[7] = tag_deltaM;
  numeric_features[8] = tag_cosThetaDSoft;
  numeric_features[9] = tag_softP3MagCM;
  numeric_features[10] = sig_Dmass;

  switch (tag_Dtype) {
    case bdtaunu::kDc_Kpipi:
      tagD_indicators[0] = 1;
      break;
    case bdtaunu::kDc_Kpipipi0:
      tagD_indicators[1] = 1; 
      break;
    case bdtaunu::kDc_KsK:
      tagD_indicators[2] = 1;
      break;
    case bdtaunu::kDc_Kspi:
      tagD_indicators[2] = 2;
      break;
    case bdtaunu::kDc_Kspipi0:
      tagD_indicators[2] = 3;
      break;
    case bdtaunu::kDc_Kspipipi:
      // do nothing
      break;
    case bdtaunu::kDc_KKpi:
      tagD_indicators[3] = 1;
      break;
    case bdtaunu::kD0_Kpi:
      tagD_indicators[4] = 1;
      break;
    case bdtaunu::kD0_Kpipi0:
      tagD_indicators[5] = 1;
      break;
    case bdtaunu::kD0_Kpipipi:
      tagD_indicators[6] = 1;
      break;
    case bdtaunu::kD0_Kpipipipi0:
      // do nothing
      break;
    case bdtaunu::kD0_Kspipi:
      tagD_indicators[7] = 1;
      break;
    case bdtaunu::kD0_Kspipipi0:
      tagD_indicators[7] = 2;
      break;
    case bdtaunu::kD0_Kspi0:
      tagD_indicators[7] = 3;
      break;
    case bdtaunu::kD0_KK:
      tagD_indicators[8] = 1;
      break;
  }

  switch (sig_Dtype) {
    case bdtaunu::kDc_Kpipi:
      sigD_indicators[0] = 1;
      break;
    case bdtaunu::kDc_Kpipipi0:
      sigD_indicators[1] = 1; 
      break;
    case bdtaunu::kDc_KsK:
      sigD_indicators[2] = 1;
      break;
    case bdtaunu::kDc_Kspi:
      sigD_indicators[2] = 2;
      break;
    case bdtaunu::kDc_Kspipi0:
      sigD_indicators[2] = 3;
      break;
    case bdtaunu::kDc_Kspipipi:
      // do nothing
      break;
    case bdtaunu::kDc_KKpi:
      sigD_indicators[3] = 1;
      break;
    case bdtaunu::kD0_Kpi:
      sigD_indicators[4] = 1;
      break;
    case bdtaunu::kD0_Kpipi0:
      sigD_indicators[5] = 1;
      break;
    case bdtaunu::kD0_Kpipipi:
      sigD_indicators[6] = 1;
      break;
    case bdtaunu::kD0_Kpipipipi0:
      // do nothing
      break;
    case bdtaunu::kD0_Kspipi:
      sigD_indicators[7] = 1;
      break;
    case bdtaunu::kD0_Kspipipi0:
      sigD_indicators[7] = 2;
      break;
    case bdtaunu::kD0_Kspi0:
      sigD_indicators[7] = 3;
      break;
    case bdtaunu::kD0_KK:
      sigD_indicators[8] = 1;
      break;
  }

  switch (tag_Dstartype) {
    case bdtaunu::kDstar0_D0pi0:
      tagDstar_indicators[0] = 1;
      break;
    case bdtaunu::kDstar0_D0gamma:
      tagDstar_indicators[1] = 1;
      break;
    case bdtaunu::kDstarc_D0pi:
      tagDstar_indicators[2] = 1;
      break;
    case bdtaunu::kDstarc_Dcpi0:
      tagDstar_indicators[3] = 1;
      break;
    case bdtaunu::kDstarc_Dcgamma:
      // do nothing
      break;
  }

  return;
}

bool DstarDpiFeatureExtractor::passed_selection() const {

  if (!YCandFeatureExtractor::passed_selection()) {
    return false;
  }

  // tag_deltaM
  if (tag_Dstartype == bdtaunu::kDstar0_D0pi0) {
    if (
        (tag_deltaM < 0.1375) ||
        (tag_deltaM > 0.1475)
       ) {
      return false;
    }
  }

  if (tag_Dstartype == bdtaunu::kDstar0_D0gamma) {
    if (
        (tag_deltaM < 0.13) ||
        (tag_deltaM > 0.155)
       ) {
      return false;
    }
  }

  if (tag_Dstartype == bdtaunu::kDstarc_D0pi) {
    if (
        (tag_deltaM < 0.1425) ||
        (tag_deltaM > 0.1490)
       ) {
      return false;
    }
  }

  if (tag_Dstartype == bdtaunu::kDstarc_Dcpi0) {
    if (
        (tag_deltaM < 0.1375) ||
        (tag_deltaM > 0.145)
       ) {
      return false;
    }
  }

  // sig_Dmass
  if (
      (sig_Dmass < 1.84) ||
      (sig_Dmass > 1.9)
     ) {
    return false;
  }

  // tag_Dtype
  if (
      (tag_Dtype == bdtaunu::kDc_Kspipipi) ||
      (tag_Dtype == bdtaunu::kD0_Kpipipipi0)
     ) {
    return false;
  }

  // tag_Dstartype
  if (
      (tag_Dstartype == bdtaunu::kDstarc_Dcgamma)
     ) {
    return false;
  }

  // sig_Dtype
  if (
      (sig_Dtype == bdtaunu::kDc_Kspipipi) ||
      (sig_Dtype == bdtaunu::kD0_Kpipipipi0)
     ) {
    return false;
  }

  return true;
}


void DstarDstarpiFeatureExtractor::extract_features() {

  ClearFeatures(); 

  numeric_features[0] = tag_lp3;
  numeric_features[1] = tag_cosBY;
  numeric_features[2] = tag_cosThetaDl;
  numeric_features[3] = sig_hp3;
  numeric_features[4] = sig_vtxB;
  numeric_features[5] = mmiss_prime2;
  numeric_features[6] = eextra50;
  numeric_features[7] = tag_deltaM;
  numeric_features[8] = tag_cosThetaDSoft;
  numeric_features[9] = tag_softP3MagCM;
  numeric_features[10] = sig_deltaM;
  numeric_features[11] = sig_cosThetaDSoft;
  numeric_features[12] = sig_softP3MagCM;

  switch (tag_Dtype) {
    case bdtaunu::kDc_Kpipi:
      tagD_indicators[0] = 1;
      break;
    case bdtaunu::kDc_Kpipipi0:
      tagD_indicators[1] = 1; 
      break;
    case bdtaunu::kDc_KsK:
      tagD_indicators[2] = 1;
      break;
    case bdtaunu::kDc_Kspi:
      tagD_indicators[2] = 2;
      break;
    case bdtaunu::kDc_Kspipi0:
      tagD_indicators[2] = 3;
      break;
    case bdtaunu::kDc_Kspipipi:
      // do nothing
      break;
    case bdtaunu::kDc_KKpi:
      tagD_indicators[3] = 1;
      break;
    case bdtaunu::kD0_Kpi:
      tagD_indicators[4] = 1;
      break;
    case bdtaunu::kD0_Kpipi0:
      tagD_indicators[5] = 1;
      break;
    case bdtaunu::kD0_Kpipipi:
      tagD_indicators[6] = 1;
      break;
    case bdtaunu::kD0_Kpipipipi0:
      tagD_indicators[7] = 1;
      break;
    case bdtaunu::kD0_Kspipi:
      tagD_indicators[8] = 1;
      break;
    case bdtaunu::kD0_Kspipipi0:
      tagD_indicators[9] = 1;
      break;
    case bdtaunu::kD0_Kspi0:
      tagD_indicators[10] = 1;
      break;
    case bdtaunu::kD0_KK:
      tagD_indicators[11] = 1;
      break;
  }

  switch (sig_Dtype) {
    case bdtaunu::kDc_Kpipi:
      sigD_indicators[0] = 1;
      break;
    case bdtaunu::kDc_Kpipipi0:
      sigD_indicators[1] = 1; 
      break;
    case bdtaunu::kDc_KsK:
      sigD_indicators[2] = 1;
      break;
    case bdtaunu::kDc_Kspi:
      sigD_indicators[2] = 2;
      break;
    case bdtaunu::kDc_Kspipi0:
      sigD_indicators[2] = 3;
      break;
    case bdtaunu::kDc_Kspipipi:
      // do nothing
      break;
    case bdtaunu::kDc_KKpi:
      sigD_indicators[2] = 4;
      break;
    case bdtaunu::kD0_Kpi:
      sigD_indicators[3] = 1;
      break;
    case bdtaunu::kD0_Kpipi0:
      sigD_indicators[4] = 1;
      break;
    case bdtaunu::kD0_Kpipipi:
      sigD_indicators[5] = 1;
      break;
    case bdtaunu::kD0_Kpipipipi0:
      sigD_indicators[6] = 1;
      break;
    case bdtaunu::kD0_Kspipi:
      sigD_indicators[7] = 1;
      break;
    case bdtaunu::kD0_Kspipipi0:
      sigD_indicators[7] = 2;
      break;
    case bdtaunu::kD0_Kspi0:
      sigD_indicators[7] = 3;
      break;
    case bdtaunu::kD0_KK:
      sigD_indicators[8] = 1;
      break;
  }

  switch (tag_Dstartype) {
    case bdtaunu::kDstar0_D0pi0:
      tagDstar_indicators[0] = 1;
      break;
    case bdtaunu::kDstar0_D0gamma:
      tagDstar_indicators[1] = 1;
      break;
    case bdtaunu::kDstarc_D0pi:
      tagDstar_indicators[2] = 1;
      break;
    case bdtaunu::kDstarc_Dcpi0:
      tagDstar_indicators[3] = 1;
      break;
    case bdtaunu::kDstarc_Dcgamma:
      // do nothing
      break;
  }

  switch (sig_Dstartype) {
    case bdtaunu::kDstar0_D0pi0:
      sigDstar_indicators[0] = 1;
      break;
    case bdtaunu::kDstar0_D0gamma:
      sigDstar_indicators[1] = 1;
      break;
    case bdtaunu::kDstarc_D0pi:
      sigDstar_indicators[2] = 1;
      break;
    case bdtaunu::kDstarc_Dcpi0:
      sigDstar_indicators[3] = 1;
      break;
    case bdtaunu::kDstarc_Dcgamma:
      // do nothing
      break;
  }

  return;
}

bool DstarDstarpiFeatureExtractor::passed_selection() const {

  if (!YCandFeatureExtractor::passed_selection()) {
    return false;
  }

  // tag_deltaM
  if (tag_Dstartype == bdtaunu::kDstar0_D0pi0) {
    if (
        (tag_deltaM < 0.1375) ||
        (tag_deltaM > 0.1475)
       ) {
      return false;
    }
  }

  if (tag_Dstartype == bdtaunu::kDstar0_D0gamma) {
    if (
        (tag_deltaM < 0.13) ||
        (tag_deltaM > 0.155)
       ) {
      return false;
    }
  }

  if (tag_Dstartype == bdtaunu::kDstarc_D0pi) {
    if (
        (tag_deltaM < 0.1425) ||
        (tag_deltaM > 0.1490)
       ) {
      return false;
    }
  }

  if (tag_Dstartype == bdtaunu::kDstarc_Dcpi0) {
    if (
        (tag_deltaM < 0.1375) ||
        (tag_deltaM > 0.145)
       ) {
      return false;
    }
  }

  // sig_deltaM
  if (sig_Dstartype == bdtaunu::kDstar0_D0pi0) {
    if (
        (sig_deltaM < 0.135) ||
        (sig_deltaM > 0.15)
       ) {
      return false;
    }
  }

  if (sig_Dstartype == bdtaunu::kDstar0_D0gamma) {
    if (
        (sig_deltaM < 0.13) ||
        (sig_deltaM > 0.155)
       ) {
      return false;
    }
  }

  if (sig_Dstartype == bdtaunu::kDstarc_D0pi) {
    if (
        (sig_deltaM < 0.14) ||
        (sig_deltaM > 0.15)
       ) {
      return false;
    }
  }

  if (sig_Dstartype == bdtaunu::kDstarc_Dcpi0) {
    if (
        (sig_deltaM < 0.1375) ||
        (sig_deltaM > 0.145)
       ) {
      return false;
    }
  }

  // tag_Dtype
  if (
      (tag_Dtype == bdtaunu::kDc_Kspipipi)
     ) {
    return false;
  }

  // tag_Dstartype
  if (
      (tag_Dstartype == bdtaunu::kDstarc_Dcgamma)
     ) {
    return false;
  }

  // sig_Dtype
  if (
      (sig_Dtype == bdtaunu::kDc_Kspipipi)
     ) {
    return false;
  }

  // sig_Dstartype
  if (
      (sig_Dstartype == bdtaunu::kDstarc_Dcgamma)
     ) {
    return false;
  }

  return true;
}


void DDrhoFeatureExtractor::extract_features() {

  ClearFeatures(); 

  numeric_features[0] = tag_lp3;
  numeric_features[1] = tag_cosBY;
  numeric_features[2] = tag_cosThetaDl;
  numeric_features[3] = sig_hp3;
  numeric_features[4] = sig_vtxB;
  numeric_features[5] = mmiss_prime2;
  numeric_features[6] = eextra50;
  numeric_features[7] = tag_Dmass;
  numeric_features[8] = sig_Dmass;
  numeric_features[9] = sig_hmass;
  numeric_features[10] = sig_vtxh;

  switch (tag_Dtype) {
    case bdtaunu::kDc_Kpipi:
      tagD_indicators[0] = 1;
      break;
    case bdtaunu::kDc_Kpipipi0:
      tagD_indicators[1] = 1; 
      break;
    case bdtaunu::kDc_KsK:
      tagD_indicators[2] = 1;
      break;
    case bdtaunu::kDc_Kspi:
      tagD_indicators[2] = 2;
      break;
    case bdtaunu::kDc_Kspipi0:
      tagD_indicators[3] = 1;
      break;
    case bdtaunu::kDc_Kspipipi:
      // do nothing
      break;
    case bdtaunu::kDc_KKpi:
      tagD_indicators[4] = 1;
      break;
    case bdtaunu::kD0_Kpi:
      tagD_indicators[5] = 1;
      break;
    case bdtaunu::kD0_Kpipi0:
      tagD_indicators[6] = 1;
      break;
    case bdtaunu::kD0_Kpipipi:
      tagD_indicators[7] = 1;
      break;
    case bdtaunu::kD0_Kpipipipi0:
      // do nothing
      break;
    case bdtaunu::kD0_Kspipi:
      tagD_indicators[8] = 1;
      break;
    case bdtaunu::kD0_Kspipipi0:
      tagD_indicators[8] = 2;
      break;
    case bdtaunu::kD0_Kspi0:
      tagD_indicators[8] = 3;
      break;
    case bdtaunu::kD0_KK:
      tagD_indicators[9] = 1;
      break;
  }

  switch (sig_Dtype) {
    case bdtaunu::kDc_Kpipi:
      sigD_indicators[0] = 1;
      break;
    case bdtaunu::kDc_Kpipipi0:
      sigD_indicators[1] = 1; 
      break;
    case bdtaunu::kDc_KsK:
      sigD_indicators[2] = 1;
      break;
    case bdtaunu::kDc_Kspi:
      sigD_indicators[2] = 2;
      break;
    case bdtaunu::kDc_Kspipi0:
      sigD_indicators[2] = 3;
      break;
    case bdtaunu::kDc_Kspipipi:
      // do nothing
      break;
    case bdtaunu::kDc_KKpi:
      sigD_indicators[3] = 1;
      break;
    case bdtaunu::kD0_Kpi:
      sigD_indicators[4] = 1;
      break;
    case bdtaunu::kD0_Kpipi0:
      sigD_indicators[5] = 1;
      break;
    case bdtaunu::kD0_Kpipipi:
      sigD_indicators[6] = 1;
      break;
    case bdtaunu::kD0_Kpipipipi0:
      // do nothing
      break;
    case bdtaunu::kD0_Kspipi:
      sigD_indicators[7] = 1;
      break;
    case bdtaunu::kD0_Kspipipi0:
      sigD_indicators[7] = 2;
      break;
    case bdtaunu::kD0_Kspi0:
      sigD_indicators[7] = 3;
      break;
    case bdtaunu::kD0_KK:
      sigD_indicators[8] = 1;
      break;
  }

  return;
}

bool DDrhoFeatureExtractor::passed_selection() const {

  if (!YCandFeatureExtractor::passed_selection()) {
    return false;
  }

  // tag_Dmass
  if (
      (tag_Dmass < 1.84) ||
      (tag_Dmass > 1.9)
     ) {
    return false;
  }

  // sig_Dmass
  if (
        (sig_Dmass < 1.84) ||
        (sig_Dmass > 1.9)
       ) {
      return false;
  }

  // tag_Dtype
  if (
      (sig_Dtype == bdtaunu::kDc_Kspipipi) ||
      (tag_Dtype == bdtaunu::kD0_Kpipipipi0)
     ) {
    return false;
  }

  // sig_Dtype
  if (
      (sig_Dtype == bdtaunu::kDc_Kspipipi) ||
      (sig_Dtype == bdtaunu::kD0_Kpipipipi0)
     ) {
    return false;
  }

  return true;
}


void DDstarrhoFeatureExtractor::extract_features() {

  ClearFeatures(); 

  numeric_features[0] = tag_lp3;
  numeric_features[1] = tag_cosBY;
  numeric_features[2] = tag_cosThetaDl;
  numeric_features[3] = sig_hp3;
  numeric_features[4] = sig_vtxB;
  numeric_features[5] = mmiss_prime2;
  numeric_features[6] = eextra50;
  numeric_features[7] = tag_Dmass;
  numeric_features[8] = sig_deltaM;
  numeric_features[9] = sig_cosThetaDSoft;
  numeric_features[10] = sig_softP3MagCM;
  numeric_features[11] = sig_hmass;
  numeric_features[12] = sig_vtxh;

  switch (tag_Dtype) {
    case bdtaunu::kDc_Kpipi:
      tagD_indicators[0] = 1;
      break;
    case bdtaunu::kDc_Kpipipi0:
      tagD_indicators[1] = 1; 
      break;
    case bdtaunu::kDc_KsK:
      tagD_indicators[2] = 1;
      break;
    case bdtaunu::kDc_Kspi:
      tagD_indicators[2] = 2;
      break;
    case bdtaunu::kDc_Kspipi0:
      tagD_indicators[2] = 3;
      break;
    case bdtaunu::kDc_Kspipipi:
      // do nothing
      break;
    case bdtaunu::kDc_KKpi:
      tagD_indicators[2] = 4;
      break;
    case bdtaunu::kD0_Kpi:
      tagD_indicators[3] = 1;
      break;
    case bdtaunu::kD0_Kpipi0:
      tagD_indicators[4] = 1;
      break;
    case bdtaunu::kD0_Kpipipi:
      tagD_indicators[5] = 1;
      break;
    case bdtaunu::kD0_Kpipipipi0:
      tagD_indicators[6] = 1;
      break;
    case bdtaunu::kD0_Kspipi:
      tagD_indicators[7] = 1;
      break;
    case bdtaunu::kD0_Kspipipi0:
      tagD_indicators[7] = 2;
      break;
    case bdtaunu::kD0_Kspi0:
      tagD_indicators[7] = 3;
      break;
    case bdtaunu::kD0_KK:
      tagD_indicators[8] = 1;
      break;
  }

  switch (sig_Dtype) {
    case bdtaunu::kDc_Kpipi:
      sigD_indicators[0] = 1;
      break;
    case bdtaunu::kDc_Kpipipi0:
      sigD_indicators[1] = 1; 
      break;
    case bdtaunu::kDc_KsK:
      sigD_indicators[2] = 1;
      break;
    case bdtaunu::kDc_Kspi:
      sigD_indicators[2] = 2;
      break;
    case bdtaunu::kDc_Kspipi0:
      sigD_indicators[2] = 3;
      break;
    case bdtaunu::kDc_Kspipipi:
      // do nothing
      break;
    case bdtaunu::kDc_KKpi:
      sigD_indicators[2] = 4;
      break;
    case bdtaunu::kD0_Kpi:
      sigD_indicators[3] = 1;
      break;
    case bdtaunu::kD0_Kpipi0:
      sigD_indicators[4] = 1;
      break;
    case bdtaunu::kD0_Kpipipi:
      sigD_indicators[5] = 1;
      break;
    case bdtaunu::kD0_Kpipipipi0:
      sigD_indicators[6] = 1;
      break;
    case bdtaunu::kD0_Kspipi:
      sigD_indicators[7] = 1;
      break;
    case bdtaunu::kD0_Kspipipi0:
      sigD_indicators[7] = 2;
      break;
    case bdtaunu::kD0_Kspi0:
      sigD_indicators[7] = 3;
      break;
    case bdtaunu::kD0_KK:
      sigD_indicators[8] = 1;
      break;
  }

  switch (sig_Dstartype) {
    case bdtaunu::kDstar0_D0pi0:
      sigDstar_indicators[0] = 1;
      break;
    case bdtaunu::kDstar0_D0gamma:
      sigDstar_indicators[1] = 1;
      break;
    case bdtaunu::kDstarc_D0pi:
      sigDstar_indicators[2] = 1;
      break;
    case bdtaunu::kDstarc_Dcpi0:
      sigDstar_indicators[3] = 1;
      break;
    case bdtaunu::kDstarc_Dcgamma:
      // do nothing
      break;
  }

  return;
}

bool DDstarrhoFeatureExtractor::passed_selection() const {

  if (!YCandFeatureExtractor::passed_selection()) {
    return false;
  }

  // tag_Dmass
  if (
      (tag_Dmass < 1.84) ||
      (tag_Dmass > 1.9) 
     ) {
    return false;
  }

  // deltaM
  if (sig_Dstartype == bdtaunu::kDstar0_D0pi0) {
    if (
        (sig_deltaM < 0.135) ||
        (sig_deltaM > 0.15)
       ) {
      return false;
    }
  }

  if (sig_Dstartype == bdtaunu::kDstar0_D0gamma) {
    if (
        (sig_deltaM < 0.13) ||
        (sig_deltaM > 0.155)
       ) {
      return false;
    }
  }

  if (sig_Dstartype == bdtaunu::kDstarc_D0pi) {
    if (
        (sig_deltaM < 0.14) ||
        (sig_deltaM > 0.15)
       ) {
      return false;
    }
  }

  if (sig_Dstartype == bdtaunu::kDstarc_Dcpi0) {
    if (
        (sig_deltaM < 0.1375) ||
        (sig_deltaM > 0.145)
       ) {
      return false;
    }
  }

  // tag_Dtype
  if (
      (tag_Dtype == bdtaunu::kDc_Kspipipi)
     ) {
    return false;
  }

  // sig_Dtype
  if (
      (sig_Dtype == bdtaunu::kDc_Kspipipi)
     ) {
    return false;
  }

  // sig_Dstartype
  if (
      (sig_Dstartype == bdtaunu::kDstarc_Dcgamma)
     ) {
    return false;
  }


  return true;
}


void DstarDrhoFeatureExtractor::extract_features() {

  ClearFeatures(); 

  numeric_features[0] = tag_lp3;
  numeric_features[1] = tag_cosBY;
  numeric_features[2] = tag_cosThetaDl;
  numeric_features[3] = sig_hp3;
  numeric_features[4] = sig_vtxB;
  numeric_features[5] = mmiss_prime2;
  numeric_features[6] = eextra50;
  numeric_features[7] = tag_deltaM;
  numeric_features[8] = tag_cosThetaDSoft;
  numeric_features[9] = tag_softP3MagCM;
  numeric_features[10] = sig_Dmass;
  numeric_features[11] = sig_hmass;
  numeric_features[12] = sig_vtxh;

  switch (tag_Dtype) {
    case bdtaunu::kDc_Kpipi:
      tagD_indicators[0] = 1;
      break;
    case bdtaunu::kDc_Kpipipi0:
      tagD_indicators[1] = 1; 
      break;
    case bdtaunu::kDc_KsK:
      tagD_indicators[2] = 1;
      break;
    case bdtaunu::kDc_Kspi:
      tagD_indicators[2] = 2;
      break;
    case bdtaunu::kDc_Kspipi0:
      tagD_indicators[2] = 3;
      break;
    case bdtaunu::kDc_Kspipipi:
      // do nothing
      break;
    case bdtaunu::kDc_KKpi:
      tagD_indicators[2] = 4;
      break;
    case bdtaunu::kD0_Kpi:
      tagD_indicators[3] = 1;
      break;
    case bdtaunu::kD0_Kpipi0:
      tagD_indicators[4] = 1;
      break;
    case bdtaunu::kD0_Kpipipi:
      tagD_indicators[5] = 1;
      break;
    case bdtaunu::kD0_Kpipipipi0:
      tagD_indicators[6] = 1;
      break;
    case bdtaunu::kD0_Kspipi:
      tagD_indicators[7] = 1;
      break;
    case bdtaunu::kD0_Kspipipi0:
      tagD_indicators[7] = 2;
      break;
    case bdtaunu::kD0_Kspi0:
      tagD_indicators[7] = 3;
      break;
    case bdtaunu::kD0_KK:
      tagD_indicators[8] = 1;
      break;
  }

  switch (sig_Dtype) {
    case bdtaunu::kDc_Kpipi:
      sigD_indicators[0] = 1;
      break;
    case bdtaunu::kDc_Kpipipi0:
      sigD_indicators[1] = 1; 
      break;
    case bdtaunu::kDc_KsK:
      sigD_indicators[2] = 1;
      break;
    case bdtaunu::kDc_Kspi:
      sigD_indicators[2] = 2;
      break;
    case bdtaunu::kDc_Kspipi0:
      sigD_indicators[2] = 3;
      break;
    case bdtaunu::kDc_Kspipipi:
      // do nothing
      break;
    case bdtaunu::kDc_KKpi:
      sigD_indicators[3] = 1;
      break;
    case bdtaunu::kD0_Kpi:
      sigD_indicators[4] = 1;
      break;
    case bdtaunu::kD0_Kpipi0:
      sigD_indicators[5] = 1;
      break;
    case bdtaunu::kD0_Kpipipi:
      sigD_indicators[6] = 1;
      break;
    case bdtaunu::kD0_Kpipipipi0:
      // do nothing
      break;
    case bdtaunu::kD0_Kspipi:
      sigD_indicators[7] = 1;
      break;
    case bdtaunu::kD0_Kspipipi0:
      sigD_indicators[7] = 2;
      break;
    case bdtaunu::kD0_Kspi0:
      sigD_indicators[7] = 3;
      break;
    case bdtaunu::kD0_KK:
      sigD_indicators[8] = 1;
      break;
  }

  switch (tag_Dstartype) {
    case bdtaunu::kDstar0_D0pi0:
      tagDstar_indicators[0] = 1;
      break;
    case bdtaunu::kDstar0_D0gamma:
      tagDstar_indicators[1] = 1;
      break;
    case bdtaunu::kDstarc_D0pi:
      tagDstar_indicators[2] = 1;
      break;
    case bdtaunu::kDstarc_Dcpi0:
      tagDstar_indicators[3] = 1;
      break;
    case bdtaunu::kDstarc_Dcgamma:
      // do nothing
      break;
  }

  return;
}

bool DstarDrhoFeatureExtractor::passed_selection() const {

  if (!YCandFeatureExtractor::passed_selection()) {
    return false;
  }

  // tag_deltaM
  if (tag_Dstartype == bdtaunu::kDstar0_D0pi0) {
    if (
        (tag_deltaM < 0.1375) ||
        (tag_deltaM > 0.1475)
       ) {
      return false;
    }
  }

  if (tag_Dstartype == bdtaunu::kDstar0_D0gamma) {
    if (
        (tag_deltaM < 0.13) ||
        (tag_deltaM > 0.155)
       ) {
      return false;
    }
  }

  if (tag_Dstartype == bdtaunu::kDstarc_D0pi) {
    if (
        (tag_deltaM < 0.1425) ||
        (tag_deltaM > 0.1490)
       ) {
      return false;
    }
  }

  if (tag_Dstartype == bdtaunu::kDstarc_Dcpi0) {
    if (
        (tag_deltaM < 0.1375) ||
        (tag_deltaM > 0.145)
       ) {
      return false;
    }
  }

  // sig_Dmass
  if (
      (sig_Dmass < 1.84) ||
      (sig_Dmass > 1.9)
     ) {
    return false;
  }

  // tag_Dtype
  if (
      (tag_Dtype == bdtaunu::kDc_Kspipipi)
     ) {
    return false;
  }

  // tag_Dstartype
  if (
      (tag_Dstartype == bdtaunu::kDstarc_Dcgamma)
     ) {
    return false;
  }

  // sig_Dtype
  if (
      (sig_Dtype == bdtaunu::kDc_Kspipipi) ||
      (sig_Dtype == bdtaunu::kD0_Kpipipipi0)
     ) {
    return false;
  }


  return true;
}


void DstarDstarrhoFeatureExtractor::extract_features() {

  ClearFeatures(); 

  numeric_features[0] = tag_lp3;
  numeric_features[1] = tag_cosBY;
  numeric_features[2] = tag_cosThetaDl;
  numeric_features[3] = sig_hp3;
  numeric_features[4] = sig_vtxB;
  numeric_features[5] = mmiss_prime2;
  numeric_features[6] = eextra50;
  numeric_features[7] = tag_deltaM;
  numeric_features[8] = tag_cosThetaDSoft;
  numeric_features[9] = tag_softP3MagCM;
  numeric_features[10] = sig_deltaM;
  numeric_features[11] = sig_cosThetaDSoft;
  numeric_features[12] = sig_softP3MagCM;
  numeric_features[13] = sig_hmass;
  numeric_features[14] = sig_vtxh;

  switch (tag_Dtype) {
    case bdtaunu::kDc_Kpipi:
      tagD_indicators[0] = 1;
      break;
    case bdtaunu::kDc_Kpipipi0:
      tagD_indicators[1] = 1; 
      break;
    case bdtaunu::kDc_KsK:
      tagD_indicators[2] = 1;
      break;
    case bdtaunu::kDc_Kspi:
      tagD_indicators[2] = 2;
      break;
    case bdtaunu::kDc_Kspipi0:
      tagD_indicators[2] = 3;
      break;
    case bdtaunu::kDc_Kspipipi:
      // do nothing
      break;
    case bdtaunu::kDc_KKpi:
      tagD_indicators[2] = 4;
      break;
    case bdtaunu::kD0_Kpi:
      tagD_indicators[3] = 1;
      break;
    case bdtaunu::kD0_Kpipi0:
      tagD_indicators[4] = 1;
      break;
    case bdtaunu::kD0_Kpipipi:
      tagD_indicators[5] = 1;
      break;
    case bdtaunu::kD0_Kpipipipi0:
      tagD_indicators[6] = 1;
      break;
    case bdtaunu::kD0_Kspipi:
      tagD_indicators[7] = 1;
      break;
    case bdtaunu::kD0_Kspipipi0:
      tagD_indicators[7] = 2;
      break;
    case bdtaunu::kD0_Kspi0:
      tagD_indicators[7] = 3;
      break;
    case bdtaunu::kD0_KK:
      tagD_indicators[8] = 1;
      break;
  }

  switch (sig_Dtype) {
    case bdtaunu::kDc_Kpipi:
      sigD_indicators[0] = 1;
      break;
    case bdtaunu::kDc_Kpipipi0:
      sigD_indicators[1] = 1; 
      break;
    case bdtaunu::kDc_KsK:
      sigD_indicators[2] = 1;
      break;
    case bdtaunu::kDc_Kspi:
      sigD_indicators[2] = 2;
      break;
    case bdtaunu::kDc_Kspipi0:
      sigD_indicators[2] = 3;
      break;
    case bdtaunu::kDc_Kspipipi:
      // do nothing
      break;
    case bdtaunu::kDc_KKpi:
      sigD_indicators[2] = 4;
      break;
    case bdtaunu::kD0_Kpi:
      sigD_indicators[3] = 1;
      break;
    case bdtaunu::kD0_Kpipi0:
      sigD_indicators[4] = 1;
      break;
    case bdtaunu::kD0_Kpipipi:
      sigD_indicators[5] = 1;
      break;
    case bdtaunu::kD0_Kpipipipi0:
      sigD_indicators[6] = 1;
      break;
    case bdtaunu::kD0_Kspipi:
      sigD_indicators[7] = 1;
      break;
    case bdtaunu::kD0_Kspipipi0:
      sigD_indicators[7] = 2;
      break;
    case bdtaunu::kD0_Kspi0:
      sigD_indicators[7] = 3;
      break;
    case bdtaunu::kD0_KK:
      sigD_indicators[8] = 1;
      break;
  }

  switch (tag_Dstartype) {
    case bdtaunu::kDstar0_D0pi0:
      tagDstar_indicators[0] = 1;
      break;
    case bdtaunu::kDstar0_D0gamma:
      tagDstar_indicators[1] = 1;
      break;
    case bdtaunu::kDstarc_D0pi:
      tagDstar_indicators[2] = 1;
      break;
    case bdtaunu::kDstarc_Dcpi0:
      tagDstar_indicators[3] = 1;
      break;
    case bdtaunu::kDstarc_Dcgamma:
      // do nothing
      break;
  }

  switch (sig_Dstartype) {
    case bdtaunu::kDstar0_D0pi0:
      sigDstar_indicators[0] = 1;
      break;
    case bdtaunu::kDstar0_D0gamma:
      sigDstar_indicators[1] = 1;
      break;
    case bdtaunu::kDstarc_D0pi:
      sigDstar_indicators[2] = 1;
      break;
    case bdtaunu::kDstarc_Dcpi0:
      sigDstar_indicators[3] = 1;
      break;
    case bdtaunu::kDstarc_Dcgamma:
      // do nothing
      break;
  }

  return;
}

bool DstarDstarrhoFeatureExtractor::passed_selection() const {

  if (!YCandFeatureExtractor::passed_selection()) {
    return false;
  }

  // tag_deltaM
  if (tag_Dstartype == bdtaunu::kDstar0_D0pi0) {
    if (
        (tag_deltaM < 0.1375) ||
        (tag_deltaM > 0.1475)
       ) {
      return false;
    }
  }

  if (tag_Dstartype == bdtaunu::kDstar0_D0gamma) {
    if (
        (tag_deltaM < 0.13) ||
        (tag_deltaM > 0.155)
       ) {
      return false;
    }
  }

  if (tag_Dstartype == bdtaunu::kDstarc_D0pi) {
    if (
        (tag_deltaM < 0.1425) ||
        (tag_deltaM > 0.1490)
       ) {
      return false;
    }
  }

  if (tag_Dstartype == bdtaunu::kDstarc_Dcpi0) {
    if (
        (tag_deltaM < 0.1375) ||
        (tag_deltaM > 0.145)
       ) {
      return false;
    }
  }

  // sig_deltaM
  if (sig_Dstartype == bdtaunu::kDstar0_D0pi0) {
    if (
        (sig_deltaM < 0.135) ||
        (sig_deltaM > 0.15)
       ) {
      return false;
    }
  }

  if (sig_Dstartype == bdtaunu::kDstar0_D0gamma) {
    if (
        (sig_deltaM < 0.13) ||
        (sig_deltaM > 0.155)
       ) {
      return false;
    }
  }

  if (sig_Dstartype == bdtaunu::kDstarc_D0pi) {
    if (
        (sig_deltaM < 0.14) ||
        (sig_deltaM > 0.15)
       ) {
      return false;
    }
  }

  if (sig_Dstartype == bdtaunu::kDstarc_Dcpi0) {
    if (
        (sig_deltaM < 0.1375) ||
        (sig_deltaM > 0.145)
       ) {
      return false;
    }
  }

  // tag_Dtype
  if (
      (tag_Dtype == bdtaunu::kDc_Kspipipi)
     ) {
    return false;
  }

  // tag_Dstartype
  if (
      (tag_Dstartype == bdtaunu::kDstarc_Dcgamma)
     ) {
    return false;
  }

  // sig_Dtype
  if (
      (sig_Dtype == bdtaunu::kDc_Kspipipi)
     ) {
    return false;
  }

  // sig_Dstartype
  if (
      (sig_Dstartype == bdtaunu::kDstarc_Dcgamma)
     ) {
    return false;
  }


  return true;
}
