#include <sqlite3.h>
#include <iostream>

#include "BDtaunuReader.h"
#include "BDtaunuMcReader.h"
#include "DatReader.h"
#include "UpsilonList.h"

#include "utilities.h"
#include "bdtaunu_create_sqldatabase.h"

int create_event_table(sqlite3 *db) {

  int db_status;
  sqlite3_stmt *stmt = NULL;

  db_status = sqlite3_prepare_v2(db, "CREATE TABLE events("
      "id INTEGER PRIMARY KEY, "
      "babar_event_id TEXT UNIQUE, "
      "run_number INTEGER, "
      "nTrk INTEGER, "
      "nY INTEGER, "
      "R2 REAL"
      ");", -1, &stmt, NULL);
  db_status = sqlite3_step(stmt);
  db_status = sqlite3_finalize(stmt);

  return db_status;
}

int create_monte_carlo_table(sqlite3 *db) {

  int db_status;
  sqlite3_stmt *stmt = NULL;

  db_status = sqlite3_prepare_v2(db, "CREATE TABLE monte_carlo("
      "id INTEGER PRIMARY KEY, "
      "babar_event_id TEXT UNIQUE, "
      "mc_evttype INTEGER"
      ");", -1, &stmt, NULL);
  db_status = sqlite3_step(stmt);
  db_status = sqlite3_finalize(stmt);

  return db_status;
}
 
int create_candidate_table(sqlite3 *db) {

  int db_status;
  sqlite3_stmt *stmt = NULL;

  db_status = sqlite3_prepare_v2(db, "CREATE TABLE candidates("
      "id INTEGER PRIMARY KEY, "
      "babar_event_id TEXT, "
      "event_candidate_index INTEGER, "
      "tag_lp3 REAL, "
      "sig_hp3 REAL, "
      "tag_cosBY REAL, "
      "sig_cosBY REAL, "
      "tag_cosThetaDl REAL, "
      "sig_cosThetaDtau REAL, "
      "sig_vtxB REAL, "
      "mmiss_prime2 REAL, "
      "eextra50 REAL, "
      "cosThetaT REAL, "
      "tag_Dtype INTEGER, "
      "tag_Dstartype INTEGER, "
      "tag_Dmass REAL, "
      "tag_deltaM REAL, "
      "tag_cosThetaDSoft REAL, "
      "tag_softP3MagCM REAL, "
      "sig_Dtype INTEGER, "
      "sig_Dstartype INTEGER, "
      "sig_Dmass REAL, "
      "sig_deltaM REAL, "
      "sig_cosThetaDSoft REAL, "
      "sig_softP3MagCM REAL, "
      "sig_hmass REAL, "
      "sig_vtxh REAL, "
      "cand_type INTEGER, "
      "samp_type INTEGER, "
      "FOREIGN KEY(babar_event_id) REFERENCES events(babar_event_id)"
      ");", -1, &stmt, NULL);
  db_status = sqlite3_step(stmt);
  db_status = sqlite3_finalize(stmt);

  return db_status;
}

