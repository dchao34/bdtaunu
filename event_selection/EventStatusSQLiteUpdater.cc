#include <cassert>
#include <string>
#include <iostream>

#include <sqlite3.h>

#include "EventStatusSQLiteUpdater.h"

EventStatusSQLiteUpdater::EventStatusSQLiteUpdater() : 
  SQLiteUpdater() {

  Initialize();
}

EventStatusSQLiteUpdater::EventStatusSQLiteUpdater(const char *dbname) : 
  SQLiteUpdater(dbname) {

  table_name = "EventStatus";

  target_colnames.push_back("failed_event_precuts");
  target_colnames.push_back("signal_score");
  target_colnames.push_back("continuum_score");

  constraint_colnames.push_back("babar_event_id");

  Initialize();
}

std::string EventStatusSQLiteUpdater::ConstructUpdateStatement() const {

  std::vector<std::string>::const_iterator it;

  std::string target_string;
  it = target_colnames.begin();
  while (it != target_colnames.end()) {
    if (it != target_colnames.begin()) {
      target_string += ", ";
    }
    target_string += (*it + "=@" + *it);
    ++it;
  }

  std::string constraint_string;
  it = constraint_colnames.begin();
  while (it != constraint_colnames.end()) {
    if (it != constraint_colnames.begin()) {
      constraint_string += ", ";
    }
    constraint_string += (*it + "=@" + *it);
    ++it;
  }

  std::string update_statement = "UPDATE " + table_name + " ";
  update_statement += ("SET " + target_string + " ");
  update_statement += ("WHERE " + constraint_string + ";");

  return update_statement;

}

void EventStatusSQLiteUpdater::BindColumns() {
  db_status = sqlite3_bind_int(stmt, sqlite3_bind_parameter_index(stmt, "@failed_event_precuts"), failed_event_precuts);
  assert(db_status == SQLITE_OK);
  db_status = sqlite3_bind_double(stmt, sqlite3_bind_parameter_index(stmt, "@signal_score"), signal_score);
  assert(db_status == SQLITE_OK);
  db_status = sqlite3_bind_double(stmt, sqlite3_bind_parameter_index(stmt, "@continuum_score"), continuum_score);
  assert(db_status == SQLITE_OK);
  db_status = sqlite3_bind_text(stmt, sqlite3_bind_parameter_index(stmt, "@babar_event_id"), babar_event_id.c_str(), -1, SQLITE_STATIC);
  assert(db_status == SQLITE_OK);
}
