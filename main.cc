#include <iostream>

#include <unistd.h>
#include <errno.h>
#include <sqlite3.h>

#include "bdtaunu_create_sqldatabase.h"

using namespace std;

int main() {
  const char *dbname = "bdtaunu.db";
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

  db_status = make_event_weight_table(db, "data/event_weights.txt");
  db_status = make_machine_learning_sample_assignment_table(db, "meta/ml_sample_assignment.txt");

  char *errmsg;
  sqlite3_exec(db, "BEGIN TRANSACTION", NULL, NULL, &errmsg);

  db_status = create_event_table(db);
  db_status = create_candidate_table(db);
  db_status = create_monte_carlo_table(db);
  db_status = insert_table(db, "data/sp1237r1.root", "ntp1", 1);
  db_status = insert_table(db, "data/sp1235r1.root", "ntp1", 1);
  db_status = insert_table(db, "data/sp1005r1.root", "ntp1", 1);
  db_status = insert_table(db, "data/sp998r1.root", "ntp1", 1);

  sqlite3_exec(db, "END TRANSACTION", NULL, NULL, &errmsg);
  sqlite3_close_v2(db);

  return 0;
}
