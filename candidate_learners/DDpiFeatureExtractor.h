#ifndef __DDPIFEATUREEXTRACTOR_H__
#define __DDPIFEATUREEXTRACTOR_H__

#include <string>

#include <sqlite3.h>

#include "YCandFeatureExtractor.h"

class DDpiFeatureExtractor : public YCandFeatureExtractor {

  private:
    const static std::string candtype_name;

  private:
    std::string mlsample_type;

  public:
    DDpiFeatureExtractor();
    DDpiFeatureExtractor(std::string &mlsample);
    ~DDpiFeatureExtractor() {};

    std::string get_candtype_name() const { return candtype_name; }
    std::string get_sql_query_statement() const;
    void update_features(sqlite3_stmt *stmt);
    bool pass_selection() const;

    std::string get_dat_header() const;
    std::string get_dat_line() const;

};

#endif