#ifndef __DDSTARPIFEATUREEXTRACTOR_H__
#define __DDSTARPIFEATUREEXTRACTOR_H__

#include <string>

#include "YCandFeatureExtractor.h"

class DDstarpiFeatureExtractor : public YCandFeatureExtractor {

  public:
    DDstarpiFeatureExtractor();
    ~DDstarpiFeatureExtractor() {};

    void extract_features();
    bool pass_selection() const;

};

#endif
