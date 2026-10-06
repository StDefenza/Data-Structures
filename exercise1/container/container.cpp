
namespace lasd {

/* ************************************************************************** */

template <typename Data>
inline bool LinearContainer<Data>::operator==(const LinearContainer<Data>& lc) const noexcept {
  if(size == lc.size) {
    for(ulong index = 0; index < size; ++index) {
      if(operator[](index) != lc[index]) {
        return false;
      }
    }
    return true;
  } else {
    return false;
  }
}

template <typename Data>
inline bool LinearContainer<Data>::operator!=(const LinearContainer<Data>& lc) const noexcept {
  return !(*this == lc);
}

/* ************************************************************************** */

//LinearContainer member functions

template <typename Data>
inline Data& LinearContainer<Data>::Front() const {
  if(size != 0) {
    return operator[](0);
  } else {
    throw std::length_error("Access to an empty linear container.");
  }
}

template <typename Data>
inline Data& LinearContainer<Data>::Back() const {
  if(size != 0) {
    return operator[](size - 1);
  } else {
    throw std::length_error("Access to an empty linear container.");
  }
}

//FoldableContainer member functions

template <typename Data>
void AuxFolderExist(const Data& dat, const void* val, void* exists) noexcept {
  if (dat == *((Data*) val)) {
    *((bool*) exists) = true;
  }
}

template <typename Data>
inline bool FoldableContainer<Data>::Exists(const Data& dat) const noexcept {
  bool exists = false;
  Fold(&AuxFolderExist<Data>, &dat, &exists);
  return exists;
}

//PreOrderMappableContainer member function

template <typename Data>
inline void PreOrderMappableContainer<Data>::Map(MapFunctor fun, void* par) {
  MapPreOrder(fun, par);
}

//PreOrderFoldableContainer member function

template <typename Data>
inline void PreOrderFoldableContainer<Data>::Fold(FoldFunctor fun, const void* par, void* acc) const {
  FoldPreOrder(fun, par, acc);
}

//PostOrderMappableContainer member function

template <typename Data>
inline void PostOrderMappableContainer<Data>::Map(MapFunctor fun, void* par) {
  MapPostOrder(fun, par);
}

//PostOrderFoldableContainer member function

template <typename Data>
inline void PostOrderFoldableContainer<Data>::Fold(FoldFunctor fun, const void* par, void* acc) const {
  FoldPostOrder(fun, par, acc);
}

}
