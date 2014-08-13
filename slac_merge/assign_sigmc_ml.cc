#include <getopt.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <ctime>

#include <TFile.h>
#include <TTree.h>

using namespace std;

// usage message
void print_usage(char **argv) {
  cout << endl;
  cout << "description: take sigmc ntp files and assigns ";
  cout << "each event to an ml sample. " << endl;
  cout << "usage: " << argv[0] << " [options] ";
  cout << "input_fname output_fname n_events_to_assign" << endl;
  cout << "  -h --help: print this message." << endl;
  cout << "  -t --trname: tree name in the input root files. " 
       << "default: ntp1" << endl;
  cout << endl;
  exit(EXIT_FAILURE);
}

// user interface
int main(int argc, char **argv) {

  string trname = "ntp1";
  struct option long_options[] = {
    { "help", no_argument, 0, 'h' }, 
    { "trname", required_argument, 0, 't' },
    { 0, 0, 0, 0 }
  };

  int c, option_index;
  while ((c = getopt_long(argc, argv, "ht:", long_options, &option_index)) != -1) {
    switch (c) {
      case 'h':
        print_usage(argv);
        break;
      case 't':
        trname = string(optarg);
        break;
    }
  }

  string input_fname = string(argv[optind]);
  string output_fname = string(argv[optind + 1]);
  int n_events_to_assign = atoi(argv[optind + 2]);

  TFile *f = new TFile(input_fname.c_str(), "r");
  TTree *tr = (TTree*) f->Get(trname.c_str());

  int platform, partition, upperID, lowerID;
  tr->SetBranchAddress("platform", &platform);
  tr->SetBranchAddress("partition", &partition);
  tr->SetBranchAddress("upperID", &upperID);
  tr->SetBranchAddress("lowerID", &lowerID);

  ofstream output(output_fname.c_str());

  int total_events = tr->GetEntries();
  for (int i = 0; i < total_events; i++) {
    tr->GetEntry(i);
    string eventId = to_string(platform) + ":" 
                   + to_string(partition) + ":" 
                   + to_string(upperID) + "/" 
                   + to_string(lowerID);

    string sample_type;
    if (i < 0.6 * n_events_to_assign) {
      sample_type = "train";
    } else if (i < 0.8 * n_events_to_assign){
      sample_type = "validate";
    } else if (i < n_events_to_assign){
      sample_type = "test";
    } else {
      sample_type = "unassigned";
    }

    string output_line = eventId + "|" + sample_type;
    output << output_line << endl;
  }

  output.close();
  f->Close();
  delete f;

  return 0;
}
