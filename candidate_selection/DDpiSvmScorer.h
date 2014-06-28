#ifndef __DDPISVMSCORER_H__
#define __DDPISVMSCORER_H__

#include <vector>

#include "CandidateSvmScorer.h"

class DDpiSvmScorer : public CandidateSvmScorer {

  public:
    DDpiSvmScorer() {};
    DDpiSvmScorer(const char *model_fname, 
                  const char *scale_fname);

    virtual ~DDpiSvmScorer();

};  

#endif
