#include <cassert> 

#include "CandidateSVM.h"
#include "DstarDstarrhoCandidateSVM.h"

DstarDstarrhoCandidateSVM::DstarDstarrhoCandidateSVM(
	const char *model_fname, 
  const char *scale_fname) : 
	CandidateSVM(2, 40),
  nr_svm_num_features(16), 
	nr_svm_ind_Ddectype(7),
	nr_svm_ind_Dstardectype(5) { 

	Initialize(model_fname, scale_fname);
}

DstarDstarrhoCandidateSVM::~DstarDstarrhoCandidateSVM() {
	Cleanup();
}

int DstarDstarrhoCandidateSVM::get_Dtype_group(int Dtype) const {
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

int DstarDstarrhoCandidateSVM::get_Dstartype_group(int Dstartype) const {
  switch (Dstartype) {
    case 1:
			return 0;
			break;
    case 2:
			return 1;
			break;
    case 3:
			return 2;
			break;
    case 4:
			return 3;
			break;
    case 5:
			return 4;
			break;
    default:
			assert(false);
			return -1;
			break;
	}
}

 
void DstarDstarrhoCandidateSVM::svm_predict(
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
  x[8].value = ftrs.tag_deltaM;
  x[9].value = ftrs.tag_cosThetaDSoft;
  x[10].value = ftrs.tag_softP3MagCM;
  x[11].value = ftrs.sig_deltaM;
  x[12].value = ftrs.sig_cosThetaDSoft;
  x[13].value = ftrs.sig_softP3MagCM;
  x[14].value = ftrs.sig_hmass;
  x[15].value = ftrs.sig_vtxh;
  x[nr_svm_num_features + 
		get_Dtype_group(ftrs.tag_Dtype)].value = 1;
  x[nr_svm_num_features + 
		nr_svm_ind_Ddectype + 
		get_Dstartype_group(ftrs.tag_Dstartype)].value = 1;
  x[nr_svm_num_features +
	  nr_svm_ind_Ddectype + nr_svm_ind_Dstardectype +
		get_Dtype_group(ftrs.sig_Dtype)].value = 1;
  x[nr_svm_num_features +
	  2 * nr_svm_ind_Ddectype + nr_svm_ind_Dstardectype +
		get_Dstartype_group(ftrs.sig_Dstartype)].value = 1;

  svm_scale();
  svm_predict_probability(model, x, prob);

}
