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

class YCandFeatureExtractorFactory {
  public:
    static YCandFeatureExtractor* CreateExtractor(int cand_type) {
      switch (cand_type) {
        case kDDpi:
          return new DDpiFeatureExtractor();
        case kDDstarpi:
          return new DDstarpiFeatureExtractor();
        case kDstarDpi:
          return new DstarDpiFeatureExtractor();
        case kDstarDstarpi:
          return new DstarDstarpiFeatureExtractor();
        case kDDrho:
          return new DDrhoFeatureExtractor();
        case kDDstarrho:
          return new DDstarrhoFeatureExtractor();
        case kDstarDrho:
          return new DstarDrhoFeatureExtractor();
        case kDstarDstarrho:
          return new DstarDstarrhoFeatureExtractor();
      }
      throw "Invalid Y(4S) candidate type.";
    }
};

#endif
