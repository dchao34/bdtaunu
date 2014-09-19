#ifndef _RECOINDEXER_H_
#define _RECOINDEXER_H_

/** @file RecoIndexer.h */

#include <initializer_list>

/** @brief This class assigns a unique index to each reconstructed particle.
 *
 * @detail 
 * # Motivation
 * The need for every reconstructed particle of the event to have a unique
 * index arises primarily in accessessing vertex information in the BGL graph. 
 * However, such an indexing is more convenient to use than the existing 
 * BtaTupleMaker indexing. 
 *
 * # Implementation
 * This class builds a hash function from the reco particle's index in the 
 * BtaTupleMaker block to a unique index. 
 *
 * See RecoIndexer.cc for details.
 */
class RecoIndexer {

  private:
    int nY, nB, nD, nC, nh, nl, ngamma;

  public:
    RecoIndexer();
    RecoIndexer(int _nY, int _nB, int _nD, 
                int _nC, int _nh, int _nl, int _ngamma);
    RecoIndexer(const RecoIndexer &r) = default;
    RecoIndexer &operator=(const RecoIndexer &r) = default;
    ~RecoIndexer() {};

    //! Given the lundId and block index, return the unique reco index.
    int operator()(int lund, int idx) const;

    //! Return total number of reco particles in this event. 
    int total() const { return nY + nB + nD + nC + nh + nl + ngamma; }

    //! Set the total number of each type of reco particle.
    /*! The list order is { nY, nB, nD, nC, nh, nl, ngamma } */
    void set(std::initializer_list<int> l);

    //! Clear cache.
    void clear();
};

#endif
