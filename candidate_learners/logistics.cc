#include <string>
#include <map>
#include <vector>

#include "bdtaunu_definitions.h"
#include "candidate_ml_declarations.h"

using namespace std;

std::map<std::string, std::string> get_cand_type_map() {
  std::map<std::string, std::string> cand_type_map;
  cand_type_map["DDpi"] = "0";
  cand_type_map["DDstarpi"] = "1";
  cand_type_map["DstarDpi"] = "2";
  cand_type_map["DstarDstarpi"] = "3";
  cand_type_map["DDrho"] = "4";
  cand_type_map["DDstarrho"] = "5";
  cand_type_map["DstarDrho"] = "6";
  cand_type_map["DstarDstarrho"] = "7";
  return cand_type_map;
}

std::map<std::string, int> get_sql_column_ordering() {

  std::map<std::string, int> sql_column_idx;
  sql_column_idx["id"] = 0;
  sql_column_idx["truth_match"] = 1;
  sql_column_idx["tag_lp3"] = 2;
  sql_column_idx["tag_cosBY"] = 3;
  sql_column_idx["tag_cosThetaDl"] = 4;
  sql_column_idx["sig_hp3"] = 5;
  sql_column_idx["sig_vtxB"] = 6;
  sql_column_idx["mmiss_prime2"] = 7;
  sql_column_idx["eextra50"] = 8;
  sql_column_idx["tag_Dmass"] = 9;
  sql_column_idx["sig_Dmass"] = 10;
  sql_column_idx["tag_Dtype"] = 11;
  sql_column_idx["sig_Dtype"] = 12;
  sql_column_idx["sig_cosBY"] = 13;
  sql_column_idx["tag_deltaM"] = 14;
  sql_column_idx["tag_cosThetaDSoft"] = 15;
  sql_column_idx["tag_softP3MagCM"] = 16;
  sql_column_idx["sig_deltaM"] = 17;
  sql_column_idx["sig_cosThetaDSoft"] = 18;
  sql_column_idx["sig_softP3MagCM"] = 19;
  sql_column_idx["sig_hmass"] = 20;
  sql_column_idx["sig_vtxh"] = 21;
  sql_column_idx["tag_Dstartype"] = 22;
  sql_column_idx["sig_Dstartype"] = 23;

  return sql_column_idx;
}

std::string get_query_stmt(std::string cand_type, 
                           std::string ml_sample_type) { 
  std::string sql_query = "SELECT "
                     "id, "
                     "truth_match, "
                     "tag_lp3, "
                     "tag_cosBY, "
                     "tag_cosThetaDl, "
                     "sig_hp3, "
                     "sig_vtxB, "
                     "mmiss_prime2, "
                     "eextra50, "
                     "tag_Dmass, "
                     "sig_Dmass, "
                     "tag_Dtype, "
                     "sig_Dtype, "
                     "sig_cosBY, "
                     "tag_deltaM, "
                     "tag_cosThetaDSoft, "
                     "tag_softP3MagCM, "
                     "sig_deltaM, "
                     "sig_cosThetaDSoft, "
                     "sig_softP3MagCM, "
                     "sig_hmass, "
                     "sig_vtxh, "
                     "tag_Dstartype, "
                     "sig_Dstartype "
                     "FROM candidates NATURAL JOIN ml_sample "
                     "WHERE ml_sample='" + ml_sample_type
                     + "' AND cand_type=" + cand_type
                     + ";";
  return sql_query;
}


bool process_DDpi(
    sqlite3_stmt *stmt, 
    map<string, int> &sql_column_ordering,
    int &truth_match, int &tag_Dtype, int &sig_Dtype,
    vector<double> &numeric_features,
    vector<int> &tag_Dtype_indicators,
    vector<int> &sig_Dtype_indicators
    ) {

  if (!pass_DDpi_cuts(stmt, sql_column_ordering)) {
    return false;
  }

  truth_match = sqlite3_column_int(stmt, sql_column_ordering["truth_match"]);
  DDpi_order_numeric_features(stmt, sql_column_ordering, numeric_features);

  tag_Dtype_indicators = vector<int>(12, 0);
  tag_Dtype = sqlite3_column_int(stmt, sql_column_ordering["tag_Dtype"]);
  DDpi_order_tagDtype_indicators(tag_Dtype, tag_Dtype_indicators);

  sig_Dtype_indicators = vector<int>(9, 0);
  sig_Dtype = sqlite3_column_int(stmt, sql_column_ordering["sig_Dtype"]);
  DDpi_order_sigDtype_indicators(sig_Dtype, sig_Dtype_indicators);

  return true;
}

