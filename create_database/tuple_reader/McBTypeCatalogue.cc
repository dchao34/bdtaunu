#include <vector>
#include <algorithm>

#include "McBTypeCatalogue.h"

McBTypeCatalogue::BType 
McBTypeCatalogue::search_catalogue(std::vector<int> lund_list) const {
  std::vector<Alphabet> word;
  bool hasX = false;
  for (auto l : lund_list) {
    Alphabet a = LundToAlphabet(l);
    if (a == Alphabet::I) {
      continue;
    } else if (a == Alphabet::X) {
      hasX = true;
    } else {
      word.push_back(a);
    }
  }

  std::sort(word.begin(), word.end());
  if (hasX) word.push_back(Alphabet::X);
  word.push_back(Alphabet::null);

  return trie.search_word(word);
}

void McBTypeCatalogue::RegisterDecays() {

  // nu_tau branch
  trie.add_word({
      Alphabet::nu_tau, Alphabet::tau, 
      Alphabet::null
    }, BType::SL);

  trie.add_word({
      Alphabet::nu_tau, Alphabet::tau, Alphabet::D,
      Alphabet::null
    }, BType::Dtau);

  trie.add_word({
      Alphabet::nu_tau, Alphabet::tau, Alphabet::Dstar,
      Alphabet::null
    }, BType::Dstartau);

  trie.add_word({
      Alphabet::nu_tau, Alphabet::tau, Alphabet::Dstarstar,
      Alphabet::null
    }, BType::Dstarstar_res);

  trie.add_word({
      Alphabet::nu_tau, Alphabet::tau, Alphabet::X,
      Alphabet::null
    }, BType::SL);

  trie.add_word({
      Alphabet::nu_tau, Alphabet::tau, 
      Alphabet::D, Alphabet::X,
      Alphabet::null
    }, BType::Dstarstar_nonres);

  trie.add_word({
      Alphabet::nu_tau, Alphabet::tau, 
      Alphabet::Dstar, Alphabet::X,
      Alphabet::null
    }, BType::Dstarstar_nonres);

  trie.add_word({
      Alphabet::nu_tau, Alphabet::tau, 
      Alphabet::Dstarstar, Alphabet::X,
      Alphabet::null
    }, BType::Dstarstar_res);

  // nu_ell branch
  trie.add_word({
      Alphabet::nu_ell, Alphabet::ell, 
      Alphabet::null
    }, BType::SL);

  trie.add_word({
      Alphabet::nu_ell, Alphabet::ell, Alphabet::D,
      Alphabet::null
    }, BType::Dl);

  trie.add_word({
      Alphabet::nu_ell, Alphabet::ell, Alphabet::Dstar,
      Alphabet::null
    }, BType::Dstarl);

  trie.add_word({
      Alphabet::nu_ell, Alphabet::ell, Alphabet::Dstarstar,
      Alphabet::null
    }, BType::Dstarstar_res);

  trie.add_word({
      Alphabet::nu_ell, Alphabet::ell, Alphabet::X,
      Alphabet::null
    }, BType::SL);

  trie.add_word({
      Alphabet::nu_ell, Alphabet::ell, 
      Alphabet::D, Alphabet::X,
      Alphabet::null
    }, BType::Dstarstar_nonres);

  trie.add_word({
      Alphabet::nu_ell, Alphabet::ell, 
      Alphabet::Dstar, Alphabet::X,
      Alphabet::null
    }, BType::Dstarstar_nonres);

  trie.add_word({
      Alphabet::nu_ell, Alphabet::ell, 
      Alphabet::Dstarstar, Alphabet::X,
      Alphabet::null
    }, BType::Dstarstar_res);

  // hadron branch
  trie.add_word({
      Alphabet::X,
      Alphabet::null
    }, BType::Had);

  trie.add_word({
      Alphabet::D, Alphabet::X, 
      Alphabet::null
    }, BType::Had);

  trie.add_word({
      Alphabet::Dstar, Alphabet::X, 
      Alphabet::null
    }, BType::Had);

  trie.add_word({
      Alphabet::Dstarstar, Alphabet::X, 
      Alphabet::null
    }, BType::Had);

  trie.add_word({
      Alphabet::D, Alphabet::D, 
      Alphabet::null
    }, BType::Had);

  trie.add_word({
      Alphabet::D, Alphabet::Dstar, 
      Alphabet::null
    }, BType::Had);

  trie.add_word({
      Alphabet::D, Alphabet::Dstarstar, 
      Alphabet::null
    }, BType::Had);

  trie.add_word({
      Alphabet::Dstar, Alphabet::Dstar, 
      Alphabet::null
    }, BType::Had);

  trie.add_word({
      Alphabet::Dstar, Alphabet::Dstarstar, 
      Alphabet::null
    }, BType::Had);

  trie.add_word({
      Alphabet::Dstarstar, Alphabet::Dstarstar, 
      Alphabet::null
    }, BType::Had);

  trie.add_word({
      Alphabet::D, Alphabet::D, Alphabet::X,
      Alphabet::null
    }, BType::Had);

  trie.add_word({
      Alphabet::D, Alphabet::Dstar, Alphabet::X,
      Alphabet::null
    }, BType::Had);

  trie.add_word({
      Alphabet::D, Alphabet::Dstarstar, Alphabet::X,
      Alphabet::null
    }, BType::Had);

  trie.add_word({
      Alphabet::Dstar, Alphabet::Dstar, Alphabet::X,
      Alphabet::null
    }, BType::Had);

  trie.add_word({
      Alphabet::Dstar, Alphabet::Dstarstar, Alphabet::X,
      Alphabet::null
    }, BType::Had);

  trie.add_word({
      Alphabet::Dstarstar, Alphabet::Dstarstar, Alphabet::X,
      Alphabet::null
    }, BType::Had);

}

McBTypeCatalogue::Alphabet McBTypeCatalogue::LundToAlphabet(int lund) const {
  switch (abs(lund)) {
    case 12: // nu_e
    case 14: // nu_mu
      return Alphabet::nu_ell;
      break;
    case 16: // nu_tau
      return Alphabet::nu_tau;
      break;
    case 11: // e
    case 13: // mu
      return Alphabet::ell;
      break;
    case 15: // tau
      return Alphabet::tau;
      break;
    case 411: // D+
    case 421: // D0
      return Alphabet::D;
      break;
    case 413: // D*+
    case 423: // D*0
      return Alphabet::Dstar;
      break;
    case 10411: // D_0*+
    case 10421: // D_0*0
    case 10413: // D_1+
    case 10423: // D_10
    case 415: // D_2*+
    case 425: // D_2*0
    case 20413: // D'_1+
    case 20423: // D'_10
    case 30411: // D(2S)+
    case 30421: // D(2S)0
    case 30413: // D*(2S)+
    case 30423: // D*(2S)0
      return Alphabet::Dstarstar;
      break;
    case 22: 
      return Alphabet::I;
      break;
    default: 
      return Alphabet::X;
      break;
  }
}
