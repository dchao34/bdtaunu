#ifndef __BDTAUNUMCREADER_H__
#define __BDTAUNUMCREADER_H__

#include "BDtaunuReader.h"
#include "bdtaunu_definitions.h"

#include <map>
#include <string>
#include <vector>

class BDtaunuMcReader : public BDtaunuReader {

  protected:
    const static int min_photon_energy = 0.02;
    const static int max_mc_length = 100;
    const static std::vector<int> ell;
    const static std::vector<int> nu;
    const static std::vector<int> dmeson;
    const static std::vector<int> dstarstar;
    const static std::vector<int> dstrange;

    static std::vector<int> build_ell();
    static std::vector<int> build_nu();
    static std::vector<int> build_dmeson();
    static std::vector<int> build_dstarstar();
    static std::vector<int> build_dstrange();

  private:
    int mcLen;
    int *mcLund; 
    int *mothIdx;
    int *dauIdx, *dauLen;
    float *mcenergy;

    int mc_evttype;

    struct McBMeson {
      int bflavor;
      int mc_idx;
      int bmctype;
      McBMeson() :
        bflavor(kUndefinedBFlavor), 
        mc_idx(-1), bmctype(kUndefinedBMcType) {};
    } McB1, McB2;

    virtual void Initialize();
    virtual void SetBranchAddress();
    virtual void ClearColumnValues();

    void FillMCInformation();
    void FindBMesons();
    int DetermineBMcType(int bmc_idx);
    int DetermineMcEventType();

  public: 
    BDtaunuMcReader();
    BDtaunuMcReader(const char *root_fname);
    BDtaunuMcReader(const char *root_fname, const char *root_trname);
    virtual ~BDtaunuMcReader();

    virtual int next_record();

    int get_mc_evttype() { return mc_evttype; }
};

#endif
