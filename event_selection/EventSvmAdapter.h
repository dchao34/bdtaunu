#ifndef __EVENTSVMADAPTER_H__
#define __EVENTSVMADAPTER_H__

#include <vector>

#include "EventFeatureExtractor.h"
#include "utilities/svm.h"

class EventSvmAdapter {

  protected: 

    std::vector<double> numeric_features;
    std::vector<int> cand_type_indicators;
    std::vector<int> tagD_indicators, sigD_indicators;
    std::vector<int> tagDstar_indicators, sigDstar_indicators;

    int nr_targets;
    int nr_svm_features;

    void load_svm_scale(const char *scale_fname);
    double upper, lower;
    double *feature_max, *feature_min;
    void svm_scale();

    svm_model *model;

    svm_node *x;
    void clear_x();

    double *prob;

    void InitializeFeatures(
        int n_targets, 
        int n_num, int n_cand_type,
        int n_tagD, int n_sigD, 
        int n_tagDstar, int n_sigDstar); 

    void InitializeSvm(
      const char *model_fname,
      const char *scale_fname);

    void Cleanup();

  public:
    EventSvmAdapter() {};
    EventSvmAdapter(int n_targets, 
                    int n_num, int n_cand_type,
                    int n_tagD, int n_sigD, 
                    int n_tagDstar, int n_sigDstar, 
                    const char *model_fname, 
                    const char *scale_fname);

    virtual ~EventSvmAdapter() {};

    void set_features(const EventFeatureExtractor&);

    void svm_predict();

		const double* get_prob() const { return prob; }

};  


class SignalSvmAdapter : public EventSvmAdapter {
  public:
    SignalSvmAdapter();
    ~SignalSvmAdapter() { Cleanup(); }
};

class ContinuumSvmAdapter : public EventSvmAdapter {
  public:
    ContinuumSvmAdapter();
    ~ContinuumSvmAdapter() { Cleanup(); }
};

class SigVsSLSvmAdapter : public EventSvmAdapter {
  public:
    SigVsSLSvmAdapter();
    ~SigVsSLSvmAdapter() { Cleanup(); }
};

class SigVsHadSvmAdapter : public EventSvmAdapter {
  public:
    SigVsHadSvmAdapter();
    ~SigVsHadSvmAdapter() { Cleanup(); }
};

class SigVsContSvmAdapter : public EventSvmAdapter {
  public:
    SigVsContSvmAdapter();
    ~SigVsContSvmAdapter() { Cleanup(); }
};

class SigVsAllSvmAdapter : public EventSvmAdapter {
  public:
    SigVsAllSvmAdapter();
    ~SigVsAllSvmAdapter() { Cleanup(); }
};

#endif
