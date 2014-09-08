#include <vector>
#include <string>
#include <utility>
#include <cassert>
#include <iostream>

#include "CandidateSQLiteTableBuilder.h"

CandidateSQLiteTableBuilder::CandidateSQLiteTableBuilder(sqlite3* database) :
  SQLiteTableBuilder(database) {

  event_table_name = "Event";
  cand_table_name = "Candidate";

  id_colnames.push_back(std::pair<std::string, std::string>("babar_event_id", "TEXT"));  
  id_colnames.push_back(std::pair<std::string, std::string>("cand_idx", "INTEGER"));  

  meta_colnames.push_back(std::pair<std::string, std::string>("cand_type", "INTEGER"));  
  meta_colnames.push_back(std::pair<std::string, std::string>("samp_type", "INTEGER")); 

  event_level_feature_colnames.push_back(std::pair<std::string, std::string>("mmiss_prime2", "REAL"));  
  event_level_feature_colnames.push_back(std::pair<std::string, std::string>("eextra50", "REAL"));  
  event_level_feature_colnames.push_back(std::pair<std::string, std::string>("cosThetaT", "REAL"));  

  cand_level_feature_colnames.push_back(std::pair<std::string, std::string>("tag_lp3", "REAL"));
  cand_level_feature_colnames.push_back(std::pair<std::string, std::string>("tag_cosBY", "REAL"));
  cand_level_feature_colnames.push_back(std::pair<std::string, std::string>("tag_cosThetaDl", "REAL"));
  cand_level_feature_colnames.push_back(std::pair<std::string, std::string>("tag_Dmass", "REAL"));
  cand_level_feature_colnames.push_back(std::pair<std::string, std::string>("tag_deltaM", "REAL"));
  cand_level_feature_colnames.push_back(std::pair<std::string, std::string>("tag_cosThetaDSoft", "REAL"));
  cand_level_feature_colnames.push_back(std::pair<std::string, std::string>("tag_softP3MagCM", "REAL"));
  cand_level_feature_colnames.push_back(std::pair<std::string, std::string>("tag_Dtype", "INTEGER"));
  cand_level_feature_colnames.push_back(std::pair<std::string, std::string>("tag_Dstartype", "INTEGER"));
  cand_level_feature_colnames.push_back(std::pair<std::string, std::string>("sig_hp3", "REAL"));
  cand_level_feature_colnames.push_back(std::pair<std::string, std::string>("sig_cosBY", "REAL"));
  cand_level_feature_colnames.push_back(std::pair<std::string, std::string>("sig_cosThetaDtau", "REAL"));
  cand_level_feature_colnames.push_back(std::pair<std::string, std::string>("sig_vtxB", "REAL"));
  cand_level_feature_colnames.push_back(std::pair<std::string, std::string>("sig_Dmass", "REAL"));
  cand_level_feature_colnames.push_back(std::pair<std::string, std::string>("sig_deltaM", "REAL"));
  cand_level_feature_colnames.push_back(std::pair<std::string, std::string>("sig_cosThetaDSoft", "REAL"));
  cand_level_feature_colnames.push_back(std::pair<std::string, std::string>("sig_softP3MagCM", "REAL"));
  cand_level_feature_colnames.push_back(std::pair<std::string, std::string>("sig_hmass", "REAL"));
  cand_level_feature_colnames.push_back(std::pair<std::string, std::string>("sig_vtxh", "REAL"));
  cand_level_feature_colnames.push_back(std::pair<std::string, std::string>("sig_Dtype", "INTEGER"));
  cand_level_feature_colnames.push_back(std::pair<std::string, std::string>("sig_Dstartype", "INTEGER"));
  cand_level_feature_colnames.push_back(std::pair<std::string, std::string>("tag_l_ePid", "INTEGER"));
  cand_level_feature_colnames.push_back(std::pair<std::string, std::string>("tag_l_muPid", "INTEGER"));
  cand_level_feature_colnames.push_back(std::pair<std::string, std::string>("sig_h_ePid", "INTEGER"));
  cand_level_feature_colnames.push_back(std::pair<std::string, std::string>("sig_h_muPid", "INTEGER"));

  bestcand_colnames.push_back(std::pair<std::string, std::string>("svm_score", "REAL"));
}

CandidateSQLiteTableBuilder::~CandidateSQLiteTableBuilder() {
}

