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
      Dc_Kpipi = 1,          /*!< \f$ D^+\rightarrow K^-\pi^+\pi^- \f$ */
      Dc_Kpipipi0 = 2,       /*!< \f$ D^+\rightarrow K^-\pi^+\pi^-\pi^0 \f$ */
      Dc_KsK = 3,            /*!< \f$ D^+\rightarrow K_s K^+ \f$ */
      Dc_Kspi = 4,           /*!< \f$ D^+\rightarrow K_s\pi^+ \f$ */
      Dc_Kspipi0 = 5,        /*!< \f$ D^+\rightarrow K_s\pi^+\pi^0 \f$ */
      Dc_Kspipipi = 6,       /*!< \f$ D^+\rightarrow K_s\pi^+\pi^-\pi^+ \f$ */
      Dc_KKpi = 7,           /*!< \f$ D^+\rightarrow K^+K^-\pi^+ \f$ */
      D0_Kpi = 8,            /*!< \f$ D^0\rightarrow K^-\pi^+ \f$ */
      D0_Kpipi0 = 9,         /*!< \f$ D^0\rightarrow K^-\pi^+\pi^0 \f$ */
      D0_Kpipipi = 10,       /*!< \f$ D^0\rightarrow K^-\pi^+\pi^+\pi^- \f$ */
      D0_Kpipipipi0 = 11,    /*!< \f$ D^0\rightarrow K^-\pi^+\pi^+\pi^-\pi^0 \f$ */
      D0_Kspipi = 12,        /*!< \f$ D^0\rightarrow K_s\pi^+\pi^- \f$ */
      D0_Kspipipi0 = 13,     /*!< \f$ D^0\rightarrow K_s\pi^+\pi^-\pi^0 \f$ */
      D0_Kspi0 = 14,         /*!< \f$ D^0\rightarrow K_s\pi^0 \f$ */
      D0_KK = 15,            /*!< \f$ D^0\rightarrow K^+K^- \f$ */
      null = -1,             /*!< Undefined */
    };

    enum class DstarType {
      NoDstar = 0,                  /*!< No \f$ D^* \f$ in \f$ B \f$ decay */
      Dstar0_D0pi0 = 1,             /*!< \f$ D^{*0}\rightarrow D^0\pi^0 \f$ */
      Dstar0_D0gamma = 2,           /*!< \f$ D^{*0}\rightarrow D^0\gamma \f$ */
      Dstarc_D0pi = 3,              /*!< \f$ D^{*+}\rightarrow D^0\pi^+ \f$ */
      Dstarc_Dcpi0 = 4,             /*!< \f$ D^{*+}\rightarrow D^+\pi^0 \f$ */
      Dstarc_Dcgamma = 5,           /*!< \f$ D^{*+}\rightarrow D^+\gamma \f$ */
      null = -1,                    /*!< Undefined */
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
