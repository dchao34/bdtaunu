#ifndef __EVENTFEATUREEXTRACTOR_H__
#define __EVENTFEATUREEXTRACTOR_H__

#include <vector>
#include <string>
#include <map>

#include "Event.h"

class EventFeatureExtractor {

  protected:

    int id;
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

    std::vector<double> numeric_features;
    std::vector<int> cand_type_indicators;
    std::vector<int> tagD_indicators, sigD_indicators;
    std::vector<int> tagDstar_indicators, sigDstar_indicators;

    void ClearCache();
    void ClearFeatures();

  public:
    EventFeatureExtractor();
    EventFeatureExtractor(
        int n_num, int n_cand_type,
        int n_tagD, int n_sigD,
        int n_tagDstar, int n_sigDstar);
    virtual ~EventFeatureExtractor() {};

    virtual int categorize_event_type() const;
    virtual bool passed_selection() const;
    virtual void extract_features() = 0;
    void extract_features(const Event &event);

    const std::vector<double>& get_numeric_features() const { return numeric_features; }
    const std::vector<int>& get_cand_type_indicators() const { return tagD_indicators; }
    const std::vector<int>& get_tagD_indicators() const { return tagD_indicators; }
    const std::vector<int>& get_sigD_indicators() const { return sigD_indicators; }
    const std::vector<int>& get_tagDstar_indicators() const { return tagDstar_indicators; }
    const std::vector<int>& get_sigDstar_indicators() const { return sigDstar_indicators; }

    void set_id(int value) { id = value; }
    void set_mc_evttypeA(int value) { mc_evttypeA = value; }
    void set_event_weight(double value) { event_weight = value; }
    void set_cand_type(int value) { cand_type = value; }
    void set_tag_Dtype(int value) { tag_Dtype = value; }
    void set_tag_Dstartype(int value) { tag_Dstartype = value; }
    void set_sig_Dtype(int value) { sig_Dtype = value; }
    void set_sig_Dstartype(int value) { sig_Dstartype = value; }
    void set_nTrk(int value) { nTrk = value; }
    void set_R2(double value) { R2 = value; }
    void set_cosThetaT(double value) { cosThetaT = value; }
    void set_eextra50(double value) { eextra50 = value; }
    void set_mmiss_prime2(double value) { mmiss_prime2 = value; }
    void set_tag_lp3(double value) { tag_lp3 = value; }
    void set_tag_cosBY(double value) { tag_cosBY = value; }
    void set_tag_cosThetaDl(double value) { tag_cosThetaDl = value;  }
    void set_sig_hp3(double value) { sig_hp3 = value; }
    void set_sig_cosBY(double value) { sig_cosBY = value; }
    void set_sig_cosThetaDtau(double value) { sig_cosThetaDtau = value; }
    void set_sig_vtxB(double value) { sig_vtxB = value; }
    void set_svm_score(double value) { svm_score = value; }
    void set_tag_Dmass(double value) { tag_Dmass = value; }
    void set_tag_deltaM(double value) { tag_deltaM = value; }
    void set_tag_cosThetaDSoft(double value) { tag_cosThetaDSoft = value; }
    void set_tag_softP3MagCM(double value) { tag_softP3MagCM = value; }
    void set_sig_Dmass(double value) { sig_Dmass = value; }
    void set_sig_deltaM(double value) { sig_deltaM = value; }
    void set_sig_cosThetaDSoft(double value) { sig_cosThetaDSoft = value; }
    void set_sig_softP3MagCM(double value) { sig_softP3MagCM = value; }
    void set_sig_hmass(double value) { sig_hmass = value; }
    void set_sig_vtxh(double value) { sig_vtxh = value; }

    std::string get_libsvm_line() const;
    double get_event_weight() const { return event_weight; }
};

class ContinuumFeatureExtractor : public EventFeatureExtractor {
  public:

    using EventFeatureExtractor::extract_features;

    ContinuumFeatureExtractor() :
        EventFeatureExtractor(12, 0, 0, 0, 0, 0)  { ClearCache(); ClearFeatures(); }

    int categorize_event_type() const;
    void extract_features();
};

class SignalFeatureExtractor : public EventFeatureExtractor {
  public:

    using EventFeatureExtractor::extract_features;

    SignalFeatureExtractor() :
        EventFeatureExtractor(10, 0, 0, 0, 0, 0)  { ClearCache(); ClearFeatures(); }

    int categorize_event_type() const;
    void extract_features();
};

class SigVsSLFeatureExtractor : public EventFeatureExtractor {
  public:

    using EventFeatureExtractor::extract_features;

    SigVsSLFeatureExtractor() :
        EventFeatureExtractor(10, 0, 0, 0, 0, 0)  { ClearCache(); ClearFeatures(); }

    int categorize_event_type() const;
    void extract_features();
};

class SigVsHadFeatureExtractor : public EventFeatureExtractor {
  public:

    using EventFeatureExtractor::extract_features;

    SigVsHadFeatureExtractor() :
        EventFeatureExtractor(10, 0, 0, 0, 0, 0)  { ClearCache(); ClearFeatures(); }

    int categorize_event_type() const;
    void extract_features();
};

class SigVsContFeatureExtractor : public EventFeatureExtractor {
  public:

    using EventFeatureExtractor::extract_features;

    SigVsContFeatureExtractor() :
        EventFeatureExtractor(12, 0, 0, 0, 0, 0)  { ClearCache(); ClearFeatures(); }

    int categorize_event_type() const;
    void extract_features();
};

class SigVsAllFeatureExtractor : public EventFeatureExtractor {
  public:

    using EventFeatureExtractor::extract_features;

    SigVsAllFeatureExtractor() :
        EventFeatureExtractor(12, 0, 0, 0, 0, 0)  { ClearCache(); ClearFeatures(); }

    int categorize_event_type() const;
    void extract_features();
};

#endif
