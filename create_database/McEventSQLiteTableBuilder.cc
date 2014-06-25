#include <string>
#include <cassert>
#include <utility>
#include <iostream>

#include "McEventSQLiteTableBuilder.h"
#include "utilities/DatReader.h"

void McEventSQLiteTableBuilder::BuildSampleAssignmentMap(const char *assignment_fname) {
  DatReader dat_reader(assignment_fname, "|");
  while (dat_reader.read_next_line()) {

    std::string eventId = dat_reader.get_field("eventId");
    std::string ml_sample = dat_reader.get_field("ml_sample");
    std::string division = dat_reader.get_field("division");

    std::pair<std::string, std::string> sample(ml_sample, division);
    sample_assignment_map[eventId] = sample;
  }
}

McEventSQLiteTableBuilder::McEventSQLiteTableBuilder(sqlite3* database, const char *assignment_fname) :
  EventSQLiteTableBuilder(database) {

  table_name = "McEvent";

  meta_colnames.push_back(std::pair<std::string, std::string>("sp_mode", "INTEGER"));
  meta_colnames.push_back(std::pair<std::string, std::string>("ml_sample", "TEXT"));
  meta_colnames.push_back(std::pair<std::string, std::string>("division", "TEXT"));
  meta_colnames.push_back(std::pair<std::string, std::string>("mc_evttype", "INTEGER"));

  BuildSampleAssignmentMap(assignment_fname);
}

McEventSQLiteTableBuilder::~McEventSQLiteTableBuilder() {
}

void McEventSQLiteTableBuilder::BindColumns() {

  EventSQLiteTableBuilder::BindColumns();

  db_status = sqlite3_bind_int(insert_stmt, sqlite3_bind_parameter_index(insert_stmt, "@sp_mode"), sp_mode);
  assert(db_status == SQLITE_OK);
  db_status = sqlite3_bind_text(insert_stmt, sqlite3_bind_parameter_index(insert_stmt, "@ml_sample"), sample_assignment_map[babar_event_id].first.c_str(), -1, SQLITE_STATIC);
  assert(db_status == SQLITE_OK);
  db_status = sqlite3_bind_text(insert_stmt, sqlite3_bind_parameter_index(insert_stmt, "@division"), sample_assignment_map[babar_event_id].second.c_str(), -1, SQLITE_STATIC);
  assert(db_status == SQLITE_OK);
  db_status = sqlite3_bind_int(insert_stmt, sqlite3_bind_parameter_index(insert_stmt, "@mc_evttype"), mc_evttype);
  assert(db_status == SQLITE_OK);
}
