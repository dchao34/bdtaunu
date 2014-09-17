#ifndef _BDTAUNU_TRIE_H_
#define _BDTAUNU_TRIE_H_

#include <iostream>
#include <vector>
#include <algorithm>

namespace bdtaunu {

template<typename alphaT, typename valueT,
         alphaT alphaNull, valueT valueNull>
class Trie {

  private:
    struct node {
      alphaT alpha;
      valueT value;
      std::vector<node*> links;

      node() : alpha(alphaT()), value(valueT()) {};
      node(alphaT a, valueT v = valueNull) : alpha(a), value(v) {};
      ~node() { for (auto l : links) delete l; }
    };

    node *root;
    node *CopyNode(const node*);

  public:
    Trie() { root = new node; }
    ~Trie() { delete root; }
    Trie(const Trie &t) { root = CopyNode(t.root); }
    Trie &operator=(const Trie&);

    void add_word(std::vector<alphaT> word, valueT value);
    valueT search_word(std::vector<alphaT> word) const;
};


template<typename alphaT, typename valueT,
         alphaT alphaNull, valueT valueNull>
typename Trie<alphaT, valueT, alphaNull, valueNull>::node*
 Trie<alphaT, valueT, alphaNull, valueNull>::CopyNode(const node *t) {
  node *n = new node(t->alpha, t->value);
  for (auto l : t->links) (n->links).push_back(CopyNode(l));
  return n;
}

template<typename alphaT, typename valueT,
         alphaT alphaNull, valueT valueNull>
Trie<alphaT, valueT, alphaNull, valueNull>&
Trie<alphaT, valueT, alphaNull, valueNull>::operator=(const Trie &target) {
  if (this != &target) {
    delete root;
    root = CopyNode(target.root);
  }
  return *this;
}


template<typename alphaT, typename valueT,
         alphaT alphaNull, valueT valueNull>
void Trie<alphaT, valueT, alphaNull, valueNull>::add_word(
    std::vector<alphaT> word, valueT value) {
  node *p = root;
  for (auto alpha : word) {
    auto e_it = find_if((p->links).begin(), (p->links).end(), 
              [alpha] (const node *n) { return (n->alpha == alpha); });

    if (e_it == (p->links).end()) {
      node *n = new node(alpha);
      if (alpha == alphaNull) n->value = value;
      (p->links).push_back(n);
      p = n;
    } else {
      p = *e_it;
    }
  }
}


template<typename alphaT, typename valueT,
         alphaT alphaNull, valueT valueNull>
valueT Trie<alphaT, valueT, alphaNull, valueNull>::search_word(
    std::vector<alphaT> word) const { 
  node *p = root;
  for (auto alpha : word) {
    auto e_it = find_if((p->links).begin(), (p->links).end(), 
              [alpha] (const node *n) { return (n->alpha == alpha); });
    if (e_it == (p->links.end())) return valueNull; 
    p = *e_it;
  }
  return p->value;
}

}

#endif
