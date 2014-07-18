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
#include "create_database/EventStatusSQLiteTableBuilder.h"
#include "create_database/OptimalCandidateSQLiteTableBuilder.h"

#include "candidate_selection/YCandSvmScorer.h"

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

  EventStatusSQLiteTableBuilder status_builder(db);
  status_builder.CreateTable();

  OptimalCandidateSQLiteTableBuilder optcand_builder(db);
  optcand_builder.CreateTable();

  YCandSvmScorer svm_scorer;

  string data_folders[2] = { "data/root/signal/may_16_2014/A/", 
                             "data/root/signal/may_16_2014/B/" };

  for (int folder = 0; folder < 2; folder++) {
    for (int spmode = 11444; spmode <= 11447; spmode++) {
      for (int run = 1; run <= 6; run++) {

        string root_fname = data_folders[folder];
        root_fname += ("sp" + to_string(spmode) + "r" + to_string(run) + ".root");
        string trname = "ntp1";

        std::cout << "begin processing " << root_fname << "." << std::endl;

        int counter = 0;
        BDtaunuSigMcReader rootreader(root_fname.c_str(), trname.c_str());
        vector<int> truth_match;
        while (rootreader.next_record() != -1) {

          if (counter % 1000 == 0) {
            std::cout << "completed " << counter << " events." << std::endl;
          }
          counter += 1;

          if (rootreader.IsMaxCandidateExceeded()) 
            continue;

          UpsilonList candidates = rootreader.get_candidate_list();
          truth_match = rootreader.get_truth_match();

          if (truth_match.size() == 0) 
            continue;

          event_builder.set_babar_event_id(rootreader.get_eventId());
          event_builder.set_run(run);
          event_builder.set_sp_mode(spmode);
          event_builder.set_event_weight(1.0);
          event_builder.set_b1mctype(rootreader.get_b1mctype());
          event_builder.set_b2mctype(rootreader.get_b2mctype());
          event_builder.set_nTrk(rootreader.get_nTrk());
          event_builder.set_R2(rootreader.get_R2All());
          event_builder.set_nY(rootreader.get_nY());
          event_builder.InsertTable();

          int svm_optcand_idx = 0;
          double max_svm_score = 0;
          int min_eextra_optcand_idx = -1;
          double min_eextra = 10.0;
          int no_candidates_passed_cuts = 1;
          while (candidates.next_candidate() != -1) {

            UpsilonCandidate curr_cand = candidates.get_current_candidate();
            svm_scorer.predict(curr_cand);

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
            candidate_builder.set_svm_score(svm_scorer.get_score());

            candidate_builder.InsertTable();

            if (svm_scorer.passed_selection()) {
              no_candidates_passed_cuts = 0;
            }

            int curr_cand_idx = curr_cand.get_event_candidate_index();

            double svm_score = svm_scorer.get_score();
            if (svm_score > max_svm_score) {
              max_svm_score = svm_score;
              svm_optcand_idx = curr_cand_idx;
            }

            double eextra = curr_cand.get_eextra50();
            if (eextra < min_eextra) {
              min_eextra = eextra;
              min_eextra_optcand_idx = curr_cand_idx;
            }
          }

          status_builder.set_babar_event_id(rootreader.get_eventId());
          status_builder.InsertTable();

          optcand_builder.set_babar_event_id(rootreader.get_eventId());
          optcand_builder.set_svm_optcand_idx(svm_optcand_idx);
          optcand_builder.set_min_eextra_optcand_idx(min_eextra_optcand_idx);
          optcand_builder.InsertTable();

        }

        std::cout << "done. " << std::endl;
        std::cout << std::endl;

      }
    }
  }

  sqlite3_exec(db, "END TRANSACTION", NULL, NULL, &errmsg);
  sqlite3_close_v2(db);

  return 0;
}
