#include <iostream> 
#include <fstream> 

#include "BDtaunuMcReader.h"

using namespace std;

int main() {

  ofstream reco_output("test_mcreader2_reco_graph.gv");
  ofstream mc_output("test_mcreader2_mc_graph.gv");

  BDtaunuMcReader reader("/Users/dchao/bdtaunu/v4/data/root/signal/aug_12_2014/A/sp11444r1.root");
  reader.next_record();

  cout << reader.get_b1_mctype() << endl;
  cout << reader.get_b2_mctype() << endl;
  cout << reader.get_b1_tau_mctype() << endl;
  cout << reader.get_b2_tau_mctype() << endl;

  reader.print_reco_graph(reco_output);
  reader.print_mc_graph(mc_output);

  return 0;
}
