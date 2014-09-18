#ifndef _RECODTYPECATALOGUE_H_
#define _RECODTYPECATALOGUE_H_

#include <vector>

#include <custom_cpp_utilities/trie.h>

class RecoDTypeCatalogue {

  public:
    enum class Alphabet { 
      Dstarc, Dstar0, Dc, D0, K, Ks, pi, pi0, gamma, null = -1,
    };

    enum class DType { 
      Dc_Kpipi = 1,
      Dc_Kpipipi0,
      Dc_KsK,
      Dc_Kspi,
      Dc_Kspipi0,
      Dc_Kspipipi,
      Dc_KKpi,
      D0_Kpi,
      D0_Kpipi0,
      D0_Kpipipi,
      D0_Kpipipipi0,
      D0_Kspipi,
      D0_Kspipipi0,
      D0_Kspi0,
      D0_KK,
      null = -1,
    };

    enum class DstarType {
      NoDstar = 0,
      Dstar0_D0pi0,
      Dstar0_D0gamma,
      Dstarc_D0pi,
      Dstarc_Dcpi0,
      Dstarc_Dcgamma,
      null = -1,
    };

    RecoDTypeCatalogue() { RegisterDecays(); }
    ~RecoDTypeCatalogue() {};

    DType search_d_catalogue(std::vector<int>) const;
    DstarType search_dstar_catalogue(std::vector<int>) const;

  private:
    void RegisterDecays();
    Alphabet LundToAlphabet(int lund) const;

    custom_cpp_utilities::trie<Alphabet, DType, Alphabet::null, DType::null> d_catalogue;
    custom_cpp_utilities::trie<Alphabet, DstarType, Alphabet::null, DstarType::null> dstar_catalogue;

};

#endif
