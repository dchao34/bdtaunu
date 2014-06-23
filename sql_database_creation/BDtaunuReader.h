#ifndef __BDTAUNUREADER_H__
#define __BDTAUNUREADER_H__

#include <TTree.h>

#include <string>
#include <map>

#include "RootReader.h"
#include "UpsilonList.h"

//! Reads ntuples produced by BtaTupleMaker and computes data related to detector response. 
/*! This class is responsible for assembling all data that can be
 * derived from the detector's response to an event. More
 * specifically, it contains the following types of information: 
 * - Macro level event infromation. Examples:
 *   - Fox-Wolfram moment. 
 *   - nTrks. 
 * - \f$\Upsilon(4S)\f$ candidate information. Examples:
 *   - \f$E_{extra}\f$.
 *   - \f$m_D\f$ of \f$B_{sig}\f$.
 *   - Reconstructed type. See #CandType enum. 
 *
 * All other event information that does not belong in the above
 * categories must be computed in a class that derives from this one.
 * For example, Monte Carlo information should be computed in a
 * subclass. */
class BDtaunuReader : public RootReader {

  protected: 
    static std::map<std::string, int> build_lund_map();

    static const int maximum_Y_candidates;
    static const int maximum_B_candidates;
    static const int maximum_D_candidates;
    static const int maximum_tau_candidates;
    static const int maximum_h_candidates;
    static const int maximum_l_candidates;
    static const int maximum_gamma_candidates;
    static std::map<std::string, int> lundIdMap;

  private: 
    int platform, partition, upperID, lowerID;
    int nTrk;
    float R2All;

    float *YBPairMmissPrime2, *YBPairEextra50;
    float *YTagBlP3MagCM, *YSigBhP3MagCM;
    float *YTagBCosBY, *YSigBCosBY;
    float *YTagBCosThetaDlCM, *YSigBCosThetaDtauCM;
    float *YSigBVtxProbB;
    float *YBPairCosThetaT;
    float *YTagBDMass, *YTagBDstarDeltaM;
    float *YTagBCosThetaDSoftCM, *YTagBsoftP3MagCM;
    float *YSigBDMass, *YSigBDstarDeltaM;
    float *YSigBCosThetaDSoftCM, *YSigBsoftP3MagCM;
    float *YSigBhMass, *YSigBVtxProbh;

  protected: 
    int nY, nB, nD; 
    int ntau, nh, nl, ngamma;
    int *Yd1Idx, *Yd2Idx;
    int *Bd1Idx, *Bd2Idx;
    int *Dd1Idx, *Dd2Idx, *Dd3Idx, *Dd4Idx, *Dd5Idx;
    int *taud1Idx;
    int *Yd1Lund, *Yd2Lund;
    int *Bd1Lund, *Bd2Lund;
    int *Dd1Lund, *Dd2Lund, *Dd3Lund, *Dd4Lund, *Dd5Lund;
    int *taud1Lund;

  private: 
    std::string eventId;
    UpsilonList upsilon_candidates;

    void FillUpsilonList();

    void ComputeCandidateDecay(
        int ups_cand_idx,
        int &Bflavor, int &tag_Dmode, int &tag_Dstarmode,
        int &sig_Dmode, int &sig_Dstarmode, int &sig_taumode);
    int DetermineBFlavor(int lundId);
    int DetermineDstarMode(int Dd1_lundId, int Dd2_lundId, 
                           int Dd3_lundId, int Dd4_lundId, int Dd5_lundId); 
    int DetermineDMode(int D_lundId, int Dd1_lundId, int Dd2_lundId, 
                       int Dd3_lundId, int Dd4_lundId, int Dd5_lundId); 
    int DetermineTauMode(int taud1_lundId);

  protected: 

    virtual void Initialize();
    virtual void SetBranchAddress();
    virtual void ClearColumnValues();


  public: 

    //! Default construction undefined. 
    BDtaunuReader();

    //! Construct with specified root file name. TTree name assumed to be "ntp1".
    BDtaunuReader(const char *root_fname);

    //! Construct with specified root file name and TTree name.
    BDtaunuReader(const char *root_fname, const char *root_trname);
    virtual ~BDtaunuReader();

    //! Read in the next event. 
    /*! Returns an integer that indexes the event number. Returns -1
     * when all events have been read. 
     *
     * Calling this automatically computes all features associated
     * with the event that the analysis is interested in. */
    virtual int next_record();

    //! Babar event Id. 
    std::string get_eventId() const { return eventId; }

    //! nTRK defined in BtaTupleMaker. 
    int get_nTrk() const { return nTrk; }

    //! Number of \f$\Upsilon(4S)\f$ candidates associated with this event. 
    int get_nY() const { return nY; }

    //! Second Fox-Wolfram moment. 
    float get_R2All() const { return R2All; }

    //! Return list of \f$\Upsilon(4S)\f$ candidates in this event. 
    const UpsilonList & get_candidate_list() const { return upsilon_candidates; }

};

#endif
