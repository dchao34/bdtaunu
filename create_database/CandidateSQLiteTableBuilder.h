#ifndef __CANDIDATESQLITETABLEBUILDER_H__
#define __CANDIDATESQLITETABLEBUILDER_H__

#include <string>
#include <vector>
#include <map>
#include <utility>

#include <sqlite3.h>

#include "SQLiteTableBuilder.h"

class CandidateSQLiteTableBuilder : public SQLiteTableBuilder {

  protected:
    std::string event_table_name;
    std::string cand_table_name;
    std::vector<std::pair<std::string, std::string> > id_colnames;
    std::vector<std::pair<std::string, std::string> > meta_colnames;
    std::vector<std::pair<std::string, std::string> > event_level_feature_colnames;
    std::vector<std::pair<std::string, std::string> > cand_level_feature_colnames;

    std::string babar_event_id;
    int cand_idx;

    int cand_type;
    int samp_type;

    double mmiss_prime2;
    double eextra50;
    double cosThetaT;

    double tag_lp3;
    double tag_cosBY;
    double tag_cosThetaDl;
    double tag_Dmass;
    double tag_deltaM;
    double tag_cosThetaDSoft;
    double tag_softP3MagCM;
    int tag_Dtype;
    int tag_Dstartype;

    double sig_hp3;
    double sig_cosBY;
    double sig_cosThetaDtau;
    double sig_vtxB;
    double sig_Dmass;
    double sig_deltaM;
    double sig_cosThetaDSoft;
    double sig_softP3MagCM;
    double sig_hmass;
    double sig_vtxh;
    int sig_Dtype;
    int sig_Dstartype;

    std::string ConstructCreateStatement() const;
    std::string ConstructInsertStatement() const;

    virtual void BindColumns();

  public:
    CandidateSQLiteTableBuilder() {};
    CandidateSQLiteTableBuilder(sqlite3 *db);
    virtual ~CandidateSQLiteTableBuilder();

    void set_babar_event_id(std::string value) { babar_event_id = value; }
    void set_cand_idx(int value) { cand_idx = value; }
    void set_cand_type(int value) { cand_type = value; }
    void set_samp_type(int value) { samp_type = value; }
    void set_mmiss_prime2(double value) { mmiss_prime2 = value; }
    void set_eextra50(double value) { eextra50 = value; }
    void set_cosThetaT(double value) { cosThetaT = value; }
    void set_tag_lp3(double value) { tag_lp3 = value; }
    void set_tag_cosBY(double value) { tag_cosBY = value; }
    void set_tag_cosThetaDl(double value) { tag_cosThetaDl = value; }
    void set_tag_Dmass(double value) { tag_Dmass = value; }
    void set_tag_deltaM(double value) { tag_deltaM = value; }
    void set_tag_cosThetaDSoft(double value) { tag_cosThetaDSoft = value; }
    void set_tag_softP3MagCM(double value) { tag_softP3MagCM = value; }
    void set_tag_Dtype(int value) { tag_Dtype = value; }
    void set_tag_Dstartype(int value) { tag_Dstartype = value; }
    void set_sig_hp3(double value) { sig_hp3 = value; }
    void set_sig_cosBY(double value) { sig_cosBY = value; }
    void set_sig_cosThetaDtau(double value) { sig_cosThetaDtau = value; }
    void set_sig_vtxB(double value) { sig_vtxB = value; }
    void set_sig_Dmass(double value) { sig_Dmass = value; }
    void set_sig_deltaM(double value) { sig_deltaM = value; }
    void set_sig_cosThetaDSoft(double value) { sig_cosThetaDSoft = value; }
    void set_sig_softP3MagCM(double value) { sig_softP3MagCM = value; }
    void set_sig_hmass(double value) { sig_hmass = value; }
    void set_sig_vtxh(double value) { sig_vtxh = value; }
    void set_sig_Dtype(int value) { sig_Dtype = value; }
    void set_sig_Dstartype(int value) { sig_Dstartype = value; }
};

#endif
