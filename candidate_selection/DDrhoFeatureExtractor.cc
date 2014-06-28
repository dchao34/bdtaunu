#include "DDrhoFeatureExtractor.h"
#include "bdtaunu_definitions.h"

#include <string>

DDrhoFeatureExtractor::DDrhoFeatureExtractor() : 
  YCandFeatureExtractor(11, 10, 9, 0, 0)  {
  Clear();
}

void DDrhoFeatureExtractor::extract_features() {

  numeric_features[0] = tag_lp3;
  numeric_features[1] = tag_cosBY;
  numeric_features[2] = tag_cosThetaDl;
  numeric_features[3] = sig_hp3;
  numeric_features[4] = sig_vtxB;
  numeric_features[5] = mmiss_prime2;
  numeric_features[6] = eextra50;
  numeric_features[7] = tag_Dmass;
  numeric_features[8] = sig_Dmass;
  numeric_features[9] = sig_hmass;
  numeric_features[10] = sig_vtxh;

  switch (tag_Dtype) {
    case kDc_Kpipi:
      tagD_indicators[0] = 1;
      break;
    case kDc_Kpipipi0:
      tagD_indicators[1] = 1; 
      break;
    case kDc_KsK:
      tagD_indicators[2] = 1;
      break;
    case kDc_Kspi:
      tagD_indicators[2] = 2;
      break;
    case kDc_Kspipi0:
      tagD_indicators[3] = 1;
      break;
    case kDc_Kspipipi:
      // do nothing
      break;
    case kDc_KKpi:
      tagD_indicators[4] = 1;
      break;
    case kD0_Kpi:
      tagD_indicators[5] = 1;
      break;
    case kD0_Kpipi0:
      tagD_indicators[6] = 1;
      break;
    case kD0_Kpipipi:
      tagD_indicators[7] = 1;
      break;
    case kD0_Kpipipipi0:
      // do nothing
      break;
    case kD0_Kspipi:
      tagD_indicators[8] = 1;
      break;
    case kD0_Kspipipi0:
      tagD_indicators[8] = 2;
      break;
    case kD0_Kspi0:
      tagD_indicators[8] = 3;
      break;
    case kD0_KK:
      tagD_indicators[9] = 1;
      break;
  }

  switch (sig_Dtype) {
    case kDc_Kpipi:
      sigD_indicators[0] = 1;
      break;
    case kDc_Kpipipi0:
      sigD_indicators[1] = 1; 
      break;
    case kDc_KsK:
      sigD_indicators[2] = 1;
      break;
    case kDc_Kspi:
      sigD_indicators[2] = 2;
      break;
    case kDc_Kspipi0:
      sigD_indicators[2] = 3;
      break;
    case kDc_Kspipipi:
      // do nothing
      break;
    case kDc_KKpi:
      sigD_indicators[3] = 1;
      break;
    case kD0_Kpi:
      sigD_indicators[4] = 1;
      break;
    case kD0_Kpipi0:
      sigD_indicators[5] = 1;
      break;
    case kD0_Kpipipi:
      sigD_indicators[6] = 1;
      break;
    case kD0_Kpipipipi0:
      // do nothing
      break;
    case kD0_Kspipi:
      sigD_indicators[7] = 1;
      break;
    case kD0_Kspipipi0:
      sigD_indicators[7] = 2;
      break;
    case kD0_Kspi0:
      sigD_indicators[7] = 3;
      break;
    case kD0_KK:
      sigD_indicators[8] = 1;
      break;
  }

  return;
}

bool DDrhoFeatureExtractor::pass_selection() const {

  if (!YCandFeatureExtractor::pass_selection()) {
    return false;
  }

  // tag_Dmass
  if (
      (tag_Dmass < 1.84) ||
      (tag_Dmass > 1.9)
     ) {
    return false;
  }

  // sig_Dmass
  if (
        (sig_Dmass < 1.84) ||
        (sig_Dmass > 1.9)
       ) {
      return false;
  }

  // tag_Dtype
  if (
      (sig_Dtype == kDc_Kspipipi) ||
      (tag_Dtype == kD0_Kpipipipi0)
     ) {
    return false;
  }

  // sig_Dtype
  if (
      (sig_Dtype == kDc_Kspipipi) ||
      (sig_Dtype == kD0_Kpipipipi0)
     ) {
    return false;
  }

  return true;
}
