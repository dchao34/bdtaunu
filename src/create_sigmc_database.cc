#include <sqlite3.h>
#include <iostream>
#include <vector>
#include <cassert>

#include "BDtaunuSigMcReader.h"
#include "DatReader.h"
#include "UpsilonList.h"

#include "utilities.h"
#include "create_sigmc_database.h"
 
int create_sigmc_candidate_table(sqlite3 *db) {

  int db_status;
  sqlite3_stmt *stmt = NULL;

  db_status = sqlite3_prepare_v2(db, "CREATE TABLE candidates("
      "id INTEGER PRIMARY KEY, "
      "babar_event_id TEXT, "
      "event_candidate_index INTEGER, "
      "truth_match INTEGER, "
      "tag_lp3 REAL, "
      "sig_hp3 REAL, "
      "tag_cosBY REAL, "
      "sig_cosBY REAL, "
      "tag_cosThetaDl REAL, "
      "sig_vtxB REAL, "
      "mmiss_prime2 REAL, "
      "eextra50 REAL, "
      "tag_Dmass REAL, "
      "tag_deltaM REAL, "
      "tag_cosThetaDSoft REAL, "
      "tag_softP3MagCM REAL, "
      "sig_Dmass REAL, "
      "sig_deltaM REAL, "
      "sig_cosThetaDSoft REAL, "
      "sig_softP3MagCM REAL, "
      "sig_hmass REAL, "
      "sig_vtxh REAL, "
      "tag_Dtype INTEGER, "
      "tag_Dstartype INTEGER, "
      "sig_Dtype INTEGER, "
      "sig_Dstartype INTEGER, "
      "cand_type INTEGER, "
      "FOREIGN KEY(babar_event_id) REFERENCES events(babar_event_id)"
      ");", -1, &stmt, NULL);
  db_status = sqlite3_step(stmt);
  db_status = sqlite3_finalize(stmt);

  return db_status;
}

