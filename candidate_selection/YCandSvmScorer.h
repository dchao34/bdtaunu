#ifndef __YCANDSVMSCORER_H__
#define __YCANDSVMSCORER_H__

#include "create_database/UpsilonCandidate.h"

#include "YCandFeatureExtractor.h"
#include "YCandSvmAdapter.h"

class YCandSvmScorer {

  private: 
    DDpiFeatureExtractor *ddpi_extr;
    DDstarpiFeatureExtractor *ddstarpi_extr;
    DstarDpiFeatureExtractor *dstardpi_extr;
    DstarDstarpiFeatureExtractor *dstardstarpi_extr;
    DDrhoFeatureExtractor *ddrho_extr;
    DDstarrhoFeatureExtractor *ddstarrho_extr;
    DstarDrhoFeatureExtractor *dstardrho_extr;
    DstarDstarrhoFeatureExtractor *dstardstarrho_extr;

    DDpiSvmAdapter *ddpi_adtr;
    DDstarpiSvmAdapter *ddstarpi_adtr;
    DstarDpiSvmAdapter *dstardpi_adtr;
    DstarDstarpiSvmAdapter *dstardstarpi_adtr;
    DDrhoSvmAdapter *ddrho_adtr;
    DDstarrhoSvmAdapter *ddstarrho_adtr;
    DstarDrhoSvmAdapter *dstardrho_adtr;
    DstarDstarrhoSvmAdapter *dstardstarrho_adtr;

    YCandFeatureExtractor *curr_extr;
    YCandSvmAdapter *curr_adtr;

    void SwitchAdapter(int cand_type);

    double predicted_score;
    bool passed_cuts;

  public:
    YCandSvmScorer(); 
    ~YCandSvmScorer(); 

    void predict(const UpsilonCandidate &cand);

    double get_score() const { return predicted_score; }
    bool passed_selection() const { return passed_cuts; }

};

#endif
