#ifndef __YCANDFEATUREEXTRACTORFACTORY_H__
#define __YCANDFEATUREEXTRACTORFACTORY_H__

#include "DDpiFeatureExtractor.h"
#include "DDstarpiFeatureExtractor.h"
#include "DstarDpiFeatureExtractor.h"
#include "DstarDstarpiFeatureExtractor.h"
#include "DDrhoFeatureExtractor.h"
#include "DDstarrhoFeatureExtractor.h"
#include "DstarDrhoFeatureExtractor.h"
#include "DstarDstarrhoFeatureExtractor.h"
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
        case kDDstarpi:
          return new DDstarpiFeatureExtractor(ml_sample_type);
        case kDstarDpi:
          return new DstarDpiFeatureExtractor(ml_sample_type);
        case kDstarDstarpi:
          return new DstarDstarpiFeatureExtractor(ml_sample_type);
        case kDDrho:
          return new DDrhoFeatureExtractor(ml_sample_type);
        case kDDstarrho:
          return new DDstarrhoFeatureExtractor(ml_sample_type);
        case kDstarDrho:
          return new DstarDrhoFeatureExtractor(ml_sample_type);
        case kDstarDstarrho:
          return new DstarDstarrhoFeatureExtractor(ml_sample_type);
      }
      throw "Invalid Y(4S) candidate type.";
    }
};

#endif
