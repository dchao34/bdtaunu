#ifndef __DSTARDSTARPIFEATUREEXTRACTOR_H__
#define __DSTARDSTARPIFEATUREEXTRACTOR_H__

#include <string>

#include "YCandFeatureExtractor.h"

class DstarDstarpiFeatureExtractor : public YCandFeatureExtractor {

  public:
    DstarDstarpiFeatureExtractor();
    ~DstarDstarpiFeatureExtractor() {};

    void extract_features();
    bool pass_selection() const;

};

#endif
