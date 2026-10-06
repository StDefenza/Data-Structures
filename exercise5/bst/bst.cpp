
namespace lasd {

/* ************************************************************************** */

//Constructor from LinearContainer
template<typename Data>
BST<Data>::BST(const LinearContainer<Data>& var) {
  for(ulong i = 0; i < var.Size(); i++) {
    Insert(var[i]);
  }
}

//Copy Constructor
template<typename Data>
BST<Data>::BST(const BST& bst):BinaryTreeLnk<Data>(bst) {
}


//Move Constructor
template<typename Data>
BST<Data>::BST(BST&& bst)noexcept:BinaryTreeLnk<Data>(std::move(bst)) {
}

//Copy Assignement
template<typename Data>
BST<Data>& BST<Data>::operator=(const BST<Data>& bst) {
  BinaryTreeLnk<Data>::operator=(bst);
  return *this;
}

//Move Assignement
template<typename Data>
BST<Data>& BST<Data>::operator=(BST<Data>&& bst) noexcept {
  BinaryTreeLnk<Data>::operator=(std::move(bst));
  return *this;
}

//Comparison Operators
template<typename Data>
bool BST<Data>::operator==(const BST& bst) const noexcept {
  if(size == bst.Size()) {
    BTInOrderIterator<Data> it1(*this);
    BTInOrderIterator<Data> it2(bst);
    while(!it1.Terminated()) {
      if(*it1 != *it2) {
        return false;
      }
      ++it1;
      ++it2;
    }
    return true;
  }
  return false;
}

template<typename Data>
bool BST<Data>::operator!=(const BST& bst) const noexcept {
  return !((*this) == bst);
}

// Specific member functions
template<typename Data>
const Data& BST<Data>::Min() const{
  if(size != 0) {
    NodeLnk* minimo = FindPointerToMin(root);
    return minimo->element;
  }
  else throw std::length_error("Access to empty BST");
}

template<typename Data>
Data BST<Data>::MinNRemove() {
  if(size != 0) {
    return DataNDelete(DetachMin(root));
  }
  else throw std::length_error("Access to empty BST");
}

template<typename Data>
void BST<Data>::RemoveMin() {
  if(size != 0) {
    delete DetachMin(root);
  }
  else throw std::length_error("Access to empty BST");
}

template<typename Data>
const Data& BST<Data>::Max() const{
  if(size != 0) {
    NodeLnk* massimo = FindPointerToMax(root);
    return massimo->element;
  }
  else throw std::length_error("Access to empty BST");
}

template<typename Data>
Data BST<Data>::MaxNRemove() {
  if(size != 0) {
    return DataNDelete(DetachMax(root));
  }
  else throw std::length_error("Access to empty BST");
}

template<typename Data>
void BST<Data>::RemoveMax() {
  if(size != 0) {
    delete DetachMax(root);
  }
  else throw std::length_error("Access to empty BST");
}

template<typename Data>
const Data& BST<Data>::Predecessor(const Data& nodo) const{
  NodeLnk* const* temp = FindPointerToPredecessor(root, nodo);

  if(temp != nullptr) {
    return (*temp)->element;
  }
  else throw std::length_error("Access to empty BST");
}

template<typename Data>
Data BST<Data>::PredecessorNRemove(const Data& nodo) {
  NodeLnk** temp = FindPointerToPredecessor(root, nodo);

  if(temp != nullptr) {
    return DataNDelete(Detach(*temp));
  }
  else throw std::length_error("Access to empty BST");
}

template<typename Data>
void BST<Data>::RemovePredecessor(const Data& nodo) {
  NodeLnk** temp = FindPointerToPredecessor(root, nodo);

  if(temp != nullptr) {
    delete Detach(*temp);
  }
  else throw std::length_error("Access to empty BST");
}

template<typename Data>
const Data& BST<Data>::Successor(const Data& nodo) const{
  NodeLnk* const* temp = FindPointerToSuccessor(root, nodo);

  if(temp != nullptr) {
    return (*temp)->element;
  }
  else throw std::length_error("Access to empty BST");
}

template<typename Data>
Data BST<Data>::SuccessorNRemove(const Data& nodo) {
  NodeLnk** temp = FindPointerToSuccessor(root, nodo);

  if(temp != nullptr) {
    return DataNDelete(Detach(*temp));
  }
  else throw std::length_error("Access to empty BST");
}

template<typename Data>
void BST<Data>::RemoveSuccessor(const Data& nodo) {
  NodeLnk** temp = FindPointerToSuccessor(root, nodo);

  if(temp != nullptr) {
    delete Detach(*temp);
  }
  else throw std::length_error("Access to empty BST");
}


// Specific member functions (inherited from DictionaryContainer)
template<typename Data>
void BST<Data>::Insert(const Data& var) {
  NodeLnk*& temp = FindPointerTo(root, var);

  if(temp == nullptr) {
    temp = new NodeLnk(var);
    size++;
  }
}

template<typename Data>
void BST<Data>::Insert(Data&& var) noexcept {
  NodeLnk*& temp = FindPointerTo(root, var);

  if(temp == nullptr) {
    temp = new NodeLnk(std::move(var));
    size++;
  }
}

template<typename Data>
void BST<Data>::Remove(const Data& var) {
  delete Detach(FindPointerTo(root, var));
}

// Specific member functions (inherited from TestableContainer)
template<typename Data>
bool BST<Data>::Exists(const Data& var) const noexcept {
  return (FindPointerTo(root, var) != nullptr);
}

//Auxiliary Functions
template<typename Data>
Data BST<Data>::DataNDelete(NodeLnk* nodo) {
  Data dat;
  std::swap(dat, nodo->element);
  delete nodo;
  return dat;
}

template<typename Data>
typename BST<Data>::NodeLnk* BST<Data>::Detach(NodeLnk*& nodo) noexcept {
  if(nodo != nullptr) {
    if(!nodo->HasRightChild()) {
        return Skip2Left(nodo);
    }
    else if(!nodo->HasLeftChild()) {
      return Skip2Right(nodo);
    }
    else {
      NodeLnk* temp = DetachMax(nodo->left);
      std::swap(temp->element, nodo->element);
      return temp;
    }
  }
  return nullptr;
}

template<typename Data>
typename BST<Data>::NodeLnk* BST<Data>::DetachMax(NodeLnk*& nodo) noexcept {
  return Skip2Left(FindPointerToMax(nodo));
}

template<typename Data>
typename BST<Data>::NodeLnk* BST<Data>::DetachMin(NodeLnk*& nodo) noexcept {
  return Skip2Right(FindPointerToMin(nodo));
}

template<typename Data>
typename BST<Data>::NodeLnk* BST<Data>::Skip2Left(NodeLnk*& nodo) noexcept {
  NodeLnk* sinistro = nullptr;
  if(nodo != nullptr) {
    std::swap(sinistro, nodo->left);
    std::swap(sinistro, nodo);
    size--;
  }

  return sinistro;
}

template<typename Data>
typename BST<Data>::NodeLnk* BST<Data>::Skip2Right(NodeLnk*& nodo) noexcept {
  NodeLnk* destro = nullptr;
  if(nodo != nullptr) {
    std::swap(destro, nodo->right);
    std::swap(destro, nodo);
    size--;
  }

  return destro;
}

template<typename Data>
typename BST<Data>::NodeLnk* const& BST<Data>::FindPointerToMin(NodeLnk* const& nodo) const noexcept {
  NodeLnk* const* pointer = &nodo;
  NodeLnk* current = nodo;

    if(current != nullptr) {
      while(current->left != nullptr) {
        pointer = &current->left;
        current = current->left;
      }
    }

    return *pointer;
}

template<typename Data>
typename BST<Data>::NodeLnk*& BST<Data>::FindPointerToMin(NodeLnk*& nodo) noexcept {
  return const_cast<NodeLnk*&>(static_cast<const BST<Data> *>(this)->FindPointerToMin(nodo));
}

template<typename Data>
typename BST<Data>::NodeLnk* const& BST<Data>::FindPointerToMax(NodeLnk* const& nodo) const noexcept {
  NodeLnk* const* pointer = &nodo;
  NodeLnk* current = nodo;

    if(current != nullptr) {
      while(current->right != nullptr) {
        pointer = &current->right;
        current = current->right;
      }
    }

    return *pointer;
}

template<typename Data>
typename BST<Data>::NodeLnk*& BST<Data>::FindPointerToMax(NodeLnk*& nodo) noexcept {
  return const_cast<NodeLnk*&>(static_cast<const BST<Data> *>(this)->FindPointerToMax(nodo));
}

template<typename Data>
typename BST<Data>::NodeLnk* const& BST<Data>::FindPointerTo(NodeLnk* const& nodo, const Data& var) const noexcept {
  NodeLnk* const* pointer = &nodo;
  NodeLnk* current = nodo;

  while(current != nullptr) {
    if(current->element > var) {
        pointer = &current->left;
        current = current->left;
    }
    else if(current->element < var) {
      pointer = &current->right;
      current = current->right;
    }
    else break;
  }

  return *pointer;
}

template<typename Data>
typename BST<Data>::NodeLnk*& BST<Data>::FindPointerTo(NodeLnk*& nodo, const Data& var) noexcept {
  return const_cast<NodeLnk*&>(static_cast<const BST<Data> *>(this)->FindPointerTo(nodo, var));
}

template<typename Data>
typename BST<Data>::NodeLnk* const* BST<Data>::FindPointerToPredecessor(NodeLnk* const& nodo, const Data& var) const noexcept {
  NodeLnk* const* pointer = &nodo;
  NodeLnk* const* extimate = nullptr;

  while(true) {
    NodeLnk& current = **pointer;
    if(current.element < var) {
      extimate = pointer;
      if(current.right == nullptr) {
        return extimate;
      }
      else {
        pointer = &current.right;
      }
    }
    else {
      if(current.left == nullptr) {
        return extimate;
      }
      else {
        if(current.element > var) {
          pointer = &current.left;
        }
        else {
          return &FindPointerToMax(current.left);
        }
      }
    }
  }
}

template<typename Data>
typename BST<Data>::NodeLnk** BST<Data>::FindPointerToPredecessor(NodeLnk*& nodo, const Data& var) noexcept {
  return const_cast<NodeLnk**>(static_cast<const BST<Data> *>(this)->FindPointerToPredecessor(nodo, var));
}

template<typename Data>
typename BST<Data>::NodeLnk* const* BST<Data>::FindPointerToSuccessor(NodeLnk* const& nodo, const Data& var) const noexcept {
  NodeLnk* const* pointer = &nodo;
  NodeLnk* const* extimate = nullptr;

  while(true) {
    NodeLnk& current = **pointer;
    if(current.element > var) {
      extimate = pointer;
      if(current.left == nullptr) {
        return extimate;
      }
      else {
        pointer = &current.left;
      }
    }
    else {
      if(current.right == nullptr) {
        return extimate;
      }
      else {
        if(current.element < var) {
          pointer = &current.right;
        }
        else {
          return &FindPointerToMin(current.right);
        }
      }
    }
  }
}

template<typename Data>
typename BST<Data>::NodeLnk** BST<Data>::FindPointerToSuccessor(NodeLnk*& nodo, const Data& var) noexcept {
  return const_cast<NodeLnk**>(static_cast<const BST<Data> *>(this)->FindPointerToSuccessor(nodo, var));
}

/* ************************************************************************** */

}
