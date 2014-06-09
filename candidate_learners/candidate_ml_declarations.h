#ifndef CAND_ML_H
#define CAND_ML_H

#include <sqlite3.h>

#include <vector>
#include <map>
#include <fstream>
#include <string>

std::map<std::string, std::string> get_cand_type_map();
std::string get_query_stmt(std::string cand_type, 
                           std::string ml_sample_type);

std::map<std::string, int> get_sql_column_ordering();

void insert_line_libsvm_file(
    std::ofstream &libsvm_file,
    std::vector<double> &numeric_features,
    std::vector<int> &tag_Dtype_indicators,
    std::vector<int> &sig_Dtype_indicators,
    std::vector<int> &tag_Dstartype_indicators,
    std::vector<int> &sig_Dstartype_indicators
);

bool process_DDpi(
    sqlite3_stmt *stmt, 
    std::map<std::string, int> &sql_column_ordering,
    int &truth_match, int &tag_Dtype, int &sig_Dtype,
    std::vector<double> &numeric_features,
    std::vector<int> &tag_Dtype_indicators,
    std::vector<int> &sig_Dtype_indicators);

void DDpi_order_numeric_features(
  sqlite3_stmt *stmt, 
  std::map<std::string, int> &sql_column_ordering,
  std::vector<double> &numeric_features);

void DDpi_order_tagDtype_indicators(
  int tag_Dtype, 
  std::vector<int> &tag_Dtype_indicators);

void DDpi_order_sigDtype_indicators(
  int sig_Dtype, 
  std::vector<int> &sig_Dtype_indicators);

bool pass_general_precuts(
  sqlite3_stmt *stmt, 
  std::map<std::string, int> &sql_column_ordering);

bool pass_DDpi_cuts(
  sqlite3_stmt *stmt, 
  std::map<std::string, int> &sql_column_ordering);

void insert_line_libsvm_file(
    std::ofstream &libsvm_file,
    int truth_match,
    std::vector<double> &numeric_features,
    std::vector<int> &tag_Dtype_indicators,
    std::vector<int> &sig_Dtype_indicators,
    std::vector<int> &tag_Dstartype_indicators,
    std::vector<int> &sig_Dstartype_indicators
    );

#endif
