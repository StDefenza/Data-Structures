#include <iostream>

namespace lasd {


/* ************************************************************************** */

// ...
template<>
class Hash<int> {

public:
  ulong operator()(const int& dat) const noexcept {
    return (dat * dat);
  }
};

template <>
class Hash<double>{
public:
  ulong operator()(const double& dat) const noexcept{
    long intgpart = floor(dat);
    long fractpart = pow(2,24) * (dat - intgpart);
    return (intgpart * fractpart);
  }
};


template <>
class Hash<std::string>{
public:
  ulong operator()(const std::string& dat) const noexcept{
    ulong hash = 5381;
    for(ulong i = 0; i < dat.length(); ++i){
      hash = (hash << 5) + dat[i];
    }
    return hash;
  }
};

//HT Constructor
template <typename Data>
HashTable<Data>::HashTable() {
  std::default_random_engine gen(std::random_device{}());

  std::uniform_int_distribution<uint> rand1 (1,primo-1);
  std::uniform_int_distribution<uint> rand2 (0,primo-1);
  a = rand1(gen);
  b = rand2(gen);
}

//HT Copy Constructor
template<typename Data>
HashTable<Data>::HashTable(const HashTable& ht){
  size = ht.size;
  tsize = ht.tsize;
  primo = ht.primo;
  a = ht.a;
  b = ht.b;
}

//HT Move Constructor
template<typename Data>
HashTable<Data>::HashTable(HashTable&& ht) noexcept {
  std::swap(size, ht.size);
  std::swap(tsize, ht.tsize);
  std::swap(primo, ht.primo);
  std::swap(a, ht.a);
  std::swap(b, ht.b);
}

//HT Copy Assignement
template<typename Data>
HashTable<Data>& HashTable<Data>::operator=(const HashTable& ht) {
  size = ht.size;
  tsize = ht.tsize;
  primo = ht.primo;
  a = ht.a;
  b = ht.b;
  return *this;
}

//HT Move Assignement
template<typename Data>
HashTable<Data>& HashTable<Data>::operator=(HashTable&& ht) noexcept {
  std::swap(size, ht.size);
  std::swap(tsize, ht.tsize);
  std::swap(primo, ht.primo);
  std::swap(a, ht.a);
  std::swap(b, ht.b);
  return *this;
}

//HT Auxiliary function
template<typename Data>
ulong HashTable<Data>::HashKey(const Data& dato) const noexcept{
  Hash<Data> AshKetchum;
  ulong k = AshKetchum(dato);
  return (((a*k) + b)%primo)%tsize;
}

/* ************************************************************************** */

}
