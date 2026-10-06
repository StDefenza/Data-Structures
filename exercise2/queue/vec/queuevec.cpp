
namespace lasd {

/* ************************************************************************** */

  //Default Constructor
  template <typename Data>
  QueueVec<Data>::QueueVec():Vector<Data>(10) {
  }

  //Specific constructor
  template <typename Data>
  QueueVec<Data>::QueueVec(const LinearContainer<Data>& con):Vector<Data>(con) {
    qhead = 0;
    qtail = con.Size()-1;
    qsize = con.Size();
    Expand();
  }

  //QueueVec copy constructor
  template <typename Data>
  QueueVec<Data>::QueueVec(const QueueVec<Data>& var):Vector<Data>(var) {
    qsize = var.qsize;
    qhead = var.qhead;
    qtail = var.qtail;
  }

  //QueueVec move constructor
  template <typename Data>
  QueueVec<Data>::QueueVec(QueueVec<Data>&& var) noexcept:Vector<Data>(std::move(var)) {
    std::swap(qsize, var.qsize);
    std::swap(qhead, var.qhead);
    std::swap(qtail, var.qtail);
  }

  //QueueVec copy assignment
  template <typename Data>
  QueueVec<Data>& QueueVec<Data>::operator=(const QueueVec<Data>& var) {
    Vector<Data>::operator=(var);
    qsize = var.qsize;
    qhead = var.qhead;
    qtail = var.qtail;
    return *this;
  }

  //QueueVec move assignment
  template<typename Data>
  QueueVec<Data>& QueueVec<Data>::operator=(QueueVec<Data>&& var) noexcept {
    Vector<Data>::operator=(var);
    std::swap(qsize, var.qsize);
    std::swap(qhead, var.qhead);
    std::swap(qtail, var.qtail);
    return *this;
  }

  //QueueVec == operator
  template<typename Data>
  bool QueueVec<Data>::operator==(const QueueVec<Data>& var) const noexcept {
    if(qsize == var.qsize) {
      ulong k = qhead;
      ulong j = var.qhead;
      for(ulong i = 0; i<qsize; i++) {
        if(Elements[k]!=var.Elements[j]) {
          return false;
        }
        k = (k+1)%size;
        j = (j+1)%var.size;
      }
      return true;
    }
    else {
      return false;
    }
  }

  //QueueVec != operator
  template<typename Data>
  inline bool QueueVec<Data>::operator!=(const QueueVec<Data>& var) const noexcept {
    return !(*this == var);
  }

  //QueueVec Head (Const Version)
  template <typename Data>
  const Data& QueueVec<Data>::Head() const {
    if(Empty()) {
      throw std::length_error("Access to empty QueueVec");
    }
    else {
      return Elements[qhead];
    }
  }

  //QueueVec Head
  template <typename Data>
  Data& QueueVec<Data>::Head(){
    if(Empty()) {
      throw std::length_error("Access to empty QueueVec");
    }
    else{
      return Elements[qhead];
    }
  }

  //QueueVec Dequeue
  template <typename Data>
  void QueueVec<Data>::Dequeue() {
    if(Empty()) {
      throw std::length_error("Access to empty QueueVec");
    }
    else {
      qhead = (qhead+1)%size;
      qsize--;
    }
  }

  //QueueVec HeadNDequeue
  template <typename Data>
  Data QueueVec<Data>::HeadNDequeue() {
      Data temp = Head();
      Dequeue();
      return temp;
  }

  //QueueVec Enqueue copy
  template <typename Data>
  void QueueVec<Data>::Enqueue(const Data& var) {
    if(qhead == (qtail+1)%size) {
      Expand();
    }
      Elements[qtail]=var;
      qtail = (qtail+1)%size;
      qsize++;
   }

  //QueueVec Enqueue move
  template <typename Data>
  void QueueVec<Data>::Enqueue(Data&& var) noexcept {
    if(qhead == (qtail+1)%size) {
      Expand();
    }
      std::swap(Elements[qtail],var);
      qtail = (qtail+1)%size;
      qsize++;
   }

   //QueueVec Empty
   template <typename Data>
   inline bool QueueVec<Data>::Empty() const noexcept {
     if(qhead == qtail) {
       return true;
     } else return false;
   }

   //QueueVec Size
   template <typename Data>
   inline ulong QueueVec<Data>::Size() const noexcept {
     return qsize;
   }

   //QueueVec Clear
   template <typename Data>
   void QueueVec<Data>::Clear() {
     qhead = 0;
     qtail = 0;
     qsize = 0;
   }

   template<typename Data>
   void QueueVec<Data>::Expand(){
     ulong newsize = size*2;
     Data* TmpElements = new Data[newsize] {};

     ulong count=0;

    while(count < size){
     for(ulong i = qhead; i<size; i++,count++){
       std::swap(TmpElements[count],Elements[i]);
     }
     if(count < size){
       for(ulong j = 0; j<qtail; j++,count++){
         std::swap(TmpElements[count],Elements[j]);
       }
     }
   }
     std::swap(TmpElements,Elements);
     size = newsize;
     qhead=0;
     qtail = qsize;
     delete []TmpElements;
   }

/* ************************************************************************** */

}
