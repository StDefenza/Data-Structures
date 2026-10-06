#include <iostream>

namespace lasd {

/* ************************************************************************** */

template <typename Data>
void Equal(const Data& dat, const void* hash, void* exists){
  if (((HashTableClsAdr<Data>*) hash) -> Exists(dat) == false){
    *((bool*) exists ) = false;
  }
}

template <typename Data>
void MapResize(const Data& dat, void* hash) {
  ((HashTableClsAdr<Data>*) hash) -> Insert(dat);
}

template <typename Data>
HashTableClsAdr<Data>::HashTableClsAdr() {
  vec.Resize(tsize);
}

//HTCA constructors
template <typename Data>
HashTableClsAdr<Data>::HashTableClsAdr(const ulong nsize) {
  tsize = nsize;
  vec.Resize(tsize);
}

template <typename Data>
HashTableClsAdr<Data>::HashTableClsAdr(const LinearContainer<Data>& lc) {
  vec.Resize(tsize);
  DictionaryContainer<Data>::Insert(lc);
}

template <typename Data>
HashTableClsAdr<Data>::HashTableClsAdr(const ulong nsize, const LinearContainer<Data>& lc) {
  tsize = nsize;
  vec.Resize(tsize);
  DictionaryContainer<Data>::Insert(lc);
}

//Copy constructors
template <typename Data>
HashTableClsAdr<Data>::HashTableClsAdr(const HashTableClsAdr& ht): HashTable<Data>(ht) {
  vec.Resize(ht.tsize);
  for(ulong i=0; i<ht.tsize; ++i){
      vec[i].Map(&MapResize<Data>, &(*this));
  }
}

//Move constructors
template <typename Data>
HashTableClsAdr<Data>::HashTableClsAdr(HashTableClsAdr&& ht) noexcept: HashTable<Data>(std::move(ht)) {
  std::swap(vec, ht.vec);
}

//Copy assignment
template <typename Data>
HashTableClsAdr<Data>& HashTableClsAdr<Data>::operator=(const HashTableClsAdr& ht) {
  HashTableClsAdr<Data>* tmp = new HashTableClsAdr<Data>(ht);
  std::swap(*tmp, *this);
  delete tmp;
  return *this;
}

//Move assignment
template <typename Data>
HashTableClsAdr<Data>& HashTableClsAdr<Data>::operator=(HashTableClsAdr&& ht) noexcept {
  HashTable<Data>::operator=(std::move(ht));
  std::swap(vec, ht.vec);
  return *this;
}

//Comparison operators
template <typename Data>
bool HashTableClsAdr<Data>::operator==(const HashTableClsAdr& ht) const noexcept {
  bool value = true;
  if (tsize == ht.tsize && size == ht.Size()) {
    if(tsize != 0 && size != 0) {
      for(ulong i=0; i<tsize; ++i) {
        vec[i].Fold(&Equal<Data>, &ht, &value);
      }
    }
    else return true;
  }
  else return false;
  return value;
}

template <typename Data>
bool HashTableClsAdr<Data>::operator!=(const HashTableClsAdr& ht) const noexcept {
  return !(*this == ht);
}

// Specific member functions (inherited from HashTable)
template <typename Data>
void HashTableClsAdr<Data>::Resize(const ulong nsize) {
  HashTableClsAdr<Data>* newhash = new HashTableClsAdr<Data>(nsize);
  for(ulong i=0; i<tsize; ++i){
    vec[i].Map(&MapResize<Data>, &(*newhash));
  }
  std::swap(*newhash, *this);
  delete newhash;
}

// Specific member functions (inherited from DictionaryContainer)
template <typename Data>
void HashTableClsAdr<Data>::Insert(const Data& dato) {
  if(Exists(dato))
    return;
  ulong address = HashTable<Data>::HashKey(dato);
  vec[address].Insert(dato);
  size++;
}

template <typename Data>
void HashTableClsAdr<Data>::Insert(Data&& dato) noexcept {
  if(Exists(dato))
    return;
  ulong address = HashTable<Data>::HashKey(std::move(dato));
  vec[address].Insert(std::move(dato));
  size++;
}

template <typename Data>
void HashTableClsAdr<Data>::Remove(const Data& dato) {
  if(!Exists(dato))
    return;
  ulong address = HashTable<Data>::HashKey(dato);
  ulong lsize = vec[address].Size();
  if(lsize == 0)
    return;
  vec[address].Remove(dato);
  size--;
}

template <typename Data>
bool HashTableClsAdr<Data>::Exists(const Data& dato) const noexcept{
  ulong address = HashTable<Data>::HashKey(dato);
  ulong lsize = vec[address].Size();
  if(lsize == 0)
    return false;
  return vec[address].Exists(dato);
}

template <typename Data>
void HashTableClsAdr<Data>::Map(MapFunctor fun, void* par) {
  for(ulong i=0; i < tsize; ++i){
    vec[i].Map(fun, par);
  }
}

template <typename Data>
void HashTableClsAdr<Data>::Fold(FoldFunctor fun, const void* par, void* acc) const {
  for(ulong i=0; i < tsize; ++i){
    vec[i].Fold(fun, par, acc);
  }
}

template <typename Data>
void HashTableClsAdr<Data>::Clear() {
  for(ulong i = 0; i < vec.Size(); ++i){
    vec[i].Clear();
  }
  size = 0;
}

/* ************************************************************************** */

}
