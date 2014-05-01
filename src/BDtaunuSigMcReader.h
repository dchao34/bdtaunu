#ifndef __BDTAUNUSIGMCREADER_H__
#define __BDTAUNUSIGMCREADER_H__

#include "BDtaunuMcReader.h"
#include "bdtaunu_definitions.h"

#include <map>
#include <string>
#include <vector>
#include <utility>


//! Reads signal Monte Carlo ntuples and computes truth match information.
/*! This class computes whether each \f$\Upsilon(4S)\f$ candidate is truth 
 *  matched to the underlying event. It should be used with signal Monte 
 *  Carlo only; while it is possible to use this with generic MC, its 
 *  behaviour is undefined. */
class BDtaunuSigMcReader : public BDtaunuMcReader {

  private:

    std::vector<int> truth_match;

    virtual void Initialize();
    virtual void SetBranchAddress();
    virtual void ClearColumnValues();
    void FillTruthMatchInfo();

    //! Data and functions needed to implement the truth matcher. 
    int *hd1Lund, *hd2Lund, *hd3Lund;
    int *hd1Idx, *hd2Idx, *hd3Idx;
    int *ld1Lund, *ld2Lund, *ld3Lund;
    int *ld1Idx, *ld2Idx, *ld3Idx;
    int *hMCIdx, *lMCIdx, *gammaMCIdx;

    enum CandBlocks {
      noblock = -1,
      Yblock,
      Bblock,
      Dblock,
      taublock,
      hblock,
      lblock,
      gammablock,
    };
    CandBlocks get_cand_block(int plund);

    std::map<CandBlocks, std::vector<std::pair<int*, int*> > > dau_map;
    std::map<CandBlocks, int*> hit_map;
    void build_dau_map();
    void build_hit_map();

    bool BTruthMatches(std::pair<int, int> &recoB);
    bool IsMcFinalState(std::pair<int, int> &mc_particle);
    bool TruthMatchesTo(std::pair<int, int> &mc_particle, 
                        std::pair<int, int> &reco_particle);
    bool HitTruthMatches(std::pair<int, int> &mc_particle, 
                         std::pair<int, int> &reco_particle);
    void McTargetDaughters(std::pair<int, int> &mc_particle,
                           std::vector<std::pair<int, int> > &mc_dau_targets);
    void RecoTargetDaughters(std::pair<int, int> &reco_particle,
                           std::vector<std::pair<int, int> > &reco_dau_targets);

  public: 

    //! Default construction undefined. 
    BDtaunuSigMcReader();

    //! Construct with specified root file name. TTree name assumed to be "ntp1".
    BDtaunuSigMcReader(const char *root_fname);

    //! Construct with specified root file name and TTree name.
    BDtaunuSigMcReader(const char *root_fname, const char *root_trname);
    virtual ~BDtaunuSigMcReader();

    //! Read in the next event. 
    /*! Returns an integer that indexes the event number. Returns -1
     * when all events have been read. 
     *
     * Calling this automatically computes all features associated
     * with the event. */
    virtual int next_record();

    //! Get the truth match status of each \f$\Upsilon(4S)\f$ candidate.
    /*! Each element of the vector saves either 1 or 0 depending if the 
     *  corresponding candidate is truth matched or not. The index of the 
     *  element in the vector corresponds to the candidate index in the 
     *  event. For example, truth_match[0] is the truth match status of 
     *  the first \f$\Upsilon(4S)\f$ candidate in the event. */
    std::vector<int> get_truth_match() const { return truth_match; }
};

#endif