int insert_table(sqlite3 *db, 
    const char *root_fname, 
    const char *root_trname, 
    int run) {

  int db_status;
  sqlite3_stmt *event_stmt = NULL;
  db_status = sqlite3_prepare_v2(db, 
      "INSERT INTO events("
      "babar_event_id, "
      "run_number, "
      "nTrk, "
      "nY, "
      "R2"
      ") VALUES("
      "@babar_event_id, "
      "@run_number, "
      "@nTrk, "
      "@nY, "
      "@R2"
      ");", -1, &event_stmt, NULL);

  sqlite3_stmt *monte_carlo_stmt = NULL;
  db_status = sqlite3_prepare_v2(db, 
      "INSERT INTO monte_carlo("
      "babar_event_id, "
      "mc_evttype"
      ") VALUES("
      "@babar_event_id, "
      "@mc_evttype"
      ");", -1, &monte_carlo_stmt, NULL);

  sqlite3_stmt *candidate_stmt = NULL;
  db_status = sqlite3_prepare_v2(db, 
      "INSERT INTO candidates("
      "babar_event_id, "
      "event_candidate_index, "
      "tag_lp3, "
      "sig_hp3, "
      "tag_cosBY, "
      "sig_cosBY, "
      "tag_cosThetaDl, "
      "sig_cosThetaDtau, "
      "sig_vtxB, "
      "mmiss_prime2, "
      "eextra50, "
      "cosThetaT, "
      "tag_Dtype, "
      "tag_Dstartype, "
      "tag_Dmass, "
      "tag_deltaM, "
      "tag_cosThetaDSoft, "
      "tag_softP3MagCM, "
      "sig_Dtype, "
      "sig_Dstartype, "
      "sig_Dmass, "
      "sig_deltaM, "
      "sig_cosThetaDSoft, "
      "sig_softP3MagCM, "
      "sig_hmass, "
      "sig_vtxh, "
      "cand_type, "
      "samp_type "
      ") VALUES("
      "@babar_event_id, "
      "@event_candidate_index, "
      "@tag_lp3, "
      "@sig_hp3, "
      "@tag_cosBY, "
      "@sig_cosBY, "
      "@tag_cosThetaDl, "
      "@sig_cosThetaDtau, "
      "@sig_vtxB, "
      "@mmiss_prime2, "
      "@eextra50, "
      "@cosThetaT, "
      "@tag_Dtype, "
      "@tag_Dstartype, "
      "@tag_Dmass, "
      "@tag_deltaM, "
      "@tag_cosThetaDSoft, "
      "@tag_softP3MagCM, "
      "@sig_Dtype, "
      "@sig_Dstartype, "
      "@sig_Dmass, "
      "@sig_deltaM, "
      "@sig_cosThetaDSoft, "
      "@sig_softP3MagCM, "
      "@sig_hmass, "
      "@sig_vtxh, "
      "@cand_type, "
      "@samp_type"
      ");", -1, &candidate_stmt, NULL);

  BDtaunuMcReader rootreader(root_fname, root_trname);
  while (rootreader.next_record() != -1) {

    db_status = sqlite3_bind_text(event_stmt, sqlite3_bind_parameter_index(event_stmt, "@babar_event_id"), rootreader.get_eventId().c_str(), -1, SQLITE_STATIC);
    db_status = sqlite3_bind_int(event_stmt, sqlite3_bind_parameter_index(event_stmt, "@run_number"), run);
    db_status = sqlite3_bind_int(event_stmt, sqlite3_bind_parameter_index(event_stmt, "@nTrk"), rootreader.get_nTrk());
    db_status = sqlite3_bind_int(event_stmt, sqlite3_bind_parameter_index(event_stmt, "@nY"), rootreader.get_nY());
    db_status = sqlite3_bind_double(event_stmt, sqlite3_bind_parameter_index(event_stmt, "@R2"), rootreader.get_R2All());
    db_status = sqlite3_step(event_stmt);
    db_status = sqlite3_reset(event_stmt);

    db_status = sqlite3_bind_text(monte_carlo_stmt, sqlite3_bind_parameter_index(monte_carlo_stmt, "@babar_event_id"), rootreader.get_eventId().c_str(), -1, SQLITE_STATIC);
    db_status = sqlite3_bind_int(monte_carlo_stmt, sqlite3_bind_parameter_index(monte_carlo_stmt, "@mc_evttype"), rootreader.get_mc_evttype());
    db_status = sqlite3_step(monte_carlo_stmt);
    db_status = sqlite3_reset(monte_carlo_stmt);

    UpsilonList candidates = rootreader.get_candidate_list();
    while (candidates.next_candidate() != -1) {
      db_status = sqlite3_bind_text(candidate_stmt, sqlite3_bind_parameter_index(candidate_stmt, "@babar_event_id"), candidates.get_current_candidate().get_eventId().c_str(), -1, SQLITE_STATIC);
      db_status = sqlite3_bind_int(candidate_stmt, sqlite3_bind_parameter_index(candidate_stmt, "@event_candidate_index"), candidates.get_current_candidate().get_event_candidate_index());
      db_status = sqlite3_bind_double(candidate_stmt, sqlite3_bind_parameter_index(candidate_stmt, "@tag_lp3"), candidates.get_current_candidate().get_tag_lp3());
      db_status = sqlite3_bind_double(candidate_stmt, sqlite3_bind_parameter_index(candidate_stmt, "@sig_hp3"), candidates.get_current_candidate().get_sig_hp3());
      db_status = sqlite3_bind_double(candidate_stmt, sqlite3_bind_parameter_index(candidate_stmt, "@tag_cosBY"), candidates.get_current_candidate().get_tag_cosBY());
      db_status = sqlite3_bind_double(candidate_stmt, sqlite3_bind_parameter_index(candidate_stmt, "@sig_cosBY"), candidates.get_current_candidate().get_sig_cosBY());
      db_status = sqlite3_bind_double(candidate_stmt, sqlite3_bind_parameter_index(candidate_stmt, "@tag_cosThetaDl"), candidates.get_current_candidate().get_tag_cosThetaDl());
      db_status = sqlite3_bind_double(candidate_stmt, sqlite3_bind_parameter_index(candidate_stmt, "@sig_cosThetaDtau"), candidates.get_current_candidate().get_sig_cosThetaDtau());
      db_status = sqlite3_bind_double(candidate_stmt, sqlite3_bind_parameter_index(candidate_stmt, "@sig_vtxB"), candidates.get_current_candidate().get_sig_vtxB());
      db_status = sqlite3_bind_double(candidate_stmt, sqlite3_bind_parameter_index(candidate_stmt, "@mmiss_prime2"), candidates.get_current_candidate().get_mmiss_prime2());
      db_status = sqlite3_bind_double(candidate_stmt, sqlite3_bind_parameter_index(candidate_stmt, "@eextra50"), candidates.get_current_candidate().get_eextra50());
      db_status = sqlite3_bind_double(candidate_stmt, sqlite3_bind_parameter_index(candidate_stmt, "@cosThetaT"), candidates.get_current_candidate().get_cosThetaT());
      db_status = sqlite3_bind_int(candidate_stmt, sqlite3_bind_parameter_index(candidate_stmt, "@tag_Dtype"), candidates.get_current_candidate().get_tag_d_mode());
      db_status = sqlite3_bind_int(candidate_stmt, sqlite3_bind_parameter_index(candidate_stmt, "@tag_Dstartype"), candidates.get_current_candidate().get_tag_dstar_mode());
      db_status = sqlite3_bind_double(candidate_stmt, sqlite3_bind_parameter_index(candidate_stmt, "@tag_Dmass"), candidates.get_current_candidate().get_tag_Dmass());
      db_status = sqlite3_bind_double(candidate_stmt, sqlite3_bind_parameter_index(candidate_stmt, "@tag_deltaM"), candidates.get_current_candidate().get_tag_deltaM());
      db_status = sqlite3_bind_double(candidate_stmt, sqlite3_bind_parameter_index(candidate_stmt, "@tag_cosThetaDSoft"), candidates.get_current_candidate().get_tag_cosThetaDSoft());
      db_status = sqlite3_bind_double(candidate_stmt, sqlite3_bind_parameter_index(candidate_stmt, "@tag_softP3MagCM"), candidates.get_current_candidate().get_tag_softP3MagCM());
      db_status = sqlite3_bind_int(candidate_stmt, sqlite3_bind_parameter_index(candidate_stmt, "@sig_Dtype"), candidates.get_current_candidate().get_sig_d_mode());
      db_status = sqlite3_bind_int(candidate_stmt, sqlite3_bind_parameter_index(candidate_stmt, "@sig_Dstartype"), candidates.get_current_candidate().get_sig_dstar_mode());
      db_status = sqlite3_bind_double(candidate_stmt, sqlite3_bind_parameter_index(candidate_stmt, "@sig_Dmass"), candidates.get_current_candidate().get_sig_Dmass());
      db_status = sqlite3_bind_double(candidate_stmt, sqlite3_bind_parameter_index(candidate_stmt, "@sig_deltaM"), candidates.get_current_candidate().get_sig_deltaM());
      db_status = sqlite3_bind_double(candidate_stmt, sqlite3_bind_parameter_index(candidate_stmt, "@sig_cosThetaDSoft"), candidates.get_current_candidate().get_sig_cosThetaDSoft());
      db_status = sqlite3_bind_double(candidate_stmt, sqlite3_bind_parameter_index(candidate_stmt, "@sig_softP3MagCM"), candidates.get_current_candidate().get_sig_softP3MagCM());
      db_status = sqlite3_bind_double(candidate_stmt, sqlite3_bind_parameter_index(candidate_stmt, "@sig_hmass"), candidates.get_current_candidate().get_sig_hmass());
      db_status = sqlite3_bind_double(candidate_stmt, sqlite3_bind_parameter_index(candidate_stmt, "@sig_vtxh"), candidates.get_current_candidate().get_sig_vtxh());
      db_status = sqlite3_bind_double(candidate_stmt, sqlite3_bind_parameter_index(candidate_stmt, "@cand_type"), candidates.get_current_candidate().get_cand_type());
      db_status = sqlite3_bind_double(candidate_stmt, sqlite3_bind_parameter_index(candidate_stmt, "@samp_type"), candidates.get_current_candidate().get_sample_type());
      db_status = sqlite3_step(candidate_stmt);
      db_status = sqlite3_reset(candidate_stmt);
    }

  }

  db_status = sqlite3_finalize(event_stmt);
  db_status = sqlite3_finalize(monte_carlo_stmt);
  db_status = sqlite3_finalize(candidate_stmt);

  return db_status;
}

