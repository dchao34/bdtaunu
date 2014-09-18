#include <vector>
#include <algorithm>
#include <cassert>

#include "BDtaunuDef.h"
#include "RecoDTypeCatalogue.h"

RecoDTypeCatalogue::DType 
RecoDTypeCatalogue::search_d_catalogue(std::vector<int> lund_list) const {
  std::vector<Alphabet> word;
  for (auto l : lund_list) word.push_back(LundToAlphabet(l));
  std::sort(word.begin(), word.end());
  word.push_back(Alphabet::null);
  return d_catalogue.find(word);
}

RecoDTypeCatalogue::DstarType 
RecoDTypeCatalogue::search_dstar_catalogue(std::vector<int> lund_list) const {
  std::vector<Alphabet> word;
  for (auto l : lund_list) word.push_back(LundToAlphabet(l));
  std::sort(word.begin(), word.end());
  word.push_back(Alphabet::null);
  return dstar_catalogue.find(word);
}

void RecoDTypeCatalogue::RegisterDecays() {

  // D catalogue
  d_catalogue.insert({
      Alphabet::Dc, Alphabet::K, Alphabet::pi, Alphabet::pi, 
      Alphabet::null
    }, DType::Dc_Kpipi);

  d_catalogue.insert({
      Alphabet::Dc, Alphabet::K, Alphabet::pi, Alphabet::pi, Alphabet::pi0,
      Alphabet::null
    }, DType::Dc_Kpipipi0);

  d_catalogue.insert({
      Alphabet::Dc, Alphabet::Ks, Alphabet::K,
      Alphabet::null
    }, DType::Dc_KsK);

  d_catalogue.insert({
      Alphabet::Dc, Alphabet::Ks, Alphabet::pi,
      Alphabet::null
    }, DType::Dc_Kspi);

  d_catalogue.insert({
      Alphabet::Dc, Alphabet::Ks, Alphabet::pi, Alphabet::pi0,
      Alphabet::null
    }, DType::Dc_Kspipi0);

  d_catalogue.insert({
      Alphabet::Dc, Alphabet::Ks, Alphabet::pi, Alphabet::pi, Alphabet::pi,
      Alphabet::null
    }, DType::Dc_Kspipipi);

  d_catalogue.insert({
      Alphabet::Dc, Alphabet::K, Alphabet::K, Alphabet::pi,
      Alphabet::null
    }, DType::Dc_KKpi);

  d_catalogue.insert({
      Alphabet::D0, Alphabet::K, Alphabet::pi,
      Alphabet::null
    }, DType::D0_Kpi);

  d_catalogue.insert({
      Alphabet::D0, Alphabet::K, Alphabet::pi, Alphabet::pi0,
      Alphabet::null
    }, DType::D0_Kpipi0);

  d_catalogue.insert({
      Alphabet::D0, Alphabet::K, Alphabet::pi, Alphabet::pi, Alphabet::pi,
      Alphabet::null
    }, DType::D0_Kpipipi);

  d_catalogue.insert({
      Alphabet::D0, Alphabet::K, Alphabet::pi, Alphabet::pi, Alphabet::pi, Alphabet::pi0,
      Alphabet::null
    }, DType::D0_Kpipipipi0);

  d_catalogue.insert({
      Alphabet::D0, Alphabet::Ks, Alphabet::pi, Alphabet::pi,
      Alphabet::null
    }, DType::D0_Kspipi);

  d_catalogue.insert({
      Alphabet::D0, Alphabet::Ks, Alphabet::pi, Alphabet::pi, Alphabet::pi0,
      Alphabet::null
    }, DType::D0_Kspipipi0);

  d_catalogue.insert({
      Alphabet::D0, Alphabet::Ks, Alphabet::pi0,
      Alphabet::null
    }, DType::D0_Kspi0);

  d_catalogue.insert({
      Alphabet::D0, Alphabet::K, Alphabet::K,
      Alphabet::null
    }, DType::D0_KK);

  // Dstar catalogue
  dstar_catalogue.insert({
      Alphabet::Dstar0, Alphabet::D0, Alphabet::pi0,
      Alphabet::null
    }, DstarType::Dstar0_D0pi0);

  dstar_catalogue.insert({
      Alphabet::Dstar0, Alphabet::D0, Alphabet::gamma,
      Alphabet::null
    }, DstarType::Dstar0_D0gamma);

  dstar_catalogue.insert({
      Alphabet::Dstarc, Alphabet::D0, Alphabet::pi,
      Alphabet::null
    }, DstarType::Dstarc_D0pi);

  dstar_catalogue.insert({
      Alphabet::Dstarc, Alphabet::Dc, Alphabet::pi0,
      Alphabet::null
    }, DstarType::Dstarc_Dcpi0);

  dstar_catalogue.insert({
      Alphabet::Dstarc, Alphabet::Dc, Alphabet::gamma,
      Alphabet::null
    }, DstarType::Dstarc_Dcgamma);

}

RecoDTypeCatalogue::Alphabet RecoDTypeCatalogue::LundToAlphabet(int lund) const {
  switch (abs(lund)) {
    case bdtaunu::DstarcLund:
      return Alphabet::Dstarc;
      break;
    case bdtaunu::Dstar0Lund:
      return Alphabet::Dstar0;
      break;
    case bdtaunu::DcLund:
      return Alphabet::Dc;
      break;
    case bdtaunu::D0Lund:
      return Alphabet::D0;
      break;
    case bdtaunu::KLund:
      return Alphabet::K;
      break;
    case bdtaunu::KSLund:
      return Alphabet::Ks;
      break;
    case bdtaunu::piLund:
      return Alphabet::pi;
      break;
    case bdtaunu::pi0Lund:
      return Alphabet::pi0;
      break;
    case bdtaunu::gammaLund:
      return Alphabet::gamma;
      break;
    default:
      assert(false);
      return Alphabet::null;
  }
}
