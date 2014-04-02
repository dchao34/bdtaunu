#ifndef __UPSILONLIST__
#define __UPSILONLIST__

#include <string>

#include "UpsilonCandidate.h"

class UpsilonList {
  private:

    struct node {
      UpsilonCandidate candidate;
      node *next;

      node(const UpsilonCandidate &cand, node *next = NULL) : 
        candidate(cand), next(next) {}
    };

    node *head, *tail;
    node *iter;

    void clear();
    void copy(const UpsilonList &);

  public:
    UpsilonList();
    UpsilonList(const UpsilonList &);
    ~UpsilonList();

    UpsilonList & operator=(const UpsilonList &);

    void add_candidate(const UpsilonCandidate &);
    int next_candidate();

    const UpsilonCandidate & get_current_candidate() const { return iter->candidate; }
};

#endif
