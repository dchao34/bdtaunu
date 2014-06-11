#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <iostream>

#include <sqlite3.h>

#include "YCandFeatureExtractor.h"
#include "bdtaunu_definitions.h"

std::map<std::string, int> 
YCandFeatureExtractor::candtype_name_map = 
YCandFeatureExtractor::build_candtype_name_map();

std::map<std::string, int> YCandFeatureExtractor::build_candtype_name_map() {

  std::map<std::string, int> candtype_name_map;
  candtype_name_map["DDpi"] = kDDpi;
  candtype_name_map["DDstarpi"] = kDDstarpi;
  candtype_name_map["DstarDpi"] = kDstarDpi;
  candtype_name_map["DstarDstarpi"] = kDstarDstarpi;
  candtype_name_map["DDrho"] = kDDrho;
  candtype_name_map["DDstarrho"] = kDDstarrho;
  candtype_name_map["DstarDrho"] = kDstarDrho;
  candtype_name_map["DstarDstarrho"] = kDstarDstarrho;

  return candtype_name_map;
}

std::map<std::string, int> 
YCandFeatureExtractor::sql_column_idx_map = 
YCandFeatureExtractor::build_sql_column_idx_map();

std::map<std::string, int> YCandFeatureExtractor::build_sql_column_idx_map() {

  std::map<std::string, int> sql_column_idx_map;
  sql_column_idx_map["id"] = 0;
  sql_column_idx_map["truth_match"] = 1;
  sql_column_idx_map["tag_lp3"] = 2;
  sql_column_idx_map["tag_cosBY"] = 3;
  sql_column_idx_map["tag_cosThetaDl"] = 4;
  sql_column_idx_map["sig_hp3"] = 5;
  sql_column_idx_map["sig_vtxB"] = 6;
  sql_column_idx_map["mmiss_prime2"] = 7;
  sql_column_idx_map["eextra50"] = 8;
  sql_column_idx_map["tag_Dmass"] = 9;
  sql_column_idx_map["sig_Dmass"] = 10;
  sql_column_idx_map["tag_Dtype"] = 11;
  sql_column_idx_map["sig_Dtype"] = 12;
  sql_column_idx_map["sig_cosBY"] = 13;
  sql_column_idx_map["tag_deltaM"] = 14;
  sql_column_idx_map["tag_cosThetaDSoft"] = 15;
  sql_column_idx_map["tag_softP3MagCM"] = 16;
  sql_column_idx_map["sig_deltaM"] = 17;
  sql_column_idx_map["sig_cosThetaDSoft"] = 18;
  sql_column_idx_map["sig_softP3MagCM"] = 19;
  sql_column_idx_map["sig_hmass"] = 20;
  sql_column_idx_map["sig_vtxh"] = 21;
  sql_column_idx_map["tag_Dstartype"] = 22;
  sql_column_idx_map["sig_Dstartype"] = 23;

  return sql_column_idx_map;
}


YCandFeatureExtractor::YCandFeatureExtractor() : 
    numeric_features(), 
    tagD_indicators(),
    sigD_indicators(), 
    tagDstar_indicators(), 
    sigDstar_indicators() {
    Clear();
}
YCandFeatureExtractor::YCandFeatureExtractor(
    int n_num, 
    int n_tagD, int n_sigD, 
    int n_tagDstar, int n_sigDstar) {

    Clear();

    if (n_num > 0) {
      numeric_features = std::vector<double>(n_num, 0);
    } else {
      numeric_features = std::vector<double>();
    }

    if (n_tagD > 0) {
      tagD_indicators = std::vector<int>(n_tagD, 0);
    } else {
      tagD_indicators = std::vector<int>();
    }

    if (n_sigD > 0) {
      sigD_indicators = std::vector<int>(n_sigD, 0);
    } else {
      sigD_indicators = std::vector<int>();
    }

    if (n_tagDstar > 0) {
      tagDstar_indicators = std::vector<int>(n_tagDstar, 0);
    } else {
      tagDstar_indicators = std::vector<int>();
    }

    if (n_sigDstar > 0) {
      sigDstar_indicators = std::vector<int>(n_sigDstar, 0);
    } else {
      sigDstar_indicators = std::vector<int>();
    }
}


std::string YCandFeatureExtractor::get_sql_query_statement(
    const std::string &candtype_name, 
    const std::string &ml_sample_type) const {

  std::stringstream ss;
  ss << candtype_name_map[candtype_name];
  std::string cand_type = ss.str();

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
                           + " AND division=1"
                           + ";";
  return sql_query;
}

