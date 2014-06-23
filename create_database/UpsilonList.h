#ifndef __UPSILONLIST__
#define __UPSILONLIST__

#include <string>

#include "UpsilonCandidate.h"

//! Linked list that stores UpsilonCandidate objects from a single event. 
/*! Currently supports only single pass iteration and back
 * insertion. The list has a pointer that tracks the current candidate
 * available for reading/extraction. */
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

    //! Insert an UpsilonCandidate at the end of the linked list. 
    void add_candidate(const UpsilonCandidate &);

    //! Move to the UpsilonCandidate in the list for reading.
    /*! This simply moves the tracking pointer forward by one. It
     * returns the new candidate's candidate index in the event;
     * return -1 if the end of list is reached. */
    int next_candidate();

    //! Get the current candidate the tracking pointer is pointing to. 
    const UpsilonCandidate & get_current_candidate() const { return iter->candidate; }
};

#endif
