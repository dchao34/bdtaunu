#include <cassert>

#include "EventSvmScorer.h"

EventSvmScorer::EventSvmScorer() {
    signal_extr = new SignalFeatureExtractor();
    continuum_extr = new ContinuumFeatureExtractor();
    sig_sl_extr = new SigVsSLFeatureExtractor();
    sig_had_extr = new SigVsHadFeatureExtractor();
    sig_cont_extr = new SigVsContFeatureExtractor();
    sig_all_extr = new SigVsAllFeatureExtractor();

    signal_adtr = new SignalSvmAdapter();
    continuum_adtr = new ContinuumSvmAdapter();
    sig_sl_adtr = new SigVsSLSvmAdapter();
    sig_had_adtr = new SigVsHadSvmAdapter();
    sig_cont_adtr = new SigVsContSvmAdapter();
    sig_all_adtr = new SigVsAllSvmAdapter();
}

EventSvmScorer::~EventSvmScorer() {
    delete signal_extr;
    delete continuum_extr;
    delete sig_sl_extr;
    delete sig_had_extr;
    delete sig_cont_extr;
    delete sig_all_extr;

    delete signal_adtr;
    delete continuum_adtr;
    delete sig_sl_adtr;
    delete sig_had_adtr;
    delete sig_cont_adtr;
    delete sig_all_adtr;
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

  sig_sl_extr->extract_features(event);
  sig_sl_adtr->set_features(*sig_sl_extr);
  sig_sl_adtr->svm_predict();
  sig_sl_score = (sig_sl_adtr->get_prob())[0];

  sig_had_extr->extract_features(event);
  sig_had_adtr->set_features(*sig_had_extr);
  sig_had_adtr->svm_predict();
  sig_had_score = (sig_had_adtr->get_prob())[0];

  sig_cont_extr->extract_features(event);
  sig_cont_adtr->set_features(*sig_cont_extr);
  sig_cont_adtr->svm_predict();
  sig_cont_score = (sig_cont_adtr->get_prob())[0];

  sig_all_extr->extract_features(event);
  sig_all_adtr->set_features(*sig_all_extr);
  sig_all_adtr->svm_predict();
  sig_all_score = (sig_all_adtr->get_prob())[0];

  if (signal_extr->passed_selection()) {
    passed_precuts_flag = true;
  } else {
    passed_precuts_flag = false;
  }
}

