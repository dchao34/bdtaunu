#include <iostream>
#include <string>
#include <vector>

#include <unistd.h>
#include <errno.h>
#include <sqlite3.h>

#include "create_database/UpsilonList.h"
#include "create_database/BDtaunuSigMcReader.h"
#include "create_database/McEventSQLiteTableBuilder.h"
#include "create_database/McCandidateSQLiteTableBuilder.h"

#include "utilities/helpers.h"

using namespace std;

int main() {

  const char *dbname = "sigmc.db";
  if (access(dbname, F_OK) == 0) {
    cout << "error: cannot create \"" << dbname << "\". " << endl;
    cout << "another file with the same name already exists. " << endl;
    return errno;
  }

  int db_status;
  sqlite3 *db = NULL;
  db_status = sqlite3_open_v2(dbname, &db, 
      SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, NULL);
  if (db_status != SQLITE_OK) {
    cout << sqlite3_errmsg(db) << endl;
    return db_status;
  }

  char *errmsg;
  sqlite3_exec(db, "BEGIN TRANSACTION", NULL, NULL, &errmsg);

  McEventSQLiteTableBuilder event_builder(db, "meta/sigmc_ml_assignment.txt");
  event_builder.CreateTable();

  McCandidateSQLiteTableBuilder candidate_builder(db);
  candidate_builder.CreateTable();

  for (int spmode = 11444; spmode <= 11444; spmode++) {
    for (int run = 1; run <= 1; run++) {

      string root_fname = "data/root/signal/may_16_2014/A/";
      root_fname += ("sp" + to_string(spmode) + "r" + to_string(run) + ".root");
      string trname = "ntp1";

      BDtaunuSigMcReader rootreader(root_fname.c_str(), trname.c_str());
      vector<int> truth_match;
      while (rootreader.next_record() != -1) {

        UpsilonList candidates = rootreader.get_candidate_list();
        truth_match = rootreader.get_truth_match();

        event_builder.set_babar_event_id(rootreader.get_eventId());
        event_builder.set_run(run);
        event_builder.set_sp_mode(spmode);
        event_builder.set_mc_evttype(rootreader.get_mc_evttype());
        event_builder.set_nTrk(rootreader.get_nTrk());
        event_builder.set_R2(rootreader.get_R2All());
        event_builder.set_nY(rootreader.get_nY());
        event_builder.InsertTable();

        while (candidates.next_candidate() != -1) {
          UpsilonCandidate curr_cand = candidates.get_current_candidate();

          candidate_builder.set_babar_event_id(curr_cand.get_eventId());
          candidate_builder.set_cand_idx(curr_cand.get_event_candidate_index());
          candidate_builder.set_cand_type(curr_cand.get_cand_type());
          candidate_builder.set_samp_type(curr_cand.get_sample_type());
          candidate_builder.set_truth_match(truth_match[curr_cand.get_event_candidate_index()]);
          candidate_builder.set_mmiss_prime2(curr_cand.get_mmiss_prime2());
          candidate_builder.set_eextra50(curr_cand.get_eextra50());
          candidate_builder.set_cosThetaT(curr_cand.get_cosThetaT());
          candidate_builder.set_tag_lp3(curr_cand.get_tag_lp3());
          candidate_builder.set_tag_cosBY(curr_cand.get_tag_cosBY());
          candidate_builder.set_tag_cosThetaDl(curr_cand.get_tag_cosThetaDl());
          candidate_builder.set_tag_Dmass(curr_cand.get_tag_Dmass());
          candidate_builder.set_tag_deltaM(curr_cand.get_tag_deltaM());
          candidate_builder.set_tag_cosThetaDSoft(curr_cand.get_tag_cosThetaDSoft());
          candidate_builder.set_tag_softP3MagCM(curr_cand.get_tag_softP3MagCM());
          candidate_builder.set_tag_Dtype(curr_cand.get_tag_d_mode());
          candidate_builder.set_tag_Dstartype(curr_cand.get_tag_dstar_mode());
          candidate_builder.set_sig_hp3(curr_cand.get_sig_hp3());
          candidate_builder.set_sig_cosBY(curr_cand.get_sig_cosBY());
          candidate_builder.set_sig_cosThetaDtau(curr_cand.get_sig_cosThetaDtau());
          candidate_builder.set_sig_vtxB(curr_cand.get_sig_vtxB());
          candidate_builder.set_sig_Dmass(curr_cand.get_sig_Dmass());
          candidate_builder.set_sig_deltaM(curr_cand.get_sig_deltaM());
          candidate_builder.set_sig_cosThetaDSoft(curr_cand.get_sig_cosThetaDSoft());
          candidate_builder.set_sig_softP3MagCM(curr_cand.get_sig_softP3MagCM());
          candidate_builder.set_sig_hmass(curr_cand.get_sig_hmass());
          candidate_builder.set_sig_vtxh(curr_cand.get_sig_vtxh());
          candidate_builder.set_sig_Dtype(curr_cand.get_sig_d_mode());
          candidate_builder.set_sig_Dstartype(curr_cand.get_sig_dstar_mode());

          candidate_builder.InsertTable();
        }
      }
    }
  }

  sqlite3_exec(db, "END TRANSACTION", NULL, NULL, &errmsg);
  sqlite3_close_v2(db);

  return 0;
}
