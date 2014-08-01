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
    int truthB_idx = to_int(dat_reader.get_field("truthB_idx"));

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
  meta_colnames.push_back(std::pair<std::string, std::string>("b1mctype", "INTEGER"));
  meta_colnames.push_back(std::pair<std::string, std::string>("b2mctype", "INTEGER"));
  meta_colnames.push_back(std::pair<std::string, std::string>("b1_taumctype", "INTEGER"));
  meta_colnames.push_back(std::pair<std::string, std::string>("b2_taumctype", "INTEGER"));
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
  db_status = sqlite3_bind_int(insert_stmt, sqlite3_bind_parameter_index(insert_stmt, "@b1mctype"), b1mctype);
  assert(db_status == SQLITE_OK);
  db_status = sqlite3_bind_int(insert_stmt, sqlite3_bind_parameter_index(insert_stmt, "@b2mctype"), b2mctype);
  assert(db_status == SQLITE_OK);
  db_status = sqlite3_bind_int(insert_stmt, sqlite3_bind_parameter_index(insert_stmt, "@b1_taumctype"), b1_taumctype);
  assert(db_status == SQLITE_OK);
  db_status = sqlite3_bind_int(insert_stmt, sqlite3_bind_parameter_index(insert_stmt, "@b2_taumctype"), b2_taumctype);
  assert(db_status == SQLITE_OK);
  db_status = sqlite3_bind_double(insert_stmt, sqlite3_bind_parameter_index(insert_stmt, "@b1_dtau_max_photon_energy"), b1_dtau_max_photon_energy);
  assert(db_status == SQLITE_OK);
  db_status = sqlite3_bind_double(insert_stmt, sqlite3_bind_parameter_index(insert_stmt, "@b2_dtau_max_photon_energy"), b2_dtau_max_photon_energy);
  assert(db_status == SQLITE_OK);
}

int McEventSQLiteTableBuilder::DetermineMcEventTypeDefA() const {

  if (b1mctype == kCont && b2mctype == kCont) {
    return kCont_BkgA;
  } else if ((b1mctype == kDtau && b2mctype == kDstartau) ||
             (b1mctype == kDstartau && b2mctype == kDtau)) {
    if ((truthB_idx_map.find(babar_event_id))->second == 0) {
      return kDtau_SigA;
    } else {
      return kDstartau_SigA;
    }
  } else if (b1mctype == kDtau || b2mctype == kDtau) {
      return kDtau_SigA;
  } else if (b1mctype == kDstartau || b2mctype == kDstartau) {
      return kDstartau_SigA;
  } else if (b1mctype == kDstarstar_res || b2mctype == kDstarstar_res ||
             b1mctype == kDstarstar_nonres || b2mctype == kDstarstar_nonres ) {
    return kDstarstar_BkgA;
  } else if ((b1mctype == kDl && b2mctype == kDstarl) ||
             (b1mctype == kDstarl && b2mctype == kDl)) {
    if ((truthB_idx_map.find(babar_event_id))->second == 0) {
      return kDl_NormA;
    } else {
      return kDstarl_NormA;
    }
  } else if (b1mctype == kDl || b2mctype == kDl) {
      return kDl_NormA;
  } else if (b1mctype == kDstarl || b2mctype == kDstarl) {
      return kDstarl_NormA;
  } else {
    int b1_dectype, b2_dectype;
    b1_dectype = b2_dectype = -2;

    switch (b1mctype) {
      case kD_SL:
      case k0D_SL:
        b1_dectype = 0;
        break;
      case k0Charm_Had:
      case k1Charm_Had:
      case k2Charm_Had:
        b1_dectype = 1;
        break;
    }

    switch (b2mctype) {
      case kD_SL:
      case k0D_SL:
        b2_dectype = 0;
        break;
      case k0Charm_Had:
      case k1Charm_Had:
      case k2Charm_Had:
        b2_dectype = 1;
        break;
    }

    int dectype_sum = b1_dectype + b2_dectype;
    switch (dectype_sum) {
      case 0:
      case 1:
        return kSL_BkgA;
      case 2:
        return kHad_BkgA;
      default:
        return kUndefinedMcEventTypeA;
    }
  }
}

