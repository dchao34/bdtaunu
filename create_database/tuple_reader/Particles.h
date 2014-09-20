#ifndef _PARTICLES_H_
#define _PARTICLES_H_

#include "BDtaunuDef.h"
#include "GraphDef.h"
#include "RecoDTypeCatalogue.h"
#include "McBTypeCatalogue.h"

/** @file Particles.h 
 * Information of specific types of particles that are computed
 * during graph traversal (see RecoGraphManager.h or McGraphManager.h).
 */

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
  int D_mode = static_cast<int>(RecoDTypeCatalogue::DType::null);
  int Dstar_mode = static_cast<int>(RecoDTypeCatalogue::DstarType::NoDstar);
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
  int mc_type = static_cast<int>(McBTypeCatalogue::BType::null);
  McTau *tau = nullptr;
};

struct McTau {
  McTau() = default;
  int mc_type = bdtaunu::kUndefinedTauMcType;
};

#endif
