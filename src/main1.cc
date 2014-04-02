#include <iostream>

#include <unistd.h>
#include <errno.h>
#include <sqlite3.h>

#include "BDtaunuReader.h"

using namespace std;

int main() {
  const char *dbname = "sp998r1.db";
  if (access(dbname, F_OK) == 0) {
    cout << "error: cannot create \"" << dbname << "\". " << endl;
    cout << "another file with the same name already exists. " << endl;
    return errno;
  }

  int db_status;
  sqlite3 *db = NULL;

  db_status = sqlite3_open_v2(dbname, &db, 
      SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, NULL);
  if (db_status != SQLITE_OK) {
    cout << sqlite3_errmsg(db) << endl;
    return db_status;
  }

  sqlite3_stmt *stmt = NULL;
  db_status = sqlite3_prepare_v2(db, 
      "CREATE TABLE events(id INTEGER PRIMARY KEY, eventId TEXT UNIQUE, R2 REAL);", -1, 
      &stmt, NULL);
  db_status = sqlite3_step(stmt);
  db_status = sqlite3_finalize(stmt);

  stmt = NULL;
  db_status = sqlite3_prepare_v2(db, 
      "INSERT INTO events(eventId, R2) VALUES(?1, ?2);", -1, 
      &stmt, NULL);

  BDtaunuReader rootreader("sp998r1.root", "ntp1");
  while (rootreader.next_record() != -1) {
    db_status = sqlite3_bind_text(stmt, 1, rootreader.get_eventId().c_str(), -1, SQLITE_STATIC);
    db_status = sqlite3_bind_double(stmt, 2, rootreader.get_R2All());
    db_status = sqlite3_step(stmt);
    db_status = sqlite3_reset(stmt);
  }
  db_status = sqlite3_finalize(stmt);

  sqlite3_close_v2(db);

  return 0;
}
