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
    Clear();
}


YCandFeatureExtractor::YCandFeatureExtractor(
    int n_num, 
    int n_tagD, int n_sigD, 
    int n_tagDstar, int n_sigDstar) {

    Clear();

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
}

void YCandFeatureExtractor::Clear() {

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

bool YCandFeatureExtractor::pass_selection() const {

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
