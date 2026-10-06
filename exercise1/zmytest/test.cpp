
#include "../zlasdtest/test.hpp"
#include "../vector/vector.hpp"
#include "test.hpp"


#include <iostream>
#include <random>
#include <algorithm>

using namespace std;

/* ************************************************************************** */

void SceltaPrincipale(){
  int scelta;

  cout << "--------------Scegli un'opzione-----------------";
  cout << "\n 1)Stuttura Dati \n 2)Esegui Test \n 3)Esci\n";
  cin >> scelta;

  switch(scelta) {
    case 1:
      SceltaStrutturaDati();
    break;

    case 2:
      lasdtest();
      SceltaPrincipale();
    break;

    case 3:
      return;
    break;

    default:
      SceltaPrincipale();
    break;
  }
}



template <typename Data>
void MapPrint(const Data& dat, void* _){
  std::cout << dat << std::endl;
}

template <>
void FunzioneMap(int& dat, void* _){
  dat = 2*dat;
}

template <>
void FunzioneMap(double& dat, void* _){
  dat = dat * dat;
}

template <>
void FunzioneMap(string& dat, void* val){
  transform(dat.begin(), dat.end(), dat.begin(), ::toupper);
}

template <>
void FunzioneFold(const int& dat, const void* val, void* acc){
  if (dat < *((int*) val)) {
    *((int*) acc) += dat;
  }
}

template <>
void FunzioneFold(const double& dat, const void* val, void* acc){
  if (dat > *((int*) val)) {
    *((double*) acc) *= dat;
  }
}

template <>
void FunzioneFold(const string& dat, const void* val, void* acc){
  if (dat.length() <= *((int*) val)) {
    *((string*) acc) += dat;
  }
}




template <typename Data>
void FunzioniLista(lasd::List<Data>& lst){

  int scelta;
  Data g;
  cout << "\n--------------Scegli la funzione da eseguire-----------------";
  cout << "\n 1)Riempi la Lista Randomicamente \n 2)Stampa la Lista \n 3)Visualizza Elemento in Testa/Coda/Indice \n 4)Inserisci un Valore \n 5)Rimuovi un Valore \n 6)Verifica l'Esistenza di un Valore  \n 7)Applica Funzione Map \n 8)Applica Funzione Fold \n 9)Torna Indietro \n 10)Esci\n";
  cin >> scelta;

  switch(scelta) {
    case 1:
      RandomLista(lst);
      FunzioniLista(lst);
    break;

    case 2:
      cout << "----------------------------------------------------\n";
      lst.MapPreOrder(MapPrint<Data>,0);
      cout << "\n----------------------------------------------------\n";
      FunzioniLista(lst);
    break;

    case 3:
      SearchList(lst);
      FunzioniLista(lst);
    break;

    case 4:
      InserisciValore(lst);
      FunzioniLista(lst);
    break;

    case 5:
      RimuoviValore(lst);
      FunzioniLista(lst);
    break;

    case 6:{
      Data g;
      cout << "--------------------------------------";
      cout << "\nInserisci un valore: ";
      cin >> g;
      if(lst.Exists(g)){
      cout << "L'elemento è presente nella Lista" << endl;
      cout << "--------------------------------------\n";
      }
      else {
        cout << "\nL'elemento non è presente nella Lista" << endl;
        cout << "--------------------------------------\n";
      }
    }
    FunzioniLista(lst);
    break;

    case 7:{
      int n = 0;
      std::cout << "\n--------------Scegli la funzione da eseguire-----------------";
      std::cout << "\n 1)PreOrder \n 2)PostOrder\n";
      std::cin >> n;
      if(n==1){
        lst.MapPreOrder(&FunzioneMap<Data>, nullptr);
        cout << "--------------------------------------";
        std::cout << "\nFunzione in PreOrder Applicata";
        cout << "\n--------------------------------------\n";
      }else if (n==2){
        lst.MapPostOrder(&FunzioneMap<Data>, nullptr);
        cout << "--------------------------------------";
        std::cout << "\nFunzione in PostOrder Applicata";
        cout << "\n--------------------------------------\n";
      }
      FunzioniLista(lst);
    }
    break;

    case 8:{
      int n,m = 0;
      std::cout << "\n--------------Scegli la funzione da eseguire-----------------";
      std::cout << "\n 1)PreOrder \n 2)PostOrder\n";
      std::cin >> n;
      cout << "--------------------------------------------------";
      std::cout << "\nInserisci il parametro per la Funzione: ";
      std::cin >> m;
      if(n==1){
        if(typeid(Data)==typeid(int)){
          int a = 0;
          lst.FoldPreOrder(&FunzioneFold<Data>, &m, &a);
          std::cout << "\nFunzione in PreOrder Applicata";
          std::cout << "Il Risultato e': " << a << std::endl;
          cout << "--------------------------------------------------\n";
        }
        else if(typeid(Data)==typeid(double)){
          double a = 1;
          lst.FoldPreOrder(&FunzioneFold<Data>, &m, &a);
          std::cout << "\nFunzione in PreOrder Applicata";
          std::cout << "\nIl Risultato e': " << a << std::endl;
          cout << "--------------------------------------------------\n";
        }
        else if(typeid(Data)==typeid(string)){
          string a = "";
          lst.FoldPreOrder(&FunzioneFold<Data>, &m, &a);
          std::cout << "\nFunzione in PreOrder Applicata";
          std::cout << "\nIl Risultato e': " << a << std::endl;
          cout << "--------------------------------------------------\n";
        }
      }else if (n==2){
        if(typeid(Data)==typeid(int)){
          int a = 0;
          lst.FoldPostOrder(&FunzioneFold<Data>, &m, &a);
          std::cout << "\nFunzione in PostOrder Applicata";
          std::cout << "\nIl Risultato e': " << a << std::endl;
          cout << "--------------------------------------------------\n";
        }
        else if(typeid(Data)==typeid(double)){
          double a = 1;
          lst.FoldPostOrder(&FunzioneFold<Data>, &m, &a);
          std::cout << "\nFunzione in PostOrder Applicata";
          std::cout << "\nIl Risultato e': " << a << std::endl;
          cout << "--------------------------------------------------\n";
        }
        else if(typeid(Data)==typeid(string)){
          string a = "";
          lst.FoldPostOrder(&FunzioneFold<Data>, &m, &a);
          std::cout << "\nFunzione in PostOrder Applicata";
          std::cout << "\nIl Risultato e': " << a << std::endl;
          cout << "--------------------------------------------------\n";
        }
      }
      FunzioniLista(lst);
    }
    break;

    case 9:
      lst.Clear();
      SceltaStrutturaDati();
    break;

    case 10:
      lst.Clear();
      return;
    break;

    default:
      FunzioniLista(lst);
    break;
  }
}

