#ifndef __UPSILONCANDIDATE__
#define __UPSILONCANDIDATE__

#include <string> 

class UpsilonCandidate {

  private:
    std::string eventId;
    int event_candidate_index;
    float eextra50, mmiss_prime2;
    float tag_lp3, sig_hp3;
    float tag_cosBY, sig_cosBY;
    float tag_cosThetaDl, sig_cosThetaDtau;
    float sig_vtxB;
    float cosThetaT;
    float tag_Dmass, tag_deltaM;
    float tag_cosThetaDSoft, tag_softP3MagCM;
    float sig_Dmass, sig_deltaM;
    float sig_cosThetaDSoft, sig_softP3MagCM;
    float sig_hmass, sig_vtxh;
    int bflavor;
    int tag_dstar_mode, tag_d_mode;
    int sig_dstar_mode, sig_d_mode;
    int sig_tau_mode;

    void copy_candidate(const UpsilonCandidate &cand);

  public:
    UpsilonCandidate();
    UpsilonCandidate(
        std::string& eventId, int event_candidate_index, 
        float eextra50, float mmiss_prime2, 
        float tag_lp3, float sig_hp3, 
        float tag_cosBY, float sig_cosBY, 
        float tag_cosThetaDl, float sig_cosThetaDtau, 
        float sig_vtxB, 
        float cosThetaT, 
        float tag_Dmass, float tag_deltaM, 
        float tag_cosThetaDSoft, float tag_softP3MagCM,
        float sig_Dmass, float sig_deltaM, 
        float sig_cosThetaDSoft, float sig_softP3MagCM, 
        float sig_hmass, float sig_vtxh, 
        int bflavor, 
        int tag_dstar_mode, int tag_d_mode,
        int sig_dstar_mode, int sig_d_mode,
        int sig_tau_mode);

    UpsilonCandidate(const UpsilonCandidate &cand);
    ~UpsilonCandidate() {};

    UpsilonCandidate & operator=(const UpsilonCandidate &cand);

    std::string get_eventId() const { return eventId; }
    int get_event_candidate_index() const { return event_candidate_index; }
    float get_eextra50() const { return eextra50; }
    float get_mmiss_prime2() const { return mmiss_prime2; }
    float get_tag_lp3() const { return tag_lp3; }
    float get_sig_hp3() const { return sig_hp3; }
    float get_tag_cosBY() const { return tag_cosBY; }
    float get_sig_cosBY() const { return sig_cosBY; }
    float get_tag_cosThetaDl() const { return tag_cosThetaDl; }
    float get_sig_cosThetaDtau() const { return sig_cosThetaDtau; }
    float get_sig_vtxB() const { return sig_vtxB; }
    float get_cosThetaT() const { return cosThetaT; }
    float get_tag_Dmass() const { return tag_Dmass; }
    float get_tag_deltaM() const { return tag_deltaM; }
    float get_tag_cosThetaDSoft() const { return tag_cosThetaDSoft; }
    float get_tag_softP3MagCM() const { return tag_softP3MagCM; }
    float get_sig_Dmass() const { return sig_Dmass; }
    float get_sig_deltaM() const { return sig_deltaM; }
    float get_sig_cosThetaDSoft() const { return sig_cosThetaDSoft; }
    float get_sig_softP3MagCM() const { return sig_softP3MagCM; }
    float get_sig_hmass() const { return sig_hmass; }
    float get_sig_vtxh() const { return sig_vtxh; }
    int get_bflavor() const { return bflavor; }
    int get_tag_dstar_mode() const { return tag_dstar_mode; }
    int get_tag_d_mode() const { return tag_d_mode; }
    int get_sig_dstar_mode() const { return sig_dstar_mode; }
    int get_sig_d_mode() const { return sig_d_mode; }
    int get_sig_tau_mode() const { return sig_tau_mode; }

    std::string get_cand_type() const;
    std::string get_sample_type() const;
};

#endif
