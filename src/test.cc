#include <iostream>
#include <string>

#include "UpsilonCandidate.h"
#include "UpsilonList.h"

using namespace std;

int main() {
  /*string id1 = "a";
  string id2 = "b";
  string id3 = "c";
  UpsilonCandidate y1(id1, 1, float(0.1), float(0.2));
  UpsilonCandidate y2(id2, 2, float(0.2), float(0.3));
  UpsilonCandidate y3(id3, 3, float(0.3), float(0.4));
  UpsilonCandidate y4(y1);
  y4 = y2;

  UpsilonList list1;
  list1.add_candidate(y1);
  list1.add_candidate(y2);
  list1.add_candidate(y3);
  list1.add_candidate(y4);

  while (list1.next_candidate() != -1) {
    cout << list1.get_eventId() << ", ";
    cout << list1.get_event_candidate_index() << ", ";
    cout << list1.get_eextra50() << ", ";
    cout << list1.get_mmiss_prime2() << endl;
  }
  cout << endl;

  UpsilonList list2(list1);
  while (list2.next_candidate() != -1) {
    cout << list2.get_eventId() << ", ";
    cout << list2.get_event_candidate_index() << ", ";
    cout << list2.get_eextra50() << ", ";
    cout << list2.get_mmiss_prime2() << endl;
  }
  cout << endl;

  list2 = list1;
  while (list2.next_candidate() != -1) {
    cout << list2.get_eventId() << ", ";
    cout << list2.get_event_candidate_index() << ", ";
    cout << list2.get_eextra50() << ", ";
    cout << list2.get_mmiss_prime2() << endl;
  }*/

  cout << (1 << 1) << endl;
  cout << (1 << 2) << endl;

  return 0;
}
