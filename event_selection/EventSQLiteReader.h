#ifndef __EVENTSQLITEREADER_H__
#define __EVENTSQLITEREADER_H__

#include <string>
#include <map>

#include <sqlite3.h>

#include "SQLiteReader.h"

class EventSQLiteReader : public SQLiteReader {

  private:
    std::string ml_sample_type;
    std::string division;

    int id;
    std::string babar_event_id;
    int mc_evttypeA;
    double event_weight;

    int cand_type;
    int tag_Dtype, tag_Dstartype;
    int sig_Dtype, sig_Dstartype;

    int nTrk;
    double R2, cosThetaT;
    double eextra50, mmiss_prime2;
    double tag_lp3, tag_cosBY, tag_cosThetaDl; 
    double sig_hp3, sig_cosBY, sig_cosThetaDtau, sig_vtxB;
    double svm_score;

    double tag_Dmass, tag_deltaM, tag_cosThetaDSoft, tag_softP3MagCM;
    double sig_Dmass, sig_deltaM, sig_cosThetaDSoft, sig_softP3MagCM;
    double sig_hmass, sig_vtxh;

    std::string ConstructSelectStatement() const;
    void BuildColumnIndexMap();
    void UpdateColumns();
    void ClearColumns();

  public:
    EventSQLiteReader();
    EventSQLiteReader(
        const char *dbname, 
        const char *ml_samp_type, 
        const char *division);
    ~EventSQLiteReader() {};

    int get_id() const { return id; }
    std::string get_babar_event_id() const { return babar_event_id; }
    int get_mc_evttypeA() const { return mc_evttypeA; }
    double get_event_weight() const { return event_weight; }

    int get_cand_type() const { return cand_type; }
    int get_tag_Dtype() const { return tag_Dtype; }
    int get_tag_Dstartype() const { return tag_Dstartype; }
    int get_sig_Dtype() const { return sig_Dtype; }
    int get_sig_Dstartype() const { return sig_Dstartype; }

    int get_nTrk() const { return nTrk; }
    double get_R2() const { return R2; }
    double get_cosThetaT() const { return cosThetaT; }
    double get_eextra50() const { return eextra50; }
    double get_mmiss_prime2() const { return mmiss_prime2; }
    double get_tag_lp3() const { return tag_lp3; }
    double get_tag_cosBY() const { return tag_cosBY; }
    double get_tag_cosThetaDl() const { return tag_cosThetaDl;  }
    double get_sig_hp3() const { return sig_hp3; }
    double get_sig_cosBY() const { return sig_cosBY; }
    double get_sig_cosThetaDtau() const { return sig_cosThetaDtau; }
    double get_sig_vtxB() const { return sig_vtxB; }
    double get_svm_score() const { return svm_score; }

    double get_tag_Dmass() const { return tag_Dmass; }
    double get_tag_deltaM() const { return tag_deltaM; }
    double get_tag_cosThetaDSoft() const { return tag_cosThetaDSoft; }
    double get_tag_softP3MagCM() const { return tag_softP3MagCM; }
    double get_sig_Dmass() const { return sig_Dmass; }
    double get_sig_deltaM() const { return sig_deltaM; }
    double get_sig_cosThetaDSoft() const { return sig_cosThetaDSoft; }
    double get_sig_softP3MagCM() const { return sig_softP3MagCM; }
    double get_sig_hmass() const { return sig_hmass; }
    double get_sig_vtxh() const { return sig_vtxh; }
};

#endif
