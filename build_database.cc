#include <iostream>

#include <unistd.h>
#include <errno.h>
#include <sqlite3.h>

#include "create_database/BDtaunuMcReader.h"
#include "create_database/McEventSQLiteTableBuilder.h"

using namespace std;

int main() {
  const char *dbname = "sigmc.db";

  int db_status;
  sqlite3 *db = NULL;
  db_status = sqlite3_open_v2(dbname, &db, 
      SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, NULL);
  if (db_status != SQLITE_OK) {
    cout << sqlite3_errmsg(db) << endl;
    return db_status;
  }

  char *errmsg;
  sqlite3_exec(db, "BEGIN TRANSACTION", NULL, NULL, &errmsg);

  McEventSQLiteTableBuilder event_builder(db, "meta/sigmc_ml_assignment.txt");
  event_builder.CreateTable();

  BDtaunuMcReader rootreader("data/root/signal/may_16_2014/A/sp11444r1.root", "ntp1");
  while (rootreader.next_record() != -1) {
    event_builder.set_babar_event_id(rootreader.get_eventId());
    event_builder.set_run(1);
    event_builder.set_sp_mode(11444);
    event_builder.set_mc_evttype(rootreader.get_mc_evttype());
    event_builder.set_nTrk(rootreader.get_nTrk());
    event_builder.set_R2(rootreader.get_R2All());
    event_builder.set_nY(rootreader.get_nY());
    event_builder.InsertTable();
  }

  sqlite3_exec(db, "END TRANSACTION", NULL, NULL, &errmsg);
  sqlite3_close_v2(db);

  return 0;
}