void DDpi_order_numeric_features(
  sqlite3_stmt *stmt, 
  map<string, int> &sql_column_ordering,
  vector<double> &numeric_features) {

  numeric_features.push_back(sqlite3_column_double(stmt, sql_column_ordering["tag_lp3"]));
  numeric_features.push_back(sqlite3_column_double(stmt, sql_column_ordering["tag_cosBY"]));
  numeric_features.push_back(sqlite3_column_double(stmt, sql_column_ordering["tag_cosThetaDl"]));
  numeric_features.push_back(sqlite3_column_double(stmt, sql_column_ordering["sig_hp3"]));
  numeric_features.push_back(sqlite3_column_double(stmt, sql_column_ordering["sig_vtxB"]));
  numeric_features.push_back(sqlite3_column_double(stmt, sql_column_ordering["mmiss_prime2"]));
  numeric_features.push_back(sqlite3_column_double(stmt, sql_column_ordering["eextra50"]));
  numeric_features.push_back(sqlite3_column_double(stmt, sql_column_ordering["tag_Dmass"]));
  numeric_features.push_back(sqlite3_column_double(stmt, sql_column_ordering["sig_Dmass"]));

}

void DDpi_order_tagDtype_indicators(
  int tag_Dtype, 
  vector<int> &tag_Dtype_indicators) {

  switch (tag_Dtype) {
    case kDc_Kpipi:
      tag_Dtype_indicators[0] = 1;
      break;
    case kDc_Kpipipi0:
      tag_Dtype_indicators[1] = 1;
      break;
    case kDc_KsK:
      tag_Dtype_indicators[2] = 1;
      break;
    case kDc_Kspi: 
      tag_Dtype_indicators[2] = 2;
      break;
    case kDc_Kspipi0:
      tag_Dtype_indicators[3] = 1;
      break;
    case kDc_Kspipipi:
      tag_Dtype_indicators[4] = 1;
      break;
    case kDc_KKpi:
      tag_Dtype_indicators[5] = 1;
      break;
    case kD0_Kpi:
      tag_Dtype_indicators[6] = 1;
      break;
    case kD0_Kpipi0:
      tag_Dtype_indicators[7] = 1;
      break;
    case kD0_Kpipipi:
      tag_Dtype_indicators[8] = 1;
      break;
    case kD0_Kspipi:
      tag_Dtype_indicators[9] = 1;
      break;
    case kD0_Kspipipi0:
      tag_Dtype_indicators[10] = 1;
      break;
    case kD0_Kspi0:
      tag_Dtype_indicators[11] = 1;
      break;
    case kD0_KK:
      tag_Dtype_indicators[11] = 2;
      break;
  }

  return;
}

void DDpi_order_sigDtype_indicators(
  int sig_Dtype, 
  vector<int> &sig_Dtype_indicators) {

  switch (sig_Dtype) {
    case kDc_Kpipi:
      sig_Dtype_indicators[0] = 1;
      break;
    case kDc_Kpipipi0:
      sig_Dtype_indicators[1] = 1;
      break;
    case kDc_KsK:
      sig_Dtype_indicators[2] = 1;
      break;
    case kDc_Kspi: 
      sig_Dtype_indicators[2] = 2;
      break;
    case kDc_Kspipi0:
      sig_Dtype_indicators[2] = 3;
      break;
    case kDc_Kspipipi:
      sig_Dtype_indicators[3] = 1;
      break;
    case kDc_KKpi:
      sig_Dtype_indicators[4] = 1;
      break;
    case kD0_Kpi:
      sig_Dtype_indicators[5] = 1;
      break;
    case kD0_Kpipi0:
      sig_Dtype_indicators[6] = 1;
      break;
    case kD0_Kpipipi:
      sig_Dtype_indicators[7] = 1;
      break;
    case kD0_Kspipi:
      sig_Dtype_indicators[8] = 1;
      break;
    case kD0_Kspi0:
      sig_Dtype_indicators[8] = 2;
      break;
    case kD0_KK:
      sig_Dtype_indicators[8] = 3;
      break;
  }

  return;
}