int insert_sigmc_table(sqlite3 *db, 
    const char *root_fname, 
    const char *root_trname) {

  int db_status;

  sqlite3_stmt *candidate_stmt = NULL;
  db_status = sqlite3_prepare_v2(db, 
      "INSERT INTO candidates("
      "babar_event_id, "
      "event_candidate_index, "
      "truth_match, "
      "tag_lp3, "
      "sig_hp3, "
      "tag_cosBY, "
      "sig_cosBY, "
      "tag_cosThetaDl, "
      "sig_vtxB, "
      "mmiss_prime2, "
      "eextra50, "
      "tag_Dmass, "
      "tag_deltaM, "
      "tag_cosThetaDSoft, "
      "tag_softP3MagCM, "
      "sig_Dmass, "
      "sig_deltaM, "
      "sig_cosThetaDSoft, "
      "sig_softP3MagCM, "
      "sig_hmass, "
      "sig_vtxh, "
      "tag_Dtype, "
      "tag_Dstartype, "
      "sig_Dtype, "
      "sig_Dstartype, "
      "cand_type "
      ") VALUES("
      "@babar_event_id, "
      "@event_candidate_index, "
      "@truth_match, "
      "@tag_lp3, "
      "@sig_hp3, "
      "@tag_cosBY, "
      "@sig_cosBY, "
      "@tag_cosThetaDl, "
      "@sig_vtxB, "
      "@mmiss_prime2, "
      "@eextra50, "
      "@tag_Dmass, "
      "@tag_deltaM, "
      "@tag_cosThetaDSoft, "
      "@tag_softP3MagCM, "
      "@sig_Dmass, "
      "@sig_deltaM, "
      "@sig_cosThetaDSoft, "
      "@sig_softP3MagCM, "
      "@sig_hmass, "
      "@sig_vtxh, "
      "@tag_Dtype, "
      "@tag_Dstartype, "
      "@sig_Dtype, "
      "@sig_Dstartype, "
      "@cand_type "
      ");", -1, &candidate_stmt, NULL);

  int counter = 0;

  BDtaunuSigMcReader rootreader(root_fname, root_trname);
  while (rootreader.next_record() != -1) {
    if (counter % 1000 == 0) {
      std::cout << "processing event " << counter << std::endl;
    }
    counter += 1;

    std::vector<int> truth_match = rootreader.get_truth_match();
    if (truth_match.size() == 0) 
      continue;

    UpsilonList candidates = rootreader.get_candidate_list();
    while (candidates.next_candidate() != -1) {
      unsigned cand_idx = candidates.get_current_candidate().get_event_candidate_index();
      assert(cand_idx < truth_match.size());

      db_status = sqlite3_bind_text(candidate_stmt, sqlite3_bind_parameter_index(candidate_stmt, "@babar_event_id"), candidates.get_current_candidate().get_eventId().c_str(), -1, SQLITE_STATIC);
      db_status = sqlite3_bind_int(candidate_stmt, sqlite3_bind_parameter_index(candidate_stmt, "@event_candidate_index"), cand_idx);
      db_status = sqlite3_bind_int(candidate_stmt, sqlite3_bind_parameter_index(candidate_stmt, "@truth_match"), truth_match[cand_idx]);
      db_status = sqlite3_bind_double(candidate_stmt, sqlite3_bind_parameter_index(candidate_stmt, "@tag_lp3"), candidates.get_current_candidate().get_tag_lp3());
      db_status = sqlite3_bind_double(candidate_stmt, sqlite3_bind_parameter_index(candidate_stmt, "@sig_hp3"), candidates.get_current_candidate().get_sig_hp3());
      db_status = sqlite3_bind_double(candidate_stmt, sqlite3_bind_parameter_index(candidate_stmt, "@tag_cosBY"), candidates.get_current_candidate().get_tag_cosBY());
      db_status = sqlite3_bind_double(candidate_stmt, sqlite3_bind_parameter_index(candidate_stmt, "@sig_cosBY"), candidates.get_current_candidate().get_sig_cosBY());
      db_status = sqlite3_bind_double(candidate_stmt, sqlite3_bind_parameter_index(candidate_stmt, "@tag_cosThetaDl"), candidates.get_current_candidate().get_tag_cosThetaDl());
      db_status = sqlite3_bind_double(candidate_stmt, sqlite3_bind_parameter_index(candidate_stmt, "@sig_vtxB"), candidates.get_current_candidate().get_sig_vtxB());
      db_status = sqlite3_bind_double(candidate_stmt, sqlite3_bind_parameter_index(candidate_stmt, "@mmiss_prime2"), candidates.get_current_candidate().get_mmiss_prime2());
      db_status = sqlite3_bind_double(candidate_stmt, sqlite3_bind_parameter_index(candidate_stmt, "@eextra50"), candidates.get_current_candidate().get_eextra50());
      db_status = sqlite3_bind_double(candidate_stmt, sqlite3_bind_parameter_index(candidate_stmt, "@tag_Dmass"), candidates.get_current_candidate().get_tag_Dmass());
      db_status = sqlite3_bind_double(candidate_stmt, sqlite3_bind_parameter_index(candidate_stmt, "@tag_deltaM"), candidates.get_current_candidate().get_tag_deltaM());
      db_status = sqlite3_bind_double(candidate_stmt, sqlite3_bind_parameter_index(candidate_stmt, "@tag_cosThetaDSoft"), candidates.get_current_candidate().get_tag_cosThetaDSoft());
      db_status = sqlite3_bind_double(candidate_stmt, sqlite3_bind_parameter_index(candidate_stmt, "@tag_softP3MagCM"), candidates.get_current_candidate().get_tag_softP3MagCM());
      db_status = sqlite3_bind_double(candidate_stmt, sqlite3_bind_parameter_index(candidate_stmt, "@sig_Dmass"), candidates.get_current_candidate().get_sig_Dmass());
      db_status = sqlite3_bind_double(candidate_stmt, sqlite3_bind_parameter_index(candidate_stmt, "@sig_deltaM"), candidates.get_current_candidate().get_sig_deltaM());
      db_status = sqlite3_bind_double(candidate_stmt, sqlite3_bind_parameter_index(candidate_stmt, "@sig_cosThetaDSoft"), candidates.get_current_candidate().get_sig_cosThetaDSoft());
      db_status = sqlite3_bind_double(candidate_stmt, sqlite3_bind_parameter_index(candidate_stmt, "@sig_softP3MagCM"), candidates.get_current_candidate().get_sig_softP3MagCM());
      db_status = sqlite3_bind_double(candidate_stmt, sqlite3_bind_parameter_index(candidate_stmt, "@sig_hmass"), candidates.get_current_candidate().get_sig_hmass());
      db_status = sqlite3_bind_double(candidate_stmt, sqlite3_bind_parameter_index(candidate_stmt, "@sig_vtxh"), candidates.get_current_candidate().get_sig_vtxh());
      db_status = sqlite3_bind_int(candidate_stmt, sqlite3_bind_parameter_index(candidate_stmt, "@tag_Dtype"), candidates.get_current_candidate().get_tag_d_mode());
      db_status = sqlite3_bind_int(candidate_stmt, sqlite3_bind_parameter_index(candidate_stmt, "@tag_Dstartype"), candidates.get_current_candidate().get_tag_dstar_mode());
      db_status = sqlite3_bind_int(candidate_stmt, sqlite3_bind_parameter_index(candidate_stmt, "@sig_Dtype"), candidates.get_current_candidate().get_sig_d_mode());
      db_status = sqlite3_bind_int(candidate_stmt, sqlite3_bind_parameter_index(candidate_stmt, "@sig_Dstartype"), candidates.get_current_candidate().get_sig_dstar_mode());
      db_status = sqlite3_bind_double(candidate_stmt, sqlite3_bind_parameter_index(candidate_stmt, "@cand_type"), candidates.get_current_candidate().get_cand_type());
      db_status = sqlite3_step(candidate_stmt);
      db_status = sqlite3_reset(candidate_stmt);
    }

  }

  db_status = sqlite3_finalize(candidate_stmt);

  return db_status;
}

