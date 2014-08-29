#ifndef __BDTAUNUREADER_H__
#define __BDTAUNUREADER_H__

#include <TTree.h>

#include <string>
#include <vector>
#include <map>

#include "RootReader.h"
#include "UpsilonCandidate.h"
#include "RecoIndexer.h"

#include <boost/graph/adjacency_list.hpp>

namespace boost {
  enum vertex_reco_index_t { vertex_reco_index };
  enum vertex_block_index_t { vertex_block_index };
  enum vertex_lund_id_t { vertex_lund_id };

  BOOST_INSTALL_PROPERTY(vertex, reco_index);
  BOOST_INSTALL_PROPERTY(vertex, block_index);
  BOOST_INSTALL_PROPERTY(vertex, lund_id);
}

template <typename T> class RecoGraphDfsVisitor;
class RecoGraphBfsVisitor;

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

  typedef boost::adjacency_list<
    boost::vecS, boost::vecS, boost::directedS, 
    boost::property<boost::vertex_reco_index_t, int,
    boost::property<boost::vertex_block_index_t, int,
    boost::property<boost::vertex_lund_id_t, int>>>, 
    boost::property<boost::edge_index_t, int>
  > RecoGraph;

  typedef typename boost::graph_traits<RecoGraph>::vertex_descriptor Vertex;

  struct YDecayProperties;
  template <typename T> friend class RecoGraphDfsVisitor;
  template <typename T> friend RecoGraphDfsVisitor<T> reco_graph_dfs_visitor(T, std::vector<YDecayProperties>&);
  friend class RecoGraphBfsVisitor;
  friend RecoGraphBfsVisitor reco_graph_bfs_visitor(const RecoGraph&, RecoGraph&);

  protected: 
    static std::map<std::string, int> lundIdMap;

    static const int maximum_Y_candidates;
    static const int maximum_B_candidates;
    static const int maximum_D_candidates;
    static const int maximum_C_candidates;
    static const int maximum_h_candidates;
    static const int maximum_l_candidates;
    static const int maximum_gamma_candidates;

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

    int *lTrkIdx, *hTrkIdx;
    int *eSelectorsMap, *muSelectorsMap, *KSelectorsMap, *piSelectorsMap;

    struct YDecayProperties {
      Vertex Y, l, tau_pi, tau_pi0;
      int bflavor;
      int tag_d_mode, sig_d_mode;
      int tag_dstar_mode, sig_dstar_mode;
      int tau_mode;
    };

  protected: 
    int nY, nB, nD, nC, nh, nl, ngamma; 
    int *YLund, *BLund, *DLund, *CLund, *hLund, *lLund, *gammaLund;
    int *Yd1Idx, *Yd2Idx;
    int *Bd1Idx, *Bd2Idx, *Bd3Idx, *Bd4Idx;
    int *Dd1Idx, *Dd2Idx, *Dd3Idx, *Dd4Idx, *Dd5Idx;
    int *Cd1Idx, *Cd2Idx;
    int *hd1Idx, *hd2Idx;
    int *ld1Idx, *ld2Idx, *ld3Idx;
    int *Yd1Lund, *Yd2Lund;
    int *Bd1Lund, *Bd2Lund, *Bd3Lund, *Bd4Lund;
    int *Dd1Lund, *Dd2Lund, *Dd3Lund, *Dd4Lund, *Dd5Lund;
    int *Cd1Lund, *Cd2Lund;
    int *hd1Lund, *hd2Lund;
    int *ld1Lund, *ld2Lund, *ld3Lund;

    std::vector<int*> YdauIdx, YdauLund;
    std::vector<int*> BdauIdx, BdauLund;
    std::vector<int*> DdauIdx, DdauLund;
    std::vector<int*> CdauIdx, CdauLund;
    std::vector<int*> hdauIdx, hdauLund;
    std::vector<int*> ldauIdx, ldauLund;

  private: 
    std::string eventId;
    std::vector<UpsilonCandidate> upsilon_candidates;
    RecoIndexer reco_indexer;
    std::map<int, Vertex> reco_vertex_map;
    RecoGraph g;

    void ConstructRecoGraph();
    void AddCandidatesToGraph(
        int nCand, int *CandLund,
        std::vector<int*> &CandDauIdx,
        std::vector<int*> &CandDauLund);

    void FillUpsilonList();

  protected: 

    virtual void Initialize();
    virtual void SetBranchAddress();
    virtual void ClearColumnValues();

  public: 

    bool IsMaxCandidateExceeded() const;

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
    const std::vector<UpsilonCandidate> &get_candidate_list() const { return upsilon_candidates; }

    RecoGraph get_reco_graph() const { return g; }
    RecoGraph get_reco_subgraph(int reco_index);

};

#endif