int make_event_weight_table(
    sqlite3 *db, 
    const char *event_weights_fname) {

  char *errmsg;
  sqlite3_exec(db, "BEGIN TRANSACTION", NULL, NULL, &errmsg);

  int db_status;
  sqlite3_stmt *stmt = NULL;

  db_status = sqlite3_prepare_v2(db, "CREATE TABLE event_weights("
      "sp_modenum INTEGER, "
      "run_number INTEGER, "
      "event_weight REAL"
      ");", -1, &stmt, NULL);
  db_status = sqlite3_step(stmt);
  db_status = sqlite3_finalize(stmt);

  stmt = NULL;
  db_status = sqlite3_prepare_v2(db, 
      "INSERT INTO event_weights("
      "sp_modenum, "
      "run_number, "
      "event_weight"
      ") VALUES("
      "?1, ?2, ?3"
      ");", -1, &stmt, NULL);

  DatReader datreader(event_weights_fname);
  while (datreader.read_next_line()) {
    int spmode = to_int(datreader.get_field("spmode"));
    int run = to_int(datreader.get_field("run"));
    double event_weight = to_double(datreader.get_field("weight"));
    db_status = sqlite3_bind_int(stmt, 1, spmode);
    db_status = sqlite3_bind_int(stmt, 2, run);
    db_status = sqlite3_bind_double(stmt, 3, event_weight);
    db_status = sqlite3_step(stmt);
    db_status = sqlite3_reset(stmt);
  }

  db_status = sqlite3_finalize(stmt);

  sqlite3_exec(db, "END TRANSACTION", NULL, NULL, &errmsg);

  return db_status;
}

int make_machine_learning_sample_assignment_table(
    sqlite3 *db, 
    const char *ml_assignment_fname) {

  char *errmsg;
  sqlite3_exec(db, "BEGIN TRANSACTION", NULL, NULL, &errmsg);

  int db_status;
  sqlite3_stmt *stmt = NULL;
  db_status = sqlite3_prepare_v2(db, "CREATE TABLE machine_learning_sample_assignment("
      "babar_event_id TEXT UNIQUE, "
      "ml_sample TEXT "
      ");", -1, &stmt, NULL);
  db_status = sqlite3_step(stmt);
  db_status = sqlite3_finalize(stmt);

  stmt = NULL;
  db_status = sqlite3_prepare_v2(db, 
      "INSERT INTO machine_learning_sample_assignment("
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
