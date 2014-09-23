#include <iostream> 
#include <fstream> 
#include <vector> 
#include <string> 
#include <cassert> 

#include "BDtaunuDef.h"
#include "BDtaunuMcReader.h"
#include "UpsilonCandidate.h"

using namespace std;

int main() {

  ofstream reco_output;
  ofstream mc_output;

  // SigMC tests
  // -----------

  cout << "Signal MC tests: " << endl;
  cout << endl;

  // sp11444r1
  // ---------
  cout << "sp11444r1: " << endl;
  cout << endl;

  // Event 0
  // -------
  BDtaunuMcReader *reader = new BDtaunuMcReader("/Users/dchao/bdtaunu/v4/data/root/signal/aug_12_2014/A/sp11444r1.root");
  reader->next_record();
  vector<UpsilonCandidate> upsilons = reader->get_upsilon_candidates();

  cout << "\tEvent " << reader->get_eventId() << " (alias 0):" << endl;
  cout << endl;
  cout << "\t\tB1McType = " << static_cast<int>(reader->get_b1_mctype()) << endl;
  cout << "\t\tB2McType = " << static_cast<int>(reader->get_b2_mctype()) << endl;
  cout << "\t\tB1TauMcType = " << static_cast<int>(reader->get_b1_tau_mctype()) << endl;
  cout << "\t\tB2TauMcType = " << static_cast<int>(reader->get_b2_tau_mctype()) << endl;
  cout << endl;

  cout << "\t\t# of Y(4S) candidates = " << upsilons.size() << endl;
  cout << endl;
  cout << "\t\tCandidate 0:" << endl;
  cout << "\t\t\ttag D mode:" << static_cast<int>(upsilons[0].get_tag_d_mode()) << endl;
  cout << "\t\t\ttag Dstar mode:" << static_cast<int>(upsilons[0].get_tag_dstar_mode()) << endl;
  cout << "\t\t\tsig D mode:" << static_cast<int>(upsilons[0].get_sig_d_mode()) << endl;
  cout << "\t\t\tsig Dstar mode:" << static_cast<int>(upsilons[0].get_sig_dstar_mode()) << endl;
  cout << "\t\t\tsig tau mode:" << static_cast<int>(upsilons[0].get_sig_tau_mode()) << endl;
  cout << endl;
  cout << "\t\tCandidate 1:" << endl;
  cout << "\t\t\ttag D mode:" << static_cast<int>(upsilons[1].get_tag_d_mode()) << endl;
  cout << "\t\t\ttag Dstar mode:" << static_cast<int>(upsilons[1].get_tag_dstar_mode()) << endl;
  cout << "\t\t\tsig D mode:" << static_cast<int>(upsilons[1].get_sig_d_mode()) << endl;
  cout << "\t\t\tsig Dstar mode:" << static_cast<int>(upsilons[1].get_sig_dstar_mode()) << endl;
  cout << "\t\t\tsig tau mode:" << static_cast<int>(upsilons[1].get_sig_tau_mode()) << endl;
  cout << endl;
  cout << "\t\tCandidate 2:" << endl;
  cout << "\t\t\ttag D mode:" << static_cast<int>(upsilons[2].get_tag_d_mode()) << endl;
  cout << "\t\t\ttag Dstar mode:" << static_cast<int>(upsilons[2].get_tag_dstar_mode()) << endl;
  cout << "\t\t\tsig D mode:" << static_cast<int>(upsilons[2].get_sig_d_mode()) << endl;
  cout << "\t\t\tsig Dstar mode:" << static_cast<int>(upsilons[2].get_sig_dstar_mode()) << endl;
  cout << "\t\t\tsig tau mode:" << static_cast<int>(upsilons[2].get_sig_tau_mode()) << endl;
  cout << endl;
  cout << "\t\tCandidate 3:" << endl;
  cout << "\t\t\ttag D mode:" << static_cast<int>(upsilons[3].get_tag_d_mode()) << endl;
  cout << "\t\t\ttag Dstar mode:" << static_cast<int>(upsilons[3].get_tag_dstar_mode()) << endl;
  cout << "\t\t\tsig D mode:" << static_cast<int>(upsilons[3].get_sig_d_mode()) << endl;
  cout << "\t\t\tsig Dstar mode:" << static_cast<int>(upsilons[3].get_sig_dstar_mode()) << endl;
  cout << "\t\t\tsig tau mode:" << static_cast<int>(upsilons[3].get_sig_tau_mode()) << endl;
  cout << endl;
  cout << "\t\tCandidate 4:" << endl;
  cout << "\t\t\ttag D mode:" << static_cast<int>(upsilons[4].get_tag_d_mode()) << endl;
  cout << "\t\t\ttag Dstar mode:" << static_cast<int>(upsilons[4].get_tag_dstar_mode()) << endl;
  cout << "\t\t\tsig D mode:" << static_cast<int>(upsilons[4].get_sig_d_mode()) << endl;
  cout << "\t\t\tsig Dstar mode:" << static_cast<int>(upsilons[4].get_sig_dstar_mode()) << endl;
  cout << "\t\t\tsig tau mode:" << static_cast<int>(upsilons[4].get_sig_tau_mode()) << endl;
  cout << endl;

  reco_output.open("sp11444r1.0.reco.gv");
  reader->print_reco_graph(reco_output);
  reco_output.close();

  mc_output.open("sp11444r1.0.mc.gv");
  reader->print_mc_graph(mc_output);
  mc_output.close();

  // Event 1
  // -------
  reader->next_record();
  upsilons = reader->get_upsilon_candidates();
  cout << "\tEvent " << reader->get_eventId() << " (alias 1):" << endl;
  cout << endl;
  cout << "\t\tB1McType = " << static_cast<int>(reader->get_b1_mctype()) << endl;
  cout << "\t\tB2McType = " << static_cast<int>(reader->get_b2_mctype()) << endl;
  cout << "\t\tB1TauMcType = " << static_cast<int>(reader->get_b1_tau_mctype()) << endl;
  cout << "\t\tB2TauMcType = " << static_cast<int>(reader->get_b2_tau_mctype()) << endl;
  cout << endl;
  cout << "\t\t# of Y(4S) candidates = " << upsilons.size() << endl;
  cout << endl;
  cout << "\t\tCandidate 0:" << endl;
  cout << "\t\t\ttag D mode:" << static_cast<int>(upsilons[0].get_tag_d_mode()) << endl;
  cout << "\t\t\ttag Dstar mode:" << static_cast<int>(upsilons[0].get_tag_dstar_mode()) << endl;
  cout << "\t\t\tsig D mode:" << static_cast<int>(upsilons[0].get_sig_d_mode()) << endl;
  cout << "\t\t\tsig Dstar mode:" << static_cast<int>(upsilons[0].get_sig_dstar_mode()) << endl;
  cout << "\t\t\tsig tau mode:" << static_cast<int>(upsilons[0].get_sig_tau_mode()) << endl;
  cout << endl;
  cout << "\t\tCandidate 1:" << endl;
  cout << "\t\t\ttag D mode:" << static_cast<int>(upsilons[1].get_tag_d_mode()) << endl;
  cout << "\t\t\ttag Dstar mode:" << static_cast<int>(upsilons[1].get_tag_dstar_mode()) << endl;
  cout << "\t\t\tsig D mode:" << static_cast<int>(upsilons[1].get_sig_d_mode()) << endl;
  cout << "\t\t\tsig Dstar mode:" << static_cast<int>(upsilons[1].get_sig_dstar_mode()) << endl;
  cout << "\t\t\tsig tau mode:" << static_cast<int>(upsilons[1].get_sig_tau_mode()) << endl;
  cout << endl;
  cout << "\t\tCandidate 2:" << endl;
  cout << "\t\t\ttag D mode:" << static_cast<int>(upsilons[2].get_tag_d_mode()) << endl;
  cout << "\t\t\ttag Dstar mode:" << static_cast<int>(upsilons[0].get_tag_dstar_mode()) << endl;
  cout << "\t\t\tsig D mode:" << static_cast<int>(upsilons[2].get_sig_d_mode()) << endl;
  cout << "\t\t\tsig Dstar mode:" << static_cast<int>(upsilons[2].get_sig_dstar_mode()) << endl;
  cout << "\t\t\tsig tau mode:" << static_cast<int>(upsilons[2].get_sig_tau_mode()) << endl;
  cout << endl;
  cout << "\t\tCandidate 3:" << endl;
  cout << "\t\t\ttag D mode:" << static_cast<int>(upsilons[3].get_tag_d_mode()) << endl;
  cout << "\t\t\ttag Dstar mode:" << static_cast<int>(upsilons[3].get_tag_dstar_mode()) << endl;
  cout << "\t\t\tsig D mode:" << static_cast<int>(upsilons[3].get_sig_d_mode()) << endl;
  cout << "\t\t\tsig Dstar mode:" << static_cast<int>(upsilons[3].get_sig_dstar_mode()) << endl;
  cout << "\t\t\tsig tau mode:" << static_cast<int>(upsilons[3].get_sig_tau_mode()) << endl;
  cout << endl;
  cout << "\t\tCandidate 4:" << endl;
  cout << "\t\t\ttag D mode:" << static_cast<int>(upsilons[4].get_tag_d_mode()) << endl;
  cout << "\t\t\ttag Dstar mode:" << static_cast<int>(upsilons[4].get_tag_dstar_mode()) << endl;
  cout << "\t\t\tsig D mode:" << static_cast<int>(upsilons[4].get_sig_d_mode()) << endl;
  cout << "\t\t\tsig Dstar mode:" << static_cast<int>(upsilons[4].get_sig_dstar_mode()) << endl;
  cout << "\t\t\tsig tau mode:" << static_cast<int>(upsilons[4].get_sig_tau_mode()) << endl;
  cout << endl;
  cout << "\t\tCandidate 5:" << endl;
  cout << "\t\t\ttag D mode:" << static_cast<int>(upsilons[5].get_tag_d_mode()) << endl;
  cout << "\t\t\ttag Dstar mode:" << static_cast<int>(upsilons[5].get_tag_dstar_mode()) << endl;
  cout << "\t\t\tsig D mode:" << static_cast<int>(upsilons[5].get_sig_d_mode()) << endl;
  cout << "\t\t\tsig Dstar mode:" << static_cast<int>(upsilons[5].get_sig_dstar_mode()) << endl;
  cout << "\t\t\tsig tau mode:" << static_cast<int>(upsilons[5].get_sig_tau_mode()) << endl;
  cout << endl;

  reco_output.open("sp11444r1.1.reco.gv");
  reader->print_reco_graph(reco_output);
  reco_output.close();

  mc_output.open("sp11444r1.1.mc.gv");
  reader->print_mc_graph(mc_output);
  mc_output.close();

  delete reader;

  // sp11445r1
  // ---------
  cout << "sp11445r1: " << endl;
  cout << endl;

  // Event 0
  // -------
  reader = new BDtaunuMcReader("/Users/dchao/bdtaunu/v4/data/root/signal/aug_12_2014/A/sp11445r1.root");
  reader->next_record();
  upsilons = reader->get_upsilon_candidates();

  cout << "\tEvent " << reader->get_eventId() << " (alias 0):" << endl;
  cout << endl;
  cout << "\t\tB1McType = " << static_cast<int>(reader->get_b1_mctype()) << endl;
  cout << "\t\tB2McType = " << static_cast<int>(reader->get_b2_mctype()) << endl;
  cout << "\t\tB1TauMcType = " << static_cast<int>(reader->get_b1_tau_mctype()) << endl;
  cout << "\t\tB2TauMcType = " << static_cast<int>(reader->get_b2_tau_mctype()) << endl;
  cout << endl;

  cout << "\t\t# of Y(4S) candidates = " << upsilons.size() << endl;
  cout << endl;
  cout << "\t\tCandidate 0:" << endl;
  cout << "\t\t\ttag D mode:" << static_cast<int>(upsilons[0].get_tag_d_mode()) << endl;
  cout << "\t\t\ttag Dstar mode:" << static_cast<int>(upsilons[0].get_tag_dstar_mode()) << endl;
  cout << "\t\t\tsig D mode:" << static_cast<int>(upsilons[0].get_sig_d_mode()) << endl;
  cout << "\t\t\tsig Dstar mode:" << static_cast<int>(upsilons[0].get_sig_dstar_mode()) << endl;
  cout << "\t\t\tsig tau mode:" << static_cast<int>(upsilons[0].get_sig_tau_mode()) << endl;
  cout << endl;
  cout << "\t\tCandidate 1:" << endl;
  cout << "\t\t\ttag D mode:" << static_cast<int>(upsilons[1].get_tag_d_mode()) << endl;
  cout << "\t\t\ttag Dstar mode:" << static_cast<int>(upsilons[1].get_tag_dstar_mode()) << endl;
  cout << "\t\t\tsig D mode:" << static_cast<int>(upsilons[1].get_sig_d_mode()) << endl;
  cout << "\t\t\tsig Dstar mode:" << static_cast<int>(upsilons[1].get_sig_dstar_mode()) << endl;
  cout << "\t\t\tsig tau mode:" << static_cast<int>(upsilons[1].get_sig_tau_mode()) << endl;
  cout << endl;
  cout << "\t\tCandidate 2:" << endl;
  cout << "\t\t\ttag D mode:" << static_cast<int>(upsilons[2].get_tag_d_mode()) << endl;
  cout << "\t\t\ttag Dstar mode:" << static_cast<int>(upsilons[2].get_tag_dstar_mode()) << endl;
  cout << "\t\t\tsig D mode:" << static_cast<int>(upsilons[2].get_sig_d_mode()) << endl;
  cout << "\t\t\tsig Dstar mode:" << static_cast<int>(upsilons[2].get_sig_dstar_mode()) << endl;
  cout << "\t\t\tsig tau mode:" << static_cast<int>(upsilons[2].get_sig_tau_mode()) << endl;
  cout << endl;

  reco_output.open("sp11445r1.0.reco.gv");
  reader->print_reco_graph(reco_output);
  reco_output.close();

  mc_output.open("sp11445r1.0.mc.gv");
  reader->print_mc_graph(mc_output);
  mc_output.close();

  // Event 1
  // -------
  reader->next_record();
  upsilons = reader->get_upsilon_candidates();
  cout << "\tEvent " << reader->get_eventId() << " (alias 1):" << endl;
  cout << endl;
  cout << "\t\tB1McType = " << static_cast<int>(reader->get_b1_mctype()) << endl;
  cout << "\t\tB2McType = " << static_cast<int>(reader->get_b2_mctype()) << endl;
  cout << "\t\tB1TauMcType = " << static_cast<int>(reader->get_b1_tau_mctype()) << endl;
  cout << "\t\tB2TauMcType = " << static_cast<int>(reader->get_b2_tau_mctype()) << endl;
  cout << endl;
  cout << "\t\t# of Y(4S) candidates = " << upsilons.size() << endl;
  cout << endl;
  cout << "\t\tCandidate 0:" << endl;
  cout << "\t\t\ttag D mode:" << static_cast<int>(upsilons[0].get_tag_d_mode()) << endl;
  cout << "\t\t\ttag Dstar mode:" << static_cast<int>(upsilons[0].get_tag_dstar_mode()) << endl;
  cout << "\t\t\tsig D mode:" << static_cast<int>(upsilons[0].get_sig_d_mode()) << endl;
  cout << "\t\t\tsig Dstar mode:" << static_cast<int>(upsilons[0].get_sig_dstar_mode()) << endl;
  cout << "\t\t\tsig tau mode:" << static_cast<int>(upsilons[0].get_sig_tau_mode()) << endl;
  cout << endl;
  cout << "\t\tCandidate 1:" << endl;
  cout << "\t\t\ttag D mode:" << static_cast<int>(upsilons[1].get_tag_d_mode()) << endl;
  cout << "\t\t\ttag Dstar mode:" << static_cast<int>(upsilons[1].get_tag_dstar_mode()) << endl;
  cout << "\t\t\tsig D mode:" << static_cast<int>(upsilons[1].get_sig_d_mode()) << endl;
  cout << "\t\t\tsig Dstar mode:" << static_cast<int>(upsilons[1].get_sig_dstar_mode()) << endl;
  cout << "\t\t\tsig tau mode:" << static_cast<int>(upsilons[1].get_sig_tau_mode()) << endl;
  cout << endl;
  cout << "\t\tCandidate 2:" << endl;
  cout << "\t\t\ttag D mode:" << static_cast<int>(upsilons[2].get_tag_d_mode()) << endl;
  cout << "\t\t\ttag Dstar mode:" << static_cast<int>(upsilons[2].get_tag_dstar_mode()) << endl;
  cout << "\t\t\tsig D mode:" << static_cast<int>(upsilons[2].get_sig_d_mode()) << endl;
  cout << "\t\t\tsig Dstar mode:" << static_cast<int>(upsilons[2].get_sig_dstar_mode()) << endl;
  cout << "\t\t\tsig tau mode:" << static_cast<int>(upsilons[2].get_sig_tau_mode()) << endl;
  cout << endl;
  cout << "\t\tCandidate 3:" << endl;
  cout << "\t\t\ttag D mode:" << static_cast<int>(upsilons[3].get_tag_d_mode()) << endl;
  cout << "\t\t\ttag Dstar mode:" << static_cast<int>(upsilons[3].get_tag_dstar_mode()) << endl;
  cout << "\t\t\tsig D mode:" << static_cast<int>(upsilons[3].get_sig_d_mode()) << endl;
  cout << "\t\t\tsig Dstar mode:" << static_cast<int>(upsilons[3].get_sig_dstar_mode()) << endl;
  cout << "\t\t\tsig tau mode:" << static_cast<int>(upsilons[3].get_sig_tau_mode()) << endl;
  cout << endl;
  cout << "\t\tCandidate 4:" << endl;
  cout << "\t\t\ttag D mode:" << static_cast<int>(upsilons[4].get_tag_d_mode()) << endl;
  cout << "\t\t\ttag Dstar mode:" << static_cast<int>(upsilons[4].get_tag_dstar_mode()) << endl;
  cout << "\t\t\tsig D mode:" << static_cast<int>(upsilons[4].get_sig_d_mode()) << endl;
  cout << "\t\t\tsig Dstar mode:" << static_cast<int>(upsilons[4].get_sig_dstar_mode()) << endl;
  cout << "\t\t\tsig tau mode:" << static_cast<int>(upsilons[4].get_sig_tau_mode()) << endl;
  cout << endl;

  reco_output.open("sp11445r1.1.reco.gv");
  reader->print_reco_graph(reco_output);
  reco_output.close();

  mc_output.open("sp11445r1.1.mc.gv");
  reader->print_mc_graph(mc_output);
  mc_output.close();

  delete reader;

  return 0;
}
