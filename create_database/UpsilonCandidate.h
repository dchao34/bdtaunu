#ifndef __UPSILONCANDIDATE__
#define __UPSILONCANDIDATE__

#include <string> 

//! Class representing an \f$\Upsilon(4S)\f$ candidate
class UpsilonCandidate {

  private:
    std::string eventId;
    int event_candidate_index;
    int reco_index;
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
    
    int l_ePidMap, l_muPidMap;
    int h_ePidMap, h_muPidMap;

    void copy_candidate(const UpsilonCandidate &cand);

  public:
    //! Constructs candidate with non-physical attributes.
    UpsilonCandidate();

    //! Constructs candidate with specified attributes. 
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

    //! Constructs candidate with specified attributes. 
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
        int sig_tau_mode,
        int l_ePidMap, int l_muPidMap); 

    //! Constructs candidate with specified attributes. 
    UpsilonCandidate(
        std::string& eventId, int event_candidate_index, 
        int reco_index, 
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
        int sig_tau_mode,
        int l_ePidMap, int l_muPidMap,
        int h_ePidMap, int h_muPidMap); 

    UpsilonCandidate(const UpsilonCandidate &cand);
    ~UpsilonCandidate() {};

    UpsilonCandidate & operator=(const UpsilonCandidate &cand);

    //! The babar ID of the event this candidate belongs to. 
    std::string get_eventId() const { return eventId; }

    //! The index that uniquely identifies the candidate within the event.
    int get_event_candidate_index() const { return event_candidate_index; }

    //! \f$ E_{extra} \f$ 
    /*! The energy sum of photons above 50 MeV that are not used in the
     * reconstruction of this candidate. */
    float get_eextra50() const { return eextra50; }

    //! \f$ M^2_{miss} \f$
    /*! This is just like the ordinary missing mass squared, except the
     * beam energy information is also incorporated to reduce the
     * uncertainty. */
    float get_mmiss_prime2() const { return mmiss_prime2; }

    //! \f$ |\vec{p}_\ell| \f$ of the \f$B_{tag}\f$
    float get_tag_lp3() const { return tag_lp3; }

    //! \f$ |\vec{p}_h| \f$ of the \f$B_{sig}\f$
    /*! \f$h\f$ is either \f$\pi\f$ or \f$\rho\f$. The letter "h"
     * is for \f$\tau\f$ decays to <B>h</B>adrons. It is the proxy for
     * the reconstructed \f$\tau\f$ since the neutrino is
     * undetectable. */
    float get_sig_hp3() const { return sig_hp3; }

    //! \f$ \cos\theta_{BY} \f$ of the \f$B_{tag}\f$
    float get_tag_cosBY() const { return tag_cosBY; }

    //! \f$ \cos\theta_{BY} \f$ of the \f$B_{sig}\f$
    float get_sig_cosBY() const { return sig_cosBY; }

    //! \f$ \cos\theta_{D\ell} \f$ of the \f$B_{tag}\f$
    float get_tag_cosThetaDl() const { return tag_cosThetaDl; }

    //! \f$ \cos\theta_{D\tau} \f$ of the \f$B_{sig}\f$
    /*! This is actually \f$ \cos\theta_{D\tau} \f$ to be precise,
     * since the \f$\tau\f$ itself is of course unreconstructable. */
    float get_sig_cosThetaDtau() const { return sig_cosThetaDtau; }

    //! \f$B_{sig}\f$ vertex quality. 
    /*! It is really (1 - pvalue)? of the \f$\chi^2\f$ fit. */
    float get_sig_vtxB() const { return sig_vtxB; }

    //! \f$ \cos\theta_{T} \f$
    /*! This is the cosine of the angle that the thrust vector makes
     * with the beam axis.  */
    float get_cosThetaT() const { return cosThetaT; }

    //! Mass of the \f$ D \f$ meson of the \f$B_{tag}\f$.
    float get_tag_Dmass() const { return tag_Dmass; }

    //! \f$\Delta m\f$ of the \f$ D \f$ meson of the \f$B_{tag}\f$.
    float get_tag_deltaM() const { return tag_deltaM; }

    //! \f$ \cos\theta_{D soft} \f$ of the \f$B_{tag}\f$
    /*! This is the cosine of the angle between the daughters of the
     * \f$D^*\f$ decay; namely the angle between the \f$ D \f$ meson
     * and the soft daughter (photon or a \f$\pi^0\f$). */
    float get_tag_cosThetaDSoft() const { return tag_cosThetaDSoft; }

    //! \f$ |\vec{p}_{soft}| \f$ of the \f$B_{tag}\f$
    /*! Magnitude of the three momentum of the \f$D^*\f$ meson's soft
     * daughter in the center of mass frame.  */
    float get_tag_softP3MagCM() const { return tag_softP3MagCM; }

    //! Mass of the \f$ D \f$ meson of the \f$B_{sig}\f$.
    float get_sig_Dmass() const { return sig_Dmass; }

    //! \f$\Delta m\f$ of the \f$ D \f$ meson of the \f$B_{sig}\f$.
    float get_sig_deltaM() const { return sig_deltaM; }

    //! \f$ \cos\theta_{D soft} \f$ of the \f$B_{sig}\f$
    /*! This is the cosine of the angle between the daughters of the
     * \f$D^*\f$ decay; namely the angle between the \f$ D \f$ meson
     * and the soft daughter (photon or a \f$\pi^0\f$). */
    float get_sig_cosThetaDSoft() const { return sig_cosThetaDSoft; }

    //! \f$ |\vec{p}_{soft}| \f$ of the \f$B_{sig}\f$
    /*! Magnitude of the three momentum of the \f$D^*\f$ meson's soft
     * daughter in the center of mass frame. */
    float get_sig_softP3MagCM() const { return sig_softP3MagCM; }

    //! Mass of the \f$h\f$. 
    float get_sig_hmass() const { return sig_hmass; }

    //! \f$h\f$ vertex quality. 
    /*! Vertex quality of the \f$h\f$. In this case, it can only be
     * the \f$\rho^+\f$. */
    float get_sig_vtxh() const { return sig_vtxh; }

    //! \f$B\f$ flavor. 
    /*! Returns an integer that corresponds to the #BFlavor enum in
     * bdtaunu_definitions.h */
    int get_bflavor() const { return bflavor; }
 
    //! Reconstructed \f$D^*\f$ mode index of the \f$B_{tag}\f$. 
    /*! Returns an integer that corresponds to the #DstarMode enum in
     * bdtaunu_definitions.h */
    int get_tag_dstar_mode() const { return tag_dstar_mode; }

    //! Reconstructed \f$D\f$ mode index of the \f$B_{tag}\f$. 
    /*! Returns an integer that corresponds to the #DMode enum in
     * bdtaunu_definitions.h */
    int get_tag_d_mode() const { return tag_d_mode; }

    //! Reconstructed \f$D^*\f$ mode index of the \f$B_{sig}\f$. 
    /*! Returns an integer that corresponds to the #DstarMode enum in
     * bdtaunu_definitions.h */
    int get_sig_dstar_mode() const { return sig_dstar_mode; }

    //! Reconstructed \f$D\f$ mode index of the \f$B_{sig}\f$. 
    /*! Returns an integer that corresponds to the #DMode enum in
     * bdtaunu_definitions.h */
    int get_sig_d_mode() const { return sig_d_mode; }

    //! Reconstructed \f$\tau\f$ mode index of the \f$B_{sig}\f$. 
    /*! Returns an integer that corresponds to the #TauMode enum in
     * bdtaunu_definitions.h */
    int get_sig_tau_mode() const { return sig_tau_mode; }

    //! Candidate type. 
    /*! Returns an int that corresponds to the #CandType enum in
     * bdtaunu_definitions.h */
    int get_cand_type() const;

    //! Sample type. 
    /*! Returns an int that corresponds to the #SampleType enum in
     * bdtaunu_definitions.h */
    int get_sample_type() const;

    //! Electron PID map of tag lepton.
    /*! Bit map is here:
     * http://www.slac.stanford.edu/BFROOT/www/Physics/Tools/Pid/Selectors/r24c/selectors.html
     */
    int get_l_ePidMap() const { return l_ePidMap; }
    int get_h_ePidMap() const { return h_ePidMap; }

    //! Muon PID map of tag lepton.
    /*! Bit map is here:
     * http://www.slac.stanford.edu/BFROOT/www/Physics/Tools/Pid/Selectors/r24c/selectors.html
     */
    int get_l_muPidMap() const { return l_muPidMap; }
    int get_h_muPidMap() const { return h_muPidMap; }

    int get_reco_index() const { return reco_index; }
};

#endif