std::string CandidateSQLiteTableBuilder::ConstructCreateStatement() const {

  std::string column_string = "id INTEGER PRIMARY KEY";

  std::vector<std::pair<std::string, std::string> >::const_iterator it;
  
  it = id_colnames.begin();
  while (it != id_colnames.end()) {
    column_string += (", " + it->first + " " + it->second);
    ++it;
  }

  it = meta_colnames.begin();
  while (it != meta_colnames.end()) {
    column_string += (", " + it->first + " " + it->second);
    ++it;
  }

  it = event_level_feature_colnames.begin();
  while (it != event_level_feature_colnames.end()) {
    column_string += (", " + it->first + " " + it->second);
    ++it;
  }

  it = cand_level_feature_colnames.begin();
  while (it != cand_level_feature_colnames.end()) {
    column_string += (", " + it->first + " " + it->second);
    ++it;
  }

  it = bestcand_colnames.begin();
  while (it != bestcand_colnames.end()) {
    column_string += (", " + it->first + " " + it->second);
    ++it;
  }

  std::string foreign_constraint_string =
    "FOREIGN KEY(babar_event_id) REFERENCES " + 
    event_table_name + "(babar_event_id)";

  std::string sql_statement  = "CREATE TABLE ";
  sql_statement += cand_table_name;
  sql_statement += ("(" + column_string + ", " + foreign_constraint_string + ");");

  return sql_statement;
}

std::string CandidateSQLiteTableBuilder::ConstructInsertStatement() const {

  std::string column_string;
  std::string value_string;

  std::vector<std::pair<std::string, std::string> >::const_iterator it;
  
  it = id_colnames.begin();
  while (it != id_colnames.end()) {

    if (it != id_colnames.begin()) {
      column_string += ", ";
      value_string += ", ";
    }

    column_string += it->first;
    value_string += ("@" + it->first);
    ++it;
  }
  
  it = meta_colnames.begin();
  while (it != meta_colnames.end()) {
    column_string += (", " + it->first);
    value_string += (", @" + it->first);
    ++it;
  }
  
  it = event_level_feature_colnames.begin();
  while (it != event_level_feature_colnames.end()) {
    column_string += (", " + it->first);
    value_string += (", @" + it->first);
    ++it;
  }
  
  it = cand_level_feature_colnames.begin();
  while (it != cand_level_feature_colnames.end()) {
    column_string += (", " + it->first);
    value_string += (", @" + it->first);
    ++it;
  }
  
  it = bestcand_colnames.begin();
  while (it != bestcand_colnames.end()) {
    column_string += (", " + it->first);
    value_string += (", @" + it->first);
    ++it;
  }

  std::string sql_statement  = "INSERT INTO ";
  sql_statement += cand_table_name;
  sql_statement += ("(" + column_string + ") VALUES(" + value_string + ");");

  return sql_statement;
}

