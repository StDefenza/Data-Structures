
namespace lasd {

/* ************************************************************************** */

//HTOA Default constructor
template <typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr() {
  vec.Resize(tsize);
  stato.Resize(tsize);
  for(ulong i = 0; i<tsize; i++){
    stato[i] = '0';
  }
}

//HTOA constructors
template <typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr(const ulong nsize) {
  tsize = nsize;
  vec.Resize(tsize);
  stato.Resize(tsize);
  for(ulong i = 0; i<tsize; i++){
    stato[i] = '0';
  }
}

template <typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr(const LinearContainer<Data>& lc) {
  vec.Resize(tsize);
  stato.Resize(tsize);
  for(ulong i = 0; i<tsize; i++){
    stato[i] = '0';
  }
  DictionaryContainer<Data>::Insert(lc);
}

template <typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr(const ulong nsize, const LinearContainer<Data>& lc) {
  tsize = nsize;
  vec.Resize(tsize);
  stato.Resize(tsize);
  for(ulong i = 0; i<tsize; i++){
    stato[i] = '0';
  }
  DictionaryContainer<Data>::Insert(lc);
}

//Copy constructors
template <typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr(const HashTableOpnAdr& ht): HashTable<Data>(ht) {
  vec = ht.vec;
  stato = ht.stato;
  vec.Resize(ht.tsize);
  stato.Resize(ht.tsize);
  c = ht.c;
}

//Move constructors
template <typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr(HashTableOpnAdr&& ht) noexcept: HashTable<Data>(std::move(ht)) {
  std::swap(vec, ht.vec);
  std::swap(stato, ht.stato);
  std::swap(c, ht.c);
}

//Copy assignment
template <typename Data>
HashTableOpnAdr<Data>& HashTableOpnAdr<Data>::operator=(const HashTableOpnAdr& ht) {
  HashTableOpnAdr<Data>* tmp = new HashTableOpnAdr<Data>(ht);
  std::swap(*tmp, *this);
  delete tmp;
  return *this;
}

//Move assignment
template <typename Data>
HashTableOpnAdr<Data>& HashTableOpnAdr<Data>::operator=(HashTableOpnAdr&& ht) noexcept {
  HashTable<Data>::operator=(std::move(ht));
  std::swap(vec, ht.vec);
  std::swap(stato, ht.stato);
  std::swap(c, ht.c);
  return *this;
}

//Comparison operators
template <typename Data>
bool HashTableOpnAdr<Data>::operator==(const HashTableOpnAdr& ht) const noexcept {
  if(tsize == ht.tsize && size == ht.Size()) {
    if(tsize != 0 && size != 0) {
      for(ulong i=0; i<tsize; ++i) {
        if(vec[i] != ht.vec[i] && stato[i] != ht.stato[i]) {
          return false;
        }
      }
      return true;
    }
    else return true;
  }
  else return false;
}

template <typename Data>
bool HashTableOpnAdr<Data>::operator!=(const HashTableOpnAdr& ht) const noexcept {
  return !(*this == ht);
}

// Specific member functions (inherited from HashTable)
template <typename Data>
void HashTableOpnAdr<Data>::Resize(const ulong nsize) {
  if(nsize == size)
    return;
  HashTableOpnAdr<Data>* newhash = new HashTableOpnAdr<Data>(nsize);
  for(ulong i=0; i < stato.Size(); ++i){
    if(stato[i] == '1'){
      newhash->Insert(vec[i]);
    }
  }
  std::swap(*newhash, *this);
  delete newhash;
}

// Specific member functions (inherited from DictionaryContainer)
template <typename Data>
void HashTableOpnAdr<Data>::Insert(const Data& dato) {
  if(Exists(dato))
    return;
  if(size >= (tsize/2)){
    Resize(FindNearestPrimeNumber(tsize*2));
  }
  ulong i = 0;
  while(i < tsize) {
    ulong j = HashKey(i, dato);
    if(stato[j] == '0' || stato[j] == '2'){
      vec[j] = dato;
      stato[j] = '1';
      size++;
      i++;
      break;
    }
    else if(stato[j] == '1'){
      j = FindEmpty(j);
      vec[j] = dato;
      stato[j] = '1';
      size++;
      break;
    }
  }
}

template <typename Data>
void HashTableOpnAdr<Data>::Insert(Data&& dato) noexcept {
  if(Exists(dato))
    return;
  if(size >= (tsize/2)){
    Resize(FindNearestPrimeNumber(tsize*2));
  }
  ulong i = 0;
  while(i < tsize) {
    ulong j = HashKey(i, dato);
    if(stato[j] == '0' || stato[j] == '2'){
      vec[j] = std::move(dato);
      stato[j] = '1';
      size++;
      i++;
      break;
    }
    else if(stato[j] == '1'){
      j = FindEmpty(j);
      vec[j] = std::move(dato);
      stato[j] = '1';
      size++;
      break;
    }
  }

}

template <typename Data>
void HashTableOpnAdr<Data>::Remove(const Data& dato) {
  ulong i = 0;
  while(i<tsize) {
    if(stato[i] == '1' && vec[i] == dato){
      stato[i] = '2';
      size--;
      break;
    }else i++;
  }
}

template <typename Data>
bool HashTableOpnAdr<Data>::Exists(const Data& dato) const noexcept {
  for(ulong i=0; i < stato.Size(); ++i){
    if(stato[i] == '1' && vec[i] == dato){
      return true;
    }
  }
  return false;
}

template <typename Data>
void HashTableOpnAdr<Data>::Map(MapFunctor fun, void* par) {
  for(ulong i=0; i < tsize; ++i){
    if(stato[i] == '1'){
      fun(vec[i], par);
    }
  }
}

template <typename Data>
void HashTableOpnAdr<Data>::Fold(FoldFunctor fun, const void* par, void* acc) const {
  for(ulong i=0; i < tsize; ++i){
    if(stato[i] == '1'){
      fun(vec[i], par, acc);
    }
  }
}

template <typename Data>
void HashTableOpnAdr<Data>::Clear() {
  for(ulong i = 0; i<tsize; i++){
    stato[i] = '0';
  }
  size=0;
}

template <typename Data>
ulong HashTableOpnAdr<Data>::FindEmpty(ulong i) const noexcept{
  while(i<tsize){
    if(stato[i] == '0' || stato[i] == '2'){
      return i;
    }else if(stato[i] == '1'){
      i = (i+1)%tsize;
    }
  }
  return i;
}

template <typename Data>
ulong HashTableOpnAdr<Data>::HashKey(const ulong& i, const Data& dato) const noexcept {
  return ((HashKey(dato) + (i*c))%tsize);
}

template <typename Data>
ulong HashTableOpnAdr<Data>::FindNearestPrimeNumber(ulong num) const {
  while(!isPrime(num)){
    num++;
  }
  return num;
}

template <typename Data>
bool HashTableOpnAdr<Data>::isPrime(const ulong& num) const {
  bool primo = true;

  if (num == 0 || num == 1) {
    primo = false;
  }

  for (int i = 2; i <= num / 2; ++i) {
    if (num % i == 0) {
      primo = false;
      break;
    }
  }
  return primo;
}

/* ************************************************************************** */

}
