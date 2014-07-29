#include <sqlite3.h>

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <cstdlib>
#include <string>

#include "event_selection/EventSQLiteReader.h"
#include "event_selection/EventStatusSQLiteUpdater.h"
#include "event_selection/Event.h"
#include "create_database/UpsilonCandidate.h"
#include "event_selection/EventSvmScorer.h"

using namespace std;

struct Status {
  int failed_event_precuts;
  double signal_score;
  double continuum_score;
  double sig_sl_score;
  double sig_had_score;
  double sig_cont_score;
  double sig_all_score;
};

int main(int argc, char **argv) {

  EventSvmScorer svm_scorer;

  map<string, Status> updates;
  EventSQLiteReader *reader = new EventSQLiteReader("generic.db", "all", "-1");

  int counter = 0;
  while (reader->next_record()) {

    if (counter % 1000 == 0) {
      std::cout << "completed " << counter << " events." << std::endl;
    }
    counter += 1;

    string eventId = reader->get_babar_event_id();
    UpsilonCandidate ups(
        eventId, 
        -1, 
        reader->get_eextra50(),
        reader->get_mmiss_prime2(), 
        reader->get_tag_lp3(),
        reader->get_sig_hp3(), 
        reader->get_tag_cosBY(),
        reader->get_sig_cosBY(), 
        reader->get_tag_cosThetaDl(),
        reader->get_sig_cosThetaDtau(), 
        reader->get_sig_vtxB(), 
        reader->get_cosThetaT(), 
        reader->get_tag_Dmass(),
        reader->get_tag_deltaM(), 
        reader->get_tag_cosThetaDSoft(),
        reader->get_tag_softP3MagCM(),
        reader->get_sig_Dmass(),
        reader->get_sig_deltaM(), 
        reader->get_sig_cosThetaDSoft(),
        reader->get_sig_softP3MagCM(), 
        reader->get_sig_hmass(),
        reader->get_sig_vtxh(), 
        -1, 
        reader->get_tag_Dstartype(),
        reader->get_tag_Dtype(),
        reader->get_sig_Dstartype(),
        reader->get_sig_Dtype(),
        0);

    Event event(
        reader->get_id(),
        eventId, 
        -1, 
        reader->get_event_weight(), 
        -1, 
        reader->get_nTrk(),
        reader->get_R2(),
        ups, 
        reader->get_svm_score(), 
        reader->get_mc_evttypeA(),
        -1);

    svm_scorer.predict(event);

    Status s;

    if (!svm_scorer.passed_precuts()) {
      s.failed_event_precuts = 1;
    } else {
      s.failed_event_precuts = 0;
    }

    s.signal_score = svm_scorer.get_signal_score();
    s.continuum_score = svm_scorer.get_continuum_score();
    s.sig_sl_score = svm_scorer.get_sig_sl_score();
    s.sig_had_score = svm_scorer.get_sig_had_score();
    s.sig_cont_score = svm_scorer.get_sig_cont_score();
    s.sig_all_score = svm_scorer.get_sig_all_score();
    updates[reader->get_babar_event_id()] = s;
  }
  delete reader;

  EventStatusSQLiteUpdater updater("generic.db");
  map<string, Status>::iterator it = updates.begin();
  while (it != updates.end()) {
    updater.set_babar_event_id(it->first);
    updater.set_failed_event_precuts((it->second).failed_event_precuts);
    updater.set_signal_score((it->second).signal_score);
    updater.set_continuum_score((it->second).continuum_score);
    updater.set_sig_sl_score((it->second).sig_sl_score);
    updater.set_sig_had_score((it->second).sig_had_score);
    updater.set_sig_cont_score((it->second).sig_cont_score);
    updater.set_sig_all_score((it->second).sig_all_score);
    updater.UpdateTable();
    ++it;
  }

  return 0;

}
