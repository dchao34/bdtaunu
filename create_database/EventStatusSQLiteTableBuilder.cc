#include <vector>
#include <string>
#include <utility>
#include <cassert>
#include <iostream>

#include "EventStatusSQLiteTableBuilder.h"

EventStatusSQLiteTableBuilder::EventStatusSQLiteTableBuilder(sqlite3* database) :
  SQLiteTableBuilder(database) {

  table_name = "EventStatus";

  id_colnames.push_back(std::pair<std::string, std::string>("babar_event_id", "TEXT UNIQUE"));  
  code_colnames.push_back(std::pair<std::string, std::string>("failed_event_precuts", "INTEGER DEFAULT 0"));
  score_colnames.push_back(std::pair<std::string, std::string>("signal_score", "REAL DEFAULT 0"));
  score_colnames.push_back(std::pair<std::string, std::string>("continuum_score", "REAL DEFAULT 0"));
  score_colnames.push_back(std::pair<std::string, std::string>("sig_sl_score", "REAL DEFAULT 0"));
  score_colnames.push_back(std::pair<std::string, std::string>("sig_had_score", "REAL DEFAULT 0"));
  score_colnames.push_back(std::pair<std::string, std::string>("sig_cont_score", "REAL DEFAULT 0"));
  score_colnames.push_back(std::pair<std::string, std::string>("sig_all_score", "REAL DEFAULT 0"));
}

EventStatusSQLiteTableBuilder::~EventStatusSQLiteTableBuilder() {
}

std::string EventStatusSQLiteTableBuilder::ConstructCreateStatement() const {

  std::string column_string = "id INTEGER PRIMARY KEY";

  std::vector<std::pair<std::string, std::string> >::const_iterator it;
  
  it = id_colnames.begin();
  while (it != id_colnames.end()) {
    column_string += (", " + it->first + " " + it->second);
    ++it;
  }

  it = code_colnames.begin();
  while (it != code_colnames.end()) {
    column_string += (", " + it->first + " " + it->second);
    ++it;
  }

  it = score_colnames.begin();
  while (it != score_colnames.end()) {
    column_string += (", " + it->first + " " + it->second);
    ++it;
  }

  std::string sql_statement  = "CREATE TABLE ";
  sql_statement += table_name;
  sql_statement += ("(" + column_string + ");");

  return sql_statement;
}

std::string EventStatusSQLiteTableBuilder::ConstructInsertStatement() const {

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
  
  it = code_colnames.begin();
  while (it != code_colnames.end()) {
    column_string += (", " + it->first);
    value_string += (", @" + it->first);
    ++it;
  }
  
  it = score_colnames.begin();
  while (it != score_colnames.end()) {
    column_string += (", " + it->first);
    value_string += (", @" + it->first);
    ++it;
  }

  std::string sql_statement  = "INSERT INTO ";
  sql_statement += table_name;
  sql_statement += ("(" + column_string + ") VALUES(" + value_string + ");");

  return sql_statement;
}

void EventStatusSQLiteTableBuilder::BindColumns() {
  db_status = sqlite3_bind_text(insert_stmt, sqlite3_bind_parameter_index(insert_stmt, "@babar_event_id"), babar_event_id.c_str(), -1, SQLITE_STATIC);
  assert(db_status == SQLITE_OK);
  db_status = sqlite3_bind_int(insert_stmt, sqlite3_bind_parameter_index(insert_stmt, "@failed_event_precuts"), failed_event_precuts);
  assert(db_status == SQLITE_OK);
  db_status = sqlite3_bind_int(insert_stmt, sqlite3_bind_parameter_index(insert_stmt, "@signal_score"), signal_score);
  assert(db_status == SQLITE_OK);
  db_status = sqlite3_bind_int(insert_stmt, sqlite3_bind_parameter_index(insert_stmt, "@continuum_score"), continuum_score);
  assert(db_status == SQLITE_OK);
  db_status = sqlite3_bind_int(insert_stmt, sqlite3_bind_parameter_index(insert_stmt, "@sig_sl_score"), sig_sl_score);
  assert(db_status == SQLITE_OK);
  db_status = sqlite3_bind_int(insert_stmt, sqlite3_bind_parameter_index(insert_stmt, "@sig_had_score"), sig_had_score);
  assert(db_status == SQLITE_OK);
  db_status = sqlite3_bind_int(insert_stmt, sqlite3_bind_parameter_index(insert_stmt, "@sig_cont_score"), sig_cont_score);
  assert(db_status == SQLITE_OK);
  db_status = sqlite3_bind_int(insert_stmt, sqlite3_bind_parameter_index(insert_stmt, "@sig_all_score"), sig_all_score);
  assert(db_status == SQLITE_OK);
}
