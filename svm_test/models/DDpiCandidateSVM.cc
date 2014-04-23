#include <cassert> 

#include "CandidateSVM.h"
#include "DDpiCandidateSVM.h"

DDpiCandidateSVM::DDpiCandidateSVM(
	const char *model_fname, 
  const char *scale_fname) : 
	CandidateSVM(2, 24),
  nr_svm_num_features(10), nr_svm_ind_Ddectype(7) { 

	Initialize(model_fname, scale_fname);
}

DDpiCandidateSVM::~DDpiCandidateSVM() {
	Cleanup();
}

int DDpiCandidateSVM::get_Dtype_group(int Dtype) const {
  switch (Dtype) {
    case 1:
      return 0;
      break;
    case 2:
      return 1;
      break;
    case 7:
      return 2;
      break;
    case 8:
      return 3;
      break;
    case 9:
      return 4;
      break;
    case 10:
      return 5;
      break;
    case 3:
    case 4:
    case 5:
    case 12:
    case 13:
    case 14:
      return 6;
      break;
    default:
      // Dtype 6, 11, 15
      assert(false);
      return -1;
  }
}

 
void DDpiCandidateSVM::svm_predict(
		const CandidateSVM::features &ftrs) {

  clear_x();
  x[0].value = ftrs.tag_lp3;
  x[1].value = ftrs.tag_cosBY;
  x[2].value = ftrs.tag_cosThetaDl;
  x[3].value = ftrs.sig_hp3;
  x[4].value = ftrs.sig_cosBY;
  x[5].value = ftrs.sig_vtxB;
  x[6].value = ftrs.mmiss_prime2;
  x[7].value = ftrs.eextra50;
  x[8].value = ftrs.tag_Dmass;
  x[9].value = ftrs.sig_Dmass;
  x[nr_svm_num_features + get_Dtype_group(ftrs.tag_Dtype)].value = 1;
  x[nr_svm_num_features + nr_svm_ind_Ddectype + 
		get_Dtype_group(ftrs.sig_Dtype)].value = 1;

  svm_scale();
  svm_predict_probability(model, x, prob);

}
