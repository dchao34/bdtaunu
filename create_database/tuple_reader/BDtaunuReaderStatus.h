#ifndef __BDTAUNUREADERSTATUS_H_
#define __BDTAUNUREADERSTATUS_H_

namespace bdtaunu {

enum BDtaunuReaderStatus {
  kReadSucceeded = 0,
  kEOF = 1,
  kMaxRecoCandExceeded = 2,
  kMaxMcParticlesExceeded = 3,
};

}

#endif
