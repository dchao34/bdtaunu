#ifndef _MCBTYPECATALOGUE_H_
#define _MCBTYPECATALOGUE_H_

#include <vector>

#include <custom_cpp_utilities/trie.h>

class McBTypeCatalogue {

  public:
    enum class Alphabet { 
      nu_ell, nu_tau, ell, tau, 
      D, Dstar, Dstarstar, X, I, null = -1, 
    };

    enum class BType { 
      Dtau = 1, Dstartau, Dl, Dstarl, 
      Dstarstar_res, Dstarstar_nonres, SL, Had, null = -1,
    };

    McBTypeCatalogue() { RegisterDecays(); }
    ~McBTypeCatalogue() {};

    BType search_catalogue(std::vector<int>) const;

  private:
    void RegisterDecays();
    Alphabet LundToAlphabet(int lund) const;

    custom_cpp_utilities::trie<Alphabet, BType, Alphabet::null, BType::null> catalogue;

};

#endif