int make_mlsample_assignment_table(
    sqlite3 *db, 
    const char *ml_assignment_fname) {

  char *errmsg;
  sqlite3_exec(db, "BEGIN TRANSACTION", NULL, NULL, &errmsg);

  int db_status;
  sqlite3_stmt *stmt = NULL;
  db_status = sqlite3_prepare_v2(db, "CREATE TABLE ml_sample("
      "babar_event_id TEXT UNIQUE, "
      "ml_sample TEXT "
      ");", -1, &stmt, NULL);
  db_status = sqlite3_step(stmt);
  db_status = sqlite3_finalize(stmt);

  stmt = NULL;
  db_status = sqlite3_prepare_v2(db, 
      "INSERT INTO ml_sample("
      "babar_event_id, "
      "ml_sample"
      ") VALUES("
      "?1, ?2"
      ");", -1, &stmt, NULL);

  DatReader datreader(ml_assignment_fname, "|");
  while (datreader.read_next_line()) {
    db_status = sqlite3_bind_text(stmt, 1, datreader.get_field("eventId").c_str(), -1, SQLITE_STATIC);
    db_status = sqlite3_bind_text(stmt, 2, datreader.get_field("ml_sample").c_str(), -1, SQLITE_STATIC);
    db_status = sqlite3_step(stmt);
    db_status = sqlite3_reset(stmt);
  }

  db_status = sqlite3_finalize(stmt);

  sqlite3_exec(db, "END TRANSACTION", NULL, NULL, &errmsg);

  return db_status;
}
