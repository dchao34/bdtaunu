#include <vector>
#include <string>
#include <utility>
#include <cassert>
#include <iostream>

#include "EventSQLiteTableBuilder.h"

EventSQLiteTableBuilder::EventSQLiteTableBuilder(sqlite3* database) :
  SQLiteTableBuilder(database) {

  table_name = "Event";

  id_colnames.push_back(std::pair<std::string, std::string>("babar_event_id", "TEXT UNIQUE"));  

  meta_colnames.push_back(std::pair<std::string, std::string>("nY", "INTEGER"));  
  meta_colnames.push_back(std::pair<std::string, std::string>("run_number", "INTEGER")); 

  feature_colnames.push_back(std::pair<std::string, std::string>("nTrk", "INTEGER"));  
  feature_colnames.push_back(std::pair<std::string, std::string>("R2", "REAL"));  
}

EventSQLiteTableBuilder::~EventSQLiteTableBuilder() {
}

std::string EventSQLiteTableBuilder::ConstructCreateStatement() const {

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

  it = feature_colnames.begin();
  while (it != feature_colnames.end()) {
    column_string += (", " + it->first + " " + it->second);
    ++it;
  }

  std::string sql_statement  = "CREATE TABLE ";
  sql_statement += table_name;
  sql_statement += ("(" + column_string + ");");

  return sql_statement;
}

std::string EventSQLiteTableBuilder::ConstructInsertStatement() const {

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
  
  it = feature_colnames.begin();
  while (it != feature_colnames.end()) {
    column_string += (", " + it->first);
    value_string += (", @" + it->first);
    ++it;
  }

  std::string sql_statement  = "INSERT INTO ";
  sql_statement += table_name;
  sql_statement += ("(" + column_string + ") VALUES(" + value_string + ");");

  return sql_statement;
}

void EventSQLiteTableBuilder::BindColumns() {
  db_status = sqlite3_bind_text(insert_stmt, sqlite3_bind_parameter_index(insert_stmt, "@babar_event_id"), babar_event_id.c_str(), -1, SQLITE_STATIC);
  assert(db_status == SQLITE_OK);
  db_status = sqlite3_bind_int(insert_stmt, sqlite3_bind_parameter_index(insert_stmt, "@run_number"), run);
  assert(db_status == SQLITE_OK);
  db_status = sqlite3_bind_int(insert_stmt, sqlite3_bind_parameter_index(insert_stmt, "@nY"), nY);
  assert(db_status == SQLITE_OK);
  db_status = sqlite3_bind_int(insert_stmt, sqlite3_bind_parameter_index(insert_stmt, "@nTrk"), nTrk);
  assert(db_status == SQLITE_OK);
  db_status = sqlite3_bind_double(insert_stmt, sqlite3_bind_parameter_index(insert_stmt, "@R2"), R2);
  assert(db_status == SQLITE_OK);
}
