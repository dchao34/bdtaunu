#ifndef  DDpiCandidateSVM_INC
#define  DDpiCandidateSVM_INC

#include "svm.h"
#include "CandidateSVM.h"

class DDpiCandidateSVM : public CandidateSVM {

  private: 
		int nr_svm_num_features;
		int nr_svm_ind_Ddectype;
    int get_Dtype_group(int Dtype) const;

  public:
    DDpiCandidateSVM(const char *model_fname, 
                     const char *scale_fname);
    ~DDpiCandidateSVM();

    void svm_predict(const CandidateSVM::features &ftr);
    
};  

#endif   /* ----- #ifndef DDpiCandidateSVM_INC  ----- */
