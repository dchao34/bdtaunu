#include <sqlite3.h>

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <cstdlib>
#include <string>

#include "candidate_selection/YCandFeatureExtractorFactory.h"
#include "candidate_selection/CandidateSvmScorer.h"
#include "bdtaunu_definitions.h"

using namespace std;

void configure_sql_qeury(
    string &sql_query,
    map<string, int> &sql_column_idx_map) {

  sql_query = "SELECT "
              "McEvent.id,"
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
              "sig_Dstartype, "
              "cand_type "
              "FROM McEvent JOIN McCandidate ON "
              "McEvent.babar_event_id = McCandidate.babar_event_id " 
              "WHERE ml_sample='explore' AND division=1;";

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
  sql_column_idx_map["cand_type"] = 24;

  return;
}

int main(int argc, char **argv) {

  string sql_query;
  map<string, int> sql_column_idx_map;
  configure_sql_qeury(sql_query, sql_column_idx_map);
  cout << sql_query << endl;

  sqlite3 *db = NULL;
  string dbname = "sigmc_small.db";
  int db_status = sqlite3_open_v2(dbname.c_str(), &db,
      SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, NULL);
  if (db_status != SQLITE_OK) {
    cout << sqlite3_errmsg(db) << endl;
    return db_status;
  }

  DDpiSvmScorer ddpi_scorer;
  DDstarpiSvmScorer ddstarpi_scorer;
  DstarDpiSvmScorer dstardpi_scorer;
  DstarDstarpiSvmScorer dstardstarpi_scorer;
  DDrhoSvmScorer ddrho_scorer;
  DDstarrhoSvmScorer ddstarrho_scorer;
  DstarDrhoSvmScorer dstardrho_scorer;
  DstarDstarrhoSvmScorer dstardstarrho_scorer;

  char *errmsg;
  sqlite3_exec(db, "BEGIN TRANSACTION", NULL, NULL, &errmsg);

  sqlite3_stmt *stmt = NULL;
  db_status = sqlite3_prepare_v2(
      db, sql_query.c_str(), -1, &stmt, NULL);

  ofstream predict_output("test.predicted", ofstream::out);

  db_status = sqlite3_step(stmt);
  while(sqlite3_step(stmt) == SQLITE_ROW) {

    int cand_type = sqlite3_column_int(stmt, sql_column_idx_map["cand_type"]);

    YCandFeatureExtractor *extractor = 
      YCandFeatureExtractorFactory::CreateExtractor(cand_type);

    CandidateSvmScorer *svm_scorer;
    switch (cand_type) {
      case kDDpi:
        svm_scorer = &ddpi_scorer;
        break;
      case kDDstarpi:
        svm_scorer = &ddstarpi_scorer;
        break;
      case kDstarDpi:
        svm_scorer = &dstardpi_scorer;
        break;
      case kDstarDstarpi:
        svm_scorer = &dstardstarpi_scorer;
        break;
      case kDDrho:
        svm_scorer = &ddrho_scorer;
        break;
      case kDDstarrho:
        svm_scorer = &ddstarrho_scorer;
        break;
      case kDstarDrho:
        svm_scorer = &dstardrho_scorer;
        break;
      case kDstarDstarrho:
        svm_scorer = &dstardstarrho_scorer;
        break;
    }


    extractor->set_truth_match(sqlite3_column_int(stmt, sql_column_idx_map["truth_match"]));
    extractor->set_tag_lp3(sqlite3_column_double(stmt, sql_column_idx_map["tag_lp3"]));
    extractor->set_tag_cosBY(sqlite3_column_double(stmt, sql_column_idx_map["tag_cosBY"]));
    extractor->set_tag_cosThetaDl(sqlite3_column_double(stmt, sql_column_idx_map["tag_cosThetaDl"]));
    extractor->set_sig_hp3(sqlite3_column_double(stmt, sql_column_idx_map["sig_hp3"]));
    extractor->set_sig_vtxB(sqlite3_column_double(stmt, sql_column_idx_map["sig_vtxB"]));
    extractor->set_mmiss_prime2(sqlite3_column_double(stmt, sql_column_idx_map["mmiss_prime2"]));
    extractor->set_eextra50(sqlite3_column_double(stmt, sql_column_idx_map["eextra50"]));
    extractor->set_tag_Dmass(sqlite3_column_double(stmt, sql_column_idx_map["tag_Dmass"]));
    extractor->set_sig_Dmass(sqlite3_column_double(stmt, sql_column_idx_map["sig_Dmass"]));
    extractor->set_sig_cosBY(sqlite3_column_double(stmt, sql_column_idx_map["sig_cosBY"]));
    extractor->set_tag_deltaM(sqlite3_column_double(stmt, sql_column_idx_map["tag_deltaM"]));
    extractor->set_tag_cosThetaDSoft(sqlite3_column_double(stmt, sql_column_idx_map["tag_cosThetaDSoft"]));
    extractor->set_tag_softP3MagCM(sqlite3_column_double(stmt, sql_column_idx_map["tag_softP3MagCM"]));
    extractor->set_sig_deltaM(sqlite3_column_double(stmt, sql_column_idx_map["sig_deltaM"]));
    extractor->set_sig_cosThetaDSoft(sqlite3_column_double(stmt, sql_column_idx_map["sig_cosThetaDSoft"]));
    extractor->set_sig_softP3MagCM(sqlite3_column_double(stmt, sql_column_idx_map["sig_softP3MagCM"]));
    extractor->set_sig_hmass(sqlite3_column_double(stmt, sql_column_idx_map["sig_hmass"]));
    extractor->set_sig_vtxh(sqlite3_column_double(stmt, sql_column_idx_map["sig_vtxh"]));
    extractor->set_tag_Dtype(sqlite3_column_int(stmt, sql_column_idx_map["tag_Dtype"]));
    extractor->set_sig_Dtype(sqlite3_column_int(stmt, sql_column_idx_map["sig_Dtype"]));
    extractor->set_tag_Dstartype(sqlite3_column_int(stmt, sql_column_idx_map["tag_Dstartype"]));
    extractor->set_sig_Dstartype(sqlite3_column_int(stmt, sql_column_idx_map["sig_Dstartype"]));
    extractor->extract_features();

    if (!extractor->pass_selection()) {
      continue;
    }

    svm_scorer->set_features(*extractor);
    svm_scorer->svm_predict();
    const double *prob = svm_scorer->get_prob();
    predict_output << prob[0] << " " << prob[1] << endl;

    delete extractor;
  }

  predict_output.close();

  db_status = sqlite3_finalize(stmt);
  sqlite3_exec(db, "END TRANSACTION", NULL, NULL, &errmsg);
  sqlite3_close_v2(db);

}
