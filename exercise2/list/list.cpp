
namespace lasd {

/* ************************************************************************** */

//Node specific constructor
template <typename Data>
List<Data>::Node::Node(Data var) {
  Element = var;
  Next = nullptr;
}

//Node Destructor
template <typename Data>
List<Data>::Node::~Node() {
  delete Next;
}

//Node copy constructor
template <typename Data>
List<Data>::Node::Node(const Node& var) {
  Element = var->Element;
  Next = var->Next;
}

//Node move constructor
template <typename Data>
List<Data>::Node::Node(Node&& var) noexcept {
   std::swap(Element,var->Element);
   std::swap(Next,var->Next);
}


//Specific constructor
template <typename Data>
List<Data>::List(const LinearContainer<Data>& con) {
  for(uint i = 0 ; i < con.Size(); i++) {
     InsertAtBack(con[i]);
  }
}

//List Destructor
template <typename Data>
 List<Data>::~List(){
   delete Head;
 }

//List copy constructor
template <typename Data>
List<Data>::List(const List& var) {
   for(Node* index = var.Head; index!=nullptr; index = index->Next) {
     InsertAtBack(index->Element);
   }
}

//List move constructor
template <typename Data>
List<Data>::List(List&& var) noexcept {
  std::swap(Head, var.Head);
  std::swap(Tail, var.Tail);
  std::swap(size, var.size);
}

//List copy assignment
template <typename Data>
List<Data>& List<Data>::operator=(const List<Data>& var) {
   List<Data>* temp = new List<Data>(var);
   std::swap(*this, *temp);
   delete temp;
   return *this;
}

//List move assignment
template<typename Data>
List<Data>& List<Data>::operator=(List<Data>&& var) noexcept {
  std::swap(Head, var.Head);
  std::swap(Tail, var.Tail);
  std::swap(size, var.size);
  return *this;
}

//List comparison operators
template<typename Data>
bool List<Data>::operator==(const List<Data>& var) const noexcept {
  if(size == var.size) {
      Node* temp1 = Head;
      Node* temp2 = var.Head;
      for(; temp1!=nullptr && temp2!=nullptr ; temp1 = temp1->Next, temp2 = temp2->Next) {
        if(temp1->Element != temp2->Element) {
          return false;
        }
      }
      return true;
  }else return false;
}

template<typename Data>
inline bool List<Data>::operator!=(const List<Data>& var) const noexcept {
  return !((*this) == var);
}

//Specific List member functions
template <typename Data>
void List<Data>::InsertAtFront(const Data& var) {
  if(Head == NULL) {
    Node* temp = new Node(var);
    Head = temp;
    Tail = temp;
    size++;
  }
  else {
     Node* temp = new Node(var);
     temp->Next = Head;
     Head = temp;
     size++;
  }
}

template <typename Data>
void List<Data>::InsertAtFront(Data&& var) noexcept {
  if(Head == NULL) {
    Node* temp = new Node();
    std::swap(temp->Element,var);
    Head = temp;
    Tail = temp;
    size++;
  }
  else {
   Node* temp = new Node();
   std::swap(temp->Element , var);
   temp->Next = Head;
   Head = temp;
   size++;
  }
}

template <typename Data>
void List<Data>::RemoveFromFront(){
  if(Head == NULL){
    throw std::length_error("Access to empty list");
  }else{
    struct Node * temp = Head;
    Head = Head->Next;
    temp->Next = nullptr;
    delete temp;
    size--;
  }
}

template <typename Data>
Data List<Data>::FrontNRemove() {
  if(Head == NULL) {
    throw std::length_error("Access to empty list");
  }else{
    Data temp = Head->Element;
    RemoveFromFront();
    return temp;
  }
}

template <typename Data>
void List<Data>::InsertAtBack(const Data& var) {
  if(Head == NULL) {
    InsertAtFront(var);
  }else{
    Node* temp = new Node(var);
    Tail->Next = temp;
    Tail = temp;
    size++;
 }
}

template <typename Data>
void List<Data>::InsertAtBack(Data&& var) noexcept {
  if(Head == NULL) {
    InsertAtFront(var);
  }
  else {
    Node* temp = new Node();
    std::swap(temp->Element , var);
    Tail->Next = temp;
    Tail = temp;
    size++;
  }
}

// Specific member functions (inherited from Container)
template <typename Data>
void List<Data>::Clear(){
  delete Head;
  Head = nullptr;
  Tail = nullptr;
  size = 0;
}

// Specific member functions (inherited from LinearContainer)
template <typename Data>
Data& List<Data>::Front() const {
  if(Head == NULL) {
    throw std::length_error("Access to empty list");
  }
  else {
    return Head->Element;
  }
}

template <typename Data>
Data& List<Data>::Back() const {
  if(Head == NULL){
    throw std::length_error("Access to empty list");
  }
  else {
    return Tail->Element;
  }
}

template <typename Data>
Data& List<Data>::operator[](const ulong index) const {
  if(index == 0) {
    return Front();
  }
  else if(index == size - 1) {
    return Back();
  }
  else if(index < size) {
    struct Node* temp = Head;
    for (ulong i = 0; i < index; i++) {
      temp = temp->Next;
    }
    return temp->Element;
  }
  else {
    throw std::out_of_range("Access at index" + std::to_string(index) + "; list size " + std::to_string(size) + ".");
  }
}


//Specific member functions inherited MappableContainer

template<typename Data>
void List<Data>::Map(MapFunctor fun, void* par) {
  if(size!=0) {
    AuxMapPreOrder(fun, par, Head);
  }
}

template<typename Data>
void List<Data>::MapPreOrder(MapFunctor fun, void* par) {
  if(size!=0) {
    AuxMapPreOrder(fun, par, Head);
  }
}

template<typename Data>
void List<Data>::MapPostOrder(MapFunctor fun, void* par) {
  if(size!=0){
    AuxMapPostOrder(fun, par, Head);
  }
}

//Specific member functions inherited FoldableContainer

template<typename Data>
void List<Data>::Fold(FoldFunctor fun, const void* par, void* acc) const {
  if(size!=0) {
    AuxFoldPreOrder(fun, par, acc, Head);
  }
}

template<typename Data>
void List<Data>::FoldPreOrder(const FoldFunctor fun, const void* par, void* acc) const {
  if(size!=0) {
    AuxFoldPreOrder(fun, par, acc, Head);
  }
}

template<typename Data>
void List<Data>::FoldPostOrder(const FoldFunctor fun, const void* par, void* acc) const {
  if(size!=0) {
    AuxFoldPostOrder(fun, par, acc, Head);
  }
}


 // Auxiliary member functions for MappableContainer

 template<typename Data>
 void List<Data>::AuxMapPreOrder(MapFunctor fun, void* par, Node* index) {
   for(; index!=nullptr; index = index->Next) {
     fun(index->Element, par);
   }
 }


 template<typename Data>
 void List<Data>::AuxMapPostOrder(MapFunctor fun, void* par, Node* index) {
   if(index->Next!=nullptr) {
     AuxMapPostOrder(fun, par, index->Next);
   }
   fun(index->Element, par);
 }

 // Auxiliary member functions for FoldableContainer

 template<typename Data>
 void List<Data>::AuxFoldPreOrder(FoldFunctor fun, const void* par, void* acc, Node* index) const {
   for(; index!=nullptr; index = index->Next) {
     fun(index->Element, par, acc);
   }
 }

 template<typename Data>
 void List<Data>::AuxFoldPostOrder(FoldFunctor fun, const void* par, void* acc, Node* index) const {
   if(index->Next!=nullptr) {
     AuxFoldPostOrder(fun, par, acc, index->Next);
   }
   fun(index->Element, par, acc);
 }

/* ************************************************************************** */

}
