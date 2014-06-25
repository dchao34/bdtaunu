#include <string>
#include <cassert>
#include <utility>
#include <iostream>

#include "McCandidateSQLiteTableBuilder.h"
#include "utilities/DatReader.h"

McCandidateSQLiteTableBuilder::McCandidateSQLiteTableBuilder(sqlite3* database) :
  CandidateSQLiteTableBuilder(database) {

  event_table_name = "McEvent";
  cand_table_name = "McCandidate";

  meta_colnames.push_back(std::pair<std::string, std::string>("truth_match", "INTEGER"));

}

McCandidateSQLiteTableBuilder::~McCandidateSQLiteTableBuilder() {
}

void McCandidateSQLiteTableBuilder::BindColumns() {

  CandidateSQLiteTableBuilder::BindColumns();

  db_status = sqlite3_bind_int(insert_stmt, sqlite3_bind_parameter_index(insert_stmt, "@truth_match"), truth_match);
  assert(db_status == SQLITE_OK);
}
