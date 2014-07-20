#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <iostream>

#include "EventFeatureExtractor.h"
#include "utilities/helpers.h"

EventFeatureExtractor::EventFeatureExtractor() : 
  numeric_features(), 
  cand_type_indicators(), 
  tagD_indicators(),
  sigD_indicators(), 
  tagDstar_indicators(), 
  sigDstar_indicators() {
  ClearCache();
  ClearFeatures();
}


EventFeatureExtractor::EventFeatureExtractor(
  int n_num, int n_cand_type,
  int n_tagD, int n_sigD, 
  int n_tagDstar, int n_sigDstar) {

  if (n_num > 0) {
    numeric_features = std::vector<double>(n_num, 0);
  } else {
    numeric_features = std::vector<double>();
  }

  if (n_cand_type > 0) {
    cand_type_indicators = std::vector<int>(n_cand_type, 0);
  } else {
    cand_type_indicators = std::vector<int>();
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

void EventFeatureExtractor::ClearCache() {

  id = 0;
  mc_evttypeA = 0;
  event_weight = 0;

  cand_type = 0;
  tag_Dtype = 0;
  tag_Dstartype = 0;
  sig_Dtype = 0;
  sig_Dstartype = 0;

  nTrk = 0;
  R2 = 0;
  cosThetaT = 0;
  eextra50 = 0;
  mmiss_prime2 = 0;
  tag_lp3 = 0;
  tag_cosBY = 0;
  tag_cosThetaDl = 0; 
  sig_hp3 = 0;
  sig_cosBY = 0;
  sig_cosThetaDtau = 0;
  sig_vtxB = 0;
  svm_score = 0;

  tag_Dmass = 0;
  tag_deltaM = 0;
  tag_cosThetaDSoft = 0;
  tag_softP3MagCM = 0;
  sig_Dmass = 0;
  sig_deltaM = 0;
  sig_cosThetaDSoft = 0;
  sig_softP3MagCM = 0;
  sig_hmass = 0;
  sig_vtxh = 0;

}

void EventFeatureExtractor::ClearFeatures() {

  std::vector<double>::iterator it_double = numeric_features.begin();
  while (it_double != numeric_features.end()) {
    *it_double = 0;
    ++it_double;
  }

  std::vector<int>::iterator it_int; 

  it_int = cand_type_indicators.begin();
  while (it_int != cand_type_indicators.end()) {
    *it_int = 0;
    ++it_int;
  }

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

bool EventFeatureExtractor::passed_selection() const {

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

int EventFeatureExtractor::categorize_event_type() const {
  return mc_evttypeA;
}


std::string EventFeatureExtractor::get_libsvm_line() const {

  std::stringstream libsvm_line;

  libsvm_line << to_string(categorize_event_type());

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

  it_int = cand_type_indicators.begin();
  while (it_int != cand_type_indicators.end()) {
    libsvm_line << " ";
    libsvm_line << feature_counter;
    libsvm_line << ":";
    libsvm_line << *it_int;
    ++feature_counter;
    ++it_int;
  }

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

int ContinuumFeatureExtractor::categorize_event_type() const {
  switch (mc_evttypeA) {
    case 7:
      return 1;
    default:
      return -1;
  }
}

void ContinuumFeatureExtractor::extract_features() {

  ClearFeatures();

  /*numeric_features[0] = nTrk;
  numeric_features[1] = R2;
  numeric_features[2] = cosThetaT;
  numeric_features[3] = sig_cosBY;
  */

  numeric_features[0] = nTrk;
  numeric_features[1] = R2;
  numeric_features[2] = cosThetaT;
  numeric_features[3] = eextra50;
  numeric_features[4] = mmiss_prime2;
  numeric_features[5] = tag_cosBY;
  numeric_features[6] = tag_lp3;
  numeric_features[7] = tag_cosThetaDl;
  numeric_features[8] = sig_hp3;
  numeric_features[9] = sig_cosBY;
  numeric_features[10] = sig_cosThetaDtau;
  numeric_features[11] = sig_vtxB;

}

int SignalFeatureExtractor::categorize_event_type() const {
  switch (mc_evttypeA) {
    case 0:
    case 1:
      return 1;
    case 7:
      return 0;
    default:
      return -1;
  }
}

void SignalFeatureExtractor::extract_features() {

  ClearFeatures();

  numeric_features[0] = nTrk;
  numeric_features[1] = eextra50;
  numeric_features[2] = mmiss_prime2;
  numeric_features[3] = tag_cosBY;
  numeric_features[4] = tag_lp3;
  numeric_features[5] = tag_cosThetaDl;
  numeric_features[6] = sig_hp3;
  numeric_features[7] = sig_cosBY;
  numeric_features[8] = sig_cosThetaDtau;
  numeric_features[9] = sig_vtxB;

}
