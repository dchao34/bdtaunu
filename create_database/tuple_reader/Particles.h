#ifndef _PARTICLES_H_
#define _PARTICLES_H_

#include "BDtaunuDef.h"
#include "GraphDef.h"

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
  int flavor = bdtaunu::kUndefinedBFlavor;
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

struct McB;
struct McTau;

struct McY {
  McY() = default;
  bool isBBbar = true;
  McB *B1 = nullptr;
  McB *B2 = nullptr;
};

struct McB {
  McB() = default;
  int flavor = bdtaunu::kUndefinedBFlavor;
  int mc_type = bdtaunu::kUndefinedBMcType;
  McTau *tau = nullptr;
};

struct McTau {
  McTau() = default;
  int mc_type = bdtaunu::kUndefinedTauMcType;
};

#endif
