#ifndef __EVENTFEATUREEXTRACTORFACTORY_H__
#define __EVENTFEATUREEXTRACTORFACTORY_H__

#include <string>

#include "EventFeatureExtractor.h"

class EventFeatureExtractorFactory {
  public:
    static EventFeatureExtractor* CreateExtractor(const char *extr_name) {
      std::string extr_str(extr_name);
      if (extr_str == "sig") {
        return new SignalFeatureExtractor();
      } else if (extr_str == "cont") {
        return new ContinuumFeatureExtractor();
      } else if (extr_str == "sigVsl") {
        return new SigVsSLFeatureExtractor();
      } else if (extr_str == "sigVhad") {
        return new SigVsHadFeatureExtractor();
      } else if (extr_str == "sigVcont") {
        return new SigVsContFeatureExtractor();
      } else if (extr_str == "sigVall") {
        return new SigVsAllFeatureExtractor();
      } else {
        throw "Invalid event feature extractor.";
      }
    }
};

#endif
