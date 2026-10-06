
namespace lasd {

/* ************************************************************************** */

  //Default Constructor
  template <typename Data>
  StackVec<Data>::StackVec():Vector<Data>(1) {
  }

  //Specific constructor
  template <typename Data>
  StackVec<Data>::StackVec(const LinearContainer<Data>& con):Vector<Data>(con) {
    stksize = con.Size();
  }

  //StackVec copy constructor
  template <typename Data>
  StackVec<Data>::StackVec(const StackVec<Data>& var):Vector<Data>(var) {
    stksize = var.stksize;
  }

  //StackVec move constructor
  template <typename Data>
  StackVec<Data>::StackVec(StackVec<Data>&& var) noexcept:Vector<Data>(std::move(var)) {
    std::swap(stksize, var.stksize);
  }

  //StackVec Destructor
  template <typename Data>
   StackVec<Data>::~StackVec() {
     Clear();
   }

 //StackVec copy assignment
 template <typename Data>
 StackVec<Data>& StackVec<Data>::operator=(const StackVec<Data>& var) {
    Vector<Data>::operator=(var);
    stksize = var.stksize;
    return *this;
 }

 //StackVec move assignment
 template<typename Data>
 StackVec<Data>& StackVec<Data>::operator=(StackVec<Data>&& var) noexcept {
   Vector<Data>::operator=(var);
   std::swap(stksize, var.stksize);
   return *this;
 }

 //StackVec == operator
 template<typename Data>
 bool StackVec<Data>::operator==(const StackVec<Data>& var) const noexcept {
   if(stksize == var.stksize){
     for(ulong i = 0; i<stksize; i++) {
       if(Elements[i]!=var.Elements[i]) {
         return false;
       }
     }
     return true;
   }
   else {
     return false;
   }
 }

 //StackVec != operator
 template<typename Data>
 inline bool StackVec<Data>::operator!=(const StackVec<Data>& var) const noexcept {
   return !(*this == var);
 }

 //StackVec Top (Const Version)
 template <typename Data>
 const Data& StackVec<Data>::Top() const {
     if(!Empty()) {
       return Elements[stksize-1];
     }
     else {
       throw std::length_error("Access to empty StackVec");
     }
 }

 //StackVec Top
 template <typename Data>
 Data& StackVec<Data>::Top() {
     if(!Empty()) {
       return Elements[stksize-1];
     }
     else {
       throw std::length_error("Access to empty StackVec");
     }
 }

 //StackVec Pop
 template <typename Data>
 void StackVec<Data>::Pop() {
   if(!Empty()) {
     stksize--;
   }
   else{
     throw std::length_error("Access to empty StackVec");
   }
 }

 //StackVec TopNPop
 template <typename Data>
 Data StackVec<Data>::TopNPop() {
   if(!Empty()) {
     Data temp = Top();
     Pop();
     return temp;
   }
   else {
     throw std::length_error("Access to empty StackVec");
   }
 }

 //StackVec Push copy
 template <typename Data>
 void StackVec<Data>::Push(const Data& var) {
   if(stksize == size) {
     Vector<Data>::Resize(size*2);
   }
   Elements[stksize]=var;
   stksize++;
  }

 //StackVec Push move
 template <typename Data>
 void StackVec<Data>::Push(Data&& var) noexcept {
   if(stksize == size){
     Vector<Data>::Resize(size*2);
   }
     std::swap(Elements[stksize],var);
     stksize++;
  }

  //StackVec Empty
  template <typename Data>
  inline bool StackVec<Data>::Empty() const noexcept {
    if(stksize==0){
      return true;
    }
    else{
      return false;
    }
  }

  //StackVec Size
  template <typename Data>
  inline ulong StackVec<Data>::Size() const noexcept {
    return stksize;
  }

  //Clear
  template <typename Data>
  void StackVec<Data>::Clear(){
    stksize=0;
  }

/* ************************************************************************** */

}
