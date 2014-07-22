#ifndef __EVENTSVMSCORER_H__
#define __EVENTSVMSCORER_H__

#include "create_database/UpsilonCandidate.h"

#include "EventFeatureExtractor.h"
#include "EventSvmAdapter.h"

class EventSvmScorer {

  private: 
    SignalFeatureExtractor *signal_extr;
    ContinuumFeatureExtractor *continuum_extr;

    SignalSvmAdapter *signal_adtr;
    ContinuumSvmAdapter *continuum_adtr;

    double signal_score;
    double continuum_score;
    bool passed_precuts_flag;

  public:
    EventSvmScorer(); 
    ~EventSvmScorer(); 

    void predict(const Event &event);

    double get_signal_score() const { return signal_score; }
    double get_continuum_score() const { return continuum_score; }
    bool passed_precuts() const { return passed_precuts_flag; }

};

#endif
