#ifndef __CANDIDATESVMSCORER_H__
#define __CANDIDATESVMSCORER_H__

#include <vector>

#include "YCandFeatureExtractor.h"
#include "svm.h"

class CandidateSvmScorer {

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

    void Initialize(const char *model_fname,
                    const char *scale_fname);
    void Cleanup();

  public:
    CandidateSvmScorer() {};
    CandidateSvmScorer(int n_targets, int n_num, 
                       int n_tagD, int n_sigD, 
                       int n_tagDstar, int n_sigDstar);

    virtual ~CandidateSvmScorer() {};

    void set_features(const YCandFeatureExtractor&);

    void svm_predict();

		const double* get_prob() const { return prob; }

};  

#endif
