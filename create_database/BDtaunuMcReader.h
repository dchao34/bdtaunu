#ifndef __BDTAUNUMCREADER_H__
#define __BDTAUNUMCREADER_H__

#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "bdtaunu_definitions.h"
#include "BDtaunuReader.h"
#include "McGraphManager.h"

//! Reads Monte Carlo ntuples and computes truth information. 
/*! In addition to computing detector response data, this class also
 * computes data related to Monte Carlo truth. */
class BDtaunuMcReader : public BDtaunuReader {

  friend class McGraphManager;

  public: 

    // Constructors
    BDtaunuMcReader() = delete;
    BDtaunuMcReader(const char *root_fname, const char *root_trname = "ntp1");
    BDtaunuMcReader(const BDtaunuMcReader&) = delete;
    BDtaunuMcReader &operator=(const BDtaunuMcReader&) = delete;
    ~BDtaunuMcReader();

    //! Read in the next event. 
    /*! Returns an integer that indexes the event number. Returns -1
     * when all events have been read. 
     *
     * Calling this automatically computes all features associated
     * with the event. */
    virtual int next_record();

    // Data Accessors
    bool is_continuum() const { return continuum; }
    int get_b1_mctype() const { return b1_mctype; }
    int get_b2_mctype() const { return b2_mctype; }
    int get_b1_tau_mctype() const { return b1_tau_mctype; }
    int get_b2_tau_mctype() const { return b2_tau_mctype; }

    // Printer
    void print_mc_graph(std::ostream &os) const { mc_graph_manager.print(os); }

  private:
    const static int max_mc_length;

	private:
    int mcLen;
    int *mcLund; 
    int *mothIdx;
    int *dauIdx;
    int *dauLen;
    float *mcenergy;

    bool continuum;
    int b1_mctype, b2_mctype;
    int b1_tau_mctype, b2_tau_mctype;

    // Constructor helpers
    void AllocateBuffer();
    void DeleteBuffer();
    void ClearBuffer();

    // Reader status helpers
    bool is_max_mc_exceeded() { return (mcLen > max_mc_length) ? true : false; }

    // Mutator helpers
    void FillMCInformation();

    // MC graph helpers
    McGraphManager mc_graph_manager;

};

#endif
