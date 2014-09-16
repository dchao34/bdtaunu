#ifndef _MCBTYPECATALOGUE_H_
#define _MCBTYPECATALOGUE_H_

#include <vector>

#include "Trie.h"

class McBTypeCatalogue {

  public:
    enum class Alphabet { 
      null = 0, nu_ell, nu_tau, ell, tau, 
      D, Dstar, Dstarstar, X, I,
    };

    enum class BType { 
      null = 0, Dtau, Dstartau, Dl, Dstarl, 
      Dstarstar_res, Dstarstar_nonres, SL, Had, 
    };

    McBTypeCatalogue() { RegisterDecays(); }
    ~McBTypeCatalogue() {};

    BType search_catalogue(std::vector<int>) const;

  private:
    void RegisterDecays();
    Alphabet LundToAlphabet(int lund) const;

    bdtaunu::Trie<Alphabet, BType, Alphabet::null, BType::null> trie;

};

#endif
