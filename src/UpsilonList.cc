#include "UpsilonList.h"
#include "UpsilonCandidate.h"

UpsilonList::UpsilonList() {
  head = NULL;
  iter = NULL;
  tail = NULL;
}

UpsilonList::UpsilonList(const UpsilonList &upslist) {
  copy(upslist);
}

UpsilonList::~UpsilonList() {
  clear();
}

// Delete the linked list.
void UpsilonList::clear() {
  if (head != NULL) {
    node *curr = head;
    while (curr != NULL) {
      head = curr->next;
      delete curr;
      curr = head;
    }
    tail = NULL;
  }
  iter = NULL;
}

// Starting from an empty list, create a new list that is a copy of
// another list. 
void UpsilonList::copy(const UpsilonList &upslist) {
  head = NULL;
  tail = NULL;
  if (upslist.head != NULL) {
    node *other_curr = upslist.head;
    while (other_curr != NULL) {
      add_candidate(other_curr->candidate);
      other_curr = other_curr->next;
    }
  }
  iter = NULL;
}

UpsilonList & UpsilonList::operator=(const UpsilonList &upslist) {
  if (this != &upslist) {
    clear();
    copy(upslist);
  }
  return *this;
}

// Add a new candidate at the end of the list. 
void UpsilonList::add_candidate(const UpsilonCandidate &cand) {
  node *new_node = new node(cand);
  if (head == NULL) {
    head = new_node;
    tail = head;
  } else {
    tail->next = new_node;
    tail = new_node;
  }
}

// Move the iterator to the next candidate. 
int UpsilonList::next_candidate() {
  if (iter == NULL) {
    if (head == NULL) {
      return -1;
    } else {
      iter = head;
      return (iter->candidate).get_event_candidate_index();
    }
  } else if (iter == tail) {
    return -1;
  } else {
    iter = iter->next;
    return (iter->candidate).get_event_candidate_index();
  }
}
