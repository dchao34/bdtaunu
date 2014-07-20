#include <map>
#include <string>
#include <sstream>
#include <iostream>

#include <sqlite3.h>

#include "EventSQLiteReader.h"

EventSQLiteReader::EventSQLiteReader() : 
  SQLiteReader(),
  ml_sample_type("all"), 
  division("-1") {

  Initialize();
}

EventSQLiteReader::EventSQLiteReader(
  const char *dbname, 
  const char *mltype, 
  const char *div) : 
  SQLiteReader(dbname),
  ml_sample_type(mltype), 
  division(div) {

  Initialize();
}

std::string EventSQLiteReader::ConstructSelectStatement() const {

  std::string where_statement= "Event.babar_event_id = SvmCand.babar_event_id";
  if (ml_sample_type != "all") {
    where_statement += (" AND Event.ml_sample = '" + ml_sample_type + "'");
  }
  if (division != "-1") {
    where_statement += (" AND Event.division = '" + division + "'");
  }

  std::string sql_query = 
    "SELECT Event.id, Event.babar_event_id, "
           "event_weight, mc_evttypeA, cand_type, "
           "nTrk, R2, eextra50, mmiss_prime2, cosThetaT, tag_lp3, "
           "tag_cosBY, tag_cosThetaDl, tag_Dmass, tag_deltaM, "
           "tag_cosThetaDSoft, tag_softP3MagCM, tag_Dtype, tag_Dstartype, "
           "sig_hp3, sig_cosBY, sig_cosThetaDtau, sig_vtxB, sig_Dmass, "
           "sig_deltaM, sig_cosThetaDSoft, sig_softP3MagCM, sig_hmass, "
           "sig_vtxh, sig_Dtype, sig_Dstartype, svm_score "
    "FROM McEvent Event, (McCandidate C JOIN OptimalCandidate S ON "
                                       "C.babar_event_id = S.babar_event_id AND C.cand_idx = S.svm) SvmCand "
    "WHERE (" + where_statement + "); ";
  return sql_query;
}

void EventSQLiteReader::BuildColumnIndexMap() {
  column_idx_map["id"] = 0;
  column_idx_map["babar_event_id"] = 1;
  column_idx_map["event_weight"] = 2;
  column_idx_map["mc_evttypeA"] = 3;
  column_idx_map["cand_type"] = 4;
  column_idx_map["nTrk"] = 5;
  column_idx_map["R2"] = 6;
  column_idx_map["eextra50"] = 7;
  column_idx_map["mmiss_prime2"] = 8;
  column_idx_map["cosThetaT"] = 9;
  column_idx_map["tag_lp3"] = 10;
  column_idx_map["tag_cosBY"] = 11;
  column_idx_map["tag_cosThetaDl"] = 12;
  column_idx_map["tag_Dmass"] = 13;
  column_idx_map["tag_deltaM"] = 14;
  column_idx_map["tag_cosThetaDSoft"] = 15;
  column_idx_map["tag_softP3MagCM"] = 16;
  column_idx_map["tag_Dtype"] = 17;
  column_idx_map["tag_Dstartype"] = 18;
  column_idx_map["sig_hp3"] = 19;
  column_idx_map["sig_cosBY"] = 20;
  column_idx_map["sig_cosThetaDtau"] = 21;
  column_idx_map["sig_vtxB"] = 22;
  column_idx_map["sig_Dmass"] = 23;
  column_idx_map["sig_deltaM"] = 24;
  column_idx_map["sig_cosThetaDSoft"] = 25;
  column_idx_map["sig_softP3MagCM"] = 26;
  column_idx_map["sig_hmass"] = 27;
  column_idx_map["sig_vtxh"] = 28;
  column_idx_map["sig_Dtype"] = 29;
  column_idx_map["sig_Dstartype"] = 30;
  column_idx_map["svm_score"] = 31;
}

