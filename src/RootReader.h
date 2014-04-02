#include <TFile.h>
#include <TTree.h>

class RootReader {

  private:
    TFile *tfile;

  protected: 
    TTree *tr;

  private: 
    int record_index;
    int total_records;

    void PrepareTreeFile(const char *root_fname, const char *root_trname);
    virtual void SetBranchAddress() = 0;

  public:
    RootReader();
    RootReader(const char *root_fname);
    RootReader(const char *root_fname, const char *root_trname);
    virtual ~RootReader();

    virtual int next_record();
};
