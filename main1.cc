#include <iostream>

#include <unistd.h>
#include <errno.h>
#include <sqlite3.h>

#include "create_sigmc_database.h"

using namespace std;

int main() {
  const char *dbname = "sigmc.db";
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

  db_status = make_mlsample_assignment_table(db, "meta/sigmc_ml_assignment.txt");

  char *errmsg;
  sqlite3_exec(db, "BEGIN TRANSACTION", NULL, NULL, &errmsg);

  db_status = create_sigmc_candidate_table(db);
  db_status = insert_sigmc_table(db, "data/sigmc_fwk.root", "ntp1");

  sqlite3_exec(db, "END TRANSACTION", NULL, NULL, &errmsg);
  sqlite3_close_v2(db);

  return 0;
}
