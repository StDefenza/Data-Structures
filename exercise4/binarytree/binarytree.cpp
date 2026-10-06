#include "../iterator/iterator.hpp"

#include "../queue/queue.hpp"

#include "../stack/stack.hpp"

#include <iostream>

namespace lasd {

/* ************************************************************************** */

// Node's Comparison Operators
template <typename Data>
bool BinaryTree<Data>::Node::operator==(const Node& var) const noexcept {
  if(this!=nullptr && &var!=nullptr) {
    if(this->IsLeaf() && var.IsLeaf()) {
      return (this->Element() == var.Element());
    }
    else if(this->HasLeftChild() && var.HasLeftChild()) {
      return (this->Element() == var.Element() && this->LeftChild() == var.LeftChild());
    }
    else if(this->HasRightChild() && var.HasRightChild()) {
      return (this->Element() == var.Element() && this->RightChild() == var.RightChild());
    }
    else if(this->HasLeftChild() && var.HasLeftChild() && this->HasRightChild() && var.HasRightChild()) {
      return (this->Element() == var.Element() && this->LeftChild() == var.LeftChild() && this->RightChild() == var.RightChild());
    }
    else return false;
  }
  else if(this==nullptr && &var==nullptr) {
    return true;
  }
  else return false;
}

template <typename Data>
bool BinaryTree<Data>::Node::operator!=(const Node& var) const noexcept {
  return !((*this) == var);
}

// BT's Comparison Operators
template <typename Data>
bool BinaryTree<Data>::operator==(const BinaryTree& bt) const noexcept {
  if(size == bt.Size()) {
    if(size != 0) {
      return (this->Root() == bt.Root());
    }
    else return true;
  }
  else return false;
}

template <typename Data>
bool BinaryTree<Data>::operator!=(const BinaryTree& bt) const noexcept {
  return !((*this) == bt);
}

// BT Specific member functions (inherited from MappableContainer)
template <typename Data>
void BinaryTree<Data>::Map(MapFunctor fun, void* par) {
  if(size != 0) {
    AuxMapPreOrder(fun, par, Root());
  }
}

// BT Specific member functions (inherited from FoldableContainer)
template <typename Data>
void BinaryTree<Data>::Fold(FoldFunctor fun, const void* par, void* acc) const {
  if(size != 0) {
    AuxFoldPreOrder(fun, par, acc, Root());
  }
}

// BT Specific member functions (inherited from PreOrderMappableContainer)
template <typename Data>
void BinaryTree<Data>::MapPreOrder(MapFunctor fun, void* par) {
  if(size != 0) {
    AuxMapPreOrder(fun, par, Root());
  }
}

// BT Specific member functions (inherited from PreOrderFoldableContainer)
template <typename Data>
void BinaryTree<Data>::FoldPreOrder(FoldFunctor fun, const void* par, void* acc) const {
  if(size != 0) {
    AuxFoldPreOrder(fun, par, acc, Root());
  }
}

// BT Specific member functions (inherited from PostOrderMappableContainer)
template <typename Data>
void BinaryTree<Data>::MapPostOrder(MapFunctor fun, void* par) {
  if(size != 0){
    AuxMapPostOrder(fun, par, Root());
  }
}

// BT Specific member functions (inherited from PostOrderFoldableContainer)
template <typename Data>
void BinaryTree<Data>::FoldPostOrder(FoldFunctor fun, const void* par, void* acc) const{
  if(size != 0) {
    AuxFoldPostOrder(fun, par, acc, Root());
  }
}

// BT Specific member functions (inherited from InOrderMappableContainer)
template <typename Data>
void BinaryTree<Data>::MapInOrder(MapFunctor fun, void* par) {
  if(size != 0){
    AuxMapInOrder(fun, par, Root());
  }
}

// BT Specific member functions (inherited from InOrderFoldableContainer)
template <typename Data>
void BinaryTree<Data>::FoldInOrder(FoldFunctor fun, const void* par, void* acc) const {
  if(size != 0) {
    AuxFoldInOrder(fun, par, acc, Root());
  }
}

// BT Specific member functions (inherited from BreadthMappableContainer)
template <typename Data>
void BinaryTree<Data>::MapBreadth(MapFunctor fun, void* par) {
  if(size != 0) {
    lasd::QueueLst<Node*> que;
    Node* current = &Root();
    que.Enqueue(current);
    while(!que.Empty()) {
      current = que.HeadNDequeue();
      fun(current->Element(), par);

      if(current->HasLeftChild()) {
        que.Enqueue(&current->LeftChild());
      }
      if(current->HasRightChild()) {
        que.Enqueue(&current->RightChild());
      }
    }
  }
  else return;
}

// BT Specific member functions (inherited from BreadthFoldableContainer)
template <typename Data>
void BinaryTree<Data>::FoldBreadth(FoldFunctor fun, const void* par, void* acc) const {
  if(size != 0) {
    lasd::QueueLst<Node*> que;
    Node* current = &Root();
    que.Enqueue(current);
    while(!que.Empty()) {
      current = que.HeadNDequeue();
      fun(current->Element(), par, acc);

      if(current->HasLeftChild()) {
        que.Enqueue(&current->LeftChild());
      }
      if(current->HasRightChild()) {
        que.Enqueue(&current->RightChild());
      }
    }
  }
  else return;
}

// BTPreOrderIterator Specific Constructor
template <typename Data>
BTPreOrderIterator<Data>::BTPreOrderIterator(const BinaryTree<Data>& bt) {
  if(bt.Size() != 0) {
    current = &bt.Root();
    reset = &bt.Root();
  }
}

// BTPreOrderIterator Copy Constructor
template <typename Data>
BTPreOrderIterator<Data>::BTPreOrderIterator(const BTPreOrderIterator<Data>& bt) {
  current = bt.current;
  stk = bt.stk;
  reset = bt.reset;
}

// BTPreOrderIterator Move Constructor
template <typename Data>
BTPreOrderIterator<Data>::BTPreOrderIterator(BTPreOrderIterator<Data>&& bt) noexcept {
  std::swap(current, bt.current);
  std::swap(stk, bt.stk);
  std::swap(reset, bt.reset);
}

// BTPreOrderIterator Copy Assignement
template <typename Data>
BTPreOrderIterator<Data>& BTPreOrderIterator<Data>::operator=(const BTPreOrderIterator<Data>& bt) {
  BTPreOrderIterator<Data>* temp = new BTPreOrderIterator<Data> (bt);
  std::swap(*this, *temp);
  delete temp;
  return *this;
}

// BTPreOrderIterator Move Assignement
template <typename Data>
BTPreOrderIterator<Data>& BTPreOrderIterator<Data>::operator=(BTPreOrderIterator<Data>&& bt) noexcept {
  std::swap(current, bt.current);
  std::swap(stk, bt.stk);
  std::swap(reset, bt.reset);
  return *this;
}

// BTPreOrderIterator Comparison operators
template <typename Data>
bool BTPreOrderIterator<Data>::operator==(const BTPreOrderIterator<Data>& bt) const noexcept {
  if(current == bt.current && stk == bt.stk && reset == bt.reset) {
    return true;
  } else return false;
}

template <typename Data>
bool BTPreOrderIterator<Data>::operator!=(const BTPreOrderIterator<Data>& bt) const noexcept {
  return !((*this) == bt);
}

// BTPreOrderIterator Specific member functions (inherited from Iterator)
template <typename Data>
Data& BTPreOrderIterator<Data>::operator*() const {
  if(Terminated()){
    throw std::out_of_range("out_of_range");
  }
  else return current->Element();
}

template <typename Data>
bool BTPreOrderIterator<Data>::Terminated() const noexcept {
  return(current == nullptr);
}

// BTPreOrderIterator Specific member functions (inherited from ForwardIterator)
template <typename Data>
ForwardIterator<Data>& BTPreOrderIterator<Data>::operator++() {
  if(Terminated()) {
    throw std::out_of_range("out_of_range");
  }
  if(current->HasRightChild()) {
    stk.Push(&current->RightChild());
  }
  if(current->HasLeftChild()) {
    stk.Push(&current->LeftChild());
  }

  if(stk.Empty()) {
    current = nullptr;
  }
  else {
    current = stk.TopNPop();
  }

  return *this;
}

// BTPreOrderIterator Specific member functions (inherited from ResettableIterator)
template <typename Data>
void BTPreOrderIterator<Data>::Reset() noexcept {
  stk.Clear();
  current = reset;
}

// Auxiliary Function for BTPostOrderIterator
template <typename Data>
typename BinaryTree<Data>::Node* BTPostOrderIterator<Data>::ExtremeLeftLeafNode(typename BinaryTree<Data>::Node& bt) {
  if(&bt != nullptr) {
    if(bt.HasLeftChild()) {
      stk.Push(&bt);
      return ExtremeLeftLeafNode(bt.LeftChild());
    }
    else if(bt.HasRightChild()) {
      stk.Push(&bt);
      return ExtremeLeftLeafNode(bt.RightChild());
    }
    else return &bt;
  }
  else return nullptr;
}


// BTPostOrderIterator Specific Constructor
template <typename Data>
BTPostOrderIterator<Data>::BTPostOrderIterator(const BinaryTree<Data>& bt) {
  if(bt.Size() != 0) {
    current = ExtremeLeftLeafNode(bt.Root());
    reset = &bt.Root();
  }
}

// BTPostOrderIterator Copy Constructor
template <typename Data>
BTPostOrderIterator<Data>::BTPostOrderIterator(const BTPostOrderIterator<Data>& bt) {
  current = bt.current;
  stk = bt.stk;
  reset = bt.reset;
}

// BTPostOrderIterator Move Constructor
template <typename Data>
BTPostOrderIterator<Data>::BTPostOrderIterator(BTPostOrderIterator<Data>&& bt) noexcept {
  std::swap(current, bt.current);
  std::swap(stk, bt.stk);
  std::swap(reset, bt.reset);
}

// BTPostOrderIterator Copy Assignement
template <typename Data>
BTPostOrderIterator<Data>& BTPostOrderIterator<Data>::operator=(const BTPostOrderIterator<Data>& bt) {
  BTPostOrderIterator<Data>* temp = new BTPostOrderIterator<Data> (bt);
  std::swap(*this, *temp);
  delete temp;
  return *this;
}

// BTPostOrderIterator Move Assignement
template <typename Data>
BTPostOrderIterator<Data>& BTPostOrderIterator<Data>::operator=(BTPostOrderIterator<Data>&& bt) noexcept {
  std::swap(current, bt.current);
  std::swap(stk, bt.stk);
  std::swap(reset, bt.reset);
  return *this;
}

// BTPostOrderIterator Comparison operators
template <typename Data>
bool BTPostOrderIterator<Data>::operator==(const BTPostOrderIterator<Data>& bt) const noexcept {
  if(current == bt.current && stk == bt.stk && reset == bt.reset) {
    return true;
  } else return false;
}

template <typename Data>
bool BTPostOrderIterator<Data>::operator!=(const BTPostOrderIterator<Data>& bt) const noexcept {
  return !((*this) == bt);
}

// BTPostOrderIterator Specific member functions (inherited from Iterator)
template <typename Data>
Data& BTPostOrderIterator<Data>::operator*() const {
  if(Terminated()){
    throw std::out_of_range("out_of_range");
  }
  else return current->Element();
}

template <typename Data>
bool BTPostOrderIterator<Data>::Terminated() const noexcept {
  return(current == nullptr);
}

// BTPostOrderIterator Specific member functions (inherited from ForwardIterator)

template <typename Data>
ForwardIterator<Data>& BTPostOrderIterator<Data>::operator++() {
  if(Terminated()) {
    throw std::out_of_range("out_of_range");
  }

  if(!stk.Empty()) {
    if(stk.Top()->HasLeftChild() && &current->Element() == &(stk.Top()->LeftChild().Element())) { //controllo se arrivo da sinistra
      if(stk.Top()->HasRightChild()) {
        stk.Push(ExtremeLeftLeafNode(stk.Top()->RightChild()));
      }
    }
  }

  if(stk.Empty()) {
    current = nullptr;
  }
  else {
    current = stk.TopNPop();
  }

  return *this;
}

// BTPostOrderIterator Specific member functions (inherited from ResettableIterator)
template <typename Data>
void BTPostOrderIterator<Data>::Reset() noexcept {
  stk.Clear();
  if(reset == nullptr){
    current = nullptr;
  }
  else {
    current = ExtremeLeftLeafNode(*reset);
  }
}


// Auxiliary function for BTInOrderIterator
template <typename Data>
typename BinaryTree<Data>::Node* BTInOrderIterator<Data>::ExtremeLeftNode(typename BinaryTree<Data>::Node& bt) {
  if(bt.HasLeftChild()) {
    stk.Push(&bt);
    return ExtremeLeftNode(bt.LeftChild());
  } else return &bt;
}

// BTInOrderIterator Specific Constructor
template <typename Data>
BTInOrderIterator<Data>::BTInOrderIterator(const BinaryTree<Data>& bt) {
  if(bt.Size() != 0) {
    current = ExtremeLeftNode(bt.Root());
    reset = &bt.Root();
  }
}

// BTInOrderIterator Copy Constructor
template <typename Data>
BTInOrderIterator<Data>::BTInOrderIterator(const BTInOrderIterator<Data>& bt) {
  current = bt.current;
  stk = bt.stk;
  reset = bt.reset;
}

// BTInOrderIterator Move Constructor
template <typename Data>
BTInOrderIterator<Data>::BTInOrderIterator(BTInOrderIterator<Data>&& bt) noexcept {
  std::swap(current, bt.current);
  std::swap(stk, bt.stk);
  std::swap(reset, bt.reset);
}

// BTInOrderIterator Copy Assignement
template <typename Data>
BTInOrderIterator<Data>& BTInOrderIterator<Data>::operator=(const BTInOrderIterator<Data>& bt) {
  BTInOrderIterator<Data>* temp = new BTInOrderIterator<Data> (bt);
  std::swap(*this, *temp);
  delete temp;
  return *this;
}

// BTInOrderIterator Move Assignement
template <typename Data>
BTInOrderIterator<Data>& BTInOrderIterator<Data>::operator=(BTInOrderIterator<Data>&& bt) noexcept {
  std::swap(current, bt.current);
  std::swap(stk, bt.stk);
  std::swap(reset, bt.reset);
  return *this;
}

// BTInOrderIterator Comparison operators
template <typename Data>
bool BTInOrderIterator<Data>::operator==(const BTInOrderIterator<Data>& bt) const noexcept {
  if(current == bt.current && stk == bt.stk && reset == bt.reset) {
    return true;
  } else return false;
}

template <typename Data>
bool BTInOrderIterator<Data>::operator!=(const BTInOrderIterator<Data>& bt) const noexcept {
  return !((*this) == bt);
}

// BTInOrderIterator Specific member functions (inherited from Iterator)
template <typename Data>
Data& BTInOrderIterator<Data>::operator*() const {
  if(Terminated()) {
    throw std::out_of_range("out_of_range");
  }
  else return current->Element();
}

template <typename Data>
bool BTInOrderIterator<Data>::Terminated() const noexcept {
  return(current == nullptr);
}

// BTInOrderIterator Specific member functions (inherited from ForwardIterator)

template <typename Data>
ForwardIterator<Data>& BTInOrderIterator<Data>::operator++() {
  if(Terminated()) {
    throw std::out_of_range("out_of_range");
  }

    if(current->HasRightChild()) {
      stk.Push(ExtremeLeftNode(current->RightChild()));
    }

  if(stk.Empty()) {
    current = nullptr;
  }
  else {
    current = stk.TopNPop();
  }

  return *this;
}

// BTInOrderIterator Specific member functions (inherited from ResettableIterator)

template <typename Data>
void BTInOrderIterator<Data>::Reset() noexcept {
  stk.Clear();
  if(reset == nullptr){
    current = nullptr;
  }
  else {
    current = ExtremeLeftNode(*reset);
  }
}

// BTBreadthIterator Specific Constructor
template <typename Data>
BTBreadthIterator<Data>::BTBreadthIterator(const BinaryTree<Data>& bt) {
  if(bt.Size() != 0) {
      current = &bt.Root();
      reset = &bt.Root();
  }
}

// BTBreadthIterator Copy Constructor
template <typename Data>
BTBreadthIterator<Data>::BTBreadthIterator(const BTBreadthIterator<Data>& bt) {
  current = bt.current;
  que = bt.que;
  reset = bt.reset;
}

// BTBreadthIterator Move Constructor
template <typename Data>
BTBreadthIterator<Data>::BTBreadthIterator(BTBreadthIterator<Data>&& bt) noexcept {
  std::swap(current, bt.current);
  std::swap(que, bt.que);
  std::swap(reset, bt.reset);
}

// BTBreadthIterator Copy Assignement
template <typename Data>
BTBreadthIterator<Data>& BTBreadthIterator<Data>::operator=(const BTBreadthIterator<Data>& bt) {
  BTBreadthIterator<Data>* temp = new BTBreadthIterator<Data> (bt);
  std::swap(*this, *temp);
  delete temp;
}

// BTBreadthIterator Move Assignement
template <typename Data>
BTBreadthIterator<Data>& BTBreadthIterator<Data>::operator=(BTBreadthIterator<Data>&& bt) noexcept {
  std::swap(current, bt.current);
  std::swap(que, bt.que);
  std::swap(reset, bt.reset);
  return *this;
}

// BTBreadthIterator Comparison operators
template <typename Data>
bool BTBreadthIterator<Data>::operator==(const BTBreadthIterator<Data>& bt) const noexcept {
  if(current == bt.current && que == bt.que && reset == bt.reset) {
    return true;
  } else return false;
}

template <typename Data>
bool BTBreadthIterator<Data>::operator!=(const BTBreadthIterator<Data>& bt) const noexcept {
  return !((*this) == bt);
}

// BTBreadthIterator Specific member functions (inherited from Iterator)
template <typename Data>
Data& BTBreadthIterator<Data>::operator*() const {
  if(Terminated()) {
    throw std::out_of_range("out_of_range");
  }
  else return current->Element();
}

template <typename Data>
bool BTBreadthIterator<Data>::Terminated() const noexcept {
  return(current == nullptr);
}

// BTBreadthIterator Specific member functions (inherited from ForwardIterator)
template <typename Data>
ForwardIterator<Data>& BTBreadthIterator<Data>::operator++() {
  if(Terminated()) {
    throw std::out_of_range("out_of_range");
  }

  if(current->HasLeftChild()) {
    que.Enqueue(&current->LeftChild());
  }
  if(current->HasRightChild()) {
    que.Enqueue(&current->RightChild());
  }

  if(que.Empty()) {
    current = nullptr;
  }
  else {
    current = que.HeadNDequeue();
  }

  return *this;
}

// BTBreadthIterator Specific member functions (inherited from ResettableIterator)
template <typename Data>
void BTBreadthIterator<Data>::Reset() noexcept {
  que.Clear();
  current = reset;
}

// Auxiliary member functions (for PreOrderMappableContainer)
template <typename Data>
void BinaryTree<Data>::AuxMapPreOrder(MapFunctor fun, void* par, Node& nodo) {
  fun(nodo.Element(), par);

  if(nodo.HasLeftChild()){
    AuxMapPreOrder(fun, par, nodo.LeftChild());
  }
  if(nodo.HasRightChild()){
    AuxMapPreOrder(fun, par, nodo.RightChild());
  }
}

// Auxiliary member functions (for PreOrderFoldableContainer)
template <typename Data>
void BinaryTree<Data>::AuxFoldPreOrder(FoldFunctor fun, const void* par, void* acc, Node& nodo) const {
  fun(nodo.Element(), par, acc);

  if(nodo.HasLeftChild()){
    AuxFoldPreOrder(fun, par, acc, nodo.LeftChild());
  }
  if(nodo.HasRightChild()){
    AuxFoldPreOrder(fun, par, acc, nodo.RightChild());
  }
}

// Auxiliary member functions (for PostOrderMappableContainer)
template <typename Data>
void BinaryTree<Data>::AuxMapPostOrder(MapFunctor fun, void* par, Node& nodo) {
  if(nodo.HasLeftChild()){
    AuxMapPostOrder(fun, par, nodo.LeftChild());
  }
  if(nodo.HasRightChild()){
    AuxMapPostOrder(fun, par, nodo.RightChild());
  }

  fun(nodo.Element(), par);

}

// Auxiliary member functions (for PostOrderFoldableContainer)
template <typename Data>
void BinaryTree<Data>::AuxFoldPostOrder(FoldFunctor fun, const void* par, void* acc, Node& nodo) const {
  if(nodo.HasLeftChild()){
    AuxFoldPostOrder(fun, par, acc, nodo.LeftChild());
  }
  if(nodo.HasRightChild()){
    AuxFoldPostOrder(fun, par, acc, nodo.RightChild());
  }

  fun(nodo.Element(), par, acc);
}

// Auxiliary member functions (for InOrderMappableContainer)
template <typename Data>
void BinaryTree<Data>::AuxMapInOrder(MapFunctor fun, void* par, Node& nodo) {
  if(nodo.HasLeftChild()){
    AuxMapInOrder(fun, par, nodo.LeftChild());
  }

  fun(nodo.Element(), par);

  if(nodo.HasRightChild()){
    AuxMapInOrder(fun, par, nodo.RightChild());
  }

}

// Auxiliary member functions (for InOrderFoldableContainer)
template <typename Data>
void BinaryTree<Data>::AuxFoldInOrder(FoldFunctor fun, const void* par, void* acc, Node& nodo) const {
  if(nodo.HasLeftChild()){
    AuxFoldInOrder(fun, par, acc, nodo.LeftChild());
  }

  fun(nodo.Element(), par, acc);

  if(nodo.HasRightChild()){
    AuxFoldInOrder(fun, par, acc, nodo.RightChild());
  }

}

/* ************************************************************************** */

}