template <typename Data>
void FunzioniVettore(lasd::Vector<Data>& vec){

  int scelta;
  Data g;
  std::cout << "\n--------------Scegli la funzione da eseguire-----------------";
  cout << "\n\n 1)Riempi il Vettore Randomicamente \n 2)Stampa il Vettore \n 3)Visualizza Elemento Iniziale/Finale/Indice \n 4)Verifica l'Esistenza di un Valore \n 5)Resize \n 6)Applica Funzione Map \n 7)Applica Funzione Fold \n 8)Torna Indietro \n 9)Esci\n";
  cin >> scelta;

  switch(scelta) {
    case 1:
      RandomVettore(vec);
      cout << "-----------------------\nVettore Riempito\n-----------------------\n";
      FunzioniVettore(vec);
    break;

    case 2:
      cout << "-----------------------\n";
      vec.MapPreOrder(MapPrint<Data>,0);
      cout << "\n-----------------------\n";
      FunzioniVettore(vec);
    break;

    case 3:
      SearchVettore(vec);
      FunzioniVettore(vec);
    break;

    case 4:{
      Data g;
      cout << "\nInserisci un valore: ";
      cin >> g;
      if(vec.Exists(g)){
      cout << "L'elemento è presente nel Vettore" << endl;
      }
      else cout << "L'elemento non è presente nel Vettore" << endl;
      FunzioniVettore(vec);
    }
    break;

    case 5:{
      int n;
      cout << "\nInserisci la nuova dimensione: ";
      cin >> n;
      vec.Resize(n);
      cout << "-----------------------------------------";
      cout << "\nLa nuova dimensione del vettore e': " << n << endl;
      cout << "-----------------------------------------\n";
      FunzioniVettore(vec);
    }
    break;

    case 6:{
      int n = 0;
      std::cout << "\n--------------Scegli la funzione da eseguire-----------------";
      std::cout << "\n 1)PreOrder \n 2)PostOrder\n";
      std::cin >> n;
      if(n==1){
        vec.MapPreOrder(&FunzioneMap<Data>, nullptr);
        cout << "--------------------------------------";
        std::cout << "\nFunzione in PreOrder Applicata";
        cout << "\n--------------------------------------\n";
      }else if (n==2){
        vec.MapPostOrder(&FunzioneMap<Data>, nullptr);
        cout << "--------------------------------------";
        std::cout << "\nFunzione in PostOrder Applicata";
        cout << "\n--------------------------------------\n";
      }
      FunzioniVettore(vec);
    }
    break;

    case 7:{
      int n,m = 0;
      std::cout << "\n--------------Scegli la funzione da eseguire-----------------";
      std::cout << "\n 1)PreOrder \n 2)PostOrder\n";
      std::cin >> n;
      cout << "--------------------------------------------------";
      std::cout << "\nInserisci il parametro per la Funzione: ";
      std::cin >> m;
      if(n==1){
        if(typeid(Data)==typeid(int)){
          int a = 0;
          vec.FoldPreOrder(&FunzioneFold<Data>, &m, &a);
          std::cout << "\nFunzione in PreOrder Applicata";
          std::cout << "\nIl Risultato e': " << a << std::endl;
          cout << "--------------------------------------------------\n";
        }
        else if(typeid(Data)==typeid(double)){
          double a = 1;
          vec.FoldPreOrder(&FunzioneFold<Data>, &m, &a);
          std::cout << "\nFunzione in PreOrder Applicata";
          std::cout << "\nIl Risultato e': " << a << std::endl;
          cout << "--------------------------------------------------\n";
        }
        else if(typeid(Data)==typeid(string)){
          string a = "";
          vec.FoldPreOrder(&FunzioneFold<Data>, &m, &a);
          std::cout << "\nFunzione in PreOrder Applicata";
          std::cout << "\nIl Risultato e': " << a << std::endl;
          cout << "--------------------------------------------------\n";
        }
      }else if (n==2){
        if(typeid(Data)==typeid(int)){
          int a = 0;
          vec.FoldPostOrder(&FunzioneFold<Data>, &m, &a);
          std::cout << "\nFunzione in PostOrder Applicata";
          std::cout << "\nIl Risultato e': " << a << std::endl;
          cout << "--------------------------------------------------\n";
        }
        else if(typeid(Data)==typeid(double)){
          double a = 1;
          vec.FoldPostOrder(&FunzioneFold<Data>, &m, &a);
          std::cout << "\nFunzione in PostOrder Applicata";
          std::cout << "\nIl Risultato e': " << a << std::endl;
          cout << "--------------------------------------------------\n";
        }
        else if(typeid(Data)==typeid(string)){
          string a = "";
          vec.FoldPostOrder(&FunzioneFold<Data>, &m, &a);
          std::cout << "\nFunzione in PostOrder Applicata";
          std::cout << "\nIl Risultato e': " << a << std::endl;
          cout << "--------------------------------------------------\n";
        }
      }
      FunzioniVettore(vec);
    }
    break;

    case 8:
      vec.Clear();
      SceltaStrutturaDati();
    break;

    case 9:
      vec.Clear();
      return;
    break;

    default:
      FunzioniVettore(vec);
    break;
  }
}

