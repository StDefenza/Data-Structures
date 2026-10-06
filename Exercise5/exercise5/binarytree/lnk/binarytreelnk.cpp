
namespace lasd {

/* ************************************************************************** */

//NodeLnk Constructor
template<typename Data>
BinaryTreeLnk<Data>::NodeLnk::NodeLnk(Data el) {
  element = el;
}

//NodeLnk Destructor
template<typename Data>
BinaryTreeLnk<Data>::NodeLnk::~NodeLnk() {
  delete right;
  delete left;
}

//Specific member functions
template<typename Data>
Data& BinaryTreeLnk<Data>::NodeLnk::Element() noexcept {
  return element;
}

template<typename Data>
const Data& BinaryTreeLnk<Data>::NodeLnk::Element() const noexcept {
  return element;
}

template<typename Data>
bool BinaryTreeLnk<Data>::NodeLnk::IsLeaf() const noexcept {
  return(!HasLeftChild() && !HasRightChild());
}

template<typename Data>
bool BinaryTreeLnk<Data>::NodeLnk::HasLeftChild() const noexcept {
  return (left != nullptr);
}

template<typename Data>
bool BinaryTreeLnk<Data>::NodeLnk::HasRightChild() const noexcept {
  return (right != nullptr);
}

template<typename Data>
typename BinaryTreeLnk<Data>::NodeLnk& BinaryTreeLnk<Data>::NodeLnk::LeftChild() const {
  if(HasLeftChild()) {
    return *left;
  }
  else {
    throw std::out_of_range("out_of_range");
  }
}

template<typename Data>
typename BinaryTreeLnk<Data>::NodeLnk& BinaryTreeLnk<Data>::NodeLnk::RightChild() const {
  if(HasRightChild()) {
    return *right;
  }
  else {
    throw std::out_of_range("out_of_range");
  }
}

//BTLnk Auxiliary Function for creation of LinearContainer
template<typename Data>
void BinaryTreeLnk<Data>::CreaLinearContainer(NodeLnk& nodo, const LinearContainer<Data>& var, ulong i) {
try{
  if(i < var.Size()){
    if(!nodo.HasLeftChild()){
      nodo.left = new NodeLnk(var[2*i+1]);
      size++;
      CreaLinearContainer(*nodo.left, var, 2*i+1);
    }

    if(!nodo.HasRightChild()){
      nodo.right = new NodeLnk(var[2*i+2]);
      size++;
      CreaLinearContainer(*nodo.right, var, 2*i+2);
    }
  else return;
  }
}
catch(...) {
  return;
}
}

//BTLnk Constructor from LinearContainer
template<typename Data>
BinaryTreeLnk<Data>::BinaryTreeLnk(const LinearContainer<Data>& var) {
  if(var.Size() != 0){
    root = new NodeLnk(var[0]);
    size++;
    CreaLinearContainer(*root, var, 0);
  }
}

//BTLnk Auxiliary Function for copy of tree
template<typename Data>
void BinaryTreeLnk<Data>::CopiaAlbero(NodeLnk& nodo, const NodeLnk& nl) {
  if(nl.HasLeftChild()){
    nodo.left = new NodeLnk(nl.left->Element());
    size++;
    CopiaAlbero(*nodo.left, *nl.left);
  }

  if(nl.HasRightChild()){
    nodo.right = new NodeLnk(nl.right->Element());
    size++;
    CopiaAlbero(*nodo.right, *nl.right);
  }
}

//BTLnk Copy Constructor
template<typename Data>
BinaryTreeLnk<Data>::BinaryTreeLnk(const BinaryTreeLnk& bt) {
   root = new NodeLnk(bt.Root().Element());
   size++;
   CopiaAlbero(*root, bt.Root());
}

//BTLnk Move Constructor
template<typename Data>
BinaryTreeLnk<Data>::BinaryTreeLnk(BinaryTreeLnk&& bt) noexcept {
  std::swap(size, bt.size);
  std::swap(root, bt.root);
}

//BTLnk Destructor
template<typename Data>
BinaryTreeLnk<Data>::~BinaryTreeLnk() {
  delete root;
}

//BTLnk Copy Assignement
template<typename Data>
BinaryTreeLnk<Data>& BinaryTreeLnk<Data>::operator=(const BinaryTreeLnk& bt) {
  BinaryTreeLnk<Data>* tmp = new BinaryTreeLnk<Data>(bt);
  std::swap(*tmp, *this);
  delete tmp;
  return *this;
}

//BTLnk Move Assignement
template<typename Data>
BinaryTreeLnk<Data>& BinaryTreeLnk<Data>::operator=(BinaryTreeLnk&& bt) noexcept {
  std::swap(size, bt.size);
  std::swap(root, bt.root);
  return *this;
}

// Comparison operators
template<typename Data>
bool BinaryTreeLnk<Data>::operator==(const BinaryTreeLnk& bt) const noexcept {
  return BinaryTree<Data>::operator==(bt);
}

template<typename Data>
bool BinaryTreeLnk<Data>::operator!=(const BinaryTreeLnk& bt) const noexcept {
  return BinaryTree<Data>::operator==(bt);
}

// Specific member functions (inherited from BinaryTree)
template<typename Data>
typename BinaryTreeLnk<Data>::NodeLnk& BinaryTreeLnk<Data>::Root() const {
  if(size != 0) {
    return *root;
  }
  else {
    throw std::length_error("Access to empty tree");
  }
}

// Specific member functions (inherited from Container)
template<typename Data>
void BinaryTreeLnk<Data>::Clear() {
  delete root;
  size = 0;
  root = nullptr;
}

/* ************************************************************************** */

}
