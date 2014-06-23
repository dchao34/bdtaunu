#ifndef __ROOTREADER_H__
#define __ROOTREADER_H__

#include <TFile.h>
#include <TTree.h>

//! Abstract base class that opens a TFile and gets a TTree. 
/*! This class is responsible for opening and closing a TFile, and it
 * also owns the pointer to the TTree from which we would like to read
 * from. 
 *
 * It supports single pass iteration of events in the TTree. */
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

    //! Undefined default constructions. 
    RootReader();
    
    //! Constructor with specified root file name and TTree name
    //assumed to be "ntp1". 
    RootReader(const char *root_fname);

    //! Constructor with specified root file name and TTree name. 
    RootReader(const char *root_fname, const char *root_trname);
    virtual ~RootReader();

    //! Read in the next event from the TTree. 
    virtual int next_record();
};

#endif
