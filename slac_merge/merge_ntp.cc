#include <getopt.h>

#include <iostream>
#include <string>

#include <TChain.h>

using namespace std;

// usage message
void print_usage(char **argv) {
  cout << endl;
  cout << "description: merges root files in target directory. " << endl;
  cout << "usage: " << argv[0] << " [options] input_directory output_fname " << endl;
  cout << "  -h --help: print this message." << endl;
  cout << "  -w --wildcard: wildcard pattern for input root files. " 
       << "default: [0-9]*.root" << endl;
  cout << "  -t --trname: tree name in the input root files. " 
       << "default: ntp1" << endl;
  cout << endl;
  exit(EXIT_FAILURE);
}

// performs the merging using root
void merge_root(string &input_dir, string &wildcard, 
                string &trname, string &output_fname) {
  TChain *ch = new TChain(trname.c_str(), "");
  ch->Add((input_dir + "/" + wildcard).c_str());
  ch->SetAutoSave(3000000000);
  ch->Merge(output_fname.c_str());
  delete ch;
}

// user interface
int main(int argc, char **argv) {

  string wildcard = "[0-9]*.root";
  string trname = "ntp1";

  struct option long_options[] = {
    { "help", no_argument, 0, 'h' }, 
    { "wildcard", required_argument, 0, 'w' }, 
    { "trname", required_argument, 0, 't' },
    { 0, 0, 0, 0 }
  };

  int c, option_index;
  while ((c = getopt_long(argc, argv, "hw:t:", long_options, &option_index)) != -1) {
    switch (c) {
      case 'h':
        print_usage(argv);
        break;
      case 'w':
        wildcard = string(optarg);
        break;
      case 't':
        trname = string(optarg);
        break;
    }
  }

  string input_dir = string(argv[optind]);
  string output_fname = string(argv[optind + 1]);

  merge_root(input_dir, wildcard, trname, output_fname);

  return 0;
}
