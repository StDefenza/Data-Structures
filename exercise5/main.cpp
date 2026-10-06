
#include "zlasdtest/test.hpp"

#include "zmytest/test.hpp"

#include "vector/vector.hpp"

#include "hashtable/clsadr/htclsadr.hpp"
#include "hashtable/opnadr/htopnadr.hpp"

/* ************************************************************************** */

#include <iostream>
//
template <typename Data>
void MapPrint(const Data& dat, void* _) {
  std::cout << dat << " ";
}


/* ************************************************************************** */

int main() {
  std::cout << "Lasd Libraries 2022" << std::endl;
  SceltaPrincipale();


  return 0;
}
