
namespace lasd {

/* ************************************************************************** */

//NodeVec Constructor
template<typename Data>
BinaryTreeVec<Data>::NodeVec::NodeVec(Data el, ulong ind, Vector<NodeVec*>& vec) {
  element = el;
  index = ind;
  vecptr = &vec;
}

//Specific member functions
template<typename Data>
Data& BinaryTreeVec<Data>::NodeVec::Element() noexcept {
  return element;
}

template<typename Data>
const Data& BinaryTreeVec<Data>::NodeVec::Element() const noexcept {
  return element;
}

template<typename Data>
bool BinaryTreeVec<Data>::NodeVec::IsLeaf() const noexcept {
  return(!HasLeftChild() && !HasRightChild());
}

template<typename Data>
bool BinaryTreeVec<Data>::NodeVec::HasLeftChild() const noexcept {
  return(2*index+1 < vecptr->Size());
}

template<typename Data>
bool BinaryTreeVec<Data>::NodeVec::HasRightChild() const noexcept {
  return(2*index+2 < vecptr->Size());
}

template<typename Data>
typename BinaryTreeVec<Data>::NodeVec& BinaryTreeVec<Data>::NodeVec::LeftChild() const {
  if(HasLeftChild()) {
    return *(vecptr->operator[](2*index+1));
  }
  else {
    throw std::out_of_range("Out of Range");
  }
}

template<typename Data>
typename BinaryTreeVec<Data>::NodeVec& BinaryTreeVec<Data>::NodeVec::RightChild() const {
  if(HasRightChild()) {
    return *(vecptr->operator[](2*index+2));
  }
  else {
    throw std::out_of_range("Out of Range");
  }
}

//BTVec Constructor from LinearContainer
template<typename Data>
BinaryTreeVec<Data>::BinaryTreeVec(const LinearContainer<Data>& var) {
  size = var.Size();
  vec.Resize(size);
  for(ulong i = 0; i < size; i++) {
    vec[i] = new NodeVec(var[i], i, vec);
  }
}

//BTVec Copy Constructor
template<typename Data>
BinaryTreeVec<Data>::BinaryTreeVec(const BinaryTreeVec& bt) {
  size = bt.Size();
  vec.Resize(size);
  for(ulong i = 0; i < size; i++) {
    vec[i] = new NodeVec(bt.vec[i]->element, i, vec);
  }
}

//BTVec Move Constructor
template<typename Data>
BinaryTreeVec<Data>::BinaryTreeVec(BinaryTreeVec&& bt) noexcept {
  std::swap(size, bt.size);
  std::swap(vec, bt.vec);
  for(ulong i = 0; i < size; i++) {
    vec[i]->vecptr = &vec;
  }
}

//BTVec Destructor
template<typename Data>
BinaryTreeVec<Data>::~BinaryTreeVec() {
  Clear();
}

//BTVec Copy Assignement
template<typename Data>
BinaryTreeVec<Data>& BinaryTreeVec<Data>::operator=(const BinaryTreeVec& bt) {
  BinaryTreeVec<Data>* temp = new BinaryTreeVec<Data>(bt);
  std::swap(*this, *temp);
  delete temp;
  return *this;
}

//BTVec Move Assignement
template<typename Data>
BinaryTreeVec<Data>& BinaryTreeVec<Data>::operator=(BinaryTreeVec&& bt) noexcept {
  std::swap(size, bt.size);
  std::swap(vec, bt.vec);
  for(ulong i = 0; i < size; i++) {
    vec[i]->vecptr = &vec;
  }
  return *this;
}

//BTVec Comparison operators
template<typename Data>
bool BinaryTreeVec<Data>::operator==(const BinaryTreeVec& bt) const noexcept {
  return BinaryTree<Data>::operator==(bt);
}

template<typename Data>
bool BinaryTreeVec<Data>::operator!=(const BinaryTreeVec& bt) const noexcept {
  return BinaryTree<Data>::operator!=(bt);
}

//Specific member functions (inherited from BinaryTree)
template<typename Data>
typename BinaryTreeVec<Data>::NodeVec& BinaryTreeVec<Data>::Root() const {
  if(size != 0) {
    return *(vec[0]);
  }
  else {
    throw std::length_error("Access to empty tree");
  }
}

//Specific member functions (inherited from Container)
template<typename Data>
void BinaryTreeVec<Data>::Clear() {
  for(ulong i = 0; i < size; i++) {
    delete vec[i];
  }
  vec.Clear();
  size = 0;
}

//Specific member functions (inherited from BreadthMappableContainer)
template<typename Data>
void BinaryTreeVec<Data>::MapBreadth(MapFunctor fun, void* par) {
  if(size != 0) {
    for(ulong i = 0; i < size; i++) {
      fun(vec[i]->element, par);
    }
  }
}

//Specific member functions (inherited from BreadthFoldableContainer)
template<typename Data>
void BinaryTreeVec<Data>::FoldBreadth(FoldFunctor fun, const void* par, void* acc) const {
  if(size != 0) {
    for(ulong i = 0; i < size; i++) {
      fun(vec[i]->element, par, acc);
    }
  }
}

/* ************************************************************************** */

}
