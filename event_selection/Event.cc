#include <string> 
#include <cassert> 

#include "Event.h"

Event::Event() : 
  id(-1), eventId(""), run(-1), 
  event_weight(1), nY(-1), 
  nTrk(-1), R2(-999), 
  ups(), ups_svm_score(-1),
  mc_evttype(-1), sp_mode(-1) {
}

Event::Event(
    int id,
    const std::string& eventId, int run, 
    double event_weight, int nY, 
    int nTrk, float R2, 
    const UpsilonCandidate &ups,
    double ups_svm_score, 
    int mc_evttype, int sp_mode) :
  id(id), eventId(eventId), run(run), 
  event_weight(event_weight), nY(nY), 
  nTrk(nTrk), R2(R2), 
  ups(ups), ups_svm_score(ups_svm_score), 
  mc_evttype(mc_evttype), sp_mode(sp_mode) {
}

Event::Event(const Event &event) {
  copy_event(event);
}

void Event::copy_event(const Event &event) {
  id = event.id;
  eventId = event.eventId;
  run = event.run;
  event_weight = event.event_weight;
  nY = event.nY;
  nTrk = event.nTrk;
  R2 = event.R2;
  ups = event.ups;
  ups_svm_score = event.ups_svm_score;
  mc_evttype = event.mc_evttype;
  sp_mode = event.sp_mode;
}

Event & Event::operator=(const Event &event) {
  if (this != &event) {
    copy_event(event);
  }
  return *this;
}
