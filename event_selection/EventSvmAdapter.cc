#include <fstream>
#include <string>
#include <vector>
#include <cassert>
#include <iostream>

#include "utilities/svm.h"
#include "EventFeatureExtractor.h"
#include "EventSvmAdapter.h"

EventSvmAdapter::EventSvmAdapter(
  int n_targets, 
  int n_num, int n_cand_type,
  int n_tagD, int n_sigD, 
  int n_tagDstar, int n_sigDstar, 
  const char *model_fname, 
  const char *scale_fname) {

  InitializeFeatures(
      n_targets, 
      n_num, n_cand_type,
      n_tagD, n_sigD,
      n_tagDstar, n_sigDstar);
  InitializeSvm(model_fname, scale_fname);

}

void EventSvmAdapter::InitializeFeatures(
  int n_targets, 
  int n_num, int n_cand_type,
  int n_tagD, int n_sigD, 
  int n_tagDstar, int n_sigDstar) {

  nr_targets = n_targets;
  numeric_features = std::vector<double>(n_num, 0);
  cand_type_indicators = std::vector<int>(n_cand_type, 0);
  tagD_indicators = std::vector<int>(n_tagD, 0);
  sigD_indicators = std::vector<int>(n_sigD, 0);
  tagDstar_indicators = std::vector<int>(n_tagDstar, 0);
  sigDstar_indicators = std::vector<int>(n_sigDstar, 0);

  nr_svm_features = 
    n_num + n_cand_type + 
    n_tagD + n_sigD +
    n_tagDstar + n_sigDstar;
}


void EventSvmAdapter::InitializeSvm(
    const char *model_fname, 
    const char *scale_fname) {

  x = new struct svm_node[nr_svm_features + 1];
  clear_x();

  model = svm_load_model(model_fname);
  assert(svm_get_nr_class(model) == nr_targets);

  feature_max = new double[nr_svm_features];
  feature_min = new double[nr_svm_features];
  load_svm_scale(scale_fname);

  prob = new double[nr_targets];
}

void EventSvmAdapter::Cleanup() {

  svm_free_and_destroy_model(&model);

  delete[] x;
  delete[] feature_max;
  delete[] feature_min;
  delete[] prob;
}

void EventSvmAdapter::clear_x() {
  for (int i = 0; i < nr_svm_features; i++) {
    x[i].index = i + 1;
    x[i].value = 0;
  }
  x[nr_svm_features].index = -1;
}

void EventSvmAdapter::load_svm_scale(const char *scale_fname) {
  std::ifstream input(scale_fname, std::ios::in);
  std::string line;
  std::getline(input, line);
  std::getline(input, line);
  int delim = line.find(" ");
  lower = std::atof(line.substr(0, delim).c_str());
  upper = std::atof(line.substr(delim + 1).c_str());

  int i = 0;
  while (getline(input, line)) {
    int delim1 = line.find(" ");
    int feature_nr = atoi(line.substr(0, delim1).c_str());
    assert(feature_nr == i + 1);
    int delim2 = line.find(" ", delim1 + 1);
    feature_min[i] = atof(line.substr(delim1 + 1, delim2 - delim1+ 1).c_str());
    feature_max[i] = atof(line.substr(delim2 + 1).c_str());
    i++;
  }

  input.close();
}

void EventSvmAdapter::svm_scale() {

  for (int i = 0; i < nr_svm_features; i++) {
    if (feature_max[i] == feature_min[i]) {
      return;
    }
    if(x[i].value == feature_min[i]) {
      x[i].value = lower;
    } else if (x[i].value == feature_max[i]) {
      x[i].value = upper;
    } else {
      x[i].value = lower + (upper - lower) *
                           (x[i].value - feature_min[i])/
                           (feature_max[i] - feature_min[i]);
    }
  }
}

void EventSvmAdapter::set_features(const EventFeatureExtractor &event_extractor) {

  assert(numeric_features.size() == event_extractor.get_numeric_features().size());
  numeric_features = event_extractor.get_numeric_features();

  assert(cand_type_indicators.size() == event_extractor.get_cand_type_indicators().size());
  cand_type_indicators = event_extractor.get_cand_type_indicators();

  assert(tagD_indicators.size() == event_extractor.get_tagD_indicators().size());
  tagD_indicators = event_extractor.get_tagD_indicators();

  assert(sigD_indicators.size() == event_extractor.get_sigD_indicators().size());
  sigD_indicators = event_extractor.get_sigD_indicators();

  assert(tagDstar_indicators.size() == event_extractor.get_tagDstar_indicators().size());
  tagDstar_indicators = event_extractor.get_tagDstar_indicators();

  assert(sigDstar_indicators.size() == event_extractor.get_sigDstar_indicators().size());
  sigDstar_indicators = event_extractor.get_sigDstar_indicators();
}
 