template <typename Data>
void SearchVettore(lasd::Vector<Data>& vec){

  int scelta, g;
  std::cout << "\n--------------Scegli la funzione da eseguire-----------------";
  cout << "\n 1)Stampa l'Elemento Iniziale \n 2)Stampa l'Elemento Finale \n 3)Stampa un indice preso in input \n 4)Torna Indietro \n 5)Esci\n";
  cin >> scelta;

  switch(scelta) {
    case 1:
      try{
        cout << "------------\n";
        cout << vec.Front() << endl;
        cout << "------------\n";
      }catch(length_error l){
        cout << "--------------------------------------\n";
        cout << "Non esiste nessun valore nel Vettore ";
        cout << "\n--------------------------------------\n";
      }
    break;

    case 2:
      try{
        cout << "------------\n";
        cout << vec.Back() << endl;
        cout << "------------\n";
      }catch(length_error l){
        cout << "--------------------------------------\n";
        cout << "Non esiste nessun valore nel Vettore ";
        cout << "\n--------------------------------------\n";
      }
    break;

    case 3:
      cout << "\nInserisci un indice: ";
      cin >> g;
      try{
        cout << "------------\n";
        cout << vec[g] << endl;
        cout << "------------\n";
      }
      catch(out_of_range o){
          cout << "-----------------------------------\n";
        cout << "Hai sforato il limite del Vettore";
          cout << "\n-----------------------------------\n";
      }
      catch(length_error l){
        cout << "-----------------------------------\n";
        cout << "Hai sforato il limite del Vettore";
        cout << "\n-----------------------------------\n";
      }
    break;

    case 4:
    break;

    case 5:
      vec.Clear();
      return;
    break;

    default:
      SearchVettore(vec);
    break;
  }
}

