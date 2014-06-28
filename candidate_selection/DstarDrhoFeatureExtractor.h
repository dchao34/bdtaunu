#ifndef __DSTARDRHOFEATUREEXTRACTOR_H__
#define __DSTARDRHOFEATUREEXTRACTOR_H__

#include <string>

#include "YCandFeatureExtractor.h"

class DstarDrhoFeatureExtractor : public YCandFeatureExtractor {

  public:
    DstarDrhoFeatureExtractor();
    ~DstarDrhoFeatureExtractor() {};

    void extract_features();
    bool pass_selection() const;

};

#endif
