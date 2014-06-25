#include <string>
#include <cassert>
#include <iostream>

#include "EventBuilder.h"

const std::string EventBuilder::creation_statement = define_creation_statement();
const std::string EventBuilder::insertion_statement = define_insertion_statement();

std::string EventBuilder::define_creation_statement() {
  std::string sql_statement  = 
    "CREATE TABLE events("
    "id INTEGER PRIMARY KEY, "
    "babar_event_id TEXT UNIQUE, "
    "run_number INTEGER, "
    "nTrk INTEGER, "
    "nY INTEGER, "
    "R2 REAL"
    ");";
  return sql_statement;
}

std::string EventBuilder::define_insertion_statement() {
  std::string sql_statement  = 
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
    ");";
  return sql_statement;
}

EventBuilder::EventBuilder(sqlite3* database) :
  db(database), 
  create_stmt(NULL), 
  insert_stmt(NULL) {

  CreateTable();

  db_status = sqlite3_prepare_v2(
    db, insertion_statement.c_str(),
    -1, &insert_stmt, NULL);
  assert(db_status == SQLITE_OK);
}

EventBuilder::~EventBuilder() {
  db_status = sqlite3_finalize(insert_stmt);
  assert(db_status == SQLITE_OK);
}

void EventBuilder::CreateTable() {
  db_status = sqlite3_prepare_v2(
      db, creation_statement.c_str(),
      -1, &create_stmt, NULL);
  assert(db_status == SQLITE_OK);

  db_status = sqlite3_step(create_stmt);
  assert(db_status == SQLITE_DONE);

  db_status = sqlite3_finalize(create_stmt);
  assert(db_status == SQLITE_OK);
}

void EventBuilder::InsertEntry() {
  db_status = sqlite3_bind_text(insert_stmt, sqlite3_bind_parameter_index(insert_stmt, "@babar_event_id"), babar_event_id.c_str(), -1, SQLITE_STATIC);
  assert(db_status == SQLITE_OK);
  db_status = sqlite3_bind_int(insert_stmt, sqlite3_bind_parameter_index(insert_stmt, "@run_number"), run);
  assert(db_status == SQLITE_OK);
  db_status = sqlite3_bind_int(insert_stmt, sqlite3_bind_parameter_index(insert_stmt, "@nTrk"), nTrk);
  assert(db_status == SQLITE_OK);
  db_status = sqlite3_bind_double(insert_stmt, sqlite3_bind_parameter_index(insert_stmt, "@R2"), R2);
  assert(db_status == SQLITE_OK);
  db_status = sqlite3_bind_int(insert_stmt, sqlite3_bind_parameter_index(insert_stmt, "@nY"), nY);
  assert(db_status == SQLITE_OK);
  db_status = sqlite3_step(insert_stmt);
  assert(db_status == SQLITE_DONE);
  db_status = sqlite3_reset(insert_stmt);
  assert(db_status == SQLITE_OK);
  db_status = sqlite3_clear_bindings(insert_stmt);
  assert(db_status == SQLITE_OK);
}