template <typename Data>
void SearchList(lasd::List<Data>& lst){

  int scelta, g;
  std::cout << "\n--------------Scegli la funzione da eseguire-----------------";
  cout << "\n 1)Stampa la Testa \n 2)Stampa la Coda \n 3)Stampa un indice preso in input \n 4)Torna Indietro \n 5)Esci\n";
  cin >> scelta;

  switch(scelta) {
    case 1:
      try{
        cout << "-----------------------\n";
        cout << lst.Front() << endl;
        cout << "-----------------------\n";
      }catch(length_error l){
        cout << "--------------------------------------\n";
        cout << "Non esiste nessun valore nella Lista ";
        cout << "\n--------------------------------------\n";
      }
    break;

    case 2:
      try{
        cout << "-----------------------\n";
        cout << lst.Back() << endl;
        cout << "-----------------------\n";
      }catch(length_error l){
        cout << "--------------------------------------\n";
        cout << "Non esiste nessun valore nella Lista ";
        cout << "\n--------------------------------------\n";
      }
    break;

    case 3:
      cout << "\nInserisci un indice: ";
      cin >> g;
      try{
        cout << "--------------\n";
        cout << lst[g] << endl;
        cout << "--------------\n";
      }
      catch(out_of_range o){
        cout << "-----------------------------------\n";
        cout << "Hai sforato il limite della Lista";
        cout << "\n-----------------------------------\n";
      }
      catch(length_error l){
        cout << "-----------------------------------\n";
        cout << "Hai sforato il limite della Lista";
        cout << "\n-----------------------------------\n";
      }
    break;

    case 4:
    break;

    case 5:
      lst.Clear();
      return;
    break;

    default:
      SearchList(lst);
    break;
  }
}

template <typename Data>
void InserisciValore(lasd::List<Data>& lst){

  int scelta;
  Data g;
  std::cout << "\n--------------Scegli la funzione da eseguire-----------------";
  cout << "\n 1)Inserire in Testa \n 2)Inserire in Coda \n 3)Torna Indietro \n 4)Esci\n";
  cin >> scelta;

  switch(scelta) {

    case 1:
      cout << "-----------------------------";
      cout << "\nInserisci un valore: ";
      cin >> g;
      cout << "-----------------------------\n";
      lst.InsertAtFront(g);
    break;

    case 2:
      cout << "-----------------------------";
      cout << "\nInserisci un valore: ";
      cin >> g;
      cout << "-----------------------------\n";
      lst.InsertAtBack(g);
    break;

    case 3:
    break;

    case 4:
      lst.Clear();
      return;
    break;

    default:
      InserisciValore(lst);
    break;
  }
}

template <typename Data>
void RimuoviValore(lasd::List<Data>& lst){

  int scelta;
  std::cout << "\n--------------Scegli la funzione da eseguire-----------------";
  cout << "\n 1)Rimuovi un elemento \n 2)Rimuovi un elemento con Print \n 3)Torna Indietro \n 4)Esci\n";
  cin >> scelta;

  switch(scelta) {

    case 1:
      try{
        cout << "-------------------------------\n";
        lst.RemoveFromFront();
        cout << "L'elemento è stato rimosso";
        cout << "\n-------------------------------\n";
      }
      catch(length_error l){
        cout << "-----------------------\n";
        cout << "La Lista è vuota";
        cout << "\n-----------------------\n";
      }
    break;

    case 2:
      try{
        cout << "------------------------------\n";
        cout << lst.FrontNRemove() << " è stato Rimosso" << endl;
        cout << "------------------------------\n";
      }
      catch(length_error l){
        cout << "-----------------------\n";
        cout << "La Lista è vuota";
        cout << "\n-----------------------\n";
      }
    break;

    case 3:
    break;

    case 4:
      lst.Clear();
      return;
    break;

    default:
      RimuoviValore(lst);
    break;
  }
}

