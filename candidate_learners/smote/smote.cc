#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <cstdlib>
#include <cctype>
#include <iostream>
#include <utility>
#include <algorithm>
#include <cassert>
#include <cmath>

#include "mtrand.h"

using namespace std;

void get_positive_instances(
    char *fname,
    vector<vector<double> > &positive_instances) {

  ifstream f(fname);
  string line;

  while (getline(f, line)) {

    unsigned int i = 0; while (line[i++] != ' ');
    if (atoi(line.substr(0, i).c_str()) == -1) continue;

    vector<double> features;
    while (i < line.size()) {
      while (line[i++] != ':');
      int t = i;
      while (!isspace(line[i++]));
      features.push_back(atof(line.substr(t, i).c_str()));
    }
    positive_instances.push_back(features);
  }

  f.close();
}


double compute_distance(vector<double> &a, vector<double> &b) {
  assert(a.size() == b.size());
  double sq_sum = 0;
  for (unsigned i = 0; i < a.size(); i++) {
    double diff = a[i] - b[i];
    diff *= diff;
    sq_sum += diff;
  }

  return sqrt(sq_sum);
}


struct NNCompare {
  bool operator()(pair<unsigned, double> a,
                  pair<unsigned, double> b){
    return a.second < b.second;
  }
} nnCompare;

void get_nearest_neighbors(
    vector<vector<double> > &samples, 
    vector<vector<unsigned> > &nn, 
    int k) {

  for (unsigned i = 0; i < samples.size(); i++) {

    vector<pair<unsigned, double> > distance;
    for (unsigned j = 0; j < samples.size(); j++) {
      distance.push_back(
          pair<unsigned, double>(
            j, compute_distance(samples[i], samples[j])));
    }

    int cts = 0;
    sort(distance.begin(), distance.end(), nnCompare);
    vector<unsigned> nearest;
    for (unsigned j = 0; j < distance.size(); j++) {

      if (cts == k) {
        break;
      }

      if (distance[j].first == i) {
        continue;
      }

      nearest.push_back(distance[j].first);
      cts += 1;

    }

    nn.push_back(nearest);
  }
}

vector<double> compute_new_instance(
  vector<double> &home, 
  vector<double> &neighbor, 
  double gap) {

  vector<double> new_instance;
  for (unsigned i = 0; i < home.size(); i++) {
    double diff = neighbor[i] - home[i];
    diff *= gap;
    new_instance.push_back(home[i] + diff);
  }

  return new_instance;
}

void get_new_instances(
      vector<vector<double> > &positive_instances, 
      vector<vector<unsigned> > &nearest_neighbors, 
      vector<vector<double> > &new_instances, 
      int k,
      int N) {

  int rand_int;
  MTRand_int32 mt_int;

  double rand_double;
  MTRand mt;

  for (unsigned i = 0; i < positive_instances.size(); i++) {
    int n_new_instances = 0;
    while (n_new_instances < N - 1) {

      rand_int = mt_int() % k;
      unsigned j = nearest_neighbors[i][rand_int];

      rand_double = mt();
      new_instances.push_back(
          compute_new_instance(
            positive_instances[i], 
            positive_instances[j], 
            rand_double));

      n_new_instances += 1;
    }
  }
}

void write_new_instances(
    char *fname, 
    vector<vector<double> > &new_instances) {

  string outname(fname);
  outname += ".new_instances";
  ofstream f(outname.c_str());

  for (unsigned i = 0; i < new_instances.size(); i++) {
    stringstream line;
    line << "1";
    for (unsigned j = 0; j < new_instances[i].size(); j++) {
      line << " " << j + 1 << ":" << new_instances[i][j];
    }
    f << line.str() << endl;
  }
  f.close();
}

int main(int argc, char **argv) {

  if (argc != 4) {
    cout << endl;
    cout << "usage: ./main input_file k N" << endl;
    cout << "  k: number of nearest neighbors. " << endl;
    cout << "  N: N * 100\% oversampling. " << endl;
    cout << endl;
    return 1;
  }

  vector<vector<double> > positive_instances;
  get_positive_instances(argv[1], positive_instances);

  vector<vector<unsigned> > nearest_neighbors;
  get_nearest_neighbors(positive_instances, nearest_neighbors, atoi(argv[2]));

  vector<vector<double> > new_instances;
  get_new_instances(
      positive_instances, 
      nearest_neighbors, 
      new_instances, 
      atoi(argv[2]),
      atoi(argv[3]));

  write_new_instances(argv[1], new_instances);

  return 0;
}
