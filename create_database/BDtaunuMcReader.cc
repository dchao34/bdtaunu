#include <map>
#include <string>
#include <cmath>
#include <cassert>

#include "utilities/helpers.h"
#include "bdtaunu_definitions.h"
#include "BDtaunuReader.h"
#include "BDtaunuReaderStatus.h"
#include "BDtaunuMcReader.h"
#include "McGraphManager.h"
#include "McBTypeCatalogue.h"

using namespace boost;

const int BDtaunuMcReader::max_mc_length = 100;

BDtaunuMcReader::BDtaunuMcReader(
  const char *root_fname,
  const char *root_trname) : 
  BDtaunuReader(root_fname, root_trname) {

  AllocateBuffer();
  ClearBuffer();

  mc_graph_manager = McGraphManager(this);

}

BDtaunuMcReader::~BDtaunuMcReader() {
  DeleteBuffer();
}


void BDtaunuMcReader::AllocateBuffer() {

  mcLund = new int[max_mc_length];
  mothIdx = new int[max_mc_length];
  dauIdx = new int[max_mc_length];
  dauLen = new int[max_mc_length];
  mcenergy = new float[max_mc_length];

  tr->SetBranchAddress("mcLen", &mcLen);
  tr->SetBranchAddress("mcLund", mcLund);
  tr->SetBranchAddress("mothIdx", mothIdx);
  tr->SetBranchAddress("dauIdx", dauIdx);
  tr->SetBranchAddress("dauLen", dauLen);
  tr->SetBranchAddress("mcenergy", mcenergy);

}

void BDtaunuMcReader::ClearBuffer() {
  mcLen = -999;
  continuum = false;
  b1_mctype = static_cast<int>(McBTypeCatalogue::BType::null);
  b2_mctype = static_cast<int>(McBTypeCatalogue::BType::null);
}

void BDtaunuMcReader::DeleteBuffer() {
  delete[] mcLund;
  delete[] mothIdx;
  delete[] dauIdx;
  delete[] dauLen;
  delete[] mcenergy;
}

// get the next event
int BDtaunuMcReader::next_record() {

  ClearBuffer();

  // read next event from root ntuple into the buffer
  int reader_status = BDtaunuReader::next_record();

  // proceed only when event is not in an error state
  if (reader_status == bdtaunu::kReadSucceeded) {
    if (!is_max_mc_exceeded()) {
      mc_graph_manager.construct_graph();
      mc_graph_manager.analyze_graph();
      FillMCInformation();
    } else {
      reader_status = bdtaunu::kMaxMcParticlesExceeded;
    }
  }
  
  return reader_status;
}

void BDtaunuMcReader::FillMCInformation() {
  if (mc_graph_manager.get_mcY()) 
    continuum = !(mc_graph_manager.get_mcY()->isBBbar);
  if (mc_graph_manager.get_mcB1()) 
    b1_mctype = mc_graph_manager.get_mcB1()->mc_type;
  if (mc_graph_manager.get_mcB2()) 
    b2_mctype = mc_graph_manager.get_mcB2()->mc_type;
  return;
}
