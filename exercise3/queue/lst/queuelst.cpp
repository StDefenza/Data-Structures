
namespace lasd {

/* ************************************************************************** */

  //Specific constructor
  template <typename Data>
  QueueLst<Data>::QueueLst(const LinearContainer<Data>& con):List<Data>(con) {
  }

  //QueueLst copy constructor
  template <typename Data>
  QueueLst<Data>::QueueLst(const QueueLst& var):List<Data>(var) {
  }

  //QueueLst move constructor
  template <typename Data>
  QueueLst<Data>::QueueLst(QueueLst&& var) noexcept:List<Data>(std::move(var)) {
  }

  //QueueLst copy assignment
  template <typename Data>
  QueueLst<Data>& QueueLst<Data>::operator=(const QueueLst<Data>& var) {
    List<Data>::operator=(var);
    return *this;
  }

  //QueueLst move assignment
  template<typename Data>
  QueueLst<Data>& QueueLst<Data>::operator=(QueueLst<Data>&& var) noexcept {
    List<Data>::operator=(var);
    return *this;
  }

  //QueueLst  == operator
  template<typename Data>
  bool QueueLst<Data>::operator==(const QueueLst<Data>& var) const noexcept {
    return List<Data>::operator==(var);
  }


  //QueueLst  != operator
  template<typename Data>
  inline bool QueueLst<Data>::operator!=(const QueueLst<Data>& var) const noexcept {
    return List<Data>::operator!=(var);
  }

  //QueueLst Head (Const Version)
  template <typename Data>
  const Data& QueueLst<Data>::Head() const {
     return List<Data>::Front();
  }

  //QueueLst Head
  template <typename Data>
  Data& QueueLst<Data>::Head() {
     return List<Data>::Front();
  }

  //QueueLst Dequeue
  template <typename Data>
  void QueueLst<Data>::Dequeue() {
     List<Data>::RemoveFromFront();
  }

  //QueueLst HeadNDequeue
  template <typename Data>
  Data QueueLst<Data>::HeadNDequeue() {
     return List<Data>::FrontNRemove();
  }

  //QueueLst Enqueue copy
  template <typename Data>
  void QueueLst<Data>::Enqueue(const Data& var) {
    List<Data>::InsertAtBack(var);
   }

  //QueueLst Enqueue move
  template <typename Data>
  void QueueLst<Data>::Enqueue(Data&& var) noexcept {
    List<Data>::InsertAtBack(std::move(var));
  }

  //QueueLst Clear
  template <typename Data>
  void QueueLst<Data>::Clear() {
    List<Data>::Clear();
  }

/* ************************************************************************** */

}
