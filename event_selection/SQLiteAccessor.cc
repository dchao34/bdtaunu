#include <cassert>
#include <iostream>
#include <string>

#include <sqlite3.h>

#include "SQLiteAccessor.h"

SQLiteAccessor::SQLiteAccessor() : 
  db(NULL),
  errmsg(NULL) {
}

SQLiteAccessor::SQLiteAccessor(const char *dbname, const char *mode) : 
  db(NULL), 
  errmsg(NULL) {

  int open_mode;
  std::string mode_str(mode);
  if (mode_str == "r") {
    open_mode = SQLITE_OPEN_READONLY;
  } else if (mode_str == "w") {
    open_mode = SQLITE_OPEN_READWRITE;
  } else {
    open_mode = SQLITE_OPEN_READWRITE;
  }

  db_status = sqlite3_open_v2(dbname, &db,
    open_mode, NULL);
  if (db_status != SQLITE_OK) {
    std::cout << sqlite3_errmsg(db) << std::endl;
    assert(db_status == SQLITE_OK);
  }

  sqlite3_exec(db, "BEGIN TRANSACTION", NULL, NULL, &errmsg);

}

SQLiteAccessor::~SQLiteAccessor() {
  sqlite3_exec(db, "END TRANSACTION", NULL, NULL, &errmsg);
  db_status = sqlite3_close_v2(db);
  if (db_status != SQLITE_OK) {
    std::cout << "SQLiteAccessor did not destruct safely. " << std::endl;
  }
}
