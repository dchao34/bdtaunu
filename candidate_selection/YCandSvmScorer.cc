#include <cassert>

#include "YCandSvmScorer.h"
#include "create_database/UpsilonCandidate.h"
#include "bdtaunu_definitions.h"

YCandSvmScorer::YCandSvmScorer() {
    ddpi_extr = new DDpiFeatureExtractor();
    ddstarpi_extr = new DDstarpiFeatureExtractor();
    dstardpi_extr = new DstarDpiFeatureExtractor();
    dstardstarpi_extr = new DstarDstarpiFeatureExtractor();
    ddrho_extr = new DDrhoFeatureExtractor();
    ddstarrho_extr = new DDstarrhoFeatureExtractor();
    dstardrho_extr = new DstarDrhoFeatureExtractor();
    dstardstarrho_extr = new DstarDstarrhoFeatureExtractor();

    ddpi_adtr = new DDpiSvmAdapter();
    ddstarpi_adtr = new DDstarpiSvmAdapter();
    dstardpi_adtr = new DstarDpiSvmAdapter();
    dstardstarpi_adtr = new DstarDstarpiSvmAdapter();
    ddrho_adtr = new DDrhoSvmAdapter();
    ddstarrho_adtr = new DDstarrhoSvmAdapter();
    dstardrho_adtr = new DstarDrhoSvmAdapter();
    dstardstarrho_adtr = new DstarDstarrhoSvmAdapter();
}

YCandSvmScorer::~YCandSvmScorer() {
    delete ddpi_extr;
    delete ddstarpi_extr;
    delete dstardpi_extr;
    delete dstardstarpi_extr;
    delete ddrho_extr;
    delete ddstarrho_extr;
    delete dstardrho_extr;
    delete dstardstarrho_extr;

    delete ddpi_adtr;
    delete ddstarpi_adtr;
    delete dstardpi_adtr;
    delete dstardstarpi_adtr;
    delete ddrho_adtr;
    delete ddstarrho_adtr;
    delete dstardrho_adtr;
    delete dstardstarrho_adtr;
}

void YCandSvmScorer::SwitchAdapter(int cand_type) {
  switch (cand_type) {
    case kDDpi:
      curr_extr = ddpi_extr;
      curr_adtr = ddpi_adtr;
      break;
    case kDDstarpi:
      curr_extr = ddstarpi_extr;
      curr_adtr = ddstarpi_adtr;
      break;
    case kDstarDpi:
      curr_extr = dstardpi_extr;
      curr_adtr = dstardpi_adtr;
      break;
    case kDstarDstarpi:
      curr_extr = dstardstarpi_extr;
      curr_adtr = dstardstarpi_adtr;
      break;
    case kDDrho:
      curr_extr = ddrho_extr;
      curr_adtr = ddrho_adtr;
      break;
    case kDDstarrho:
      curr_extr = ddstarrho_extr;
      curr_adtr = ddstarrho_adtr;
      break;
    case kDstarDrho:
      curr_extr = dstardrho_extr;
      curr_adtr = dstardrho_adtr;
      break;
    case kDstarDstarrho:
      curr_extr = dstardstarrho_extr;
      curr_adtr = dstardstarrho_adtr;
      break;
    default: 
      assert(false);
  }
}

void YCandSvmScorer::predict(const UpsilonCandidate &cand) {
  SwitchAdapter(cand.get_cand_type());
  curr_extr->extract_features(cand);
  curr_adtr->set_features(*curr_extr);
  curr_adtr->svm_predict();
  predicted_score = (curr_adtr->get_prob())[0];
}

