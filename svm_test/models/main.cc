#include <iostream>

#include "svm.h"
#include "CandidateSVM.h"
#include "DDpiCandidateSVM.h"
#include "DstarDstarrhoCandidateSVM.h"

using namespace std;

int main() {
  DDpiCandidateSVM svm("DDpi/DDpi_train.scale.model", "DDpi/DDpi_range");
	CandidateSVM::features features;
	features.tag_lp3 = 1.83153;
	features.tag_cosBY = -1.13939;
  features.tag_cosThetaDl = -0.923469;
  features.sig_hp3 = 0.127902;
  features.sig_cosBY = -12.2005;
  features.sig_vtxB = 0.0546098;
  features.mmiss_prime2 = -0.577507;
  features.eextra50 = 2.37059;
  features.tag_Dmass = 1.87982;
  features.sig_Dmass = 1.8645;
  features.tag_Dtype = 10;
  features.sig_Dtype = 8;
  svm.svm_predict(features);
	const double *prob = svm.get_prob();
	cout << prob[0] << " " << prob[1] << endl;

	features.tag_lp3 = 1.83153;
	features.tag_cosBY = -0.985064;
  features.tag_cosThetaDl = -0.936036;
  features.sig_hp3 = 0.536418;
  features.sig_cosBY = -14.7438;
  features.sig_vtxB = 0.0461822;
  features.mmiss_prime2 = -1.90693;
  features.eextra50 = 2.37059;
  features.tag_Dmass = 1.82847;
  features.sig_Dmass = 1.8645;
  features.tag_Dtype = 10;
  features.sig_Dtype = 8;

  svm.svm_predict(features);
	prob = svm.get_prob();
	cout << prob[0] << " " << prob[1] << endl;
 
  return 0;
}
