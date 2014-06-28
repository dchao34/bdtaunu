#ifndef __DDSTARRHOFEATUREEXTRACTOR_H__
#define __DDSTARRHOFEATUREEXTRACTOR_H__

#include <string>

#include "YCandFeatureExtractor.h"

class DDstarrhoFeatureExtractor : public YCandFeatureExtractor {

  public:
    DDstarrhoFeatureExtractor();
    ~DDstarrhoFeatureExtractor() {};

    void extract_features();
    bool pass_selection() const;

};

#endif