void EventSQLiteReader::UpdateColumns() {

  ClearColumns();

  id = sqlite3_column_int(stmt, column_idx_map["id"]);
  babar_event_id = std::string(
      reinterpret_cast<const char*>(
        sqlite3_column_text(stmt, column_idx_map["babar_event_id"])));
  mc_evttypeA = sqlite3_column_int(stmt, column_idx_map["mc_evttypeA"]);

  cand_type = sqlite3_column_int(stmt, column_idx_map["cand_type"]);
  nTrk = sqlite3_column_int(stmt, column_idx_map["nTrk"]);
  tag_Dtype = sqlite3_column_int(stmt, column_idx_map["tag_Dtype"]);
  tag_Dstartype = sqlite3_column_int(stmt, column_idx_map["tag_Dstartype"]);
  sig_Dtype = sqlite3_column_int(stmt, column_idx_map["sig_Dtype"]);
  sig_Dstartype = sqlite3_column_int(stmt, column_idx_map["sig_Dstartype"]);

  event_weight = sqlite3_column_double(stmt, column_idx_map["event_weight"]);
  R2 = sqlite3_column_double(stmt, column_idx_map["R2"]);
  eextra50 = sqlite3_column_double(stmt, column_idx_map["eextra50"]);
  mmiss_prime2 = sqlite3_column_double(stmt, column_idx_map["mmiss_prime2"]);
  cosThetaT = sqlite3_column_double(stmt, column_idx_map["cosThetaT"]);
  tag_lp3 = sqlite3_column_double(stmt, column_idx_map["tag_lp3"]);
  tag_cosBY = sqlite3_column_double(stmt, column_idx_map["tag_cosBY"]);
  tag_cosThetaDl = sqlite3_column_double(stmt, column_idx_map["tag_cosThetaDl"]);
  tag_Dmass = sqlite3_column_double(stmt, column_idx_map["tag_Dmass"]);
  tag_deltaM = sqlite3_column_double(stmt, column_idx_map["tag_deltaM"]);
  tag_cosThetaDSoft = sqlite3_column_double(stmt, column_idx_map["tag_cosThetaDSoft"]);
  tag_softP3MagCM = sqlite3_column_double(stmt, column_idx_map["tag_softP3MagCM"]);
  sig_hp3 = sqlite3_column_double(stmt, column_idx_map["sig_hp3"]);
  sig_cosBY = sqlite3_column_double(stmt, column_idx_map["sig_cosBY"]);
  sig_cosThetaDtau = sqlite3_column_double(stmt, column_idx_map["sig_cosThetaDtau"]);
  sig_vtxB = sqlite3_column_double(stmt, column_idx_map["sig_vtxB"]);
  sig_Dmass = sqlite3_column_double(stmt, column_idx_map["sig_Dmass"]);
  sig_deltaM = sqlite3_column_double(stmt, column_idx_map["sig_deltaM"]);
  sig_cosThetaDSoft = sqlite3_column_double(stmt, column_idx_map["sig_cosThetaDSoft"]);
  sig_softP3MagCM = sqlite3_column_double(stmt, column_idx_map["sig_softP3MagCM"]);
  sig_hmass = sqlite3_column_double(stmt, column_idx_map["sig_hmass"]);
  sig_vtxh = sqlite3_column_double(stmt, column_idx_map["sig_vtxh"]);
  svm_score = sqlite3_column_double(stmt, column_idx_map["svm_score"]);
}

void EventSQLiteReader::ClearColumns() {

  id = -1;
  babar_event_id = "";
  mc_evttypeA = -1;

  cand_type = -1;
  nTrk = -1;
  tag_Dtype = -1;
  tag_Dstartype = -1;
  sig_Dtype = -1;
  sig_Dstartype = -1;

  event_weight = 0;
  R2 = 0;
  eextra50 = 0;
  mmiss_prime2 = 0;
  cosThetaT = 0;
  tag_lp3 = 0;
  tag_cosBY = 0;
  tag_cosThetaDl = 0;
  tag_Dmass = 0;
  tag_deltaM = 0;
  tag_cosThetaDSoft = 0;
  tag_softP3MagCM = 0;
  sig_hp3 = 0;
  sig_cosBY = 0;
  sig_cosThetaDtau = 0;
  sig_vtxB = 0;
  sig_Dmass = 0;
  sig_deltaM = 0;
  sig_cosThetaDSoft = 0;
  sig_softP3MagCM = 0;
  sig_hmass = 0;
  sig_vtxh = 0;
  svm_score = 0;

}
