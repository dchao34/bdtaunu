#include "DDstarrhoFeatureExtractor.h"
#include "bdtaunu_definitions.h"

#include <string>
#include <sstream>
#include <cassert>

const std::string DDstarrhoFeatureExtractor::candtype_name = "DDstarrho";

DDstarrhoFeatureExtractor::DDstarrhoFeatureExtractor() : 
  YCandFeatureExtractor(13, 9, 9, 0, 4)  {

  Clear();
}

DDstarrhoFeatureExtractor::DDstarrhoFeatureExtractor(std::string &mlsample) :
  YCandFeatureExtractor(13, 9, 9, 0, 4)  {

  Clear();
  mlsample_type = mlsample;
}

std::string DDstarrhoFeatureExtractor::get_sql_query_statement() const {
  return YCandFeatureExtractor::get_sql_query_statement(
            candtype_name, mlsample_type);
}

void DDstarrhoFeatureExtractor::update_features(sqlite3_stmt *stmt) {

  YCandFeatureExtractor::update_features(stmt);

  numeric_features[0] = tag_lp3;
  numeric_features[1] = tag_cosBY;
  numeric_features[2] = tag_cosThetaDl;
  numeric_features[3] = sig_hp3;
  numeric_features[4] = sig_vtxB;
  numeric_features[5] = mmiss_prime2;
  numeric_features[6] = eextra50;
  numeric_features[7] = tag_Dmass;
  numeric_features[8] = sig_deltaM;
  numeric_features[9] = sig_cosThetaDSoft;
  numeric_features[10] = sig_softP3MagCM;
  numeric_features[11] = sig_hmass;
  numeric_features[12] = sig_vtxh;

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
      tagD_indicators[2] = 3;
      break;
    case kDc_Kspipipi:
      // do nothing
      break;
    case kDc_KKpi:
      tagD_indicators[2] = 4;
      break;
    case kD0_Kpi:
      tagD_indicators[3] = 1;
      break;
    case kD0_Kpipi0:
      tagD_indicators[4] = 1;
      break;
    case kD0_Kpipipi:
      tagD_indicators[5] = 1;
      break;
    case kD0_Kpipipipi0:
      tagD_indicators[6] = 1;
      break;
    case kD0_Kspipi:
      tagD_indicators[7] = 1;
      break;
    case kD0_Kspipipi0:
      tagD_indicators[7] = 2;
      break;
    case kD0_Kspi0:
      tagD_indicators[7] = 3;
      break;
    case kD0_KK:
      tagD_indicators[8] = 1;
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
      sigD_indicators[2] = 4;
      break;
    case kD0_Kpi:
      sigD_indicators[3] = 1;
      break;
    case kD0_Kpipi0:
      sigD_indicators[4] = 1;
      break;
    case kD0_Kpipipi:
      sigD_indicators[5] = 1;
      break;
    case kD0_Kpipipipi0:
      sigD_indicators[6] = 1;
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

  switch (sig_Dstartype) {
    case kDstar0_D0pi0:
      sigDstar_indicators[0] = 1;
      break;
    case kDstar0_D0gamma:
      sigDstar_indicators[1] = 1;
      break;
    case kDstarc_D0pi:
      sigDstar_indicators[2] = 1;
      break;
    case kDstarc_Dcpi0:
      sigDstar_indicators[3] = 1;
      break;
    case kDstarc_Dcgamma:
      // do nothing
      break;
  }

  return;
}

bool DDstarrhoFeatureExtractor::pass_selection() const {

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

  // deltaM
  if (sig_Dstartype == kDstar0_D0pi0) {
    if (
        (sig_deltaM < 0.135) ||
        (sig_deltaM > 0.15)
       ) {
      return false;
    }
  }

  if (sig_Dstartype == kDstar0_D0gamma) {
    if (
        (sig_deltaM < 0.13) ||
        (sig_deltaM > 0.155)
       ) {
      return false;
    }
  }

  if (sig_Dstartype == kDstarc_D0pi) {
    if (
        (sig_deltaM < 0.14) ||
        (sig_deltaM > 0.15)
       ) {
      return false;
    }
  }

  if (sig_Dstartype == kDstarc_Dcpi0) {
    if (
        (sig_deltaM < 0.1375) ||
        (sig_deltaM > 0.145)
       ) {
      return false;
    }
  }

  // tag_Dtype
  if (
      (tag_Dtype == kDc_Kspipipi)
     ) {
    return false;
  }

  // sig_Dtype
  if (
      (sig_Dtype == kDc_Kspipipi)
     ) {
    return false;
  }

  // sig_Dstartype
  if (
      (sig_Dstartype == kDstarc_Dcgamma)
     ) {
    return false;
  }


  return true;
}

std::string DDstarrhoFeatureExtractor::get_dat_header() const {
  std::stringstream ss;
  ss << "truth_match" << "|";
  ss << "tag_lp3" << "|";
  ss << "tag_cosBY" << "|";
  ss << "tag_cosThetaDl" << "|";
  ss << "sig_hp3" << "|";
  ss << "sig_vtxB" << "|";
  ss << "mmiss_prime2" << "|";
  ss << "eextra50" << "|";
  ss << "tag_Dmass" << "|";
  ss << "sig_deltaM" << "|";
  ss << "sig_cosThetaDSoft" << "|"; 
  ss << "sig_softP3MagCM" << "|";
  ss << "sig_hmass" << "|";
  ss << "sig_vtxh" << "|";
  ss << "tag_Dtype" << "|";
  ss << "sig_Dtype" << "|";
  ss << "sig_Dstartype";
  return ss.str();
}


std::string DDstarrhoFeatureExtractor::get_dat_line() const {
  std::stringstream ss;
  ss << truth_match << "|";
  ss << tag_lp3 << "|";
  ss << tag_cosBY << "|";
  ss << tag_cosThetaDl << "|";
  ss << sig_hp3 << "|";
  ss << sig_vtxB << "|";
  ss << mmiss_prime2 << "|";
  ss << eextra50 << "|";
  ss << tag_Dmass << "|";
  ss << sig_deltaM << "|";
  ss << sig_cosThetaDSoft << "|"; 
  ss << sig_softP3MagCM << "|";
  ss << sig_hmass << "|";
  ss << sig_vtxh << "|";
  ss << tag_Dtype << "|";
  ss << sig_Dtype << "|";
  ss << sig_Dstartype;
  return ss.str();
}
