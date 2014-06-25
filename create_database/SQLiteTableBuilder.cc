#include <string>
#include <cassert>
#include <iostream>

#include "SQLiteTableBuilder.h"

SQLiteTableBuilder::SQLiteTableBuilder(sqlite3* database) :
  db(database), 
  create_stmt(NULL), 
  insert_stmt(NULL) {
}

SQLiteTableBuilder::~SQLiteTableBuilder() {
  db_status = sqlite3_finalize(insert_stmt);
  assert(db_status == SQLITE_OK);
}

void SQLiteTableBuilder::CreateTable() {
  db_status = sqlite3_prepare_v2(
      db, ConstructCreateStatement().c_str(),
      -1, &create_stmt, NULL);
  assert(db_status == SQLITE_OK);

  db_status = sqlite3_step(create_stmt);
  assert(db_status == SQLITE_DONE);

  db_status = sqlite3_finalize(create_stmt);
  assert(db_status == SQLITE_OK);

  db_status = sqlite3_prepare_v2(
    db, ConstructInsertStatement().c_str(),
    -1, &insert_stmt, NULL);
  assert(db_status == SQLITE_OK);
}

void SQLiteTableBuilder::InsertTable() {

  BindColumns();

  db_status = sqlite3_step(insert_stmt);
  assert(db_status == SQLITE_DONE);
  db_status = sqlite3_reset(insert_stmt);
  assert(db_status == SQLITE_OK);
  db_status = sqlite3_clear_bindings(insert_stmt);
  assert(db_status == SQLITE_OK);
}