bool pass_general_precuts(
  sqlite3_stmt *stmt, 
  map<string, int> &sql_column_ordering) {

  double tag_lp3 = sqlite3_column_double(stmt, sql_column_ordering["tag_lp3"]);
  double tag_cosBY = sqlite3_column_double(stmt, sql_column_ordering["tag_cosBY"]);
  double mmiss_prime2 = sqlite3_column_double(stmt, sql_column_ordering["mmiss_prime2"]);
  double eextra50 = sqlite3_column_double(stmt, sql_column_ordering["eextra50"]);
  double sig_cosBY = sqlite3_column_double(stmt, sql_column_ordering["sig_cosBY"]);

  // tag_lp3
  if ( 
      (tag_lp3 < 0.6)
     ) {
    return false;
  }

  // cosBY
  if ( 
      (tag_cosBY < -5.0) ||
      (tag_cosBY > 1.5)
     ) {
    return false;
  }

  if ( 
      (sig_cosBY < -20.0)
     ) {
    return false;
  }

  // mmiss_prime2
  if ( 
      (mmiss_prime2 < -20.0) || 
      (mmiss_prime2 > 20.0)
     ) {
    return false;
  }

  // eextra50
  if ( 
      (eextra50 > 2.5)
     ) {
    return false;
  }

  return true;
}


bool pass_DDpi_cuts(
  sqlite3_stmt *stmt, 
  map<string, int> &sql_column_ordering) {

  double tag_Dmass = sqlite3_column_double(stmt, sql_column_ordering["tag_Dmass"]);
  double sig_Dmass = sqlite3_column_double(stmt, sql_column_ordering["sig_Dmass"]);
  int tag_Dtype = sqlite3_column_int(stmt, sql_column_ordering["tag_Dtype"]);
  int sig_Dtype = sqlite3_column_int(stmt, sql_column_ordering["sig_Dtype"]);

  // Dmass
  if ( 
      (tag_Dmass < 1.82) ||
      (tag_Dmass > 1.91)
     ) {
    return false;
  }

  if ( 
      (sig_Dmass < 1.82) ||
      (sig_Dmass > 1.91)
     ) {
    return false;
  }

  // tag_Dtype
  if ( 
      (tag_Dtype == kD0_Kpipipipi0) 
     ) {
    return false;
  }

  // sig_Dtype
  if ( 
      (sig_Dtype == kD0_Kpipipipi0) || 
      (sig_Dtype == kD0_Kspipipi0)
     ) {
    return false;
  }

  return true;
}


void insert_line_libsvm_file(
    ofstream &libsvm_file,
    int truth_match,
    vector<double> &numeric_features,
    vector<int> &tag_Dtype_indicators,
    vector<int> &sig_Dtype_indicators,
    vector<int> &tag_Dstartype_indicators,
    vector<int> &sig_Dstartype_indicators
    ) {

  if (truth_match) {
    libsvm_file << "1";
  } else {
    libsvm_file << "-1";
  }

  int feature_counter = 1;

  vector<double>::iterator it_double = numeric_features.begin();
  while (it_double != numeric_features.end()) {
    libsvm_file << " ";
    libsvm_file << feature_counter;
    libsvm_file << ":"; 
    libsvm_file << *it_double; 
    ++feature_counter;
    ++it_double;
  }


  vector<int>::iterator it_int; 
  

  it_int = tag_Dtype_indicators.begin();
  while (it_int != tag_Dtype_indicators.end()) {
    libsvm_file << " ";
    libsvm_file << feature_counter;
    libsvm_file << ":"; 
    libsvm_file << *it_int; 
    ++feature_counter;
    ++it_int;
  }

  it_int = sig_Dtype_indicators.begin();
  while (it_int != sig_Dtype_indicators.end()) {
    libsvm_file << " ";
    libsvm_file << feature_counter;
    libsvm_file << ":"; 
    libsvm_file << *it_int; 
    ++feature_counter;
    ++it_int;
  }

  it_int = tag_Dstartype_indicators.begin();
  while (it_int != tag_Dstartype_indicators.end()) {
    libsvm_file << " ";
    libsvm_file << feature_counter;
    libsvm_file << ":"; 
    libsvm_file << *it_int; 
    ++feature_counter;
    ++it_int;
  }

  it_int = sig_Dstartype_indicators.begin();
  while (it_int != sig_Dstartype_indicators.end()) {
    libsvm_file << " ";
    libsvm_file << feature_counter;
    libsvm_file << ":"; 
    libsvm_file << *it_int; 
    ++feature_counter;
    ++it_int;
  }

  libsvm_file << endl;

}
