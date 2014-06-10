#ifndef __YCANDFEATUREEXTRACTORFACTORY_H__
#define __YCANDFEATUREEXTRACTORFACTORY_H__

#include "YCandFeatureExtractor.h"
#include "DDpiFeatureExtractor.h"
#include "bdtaunu_definitions.h"

#include <string>

class YCandFeatureExtractorFactory {
  public:
    static YCandFeatureExtractor* CreateExtractor(
        int cand_type, 
        std::string ml_sample_type) {
      switch (cand_type) {
        case kDDpi:
          return new DDpiFeatureExtractor(ml_sample_type);
      }
      throw "Invalid Y(4S) candidate type.";
    }
};

#endif
