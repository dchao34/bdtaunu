#include <cassert>
#include <string>
#include <iostream>

#include <sqlite3.h>

#include "SQLiteUpdater.h"

SQLiteUpdater::SQLiteUpdater() : 
  SQLiteAccessor(), 
  stmt(NULL) {
}

SQLiteUpdater::SQLiteUpdater(const char *dbname) : 
  SQLiteAccessor(dbname, "w"), 
  stmt(NULL) {
}

void SQLiteUpdater::Initialize() {
  db_status = sqlite3_prepare_v2(
      db, ConstructUpdateStatement().c_str(), 
      -1, &stmt, NULL);
  assert(db_status == SQLITE_OK);
}

SQLiteUpdater::~SQLiteUpdater() {
  db_status = sqlite3_finalize(stmt);
  if (db_status != SQLITE_OK) {
    std::cout << "SQLiteUpdater did not destruct safely. " << std::endl;
  }
}

void SQLiteUpdater::UpdateTable() {

  BindColumns();
  db_status = sqlite3_step(stmt);
  assert(db_status == SQLITE_DONE);
  db_status = sqlite3_reset(stmt);
  assert(db_status == SQLITE_OK);
  db_status = sqlite3_clear_bindings(stmt);
  assert(db_status == SQLITE_OK);

}
