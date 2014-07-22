#include <cassert>

#include "EventSvmScorer.h"

EventSvmScorer::EventSvmScorer() {
    signal_extr = new SignalFeatureExtractor();
    continuum_extr = new ContinuumFeatureExtractor();

    signal_adtr = new SignalSvmAdapter();
    continuum_adtr = new ContinuumSvmAdapter();
}

EventSvmScorer::~EventSvmScorer() {
    delete signal_extr;
    delete continuum_extr;

    delete signal_adtr;
    delete continuum_adtr;
}

void EventSvmScorer::predict(const Event &event) {

  signal_extr->extract_features(event);
  signal_adtr->set_features(*signal_extr);
  signal_adtr->svm_predict();
  signal_score = (signal_adtr->get_prob())[0];

  continuum_extr->extract_features(event);
  continuum_adtr->set_features(*continuum_extr);
  continuum_adtr->svm_predict();
  continuum_score = (continuum_adtr->get_prob())[0];

  if (signal_extr->passed_selection()) {
    passed_precuts_flag = true;
  } else {
    passed_precuts_flag = false;
  }
}

