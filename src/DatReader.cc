#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <cassert>

#include "DatReader.h"

// default constructor does not initialize the field vector or the
// field_name_index map. this behavior needs to be handled correctly
// in the methods.
DatReader::DatReader() {
}

// open file with name fname and parse its contents by white space. 
DatReader::DatReader(const char *fname) {
  delim = " \n\t\v\f\r";
  Initialize(fname, delim);
}

// open file with name fname and parse its contents by specified delimiter
DatReader::DatReader(const char *fname, const char *delimiter) {
  delim = std::string(delimiter); 
  Initialize(fname, delim);
}

// close file if it is open
DatReader::~DatReader() {
  if (file.is_open()) {
    file.close();
  }
}

// initialize the vector that will store the fields of the data file,
// and also build the index that maps each field name to the location
// in the field vector. 
void DatReader::Initialize(const char *fname, const std::string &delim) {

  // open the file. 
  file.open(fname, std::ifstream::in);

  // check if file is successfully opened 
  if (file.is_open()) {
    std::string title;
    getline(file, title);

    // proceed if not an empty file
    if (file.good()) {

      // parsing algorithm: look for the first non-delim character.
      // then look for the first delim character. between these two
      // characters is a valid field entry, so we store it. repeat
      // until we have scanned the entire line.

      // tracker of the index number into the field vector 
      std::vector<std::string>::size_type idx = 0;
      std::string::size_type first_valid_pos = title.find_first_not_of(delim, 0);

      // loop invariant: found a non-delim character. 
      while (first_valid_pos != std::string::npos) {

        // find the next delim character
        std::string::size_type first_invalid_pos = title.find_first_of(delim, first_valid_pos);

        // make a new entry in the field name index map. the map key
        // is the sub-string between [first_valid_pos, first_invalid_pos).
        field_name_index[title.substr(first_valid_pos, first_invalid_pos - first_valid_pos)] = idx++;

        // find the next non-delim character
        first_valid_pos = title.find_first_not_of(delim, first_invalid_pos);
      }

      // allocate enough slots in the field vector to store all the
      // field entries
      fields = std::vector<std::string>(idx + 1);
    }
  } else {
    std::cout << "file \"" << fname << "\" cannot be opened." << std::endl;
    assert(false);
  }
}

// read the next line in the dat file. do this by overwriting the
// field vector entries as a side effect. return value indicates
// whether we were successful in reading a new line
int DatReader::read_next_line() {

  // get the next line
  std::string next_line;
  getline(file, next_line);

  // check if we are at eof (maybe good() is too general)
  if (file.good()) {

    // same algorithm as in Initialize(), except we are stomping over
    // the field vector entries instead of creating the map keys.
    std::vector<std::string>::iterator fields_it = fields.begin();
    std::string::size_type first_valid_pos = next_line.find_first_not_of(delim, 0);
    while (first_valid_pos != std::string::npos) {
      std::string::size_type first_invalid_pos = next_line.find_first_of(delim, first_valid_pos);

      // stomping over the field vector
      *(fields_it++) = next_line.substr(first_valid_pos, first_invalid_pos - first_valid_pos);

      first_valid_pos = next_line.find_first_not_of(delim, first_invalid_pos);
    }

    // read a new line
    return 1;

  } else {

    // did not read a new line. eof. 
    return 0;
  }
}

// access field vector by field name
std::string DatReader::get_field(const char *field_name) {

  std::map<std::string, std::vector<std::string>::size_type>::iterator it;

  // if field_name doesn't exist in the name index, then exit program
  // and print the valid entries available back to stdout.
  it = field_name_index.find(std::string(field_name));
  if (it == field_name_index.end()) {
    std::cout << "Key \""<< field_name << "\" does not exist." << std::endl;
    std::cout << "Valid keys are: ";
    it = field_name_index.begin();
    while (it != field_name_index.end()) {
      std::cout << it->first << " ";
      ++it;
    }
    std::cout << std::endl;
    assert(false);

  } 

  return fields[it->second];
}
