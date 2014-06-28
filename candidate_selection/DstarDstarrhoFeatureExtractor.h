#ifndef __DSTARDSTARRHOFEATUREEXTRACTOR_H__
#define __DSTARDSTARRHOFEATUREEXTRACTOR_H__

#include <string>

#include "YCandFeatureExtractor.h"

class DstarDstarrhoFeatureExtractor : public YCandFeatureExtractor {

  public:
    DstarDstarrhoFeatureExtractor();
    ~DstarDstarrhoFeatureExtractor() {};

    void extract_features();
    bool pass_selection() const;

};

#endif
