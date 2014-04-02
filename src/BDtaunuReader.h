#include <TTree.h>

#include <string>
#include <map>

#include "RootReader.h"
#include "UpsilonList.h"

class BDtaunuReader : public RootReader {

  protected: 
    static std::map<std::string, int> build_lund_map();

    static const int maximum_candidates_allowed;
    static std::map<std::string, int> lundIdMap;

  private: 

    int platform, partition, upperID, lowerID;
    int nTrk, nY;
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
    int *Yd1Idx, *Yd2Idx;
    int *Bd1Idx, *Bd2Idx;
    int *Dd1Idx;
    int *Yd2Lund;
    int *Bd1Lund;
    int *Dd1Lund, *Dd2Lund, *Dd3Lund, *Dd4Lund, *Dd5Lund;
    int *taud1Lund;

    std::string eventId;
    UpsilonList upsilon_candidates;

    virtual void Initialize();
    virtual void SetBranchAddress();
    virtual void ClearColumnValues();

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


  public: 
    BDtaunuReader();
    BDtaunuReader(const char *root_fname);
    BDtaunuReader(const char *root_fname, const char *root_trname);
    virtual ~BDtaunuReader();

    int next_record();

    std::string get_eventId() const { return eventId; }
    int get_nTrk() const { return nTrk; }
    int get_nY() const { return nY; }
    float get_R2All() const { return R2All; }
    const UpsilonList & get_candidate_list() const { return upsilon_candidates; }

    int next_candidate() { return upsilon_candidates.next_candidate(); }
    int get_event_candidate_index() const { return upsilon_candidates.get_current_candidate().get_event_candidate_index(); }
    float get_eextra50() const { return upsilon_candidates.get_current_candidate().get_eextra50(); }
    float get_mmiss_prime2() const { return upsilon_candidates.get_current_candidate().get_mmiss_prime2(); }
};
