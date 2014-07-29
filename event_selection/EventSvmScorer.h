#ifndef __EVENTSVMSCORER_H__
#define __EVENTSVMSCORER_H__

#include "create_database/UpsilonCandidate.h"

#include "EventFeatureExtractor.h"
#include "EventSvmAdapter.h"

class EventSvmScorer {

  private: 
    SignalFeatureExtractor *signal_extr;
    ContinuumFeatureExtractor *continuum_extr;
    SigVsSLFeatureExtractor *sig_sl_extr;
    SigVsHadFeatureExtractor *sig_had_extr;
    SigVsContFeatureExtractor *sig_cont_extr;
    SigVsAllFeatureExtractor *sig_all_extr;

    SignalSvmAdapter *signal_adtr;
    ContinuumSvmAdapter *continuum_adtr;
    SigVsSLSvmAdapter *sig_sl_adtr;
    SigVsHadSvmAdapter *sig_had_adtr;
    SigVsContSvmAdapter *sig_cont_adtr;
    SigVsAllSvmAdapter *sig_all_adtr;

    double signal_score;
    double continuum_score;
    double sig_sl_score;
    double sig_had_score;
    double sig_cont_score;
    double sig_all_score;
    bool passed_precuts_flag;

  public:
    EventSvmScorer(); 
    ~EventSvmScorer(); 

    void predict(const Event &event);

    double get_signal_score() const { return signal_score; }
    double get_continuum_score() const { return continuum_score; }
    double get_sig_sl_score() const { return sig_sl_score; }
    double get_sig_had_score() const { return sig_had_score; }
    double get_sig_cont_score() const { return sig_cont_score; }
    double get_sig_all_score() const { return sig_all_score; }
    bool passed_precuts() const { return passed_precuts_flag; }

};

#endif
