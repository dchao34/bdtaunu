#ifndef __BDTAUNUMCREADER_H__
#define __BDTAUNUMCREADER_H__

#include "BDtaunuReader.h"
#include "bdtaunu_definitions.h"

#include <map>
#include <string>
#include <vector>


//! Reads Monte Carlo ntuples and computes truth information. 
/*! In addition to computing detector response data, this class also
 * computes data related to Monte Carlo truth. */
class BDtaunuMcReader : public BDtaunuReader {

  private:
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

	protected:
    int mcLen;
    int *mcLund; 
    int *mothIdx;
    int *dauIdx, *dauLen;
    float *mcenergy;

    struct McBMeson {
      int bflavor;
      int mc_idx;
      int bmctype;
      McBMeson() :
        bflavor(kUndefinedBFlavor), 
        mc_idx(-1), bmctype(kUndefinedBMcType) {};
    } McB1, McB2;

  private:
    int mc_evttype;

    void FillMCInformation();
    void FindBMesons();
    int DetermineBMcType(int bmc_idx);
    int DetermineMcEventType();

	protected:
    virtual void Initialize();
    virtual void SetBranchAddress();
    virtual void ClearColumnValues();

  public: 

    //! Default construction undefined. 
    BDtaunuMcReader();

    //! Construct with specified root file name. TTree name assumed to be "ntp1".
    BDtaunuMcReader(const char *root_fname);

    //! Construct with specified root file name and TTree name.
    BDtaunuMcReader(const char *root_fname, const char *root_trname);
    virtual ~BDtaunuMcReader();

    //! Read in the next event. 
    /*! Returns an integer that indexes the event number. Returns -1
     * when all events have been read. 
     *
     * Calling this automatically computes all features associated
     * with the event. */
    virtual int next_record();

    //! MC event type. 
    /*! Returns an int that corresponds to the #McEventType enum in
     * bdtaunu_definitions.h */
    int get_mc_evttype() const { return mc_evttype; }
};

#endif