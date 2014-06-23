#include <string>
#include <sstream>

#include "helpers.h"

std::string to_string(int a) {
  std::stringstream ss;
  ss << a;
  return ss.str();
}

double to_double(const std::string &s) {
  double d; 
  std::stringstream ss(s);
  ss >> d;
  return d;
}

int to_int(const std::string &s) {
  int i; 
  std::stringstream ss(s);
  ss >> i;
  return i;
}
