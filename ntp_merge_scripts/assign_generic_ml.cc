#include <getopt.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <map>

#include <TFile.h>
#include <TTree.h>

#include "mtrand.h"

using namespace std;

string to_string(int a) {
  stringstream ss;
  ss << a;
  return ss.str();
}

// read old ml assignments into a map
void get_old_assignments(map<string, string> &ml_assignment) {
  ifstream f(__OLD_GENERIC_EVENTID_PATHNAME);
  string line;
  while (getline(f, line)) {
    for (unsigned int i = 0; i < line.length(); i++) {
      if (line[i] == '|') {
        string eventId = line.substr(0, i);
        string sample_type = line.substr(i+1);
        if (ml_assignment.find(eventId) != ml_assignment.end()) {
          cout << eventId << " appears twice in ";
          cout << __OLD_GENERIC_EVENTID_PATHNAME << endl;
          exit(EXIT_FAILURE);
        }
        ml_assignment[eventId] = sample_type;
      }
    }
  }
}

// usage message
void print_usage(char **argv) {
  cout << endl;
  cout << "description: take ntp files and assigns ";
  cout << "each unassigned event to an ml sample. " << endl;
  cout << "usage: " << argv[0] << " [options] ";
  cout << "input_fname output_fname" << endl;
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

  TFile *f = new TFile(input_fname.c_str(), "r");
  TTree *tr = (TTree*) f->Get(trname.c_str());

  int platform, partition, upperID, lowerID;
  tr->SetBranchAddress("platform", &platform);
  tr->SetBranchAddress("partition", &partition);
  tr->SetBranchAddress("upperID", &upperID);
  tr->SetBranchAddress("lowerID", &lowerID);


  map<string, string> ml_assignment;
  get_old_assignments(ml_assignment);

  unsigned s = time(0);
  MTRand mt(s);

  ofstream output(output_fname.c_str());

  int total_events = tr->GetEntries();
  for (int i = 0; i < total_events; i++) {
    tr->GetEntry(i);
    string eventId = to_string(platform) + ":" 
                   + to_string(partition) + ":" 
                   + to_string(upperID) + "/" 
                   + to_string(lowerID);
    string sample_type;

    if (ml_assignment.find(eventId) == ml_assignment.end()) {
      double rand = mt();
      if (rand < 1.0 / 6) {
        sample_type = "explore";
      } else if (rand < 4.0 / 6) {
        sample_type = "train";
      } else if (rand < 5.0 / 6) {
        sample_type = "validate";
      } else {
        sample_type = "test";
      }

      string output_line = eventId + "|" + sample_type;
      output << output_line << endl;
    }
  }
  output.close();
  f->Close();
  delete f;

  return 0;
}
