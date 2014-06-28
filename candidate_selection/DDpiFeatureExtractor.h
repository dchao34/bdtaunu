#ifndef __DDPIFEATUREEXTRACTOR_H__
#define __DDPIFEATUREEXTRACTOR_H__

#include <string>

#include "YCandFeatureExtractor.h"

class DDpiFeatureExtractor : public YCandFeatureExtractor {

  public:
    DDpiFeatureExtractor();
    ~DDpiFeatureExtractor() {};

    void extract_features();
    bool pass_selection() const;

};

#endif
