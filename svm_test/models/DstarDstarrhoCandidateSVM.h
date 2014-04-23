#ifndef  DstarDstarrhoCandidateSVM_INC
#define  DstarDstarrhoCandidateSVM_INC

#include "svm.h"
#include "CandidateSVM.h"

class DstarDstarrhoCandidateSVM : public CandidateSVM {

  private: 
		int nr_svm_num_features;
		int nr_svm_ind_Ddectype;
		int nr_svm_ind_Dstardectype;
    int get_Dtype_group(int Dtype) const;
    int get_Dstartype_group(int Dstartype) const;

  public:
    DstarDstarrhoCandidateSVM(const char *model_fname, 
														  const char *scale_fname);
    ~DstarDstarrhoCandidateSVM();

    void svm_predict(const CandidateSVM::features &ftr);
    
};  

#endif   /* ----- #ifndef DstarDstarrhoCandidateSVM_INC  ----- */
