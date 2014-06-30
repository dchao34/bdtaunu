#ifndef __YCANDFEATUREEXTRACTOR_H__
#define __YCANDFEATUREEXTRACTOR_H__

#include <vector>
#include <string>
#include <map>

#include "create_database/UpsilonCandidate.h"

class YCandFeatureExtractor {

  protected:

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

    std::vector<double> numeric_features;
    std::vector<int> tagD_indicators, sigD_indicators;
    std::vector<int> tagDstar_indicators, sigDstar_indicators;

    void ClearCache();
    void ClearFeatures();

  public:
    YCandFeatureExtractor();
    YCandFeatureExtractor(
        int n_num, 
        int n_tagD, int n_sigD,
        int n_tagDstar, int n_sigDstar);
    virtual ~YCandFeatureExtractor() {};

    virtual bool pass_selection() const;
    virtual void extract_features() = 0;
    void extract_features(const UpsilonCandidate&);

    const std::vector<double>& get_numeric_features() const { return numeric_features; }
    const std::vector<int>& get_tagD_indicators() const { return tagD_indicators; }
    const std::vector<int>& get_sigD_indicators() const { return sigD_indicators; }
    const std::vector<int>& get_tagDstar_indicators() const { return tagDstar_indicators; }
    const std::vector<int>& get_sigDstar_indicators() const { return sigDstar_indicators; }

    void set_id(int value) { id = value; }
    void set_truth_match(int value) { truth_match = value; }
    void set_tag_lp3(double value) { tag_lp3 = value; }
    void set_tag_cosBY(double value) { tag_cosBY = value; }
    void set_tag_cosThetaDl(double value) { tag_cosThetaDl = value; }
    void set_sig_hp3(double value) { sig_hp3 = value; }
    void set_sig_vtxB(double value) { sig_vtxB = value; }
    void set_mmiss_prime2(double value) { mmiss_prime2 = value; }
    void set_eextra50(double value) { eextra50 = value; }
    void set_tag_Dmass(double value) { tag_Dmass = value; }
    void set_sig_Dmass(double value) { sig_Dmass = value; }
    void set_sig_cosBY(double value) { sig_cosBY = value; }
    void set_tag_deltaM(double value) { tag_deltaM = value; }
    void set_tag_cosThetaDSoft(double value) { tag_cosThetaDSoft = value; }
    void set_tag_softP3MagCM(double value) { tag_softP3MagCM = value; }
    void set_sig_deltaM(double value) { sig_deltaM = value; }
    void set_sig_cosThetaDSoft(double value) { sig_cosThetaDSoft = value; }
    void set_sig_softP3MagCM(double value) { sig_softP3MagCM = value; }
    void set_sig_hmass(double value) { sig_hmass = value; }
    void set_sig_vtxh(double value) { sig_vtxh = value; }
    void set_tag_Dtype(int value) { tag_Dtype = value; }
    void set_sig_Dtype(int value) { sig_Dtype = value; }
    void set_tag_Dstartype(int value) { tag_Dstartype = value; }
    void set_sig_Dstartype(int value) { sig_Dstartype = value; }

    std::string get_libsvm_line() const;
};

class DDpiFeatureExtractor : public YCandFeatureExtractor {

  public:
    DDpiFeatureExtractor() : 
      YCandFeatureExtractor(9, 10, 9, 0, 0)  { ClearCache(); ClearFeatures(); }
    ~DDpiFeatureExtractor() {};

    void extract_features();
    bool pass_selection() const;

};

class DDstarpiFeatureExtractor : public YCandFeatureExtractor {

  public:
    DDstarpiFeatureExtractor() :
      YCandFeatureExtractor(11, 9, 7, 0, 4)  { ClearCache(); ClearFeatures(); }

    void extract_features();
    bool pass_selection() const;

};

class DstarDpiFeatureExtractor : public YCandFeatureExtractor {

  public:
    DstarDpiFeatureExtractor() :
      YCandFeatureExtractor(11, 9, 9, 4, 0)  { ClearCache(); ClearFeatures(); }

    void extract_features();
    bool pass_selection() const;

};

class DstarDstarpiFeatureExtractor : public YCandFeatureExtractor {

  public:
    DstarDstarpiFeatureExtractor() :
      YCandFeatureExtractor(13, 12, 9, 4, 4)  { ClearCache(); ClearFeatures(); }

    void extract_features();
    bool pass_selection() const;

};

class DDrhoFeatureExtractor : public YCandFeatureExtractor {

  public:
    DDrhoFeatureExtractor() : 
      YCandFeatureExtractor(11, 10, 9, 0, 0)  { ClearCache(); ClearFeatures(); }
    ~DDrhoFeatureExtractor() {};

    void extract_features();
    bool pass_selection() const;

};

class DDstarrhoFeatureExtractor : public YCandFeatureExtractor {

  public:
    DDstarrhoFeatureExtractor() :
      YCandFeatureExtractor(13, 9, 9, 0, 4)  { ClearCache(); ClearFeatures(); }

    void extract_features();
    bool pass_selection() const;

};

class DstarDrhoFeatureExtractor : public YCandFeatureExtractor {

  public:
    DstarDrhoFeatureExtractor() :
      YCandFeatureExtractor(13, 9, 9, 4, 0)  { ClearCache(); ClearFeatures(); }

    void extract_features();
    bool pass_selection() const;

};

class DstarDstarrhoFeatureExtractor : public YCandFeatureExtractor {

  public:
    DstarDstarrhoFeatureExtractor() :
      YCandFeatureExtractor(15, 9, 9, 4, 4)  { ClearCache(); ClearFeatures(); }

    void extract_features();
    bool pass_selection() const;

};

#endif
