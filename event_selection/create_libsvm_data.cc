#include <iostream>
#include <fstream>
#include <string>

#include "EventSQLiteReader.h"
#include "EventFeatureExtractor.h"
#include "EventFeatureExtractorFactory.h"

using namespace std;

void print_usage(char **argv) {
  cout << endl;
  cout << "Description: Retrieves event records from SQL database, " << endl;
  cout << "extract features, and outputs libsvm files. " << endl;
  cout << endl;
  cout << "Usage: " << argv[0] << " "
       << "event_extractor_type "
       << "ml_sample_type "
       << "division "
       << endl;
  cout << "  event_extractor_type: One of the following strings." << endl;
  cout << "     sig, or cont" << endl;
  cout << endl;
  cout << "  ml_sample_type: One of the following strings." << endl;
  cout << "     all, explore, train, validate, or test" << endl;
  cout << endl;
  cout << "  division: 1-10. -1 for all" << endl;
  cout << endl;
  exit(EXIT_FAILURE);
}

int main(int argc, char **argv) {

  if (argc != 4) {
    print_usage(argv);
  }

  EventSQLiteReader *reader = 
    new EventSQLiteReader("generic.db", argv[2], argv[3]);

  EventFeatureExtractor *extractor = 
    EventFeatureExtractorFactory::CreateExtractor(argv[1]);

  string libsvm_fname = string(argv[1]) + "." + string(argv[2]);
  ofstream libsvm_file(libsvm_fname.c_str(), ofstream::out);

  string weight_fname = libsvm_fname + ".wgt";
  ofstream weight_file(weight_fname.c_str(), ofstream::out);

  while (reader->next_record()) {
    extractor->set_id(reader->get_id());
    extractor->set_mc_evttypeA(reader->get_mc_evttypeA());
    extractor->set_event_weight(reader->get_event_weight());
    extractor->set_cand_type(reader->get_cand_type());
    extractor->set_tag_Dtype(reader->get_tag_Dtype());
    extractor->set_tag_Dstartype(reader->get_tag_Dstartype());
    extractor->set_sig_Dtype(reader->get_sig_Dtype());
    extractor->set_sig_Dstartype(reader->get_sig_Dstartype());
    extractor->set_nTrk(reader->get_nTrk());
    extractor->set_R2(reader->get_R2());
    extractor->set_cosThetaT(reader->get_cosThetaT());
    extractor->set_eextra50(reader->get_eextra50());
    extractor->set_mmiss_prime2(reader->get_mmiss_prime2());
    extractor->set_tag_lp3(reader->get_tag_lp3());
    extractor->set_tag_cosBY(reader->get_tag_cosBY());
    extractor->set_tag_cosThetaDl(reader->get_tag_cosThetaDl());
    extractor->set_sig_hp3(reader->get_sig_hp3());
    extractor->set_sig_cosBY(reader->get_sig_cosBY());
    extractor->set_sig_cosThetaDtau(reader->get_sig_cosThetaDtau());
    extractor->set_sig_vtxB(reader->get_sig_vtxB());
    extractor->set_svm_score(reader->get_svm_score());
    extractor->set_tag_Dmass(reader->get_tag_Dmass());
    extractor->set_tag_deltaM(reader->get_tag_deltaM());
    extractor->set_tag_cosThetaDSoft(reader->get_tag_cosThetaDSoft());
    extractor->set_tag_softP3MagCM(reader->get_tag_softP3MagCM());
    extractor->set_sig_Dmass(reader->get_sig_Dmass());
    extractor->set_sig_deltaM(reader->get_sig_deltaM());
    extractor->set_sig_cosThetaDSoft(reader->get_sig_cosThetaDSoft());
    extractor->set_sig_softP3MagCM(reader->get_sig_softP3MagCM());
    extractor->set_sig_hmass(reader->get_sig_hmass());
    extractor->set_sig_vtxh(reader->get_sig_vtxh());


    if (!extractor->passed_selection()) {
      continue;
    }

    if (extractor->categorize_event_type() == 0) {
      continue;
    }

    extractor->extract_features();
    libsvm_file << extractor->get_libsvm_line() << endl;
    weight_file << extractor->get_event_weight() << endl;

  }

  libsvm_file.close();
  weight_file.close();

  delete extractor;
  delete reader;

  return 0;

}
