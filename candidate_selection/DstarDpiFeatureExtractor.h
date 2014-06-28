#ifndef __DSTARDPIFEATUREEXTRACTOR_H__
#define __DSTARDPIFEATUREEXTRACTOR_H__

#include <string>

#include "YCandFeatureExtractor.h"

class DstarDpiFeatureExtractor : public YCandFeatureExtractor {

  public:
    DstarDpiFeatureExtractor();
    ~DstarDpiFeatureExtractor() {};

    void extract_features();
    bool pass_selection() const;

};

#endif
