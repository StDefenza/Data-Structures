
namespace lasd {

/* ************************************************************************** */

template <typename Data>
Vector<Data>::Vector(const ulong newsize) {
  Elements = new Data[newsize] {};
  size = newsize;
}

template <typename Data>
Vector<Data>::Vector(const LinearContainer<Data>& con) {
  size = con.Size();
  Elements = new Data[size];
  for (ulong index = 0; index < size; ++index) {
    Elements[index] = con[index];
  }
}

//Copy constructors
template<typename Data>
Vector<Data>::Vector(const Vector<Data>& vec) {
  Elements = new Data[vec.size];
  std::copy(vec.Elements, vec.Elements + vec.size, Elements);
  size = vec.size;
}

//Move constructor
template<typename Data>
Vector<Data>::Vector(Vector<Data>&& vec) noexcept {
  std::swap(Elements, vec.Elements);
  std::swap(size, vec.size);
}

//Destructor
template<typename Data>
Vector<Data>::~Vector() {
  delete[] Elements;
}

//Copy assignment
template<typename Data>
Vector<Data>& Vector<Data>::operator=(const Vector<Data>& vec) {
  Vector<Data>* tmpvec = new Vector<Data>(vec);
  std::swap(*tmpvec, *this);
  delete tmpvec;
  return *this;
}

//Move assignment
template<typename Data>
Vector<Data>& Vector<Data>::operator=(Vector<Data>&& vec) noexcept {
  std::swap(Elements, vec.Elements);
  std::swap(size, vec.size);
  return *this;
}

//Comparison operators
template<typename Data>
bool Vector<Data>::operator==(const Vector<Data>& vec) const noexcept {
  if (size == vec.size) {
    for (ulong index = 0; index < size; ++index) {
      if (Elements[index] != vec.Elements[index]) {
        return false;
      }
    }
    return true;
  }
  else {
    return false;
  }
}

template<typename Data>
inline bool Vector<Data>::operator!=(const Vector<Data>& vec) const noexcept {
  return !(*this == vec);
}

// Specific member function

template<typename Data>
void Vector<Data>::Resize(const ulong newsize) {
  if (newsize == 0) {
    Clear();
  }
  else if (size != newsize) {
    ulong limit = (size < newsize) ? size : newsize;
    Data* TmpElements = new Data[newsize] {};
    for (ulong index = 0; index < limit; ++index) {
      std::swap(Elements[index], TmpElements[index]);
    }
    std::swap(Elements, TmpElements);
    size = newsize;
    delete[] TmpElements;
  }
}

// Specific member function (inherited from Container)

template<typename Data>
void Vector<Data>::Clear() {
  delete[] Elements;
  Elements = nullptr;
  size = 0;
}

template<typename Data>
Data& Vector<Data>::Front() const {
  if (size != 0){
    return Elements[0];
  }
  else {
    throw std::length_error("Access to an empty vector");
  }
}

template<typename Data>
Data& Vector<Data>::Back() const {
  if (size != 0) {
    return Elements[size - 1];
  }
  else {
    throw std::length_error("Access to empty vector");
  }
}

template <typename Data>
Data& Vector<Data>::operator[](const ulong index) const {
  if(index < size) {
    return Elements[index];
  }
  else {
    throw std::out_of_range("Access at index" + std::to_string(index) + "; vector size " + std::to_string(size) + ".");
  }
}

// Specific member function inherited from MappableContainer

template<typename Data>
inline void Vector<Data>::Map(MapFunctor fun, void* par) {
  MapPreOrder(fun, par);
}

// Specific member function inherited from PreOrderMappableContainer

template<typename Data>
void Vector<Data>::MapPreOrder(MapFunctor fun, void* par) {
  for (ulong index = 0; index < size; ++index) {
    fun(Elements[index], par);
  }
}

// Specific member function inherited from PostOrderMappableContainer

template<typename Data>
void Vector<Data>::MapPostOrder(MapFunctor fun, void* par) {
  ulong index = size;
  while (index > 0) {
    fun(Elements[--index], par);
  }
}

// Specific member function inherited from FoldableContainer

template<typename Data>
inline void Vector<Data>::Fold(FoldFunctor fun, const void* par, void* acc) const {
  FoldPreOrder(fun, par, acc);
}

// Specific member function inherited from PreOrderFoldableContainer

template<typename Data>
void Vector<Data>::FoldPreOrder(FoldFunctor fun, const void* par, void* acc) const {
  for (ulong index = 0; index < size; ++index) {
    fun(Elements[index], par, acc);
  }
}

// Specific member function inherited from PostOrderFoldableContainer

template<typename Data>
void Vector<Data>::FoldPostOrder(FoldFunctor fun, const void* par, void* acc) const {
  ulong index = size;
  while (index > 0) {
    fun(Elements[--index], par, acc);
  }
}

/* ************************************************************************** */

}
