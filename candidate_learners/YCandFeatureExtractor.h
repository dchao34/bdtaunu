#ifndef __YCANDFEATUREEXTRACTOR_H__
#define __YCANDFEATUREEXTRACTOR_H__

#include <vector>
#include <string>
#include <map>

#include <sqlite3.h>

class YCandFeatureExtractor {
  private: 
    static std::map<std::string, int> candtype_name_map;
    static std::map<std::string, int> sql_column_idx_map;

    static std::map<std::string, int> build_candtype_name_map();
    static std::map<std::string, int> build_sql_column_idx_map();

  protected:

    std::vector<double> numeric_features;
    std::vector<int> tagD_indicators, sigD_indicators;
    std::vector<int> tagDstar_indicators, sigDstar_indicators;

    int id;
    int truth_match;
    double tag_lp3, tag_cosBY, tag_cosThetaDl;
    double tag_Dmass, tag_deltaM, tag_cosThetaDSoft, tag_softP3MagCM;
    double sig_hp3, sig_cosBY, sig_vtxB;
    double sig_Dmass, sig_deltaM, sig_cosThetaDSoft, sig_softP3MagCM;
    double sig_hmass, sig_vtxh;
    double mmiss_prime2, eextra50;
    int tag_Dtype, sig_Dtype;
    int tag_Dstartype, sig_Dstartype;

    std::string get_sql_query_statement(
        const std::string &candtype_name, 
        const std::string &ml_sample_type) const;

    void Clear();

  public:
    YCandFeatureExtractor();
    YCandFeatureExtractor(int n_num, int n_tagD, int n_sigD);
    virtual ~YCandFeatureExtractor() {};

    virtual std::string get_candtype_name() const = 0;
    virtual std::string get_sql_query_statement() const = 0;
    virtual void update_features(sqlite3_stmt *stmt);
    virtual bool pass_selection() const;

    virtual std::string get_dat_header() const = 0;
    virtual std::string get_dat_line() const = 0;
    std::string get_libsvm_line() const;
};

#endif
