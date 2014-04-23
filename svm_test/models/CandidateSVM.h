#ifndef  CandidateSVM_INC
#define  CandidateSVM_INC

#include "svm.h"

class CandidateSVM {

  public:
    struct features {
      double tag_lp3, tag_cosBY, tag_cosThetaDl;
      double sig_hp3, sig_cosBY, sig_vtxB;
      double mmiss_prime2, eextra50;
			double tag_Dmass, sig_Dmass;
			double tag_deltaM, tag_cosThetaDSoft, tag_softP3MagCM;
			double sig_deltaM, sig_cosThetaDSoft, sig_softP3MagCM;
			double sig_hmass, sig_vtxh;
      int tag_Dtype, tag_Dstartype;
      int sig_Dtype, sig_Dstartype;
    };

  protected: 
    int nr_targets;
    int nr_svm_features;
    svm_model *model;

    double upper, lower;
    double *feature_max, *feature_min;
    void load_svm_scale(const char *scale_fname);
    void svm_scale();

    svm_node *x;
    void clear_x();

    double *prob;

    void Initialize(const char *model_fname,
                    const char *scale_fname);
    void Cleanup();

  public:
    CandidateSVM(int nr_targets, int nr_svm_features); 
    virtual ~CandidateSVM() {};

    virtual void svm_predict(const features &ftrs) = 0;

		const double * get_prob() const { return prob; }

};  

#endif   /* ----- #ifndef CandidateSVM_INC  ----- */
