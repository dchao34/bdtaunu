#include <string>
#include <cassert>
#include <utility>
#include <iostream>

#include "McEventSQLiteTableBuilder.h"
#include "utilities/DatReader.h"
#include "utilities/helpers.h"
#include "bdtaunu_definitions.h"

void McEventSQLiteTableBuilder::BuildCachedDataMap(const char *assignment_fname) {
  DatReader dat_reader(assignment_fname, "|");
  while (dat_reader.read_next_line()) {

    std::string eventId = dat_reader.get_field("eventId");
    std::string ml_sample = dat_reader.get_field("ml_sample");
    std::string division = dat_reader.get_field("division");
    int truthB_idx = std::stoi(dat_reader.get_field("truthB_idx"));

    std::pair<std::string, std::string> sample(ml_sample, division);
    sample_assignment_map[eventId] = sample;

    truthB_idx_map[eventId] = truthB_idx;
  }
}

McEventSQLiteTableBuilder::McEventSQLiteTableBuilder(sqlite3* database, const char *assignment_fname) :
  EventSQLiteTableBuilder(database) {

  table_name = "McEvent";

  meta_colnames.push_back(std::pair<std::string, std::string>("sp_mode", "INTEGER"));
  meta_colnames.push_back(std::pair<std::string, std::string>("event_weight", "REAL"));
  meta_colnames.push_back(std::pair<std::string, std::string>("ml_sample", "TEXT"));
  meta_colnames.push_back(std::pair<std::string, std::string>("division", "TEXT"));
  meta_colnames.push_back(std::pair<std::string, std::string>("mc_evttypeA", "INTEGER"));
  meta_colnames.push_back(std::pair<std::string, std::string>("b1_mctype", "INTEGER"));
  meta_colnames.push_back(std::pair<std::string, std::string>("b2_mctype", "INTEGER"));
  meta_colnames.push_back(std::pair<std::string, std::string>("b1_tau_mctype", "INTEGER"));
  meta_colnames.push_back(std::pair<std::string, std::string>("b2_tau_mctype", "INTEGER"));
  meta_colnames.push_back(std::pair<std::string, std::string>("b1_dtau_max_photon_energy", "REAL"));
  meta_colnames.push_back(std::pair<std::string, std::string>("b2_dtau_max_photon_energy", "REAL"));

  BuildCachedDataMap(assignment_fname);
}

McEventSQLiteTableBuilder::~McEventSQLiteTableBuilder() {
}

void McEventSQLiteTableBuilder::BindColumns() {

  EventSQLiteTableBuilder::BindColumns();

  db_status = sqlite3_bind_int(insert_stmt, sqlite3_bind_parameter_index(insert_stmt, "@sp_mode"), sp_mode);
  assert(db_status == SQLITE_OK);
  db_status = sqlite3_bind_double(insert_stmt, sqlite3_bind_parameter_index(insert_stmt, "@event_weight"), event_weight);
  assert(db_status == SQLITE_OK);
  db_status = sqlite3_bind_text(insert_stmt, sqlite3_bind_parameter_index(insert_stmt, "@ml_sample"), sample_assignment_map[babar_event_id].first.c_str(), -1, SQLITE_STATIC);
  assert(db_status == SQLITE_OK);
  db_status = sqlite3_bind_text(insert_stmt, sqlite3_bind_parameter_index(insert_stmt, "@division"), sample_assignment_map[babar_event_id].second.c_str(), -1, SQLITE_STATIC);
  assert(db_status == SQLITE_OK);
  db_status = sqlite3_bind_int(insert_stmt, sqlite3_bind_parameter_index(insert_stmt, "@mc_evttypeA"), DetermineMcEventTypeDefA());
  assert(db_status == SQLITE_OK);
  db_status = sqlite3_bind_int(insert_stmt, sqlite3_bind_parameter_index(insert_stmt, "@b1_mctype"), b1_mctype);
  assert(db_status == SQLITE_OK);
  db_status = sqlite3_bind_int(insert_stmt, sqlite3_bind_parameter_index(insert_stmt, "@b2_mctype"), b2_mctype);
  assert(db_status == SQLITE_OK);
  db_status = sqlite3_bind_int(insert_stmt, sqlite3_bind_parameter_index(insert_stmt, "@b1_tau_mctype"), b1_tau_mctype);
  assert(db_status == SQLITE_OK);
  db_status = sqlite3_bind_int(insert_stmt, sqlite3_bind_parameter_index(insert_stmt, "@b2_tau_mctype"), b2_tau_mctype);
  assert(db_status == SQLITE_OK);
  db_status = sqlite3_bind_double(insert_stmt, sqlite3_bind_parameter_index(insert_stmt, "@b1_dtau_max_photon_energy"), b1_dtau_max_photon_energy);
  assert(db_status == SQLITE_OK);
  db_status = sqlite3_bind_double(insert_stmt, sqlite3_bind_parameter_index(insert_stmt, "@b2_dtau_max_photon_energy"), b2_dtau_max_photon_energy);
  assert(db_status == SQLITE_OK);
}

int McEventSQLiteTableBuilder::DetermineMcEventTypeDefA() const {
  return -1;
}