void EventSvmAdapter::svm_predict() {

  clear_x();

  int svm_ftr_idx =0;

  std::vector<double>::iterator dit;
  dit = numeric_features.begin();
  while (dit != numeric_features.end()) {
    x[svm_ftr_idx].value = *dit;
    ++svm_ftr_idx;
    ++dit;
  }

  std::vector<int>::iterator it;

  it = cand_type_indicators.begin();
  while (it != cand_type_indicators.end()) {
    x[svm_ftr_idx].value = *it;
    ++svm_ftr_idx;
    ++it;
  }

  it = tagD_indicators.begin();
  while (it != tagD_indicators.end()) {
    x[svm_ftr_idx].value = *it;
    ++svm_ftr_idx;
    ++it;
  }

  it = sigD_indicators.begin();
  while (it != sigD_indicators.end()) {
    x[svm_ftr_idx].value = *it;
    ++svm_ftr_idx;
    ++it;
  }

  it = tagDstar_indicators.begin();
  while (it != tagDstar_indicators.end()) {
    x[svm_ftr_idx].value = *it;
    ++svm_ftr_idx;
    ++it;
  }

  it = sigDstar_indicators.begin();
  while (it != sigDstar_indicators.end()) {
    x[svm_ftr_idx].value = *it;
    ++svm_ftr_idx;
    ++it;
  }

  svm_scale();
  svm_predict_probability(model, x, prob);

}

SignalSvmAdapter::SignalSvmAdapter() {
  InitializeFeatures(2, 10, 0, 0, 0, 0, 0);
  std::string trained_path = std::string(__MODEL_ROOTNAME);
  std::string model_fname = trained_path + "/models/sig.model";
  std::string scale_fname = trained_path + "/ranges/sig.range";
  InitializeSvm(model_fname.c_str(), scale_fname.c_str());
}

ContinuumSvmAdapter::ContinuumSvmAdapter() {
  InitializeFeatures(2, 12, 0, 0, 0, 0, 0);
  std::string trained_path = std::string(__MODEL_ROOTNAME);
  std::string model_fname = trained_path + "/models/cont.model";
  std::string scale_fname = trained_path + "/ranges/cont.range";
  InitializeSvm(model_fname.c_str(), scale_fname.c_str());
}

SigVsSLSvmAdapter::SigVsSLSvmAdapter() {
  InitializeFeatures(2, 12, 0, 0, 0, 0, 0);
  std::string trained_path = std::string(__MODEL_ROOTNAME);
  std::string model_fname = trained_path + "/models/sigVsl.model";
  std::string scale_fname = trained_path + "/ranges/sigVsl.range";
  InitializeSvm(model_fname.c_str(), scale_fname.c_str());
}

SigVsHadSvmAdapter::SigVsHadSvmAdapter() {
  InitializeFeatures(2, 12, 0, 0, 0, 0, 0);
  std::string trained_path = std::string(__MODEL_ROOTNAME);
  std::string model_fname = trained_path + "/models/sigVhad.model";
  std::string scale_fname = trained_path + "/ranges/sigVhad.range";
  InitializeSvm(model_fname.c_str(), scale_fname.c_str());
}

SigVsContSvmAdapter::SigVsContSvmAdapter() {
  InitializeFeatures(2, 12, 0, 0, 0, 0, 0);
  std::string trained_path = std::string(__MODEL_ROOTNAME);
  std::string model_fname = trained_path + "/models/sigVcont.model";
  std::string scale_fname = trained_path + "/ranges/sigVcont.range";
  InitializeSvm(model_fname.c_str(), scale_fname.c_str());
}

SigVsAllSvmAdapter::SigVsAllSvmAdapter() {
  InitializeFeatures(2, 12, 0, 0, 0, 0, 0);
  std::string trained_path = std::string(__MODEL_ROOTNAME);
  std::string model_fname = trained_path + "/models/sigVall.model";
  std::string scale_fname = trained_path + "/ranges/sigVall.range";
  InitializeSvm(model_fname.c_str(), scale_fname.c_str());
}
