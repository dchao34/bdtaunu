#ifndef _RECOPARTICLES_H_
#define _RECOPARTICLES_H_

#include "bdtaunu_definitions.h"
#include "RecoGraph.h"

struct RecoB;
struct RecoD;
struct RecoLepton;

struct RecoY {
  RecoY() = default;
  RecoB *tagB = nullptr;
  RecoB *sigB = nullptr;
};

struct RecoB {
  RecoB() = default;
  int flavor;
  RecoD *D = nullptr;
  RecoLepton *Lepton = nullptr;
};

struct RecoD {
  RecoD() = default;
  int D_mode = bdtaunu::kUndefinedDMode;
  int Dstar_mode = bdtaunu::kUndefinedDstarMode;
};

struct RecoLepton {
  int l_block_idx = -1;
  int pi_block_idx = -1;
  int tau_mode = bdtaunu::kUndefinedTauMode;
};

#endif
