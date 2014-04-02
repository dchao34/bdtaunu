#include <string>
#include <vector>
#include <map>
#include <fstream>

// read a data file line by line and allows access to field
// entries by name. it only keeps track of the current line.
//
// the file is expected to be in the format: 
// line 1: title1<delimiter characters>title2<delimiter characters>...<delimiter characters>titleM
// line 2: field1<delimiter characters>field2<delimiter characters>...<delimiter characters>fieldM
// ...
// line N: field1<delimiter characters>field2<delimiter characters>...<delimiter characters>fieldM
// 
// on any line, sequences formed from members of <delimiter
// characters> delimit the fields. this covers two important cases
// where <delimiter character> has only 1 character (as in a csv
// file), or by white spaces (white space separated files).

class DatReader {

  private:

    // file stream
    std::fstream file;

    // delimiter character set
    std::string delim;

    // fields stores the value entries of the current line
    std::vector<std::string> fields;

    // map between field names and their indices in the fields vector
    std::map<std::string, std::vector<std::string>::size_type> field_name_index;

    void Initialize(const char*, const std::string &);

  public:

    // default constructor has no behavior. 
    DatReader();
    
    // construct with file name, assume whitespace delimited
    DatReader(const char *fname);

    // construct with file name and delimiter character set
    DatReader(const char *fname, const char *delimiter);

    ~DatReader();

    // read in the next line in the file
    int read_next_line();

    // access a field in the current line by name
    std::string get_field(const char*);
};
