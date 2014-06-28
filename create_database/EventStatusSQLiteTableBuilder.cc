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

  code_colnames.push_back(std::pair<std::string, std::string>("no_candidates_passed_cuts", "INTEGER"));
  code_colnames.push_back(std::pair<std::string, std::string>("failed_event_selection", "INTEGER"));
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

  std::string sql_statement  = "INSERT INTO ";
  sql_statement += table_name;
  sql_statement += ("(" + column_string + ") VALUES(" + value_string + ");");

  return sql_statement;
}

void EventStatusSQLiteTableBuilder::BindColumns() {
  db_status = sqlite3_bind_text(insert_stmt, sqlite3_bind_parameter_index(insert_stmt, "@babar_event_id"), babar_event_id.c_str(), -1, SQLITE_STATIC);
  assert(db_status == SQLITE_OK);
  db_status = sqlite3_bind_int(insert_stmt, sqlite3_bind_parameter_index(insert_stmt, "@no_candidates_passed_cuts"), no_candidates_passed_cuts);
  assert(db_status == SQLITE_OK);
  db_status = sqlite3_bind_int(insert_stmt, sqlite3_bind_parameter_index(insert_stmt, "@failed_event_selection"), failed_event_selection);
  assert(db_status == SQLITE_OK);
}
