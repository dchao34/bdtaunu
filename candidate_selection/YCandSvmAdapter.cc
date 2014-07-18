#include <fstream>
#include <string>
#include <vector>
#include <cassert>
#include <iostream>

#include "utilities/svm.h"
#include "YCandFeatureExtractor.h"
#include "YCandSvmAdapter.h"

YCandSvmAdapter::YCandSvmAdapter(
  int n_targets, int n_num, 
  int n_tagD, int n_sigD, 
  int n_tagDstar, int n_sigDstar, 
  const char *model_fname, 
  const char *scale_fname) {

  InitializeFeatures(
      n_targets, n_num, 
      n_tagD, n_sigD,
      n_tagDstar, n_sigDstar);
  InitializeSvm(model_fname, scale_fname);

}

void YCandSvmAdapter::InitializeFeatures(
  int n_targets, int n_num, 
  int n_tagD, int n_sigD, 
  int n_tagDstar, int n_sigDstar) {

  nr_targets = n_targets;
  numeric_features = std::vector<double>(n_num, 0);
  tagD_indicators = std::vector<int>(n_tagD, 0);
  sigD_indicators = std::vector<int>(n_sigD, 0);
  tagDstar_indicators = std::vector<int>(n_tagDstar, 0);
  sigDstar_indicators = std::vector<int>(n_sigDstar, 0);

  nr_svm_features = 
    n_num + 
    n_tagD + n_sigD +
    n_tagDstar + n_sigDstar;
}


void YCandSvmAdapter::InitializeSvm(
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

void YCandSvmAdapter::Cleanup() {

  svm_free_and_destroy_model(&model);

  delete[] x;
  delete[] feature_max;
  delete[] feature_min;
  delete[] prob;
}

void YCandSvmAdapter::clear_x() {
  for (int i = 0; i < nr_svm_features; i++) {
    x[i].index = i + 1;
    x[i].value = 0;
  }
  x[nr_svm_features].index = -1;
}

void YCandSvmAdapter::load_svm_scale(const char *scale_fname) {
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

void YCandSvmAdapter::svm_scale() {

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

void YCandSvmAdapter::set_features(const YCandFeatureExtractor &cand_extractor) {

  assert(numeric_features.size() == cand_extractor.get_numeric_features().size());
  numeric_features = cand_extractor.get_numeric_features();

  assert(tagD_indicators.size() == cand_extractor.get_tagD_indicators().size());
  tagD_indicators = cand_extractor.get_tagD_indicators();

  assert(sigD_indicators.size() == cand_extractor.get_sigD_indicators().size());
  sigD_indicators = cand_extractor.get_sigD_indicators();

  assert(tagDstar_indicators.size() == cand_extractor.get_tagDstar_indicators().size());
  tagDstar_indicators = cand_extractor.get_tagDstar_indicators();

  assert(sigDstar_indicators.size() == cand_extractor.get_sigDstar_indicators().size());
  sigDstar_indicators = cand_extractor.get_sigDstar_indicators();
}
 
void YCandSvmAdapter::svm_predict() {

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

DDpiSvmAdapter::DDpiSvmAdapter() {
  InitializeFeatures(2, 9, 10, 9, 0, 0);
  std::string trained_path = std::string(__MODEL_ROOTNAME);
  std::string model_fname = trained_path + "/models/DDpi.model";
  std::string scale_fname = trained_path + "/ranges/DDpi.range";
  InitializeSvm(model_fname.c_str(), scale_fname.c_str());
}

DDstarpiSvmAdapter::DDstarpiSvmAdapter() {
  InitializeFeatures(2, 11, 9, 7, 0, 4);
  std::string trained_path = std::string(__MODEL_ROOTNAME);
  std::string model_fname = trained_path + "/models/DDstarpi.model";
  std::string scale_fname = trained_path + "/ranges/DDstarpi.range";
  InitializeSvm(model_fname.c_str(), scale_fname.c_str());
}

DstarDpiSvmAdapter::DstarDpiSvmAdapter() {
  InitializeFeatures(2, 11, 9, 9, 4, 0);
  std::string trained_path = std::string(__MODEL_ROOTNAME);
  std::string model_fname = trained_path + "/models/DstarDpi.model";
  std::string scale_fname = trained_path + "/ranges/DstarDpi.range";
  InitializeSvm(model_fname.c_str(), scale_fname.c_str());
}

DstarDstarpiSvmAdapter::DstarDstarpiSvmAdapter() {
  InitializeFeatures(2, 13, 12, 9, 4, 4);
  std::string trained_path = std::string(__MODEL_ROOTNAME);
  std::string model_fname = trained_path + "/models/DstarDstarpi.model";
  std::string scale_fname = trained_path + "/ranges/DstarDstarpi.range";
  InitializeSvm(model_fname.c_str(), scale_fname.c_str());
}

DDrhoSvmAdapter::DDrhoSvmAdapter() {
  InitializeFeatures(2, 11, 10, 9, 0, 0);
  std::string trained_path = std::string(__MODEL_ROOTNAME);
  std::string model_fname = trained_path + "/models/DDrho.model";
  std::string scale_fname = trained_path + "/ranges/DDrho.range";
  InitializeSvm(model_fname.c_str(), scale_fname.c_str());
}

DDstarrhoSvmAdapter::DDstarrhoSvmAdapter() {
  InitializeFeatures(2, 13, 9, 9, 0, 4);
  std::string trained_path = std::string(__MODEL_ROOTNAME);
  std::string model_fname = trained_path + "/models/DDstarrho.model";
  std::string scale_fname = trained_path + "/ranges/DDstarrho.range";
  InitializeSvm(model_fname.c_str(), scale_fname.c_str());
}

DstarDrhoSvmAdapter::DstarDrhoSvmAdapter() {
  InitializeFeatures(2, 13, 9, 9, 4, 0);
  std::string trained_path = std::string(__MODEL_ROOTNAME);
  std::string model_fname = trained_path + "/models/DstarDrho.model";
  std::string scale_fname = trained_path + "/ranges/DstarDrho.range";
  InitializeSvm(model_fname.c_str(), scale_fname.c_str());
}

DstarDstarrhoSvmAdapter::DstarDstarrhoSvmAdapter() {
  InitializeFeatures(2, 15, 9, 9, 4, 4);
  std::string trained_path = std::string(__MODEL_ROOTNAME);
  std::string model_fname = trained_path + "/models/DstarDstarrho.model";
  std::string scale_fname = trained_path + "/ranges/DstarDstarrho.range";
  InitializeSvm(model_fname.c_str(), scale_fname.c_str());
}