template <typename Data>
void RandomVettore(lasd::Vector<Data>& vec){

  if(typeid(Data)==typeid(int)){
    Data g;

    default_random_engine gen(random_device{}());
    uniform_int_distribution<uint> random (1,1000);

    try{
      for(ulong i=0; i<vec.Size(); i++){
        g=random(gen);
        vec[i]=g;
      }
    }
    catch(out_of_range o){
      cout << "Hai superato il limite";
    }
  }
    else if(typeid(Data)==typeid(double)){
      Data g;

      default_random_engine gen(random_device{}());
      uniform_real_distribution<double> random (1.00,1000.00);

      try{
        for(ulong i=0; i<vec.Size(); i++){
          g=random(gen);
          vec[i]=g;
        }
      }
      catch(out_of_range o){
        cout << "Hai superato il limite";
      }
    }
    else if(typeid(Data)==typeid(string)){

      default_random_engine gen(random_device{}());
      uniform_int_distribution<int> random ('a', 'z');
      uniform_int_distribution<uint> random1 (1,26);
      int r = 0;

      try{
        for(ulong i=0; i<vec.Size(); i++){
          Data app;
          r=random1(gen);
          for(ulong j=0; j<r; j++){
            app+=random(gen);
          }
          vec[i]=app;
        }
      }catch(out_of_range o){
        cout << "Hai superato il limite";
      }
    }
}

template <typename Data>
void RandomLista(lasd::List<Data>& lst){

  int n=0;
  cout << "--------------------------------------";
  cout << "\nQuanti valori vuoi inserire? : ";
  cin >> n;
  cout << "--------------------------------------\n";


  if(typeid(Data)==typeid(int)){
    Data g;

    default_random_engine gen(random_device{}());
    uniform_int_distribution<uint> random (1,1000);

    for(ulong i=0; i<n; i++){
      g=random(gen);
      lst.InsertAtBack(g);
    }
  }
  else if(typeid(Data)==typeid(double)){
    Data g;

    default_random_engine gen(random_device{}());
    uniform_real_distribution<double> random (1.00,1000.00);

    for(ulong i=0; i<n; i++){
      g=random(gen);
      lst.InsertAtBack(g);
    }
  }
  else if(typeid(Data)==typeid(string)){
    default_random_engine gen(random_device{}());
    uniform_int_distribution<int> random ('a', 'z');
    uniform_int_distribution<uint> random1 (1,26);
    int r = 0;

    for(ulong i=0; i<n; i++){
      Data app;
      r=random1(gen);
      for(ulong j=0; j<r; j++){
        app+=random(gen);
      }
      lst.InsertAtBack(app);
    }
  }
}

void SceltaStrutturaDati(){

  int scelta;
  std::cout << "\n--------------Scegli la funzione da eseguire-----------------";
  cout << "\n 1)Vettore \n 2)Lista \n 3)Torna Indietro\n 4)Esci\n";
  cin >> scelta;

  switch(scelta){
    case 1:
      SceltaTipoVettore();
    break;

    case 2:
      SceltaTipoLista();
    break;

    case 3:
      SceltaPrincipale();
    break;

    case 4:
      return;
    break;

    default:
      SceltaStrutturaDati();
    break;
  }
}

void SceltaTipoVettore(){

  int scelta, n;
  std::cout << "\n--------------Scegli la funzione da eseguire-----------------";
  cout << "\n 1)Intero \n 2)Double \n 3)String \n 4)Torna Indietro \n 5)Esci\n";
  cin >> scelta;


  switch(scelta){
    case 1:{
      cout << "\nScegli la Grandezza del Vettore: ";
      cin >> n;
      lasd::Vector<int> vettint(n);
      FunzioniVettore(vettint);
    break;}

    case 2:{
      cout << "\nScegli la Grandezza del Vettore: ";
      cin >> n;
      lasd::Vector<double> vettdouble(n);
      FunzioniVettore(vettdouble);
    break;}

    case 3:{
      cout << "\nScegli la Grandezza del Vettore: ";
      cin >> n;
      lasd::Vector<string> vettstring(n);
      FunzioniVettore(vettstring);
    break;}

    case 4:
      SceltaStrutturaDati();
    break;

    case 5:
      return;
    break;

    default:
      SceltaTipoVettore();
    break;
  }
}

void SceltaTipoLista(){

  int scelta;
  std::cout << "\n--------------Scegli la funzione da eseguire-----------------";
  cout << "\n 1)Intero \n 2)Double \n 3)String \n 4)Torna Indietro \n 5)Esci\n";
  cin >> scelta;

  switch(scelta) {
    case 1:{
      lasd::List<int> lstint;
      FunzioniLista(lstint);
    break;
    }

    case 2:{
      lasd::List<double> lstdouble;
      FunzioniLista(lstdouble);
    break;
    }

    case 3:{
      lasd::List<string> lststring;
      FunzioniLista(lststring);
    break;
    }

    case 4:
      SceltaStrutturaDati();
    break;

    case 5:
      return;
    break;

    default:
      SceltaTipoLista();
    break;
  }
}
