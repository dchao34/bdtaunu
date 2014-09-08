#ifndef __BDTAUNUMCREADER_H__
#define __BDTAUNUMCREADER_H__

#include "BDtaunuReader.h"
#include "bdtaunu_definitions.h"

#include <map>
#include <string>
#include <vector>

#include <boost/graph/adjacency_list.hpp>

namespace boost {
  enum vertex_mc_index_t { vertex_mc_index };

  BOOST_INSTALL_PROPERTY(vertex, mc_index);
}


//! Reads Monte Carlo ntuples and computes truth information. 
/*! In addition to computing detector response data, this class also
 * computes data related to Monte Carlo truth. */
class BDtaunuMcReader : public BDtaunuReader {

  typedef boost::adjacency_list<
  boost::vecS, boost::vecS, boost::directedS,
  boost::property<boost::vertex_mc_index_t, int,
  boost::property<boost::vertex_lund_id_t, int>>,
  boost::property<boost::edge_index_t, int>
  > McGraph;

  typedef typename boost::graph_traits<McGraph>::vertex_descriptor Vertex;

  McGraph g_mc;
  std::map<int, Vertex> mc_vertex_map;

  void ConstructMcGraph();

  const static double min_photon_energy;
  const static int max_mc_length;

  public:
    McGraph get_mc_graph() const { return g_mc; }

  private:
    const static std::vector<int> ell;
    const static std::vector<int> nu;
    const static std::vector<int> dmeson;
    const static std::vector<int> dstar;
    const static std::vector<int> dstarstar;
    const static std::vector<int> dstrange;
    const static std::vector<int> pion;

    static std::vector<int> build_ell();
    static std::vector<int> build_nu();
    static std::vector<int> build_dmeson();
    static std::vector<int> build_dstar();
    static std::vector<int> build_dstarstar();
    static std::vector<int> build_dstrange();
    static std::vector<int> build_pion();

	protected:
    int mcLen;
    int *mcLund; 
    int *mothIdx;
    int *dauIdx, *dauLen;
    float *mcenergy;

    struct McBMeson {
      int bflavor;
      int mc_idx;
      int b_mctype;
      int tau_mctype;
      double dtau_max_photon_energy;
      McBMeson() :
        bflavor(bdtaunu::kUndefinedBFlavor), 
        mc_idx(-1), 
        b_mctype(bdtaunu::kUndefinedBMcType),
        tau_mctype(bdtaunu::kUndefinedTauMcType), 
        dtau_max_photon_energy(-1) {};
    } McB1, McB2;

  private:
    void FillMCInformation();
    void FindBMesons();
    void DetermineBMcType(McBMeson &mcB);

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

    //! B MC type of first truth B. 
    /*! Returns an int that corresponds to the #BMcType enum in */
    int get_b1_mctype() const { return McB1.b_mctype; }

    //! B MC type of second truth B. 
    /*! Returns an int that corresponds to the #BMcType enum in */
    int get_b2_mctype() const { return McB2.b_mctype; }

    //! tau MC type of first truth B 
    /*! Returns an int corresponding to #TauMcType enum. */
    int get_b1_tau_mctype() const { return McB1.tau_mctype; }

    //! tau MC type of second truth B 
    /*! Returns an int corresponding to #TauMcType enum. */
    int get_b2_tau_mctype() const { return McB2.tau_mctype; }

    //! Energy of the highest energy photon of first truth B. 
    /*! Returns -1 if no photons exist. */
    double get_b1_dtau_max_photon_energy() const { return McB1.dtau_max_photon_energy; }

    //! Energy of the highest energy photon of second truth B. 
    /*! Returns -1 if no photons exist. */
    double get_b2_dtau_max_photon_energy() const { return McB2.dtau_max_photon_energy; }
};

#endif
