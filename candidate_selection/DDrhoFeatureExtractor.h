#ifndef __DDRHOFEATUREEXTRACTOR_H__
#define __DDRHOFEATUREEXTRACTOR_H__

#include <string>

#include "YCandFeatureExtractor.h"

class DDrhoFeatureExtractor : public YCandFeatureExtractor {

  public:
    DDrhoFeatureExtractor();
    ~DDrhoFeatureExtractor() {};

    void extract_features();
    bool pass_selection() const;

};

#endif
