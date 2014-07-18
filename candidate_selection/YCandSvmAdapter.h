#ifndef __YCANDSVMADAPTER_H__
#define __YCANDSVMADAPTER_H__

#include <vector>

#include "YCandFeatureExtractor.h"
#include "utilities/svm.h"

class YCandSvmAdapter {

  protected: 

    std::vector<double> numeric_features;
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
        int n_targets, int n_num, 
        int n_tagD, int n_sigD, 
        int n_tagDstar, int n_sigDstar); 

    void InitializeSvm(
      const char *model_fname,
      const char *scale_fname);

    void Cleanup();

  public:
    YCandSvmAdapter() {};
    YCandSvmAdapter(int n_targets, int n_num, 
                       int n_tagD, int n_sigD, 
                       int n_tagDstar, int n_sigDstar, 
                       const char *model_fname, 
                       const char *scale_fname);

    virtual ~YCandSvmAdapter() {};

    void set_features(const YCandFeatureExtractor&);

    void svm_predict();

		const double* get_prob() const { return prob; }

};  


class DDpiSvmAdapter : public YCandSvmAdapter {
  public:
    DDpiSvmAdapter();
    ~DDpiSvmAdapter() { Cleanup(); }
};

class DDstarpiSvmAdapter : public YCandSvmAdapter {
  public:
    DDstarpiSvmAdapter();
    ~DDstarpiSvmAdapter() { Cleanup(); }
};

class DstarDpiSvmAdapter : public YCandSvmAdapter {
  public:
    DstarDpiSvmAdapter();
    ~DstarDpiSvmAdapter() { Cleanup(); }
};

class DstarDstarpiSvmAdapter : public YCandSvmAdapter {
  public:
    DstarDstarpiSvmAdapter();
    ~DstarDstarpiSvmAdapter() { Cleanup(); }
};

class DDrhoSvmAdapter : public YCandSvmAdapter {
  public:
    DDrhoSvmAdapter();
    ~DDrhoSvmAdapter() { Cleanup(); }
};

class DDstarrhoSvmAdapter : public YCandSvmAdapter {
  public:
    DDstarrhoSvmAdapter();
    ~DDstarrhoSvmAdapter() { Cleanup(); }
};

class DstarDrhoSvmAdapter : public YCandSvmAdapter {
  public:
    DstarDrhoSvmAdapter();
    ~DstarDrhoSvmAdapter() { Cleanup(); }
};

class DstarDstarrhoSvmAdapter : public YCandSvmAdapter {
  public:
    DstarDstarrhoSvmAdapter();
    ~DstarDstarrhoSvmAdapter() { Cleanup(); }
};

#endif
