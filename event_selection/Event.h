#ifndef __EVENT_H__
#define __EVENT_H__

#include <string> 

#include "create_database/UpsilonCandidate.h"

class Event {

  private:
    int id;
    std::string eventId;
    int run;
    double event_weight;

    int nY;
    int nTrk;
    float R2;

    UpsilonCandidate ups;

    double ups_svm_score;

    int mc_evttype;
    int sp_mode;

    void copy_event(const Event &event);

  public:
    Event();
    Event(
        int id, const std::string &eventId, int run, 
        double event_weight, int nY, 
        int nTrk, float R2, 
        const UpsilonCandidate &ups,
        double ups_svm_score,
        int mc_evttype, int sp_mode);

    Event(const Event &event);
    ~Event() {};

    Event & operator=(const Event &event);

    int get_id() const { return id; }
    std::string get_eventId() const { return eventId; }
    int get_run() const { return run; }
    float get_event_weight() const { return event_weight; }
    int get_nY() const { return nY; }
    int get_nTrk() const { return nTrk; }
    float get_R2() const { return R2; }
    UpsilonCandidate get_upsilon() const { return ups; }

    double get_ups_svm_score() const { return ups_svm_score; }

    int get_mc_evttype() const { return mc_evttype; }
    int get_sp_mode() const { return sp_mode; }
};

#endif