void YCandFeatureExtractor::update_features(sqlite3_stmt *stmt) {

  Clear();

  id = sqlite3_column_int(stmt, sql_column_idx_map["id"]);
  truth_match = sqlite3_column_int(stmt, sql_column_idx_map["truth_match"]);

  tag_lp3 = sqlite3_column_double(stmt, sql_column_idx_map["tag_lp3"]);
  tag_cosBY = sqlite3_column_double(stmt, sql_column_idx_map["tag_cosBY"]);
  tag_cosThetaDl = sqlite3_column_double(stmt, sql_column_idx_map["tag_cosThetaDl"]);
  sig_hp3 = sqlite3_column_double(stmt, sql_column_idx_map["sig_hp3"]);
  sig_vtxB = sqlite3_column_double(stmt, sql_column_idx_map["sig_vtxB"]);
  mmiss_prime2 = sqlite3_column_double(stmt, sql_column_idx_map["mmiss_prime2"]);
  eextra50 = sqlite3_column_double(stmt, sql_column_idx_map["eextra50"]);
  tag_Dmass = sqlite3_column_double(stmt, sql_column_idx_map["tag_Dmass"]);
  sig_Dmass = sqlite3_column_double(stmt, sql_column_idx_map["sig_Dmass"]);
  sig_cosBY = sqlite3_column_double(stmt, sql_column_idx_map["sig_cosBY"]);
  tag_deltaM = sqlite3_column_double(stmt, sql_column_idx_map["tag_deltaM"]);
  tag_cosThetaDSoft = sqlite3_column_double(stmt, sql_column_idx_map["tag_cosThetaDSoft"]);
  tag_softP3MagCM = sqlite3_column_double(stmt, sql_column_idx_map["tag_softP3MagCM"]);
  sig_deltaM = sqlite3_column_double(stmt, sql_column_idx_map["sig_deltaM"]);
  sig_cosThetaDSoft = sqlite3_column_double(stmt, sql_column_idx_map["sig_cosThetaDSoft"]);
  sig_softP3MagCM = sqlite3_column_double(stmt, sql_column_idx_map["sig_softP3MagCM"]);
  sig_hmass = sqlite3_column_double(stmt, sql_column_idx_map["sig_hmass"]);
  sig_vtxh = sqlite3_column_double(stmt, sql_column_idx_map["sig_vtxh"]);

  tag_Dtype = sqlite3_column_int(stmt, sql_column_idx_map["tag_Dtype"]);
  sig_Dtype = sqlite3_column_int(stmt, sql_column_idx_map["sig_Dtype"]);
  tag_Dstartype = sqlite3_column_int(stmt, sql_column_idx_map["tag_Dstartype"]);
  sig_Dstartype = sqlite3_column_int(stmt, sql_column_idx_map["sig_Dstartype"]);
}

void YCandFeatureExtractor::Clear() {

  id = 0;
  truth_match = 0;

  tag_lp3 = 0;
  tag_cosBY = 0;
  tag_cosThetaDl = 0;
  sig_hp3 = 0;
  sig_vtxB = 0;
  mmiss_prime2 = 0;
  eextra50 = 0;
  tag_Dmass = 0;
  sig_Dmass = 0;
  sig_cosBY = 0;
  tag_deltaM = 0;
  tag_cosThetaDSoft = 0;
  tag_softP3MagCM = 0;
  sig_deltaM = 0;
  sig_cosThetaDSoft = 0;
  sig_softP3MagCM = 0;
  sig_hmass = 0;
  sig_vtxh = 0;

  tag_Dtype = 0;
  sig_Dtype = 0;
  tag_Dstartype = 0;
  sig_Dstartype = 0;

  std::vector<double>::iterator it_double = numeric_features.begin();
  while (it_double != numeric_features.end()) {
    *it_double = 0;
    ++it_double;
  }

  std::vector<int>::iterator it_int; 

  it_int = tagD_indicators.begin();
  while (it_int != tagD_indicators.end()) {
    *it_int = 0;
    ++it_int;
  }

  it_int = sigD_indicators.begin();
  while (it_int != sigD_indicators.end()) {
    *it_int = 0;
    ++it_int;
  }

  it_int = tagDstar_indicators.begin();
  while (it_int != tagDstar_indicators.end()) {
    *it_int = 0;
    ++it_int;
  }

  it_int = sigDstar_indicators.begin();
  while (it_int != sigDstar_indicators.end()) {
    *it_int = 0;
    ++it_int;
  }

}

bool YCandFeatureExtractor::pass_selection() const {

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

std::string YCandFeatureExtractor::get_libsvm_line() const {

  std::stringstream libsvm_line;
  if (truth_match) {
    libsvm_line << "1";
  } else {
    libsvm_line << "-1";
  }

  int feature_counter = 1;

  std::vector<double>::const_iterator it_double = numeric_features.begin();
  while (it_double != numeric_features.end()) {
    libsvm_line << " ";
    libsvm_line << feature_counter;
    libsvm_line << ":";
    libsvm_line << *it_double;
    ++feature_counter;
    ++it_double;
  }


  std::vector<int>::const_iterator it_int;

  it_int = tagD_indicators.begin();
  while (it_int != tagD_indicators.end()) {
    libsvm_line << " ";
    libsvm_line << feature_counter;
    libsvm_line << ":";
    libsvm_line << *it_int;
    ++feature_counter;
    ++it_int;
  }

  it_int = sigD_indicators.begin();
  while (it_int != sigD_indicators.end()) {
    libsvm_line << " ";
    libsvm_line << feature_counter;
    libsvm_line << ":";
    libsvm_line << *it_int;
    ++feature_counter;
    ++it_int;
  }

  it_int = tagDstar_indicators.begin();
  while (it_int != tagDstar_indicators.end()) {
    libsvm_line << " ";
    libsvm_line << feature_counter;
    libsvm_line << ":";
    libsvm_line << *it_int;
    ++feature_counter;
    ++it_int;
  }

  it_int = sigDstar_indicators.begin();
  while (it_int != sigDstar_indicators.end()) {
    libsvm_line << " ";
    libsvm_line << feature_counter;
    libsvm_line << ":";
    libsvm_line << *it_int;
    ++feature_counter;
    ++it_int;
  }

  return libsvm_line.str();
}
