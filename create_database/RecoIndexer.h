#ifndef _RECOINDEXER_H_
#define _RECOINDEXER_H_

#include <initializer_list>

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

    int operator()(int lund, int idx) const;

    int total() const { return nY + nB + nD + nC + nh + nl + ngamma; }
    void clear();
    void set(std::initializer_list<int> l);
};

#endif
