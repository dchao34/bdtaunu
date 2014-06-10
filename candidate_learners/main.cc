#include <sqlite3.h>

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <cstdlib>
#include <string>

#include "YCandFeatureExtractorFactory.h"
#include "YCandFeatureExtractor.h"

using namespace std;

void print_usage(char **argv) {
  cout << endl;
  cout << "Description: Retrieves Y(4S) candidate records from SQL database. " << endl;
  cout << endl;
  cout << "Usage: " << argv[0]
       << "cand_type "
       << "ml_sample_type "
       << endl;
  cout << "  cand_type: One of the following numerical codes." << endl;
  cout << "     0: DDpi " << endl;
  cout << "     1: DDstarpi " << endl;
  cout << "     2: DstarDpi " << endl;
  cout << "     3: DstarDstarpi " << endl;
  cout << "     4: DDrho " << endl;
  cout << "     5: DDstarrho " << endl;
  cout << "     6: DstarDrho " << endl;
  cout << "     7: DstarDstarrho " << endl;
  cout << endl;
  cout << "  ml_sample_type: One of the following strings." << endl;
  cout << "     explore, train, validate, or test" << endl;
  cout << endl;
  exit(EXIT_FAILURE);
}

int main(int argc, char **argv) {

  if (argc != 3) {
    print_usage(argv);
  }

  sqlite3 *db = NULL;
  string dbname = "../sigmc.db";
  int db_status = sqlite3_open_v2(dbname.c_str(), &db,
      SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, NULL);
  if (db_status != SQLITE_OK) {
    cout << sqlite3_errmsg(db) << endl;
    return db_status;
  }

  YCandFeatureExtractor *extractor = 
    YCandFeatureExtractorFactory::CreateExtractor(atoi(argv[1]), string(argv[2]));

  char *errmsg;
  sqlite3_exec(db, "BEGIN TRANSACTION", NULL, NULL, &errmsg);

  sqlite3_stmt *stmt = NULL;
  db_status = sqlite3_prepare_v2(
      db, extractor->get_sql_query_statement().c_str(), -1, &stmt, NULL);

  string libsvm_fname = extractor->get_candtype_name() + "." + string(argv[2]);
  ofstream libsvm_file(libsvm_fname.c_str(), ofstream::out);

  string dat_fname = extractor->get_candtype_name() + "." + string(argv[2]) + ".dat";
  ofstream dat_file(dat_fname.c_str(), ofstream::out);
  dat_file << extractor->get_dat_header() << endl;

  db_status = sqlite3_step(stmt);
  while(sqlite3_step(stmt) == SQLITE_ROW) {

    extractor->update_features(stmt);

    if (!extractor->pass_selection()) {
      continue;
    }

    libsvm_file << extractor->get_libsvm_line() << endl;
    dat_file << extractor->get_dat_line() << endl;
  }

  libsvm_file.close();

  delete extractor;

  db_status = sqlite3_finalize(stmt);
  sqlite3_exec(db, "END TRANSACTION", NULL, NULL, &errmsg);
  sqlite3_close_v2(db);

}
