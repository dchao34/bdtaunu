#include <cassert>
#include <string>
#include <iostream>

#include <sqlite3.h>

#include "SQLiteReader.h"

SQLiteReader::SQLiteReader() : 
  SQLiteAccessor(), 
  stmt(NULL) {
}

SQLiteReader::SQLiteReader(const char *dbname) : 
  SQLiteAccessor(dbname, "r"), 
  stmt(NULL) {
}

void SQLiteReader::Initialize() {

  BuildColumnIndexMap();

  db_status = sqlite3_prepare_v2(
      db, ConstructSelectStatement().c_str(), 
      -1, &stmt, NULL);

  assert(db_status == SQLITE_OK);

  ClearColumns();
}

SQLiteReader::~SQLiteReader() {
  db_status = sqlite3_finalize(stmt);
  if (db_status != SQLITE_OK) {
    std::cout << "SQLiteReader did not destruct safely. " << std::endl;
  }
}

int SQLiteReader::next_record() {
  db_status = sqlite3_step(stmt);
  if (db_status == SQLITE_ROW) {
    UpdateColumns();
    return 1;
  } else {
    return 0;
  }
}
