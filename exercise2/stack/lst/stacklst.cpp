
namespace lasd {

/* ************************************************************************** */

  //Specific constructor
  template <typename Data>
  StackLst<Data>::StackLst(const LinearContainer<Data>& con):List<Data>(con) {
  }

  //StackLst copy constructor
  template <typename Data>
  StackLst<Data>::StackLst(const StackLst<Data>& var):List<Data>(var) {
  }

  //StackLst move constructor
  template <typename Data>
  StackLst<Data>::StackLst(StackLst&& var) noexcept:List<Data>(std::move(var)) {
  }

 //StackLst copy assignment
 template <typename Data>
 StackLst<Data>& StackLst<Data>::operator=(const StackLst<Data>& var) {
    List<Data>::operator=(var);
    return *this;
 }

 //StackLst move assignment
 template<typename Data>
 StackLst<Data>& StackLst<Data>::operator=(StackLst<Data>&& var) noexcept {
   List<Data>::operator=(var);
   return *this;
 }

 //StackLst  == operator
 template<typename Data>
 bool StackLst<Data>::operator==(const StackLst<Data>& var) const noexcept {
   return List<Data>::operator==(var);
 }


 //StackLst  != operator
 template<typename Data>
 inline bool StackLst<Data>::operator!=(const StackLst<Data>& var) const noexcept {
   return List<Data>::operator!=(var);
 }

 //StackLst Top (Const Version)
 template <typename Data>
 const Data& StackLst<Data>::Top() const {
   return List<Data>::Front();
 }

 //StackLst Top
 template <typename Data>
 Data& StackLst<Data>::Top() {
   return List<Data>::Front();
 }

 //StackLst Pop
 template <typename Data>
 void StackLst<Data>::Pop() {
   List<Data>::RemoveFromFront();
 }

 //StackLst TopNPop
 template <typename Data>
 Data StackLst<Data>::TopNPop() {
   return List<Data>::FrontNRemove();
 }

 //StackLst Push copy
 template <typename Data>
 void StackLst<Data>::Push(const Data& var) {
   List<Data>::InsertAtFront(var);
  }

 //StackLst Push move
 template <typename Data>
 void StackLst<Data>::Push(Data&& var) noexcept {
   List<Data>::InsertAtFront(var);
 }

 //Clear
 template <typename Data>
 void StackLst<Data>::Clear(){
   List<Data>::Clear();
 }



/* ************************************************************************** */

}
