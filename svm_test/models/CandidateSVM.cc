#include <fstream>
#include <string>
#include <cassert>
#include <iostream>

#include "svm.h"
#include "CandidateSVM.h"

CandidateSVM::CandidateSVM(
		int targets, int features) :
    nr_targets(targets), nr_svm_features(features) {
}


void CandidateSVM::Initialize(const char *model_fname, 
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

void CandidateSVM::Cleanup() {

  svm_free_and_destroy_model(&model);

  delete[] x;
  delete[] feature_max;
  delete[] feature_min;
  delete[] prob;
}

void CandidateSVM::clear_x() {
  for (int i = 0; i < nr_svm_features; i++) {
    x[i].index = i + 1;
    x[i].value = 0;
  }
  x[nr_svm_features].index = -1;
}

void CandidateSVM::load_svm_scale(const char *scale_fname) {
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

void CandidateSVM::svm_scale() {

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