void CandidateSQLiteTableBuilder::BindColumns() {
  db_status = sqlite3_bind_text(insert_stmt, sqlite3_bind_parameter_index(insert_stmt, "@babar_event_id"), babar_event_id.c_str(), -1, SQLITE_STATIC);
  assert(db_status == SQLITE_OK);
  db_status = sqlite3_bind_int(insert_stmt, sqlite3_bind_parameter_index(insert_stmt, "@cand_idx"), cand_idx);
  assert(db_status == SQLITE_OK);
  db_status = sqlite3_bind_int(insert_stmt, sqlite3_bind_parameter_index(insert_stmt, "@cand_type"), cand_type);
  assert(db_status == SQLITE_OK);
  db_status = sqlite3_bind_int(insert_stmt, sqlite3_bind_parameter_index(insert_stmt, "@samp_type"), samp_type);
  assert(db_status == SQLITE_OK);
  db_status = sqlite3_bind_double(insert_stmt, sqlite3_bind_parameter_index(insert_stmt, "@mmiss_prime2"), mmiss_prime2);
  assert(db_status == SQLITE_OK);
  db_status = sqlite3_bind_double(insert_stmt, sqlite3_bind_parameter_index(insert_stmt, "@eextra50"), eextra50);
  assert(db_status == SQLITE_OK);
  db_status = sqlite3_bind_double(insert_stmt, sqlite3_bind_parameter_index(insert_stmt, "@cosThetaT"), cosThetaT);
  assert(db_status == SQLITE_OK);
  db_status = sqlite3_bind_double(insert_stmt, sqlite3_bind_parameter_index(insert_stmt, "@tag_lp3"), tag_lp3);
  assert(db_status == SQLITE_OK);
  db_status = sqlite3_bind_double(insert_stmt, sqlite3_bind_parameter_index(insert_stmt, "@tag_cosBY"), tag_cosBY);
  assert(db_status == SQLITE_OK);
  db_status = sqlite3_bind_double(insert_stmt, sqlite3_bind_parameter_index(insert_stmt, "@tag_cosThetaDl"), tag_cosThetaDl);
  assert(db_status == SQLITE_OK);
  db_status = sqlite3_bind_double(insert_stmt, sqlite3_bind_parameter_index(insert_stmt, "@tag_Dmass"), tag_Dmass);
  assert(db_status == SQLITE_OK);
  db_status = sqlite3_bind_double(insert_stmt, sqlite3_bind_parameter_index(insert_stmt, "@tag_deltaM"), tag_deltaM);
  assert(db_status == SQLITE_OK);
  db_status = sqlite3_bind_double(insert_stmt, sqlite3_bind_parameter_index(insert_stmt, "@tag_cosThetaDSoft"), tag_cosThetaDSoft);
  assert(db_status == SQLITE_OK);
  db_status = sqlite3_bind_double(insert_stmt, sqlite3_bind_parameter_index(insert_stmt, "@tag_softP3MagCM"), tag_softP3MagCM);
  assert(db_status == SQLITE_OK);
  db_status = sqlite3_bind_int(insert_stmt, sqlite3_bind_parameter_index(insert_stmt, "@tag_Dtype"), tag_Dtype);
  assert(db_status == SQLITE_OK);
  db_status = sqlite3_bind_int(insert_stmt, sqlite3_bind_parameter_index(insert_stmt, "@tag_Dstartype"), tag_Dstartype);
  assert(db_status == SQLITE_OK);
  db_status = sqlite3_bind_double(insert_stmt, sqlite3_bind_parameter_index(insert_stmt, "@sig_hp3"), sig_hp3);
  assert(db_status == SQLITE_OK);
  db_status = sqlite3_bind_double(insert_stmt, sqlite3_bind_parameter_index(insert_stmt, "@sig_cosBY"), sig_cosBY);
  assert(db_status == SQLITE_OK);
  db_status = sqlite3_bind_double(insert_stmt, sqlite3_bind_parameter_index(insert_stmt, "@sig_cosThetaDtau"), sig_cosThetaDtau);
  assert(db_status == SQLITE_OK);
  db_status = sqlite3_bind_double(insert_stmt, sqlite3_bind_parameter_index(insert_stmt, "@sig_vtxB"), sig_vtxB);
  assert(db_status == SQLITE_OK);
  db_status = sqlite3_bind_double(insert_stmt, sqlite3_bind_parameter_index(insert_stmt, "@sig_Dmass"), sig_Dmass);
  assert(db_status == SQLITE_OK);
  db_status = sqlite3_bind_double(insert_stmt, sqlite3_bind_parameter_index(insert_stmt, "@sig_deltaM"), sig_deltaM);
  assert(db_status == SQLITE_OK);
  db_status = sqlite3_bind_double(insert_stmt, sqlite3_bind_parameter_index(insert_stmt, "@sig_cosThetaDSoft"), sig_cosThetaDSoft);
  assert(db_status == SQLITE_OK);
  db_status = sqlite3_bind_double(insert_stmt, sqlite3_bind_parameter_index(insert_stmt, "@sig_softP3MagCM"), sig_softP3MagCM);
  assert(db_status == SQLITE_OK);
  db_status = sqlite3_bind_double(insert_stmt, sqlite3_bind_parameter_index(insert_stmt, "@sig_hmass"), sig_hmass);
  assert(db_status == SQLITE_OK);
  db_status = sqlite3_bind_double(insert_stmt, sqlite3_bind_parameter_index(insert_stmt, "@sig_vtxh"), sig_vtxh);
  assert(db_status == SQLITE_OK);
  db_status = sqlite3_bind_int(insert_stmt, sqlite3_bind_parameter_index(insert_stmt, "@sig_Dtype"), sig_Dtype);
  assert(db_status == SQLITE_OK);
  db_status = sqlite3_bind_int(insert_stmt, sqlite3_bind_parameter_index(insert_stmt, "@sig_Dstartype"), sig_Dstartype);
  assert(db_status == SQLITE_OK);
  db_status = sqlite3_bind_int(insert_stmt, sqlite3_bind_parameter_index(insert_stmt, "@tag_l_ePid"), tag_l_ePid);
  assert(db_status == SQLITE_OK);
  db_status = sqlite3_bind_int(insert_stmt, sqlite3_bind_parameter_index(insert_stmt, "@tag_l_muPid"), tag_l_muPid);
  assert(db_status == SQLITE_OK);
  db_status = sqlite3_bind_int(insert_stmt, sqlite3_bind_parameter_index(insert_stmt, "@sig_h_ePid"), sig_h_ePid);
  assert(db_status == SQLITE_OK);
  db_status = sqlite3_bind_int(insert_stmt, sqlite3_bind_parameter_index(insert_stmt, "@sig_h_muPid"), sig_h_muPid);
  assert(db_status == SQLITE_OK);
  db_status = sqlite3_bind_double(insert_stmt, sqlite3_bind_parameter_index(insert_stmt, "@svm_score"), svm_score);
  assert(db_status == SQLITE_OK);
}
