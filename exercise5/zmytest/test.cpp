#include "../zlasdtest/test.hpp"
#include "test.hpp"

#include <iostream>
#include <random>

using namespace std;

void SceltaPrincipale(){
  int scelta;

  cout << "--------------Scegli un'opzione-----------------";
  cout << "\n 1)Crea un HashTable \n 2)Esegui Test \n 3)Esci\n";
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
void FunzioneFold(const int& dat, const void* val, void* acc){
  if (dat < *((int*) val)) {
    *((int*) acc) *= dat;
  }
}

template <>
void FunzioneFold(const double& dat, const void* val, void* acc){
  if (dat > *((int*) val)) {
    *((double*) acc) += dat;
  }
}

template <>
void FunzioneFold(const string& dat, const void* val, void* acc){
  if (dat.length() <= *((int*) val)) {
    *((string*) acc) += dat;
  }
}

void SceltaStrutturaDati(){

  int scelta;
  std::cout << "\n--------------Scegli la funzione da eseguire-----------------";
  cout << "\n 1)HashTable Close Address \n 2)HashTable Open Address \n 3)Torna Indietro\n 4)Esci\n";
  cin >> scelta;

  switch(scelta){
    case 1:
      SceltaTipoCLS();
    break;

    case 2:
      SceltaTipoOPN();
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

void SceltaTipoCLS(){

  int scelta, n, m;
  cout << "\n--------------Scegli il Tipo di HashTableClsAdr-----------------";
  cout << "\n 1)Intero \n 2)Double \n 3)String \n 4)Torna Indietro \n 5)Esci\n";
  cin >> scelta;



  switch(scelta){
    case 1:{
      cout << "\nScegli la Grandezza del Vettore: ";
      cin >> n;
      lasd::Vector<int> vec(n);
      RandomHash(vec);
      cout << "\nScegli la Grandezza della HashTable: ";
      cin >> m;
      lasd::HashTableClsAdr<int> cls(m, vec);
      FunzioniCLS(cls);
    break;}

    case 2:{
      cout << "\nScegli la Grandezza del Vettore: ";
      cin >> n;
      lasd::Vector<double> vec(n);
      RandomHash(vec);
      cout << "\nScegli la Grandezza della HashTable: ";
      cin >> m;
      lasd::HashTableClsAdr<double> cls(m, vec);
      FunzioniCLS(cls);
    break;}

    case 3:{
      cout << "\nScegli la Grandezza del Vettore: ";
      cin >> n;
      lasd::Vector<string> vec(n);
      RandomHash(vec);
      cout << "\nScegli la Grandezza della HashTable: ";
      cin >> m;
      lasd::HashTableClsAdr<string> cls(m, vec);
      FunzioniCLS(cls);
    break;}

    case 4:
      SceltaTipoCLS();
    break;

    case 5:
      return;
    break;

    default:
      SceltaTipoCLS();
    break;
  }
}

template <typename Data>
  void RandomHash(lasd::Vector<Data>& vec){

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
  void FunzioniCLS(lasd::HashTableClsAdr<Data>& ht){

    int scelta;
    Data g, el;
    std::cout << "\n--------------Scegli la funzione da eseguire-----------------";
    cout << "\n\n 1)Stampa il Vettore \n 2)Verifica l'Esistenza di un Valore \n 3)Insersci un Elemento \n 4)Elimina un elemento \n 5)Applica Funzione Fold \n 6)Torna Indietro \n 7)Esci\n";
    cin >> scelta;

    switch(scelta) {

      case 1:
        cout << "-----------------------\n";
        ht.Map(MapPrint<Data>,0);
        cout << "\n-----------------------\n";
        FunzioniCLS(ht);
      break;

      case 2:{
        Data g;
        cout << "\nInserisci un valore: ";
        cin >> g;
        if(ht.Exists(g)){
          cout << "------------------------------------------ \n Il Valore è presente nella HashTable\n------------------------------------------";
        }
        else cout << "------------------------------------------ \n Il Valore non è presente nella HashTable\n------------------------------------------";
        FunzioniCLS(ht);
      }
      break;

      case 3:{
        cout << "Inserisci il Valore: ";
        cin >> el;
        if(ht.Exists(el)){
          cout << "------------------------------------------ \n Il Valore già è presente nella HashTable\n------------------------------------------";
        }
        else {
          ht.Insert(el);
        cout << "--------------------------------- \n Il Valore è stato Inserito\n---------------------------------";
        }
        FunzioniCLS(ht);
      }
      break;

      case 4:{
        cout << "Inserisci il Valore da Rimuovere: ";
        cin >> el;
        if(ht.Exists(el)) {
          ht.Remove(el);
          cout << "--------------------------- \n Il Valore è stato Rimosso\n---------------------------";
        }
        else cout << "------------------------- \n Il Valore Non esiste\n-------------------------";
        FunzioniCLS(ht);
      }
      break;

      case 5:{
        int n,m = 0;
        cout << "--------------------------------------------------";
        std::cout << "\nInserisci il parametro per la Funzione: ";
        std::cin >> m;
          if(typeid(Data)==typeid(int)){
            int a = 1;
            ht.Fold(&FunzioneFold<Data>, &m, &a);
            std::cout << "\nFunzione Fold Applicata";
            std::cout << "\nIl Risultato e': " << a << std::endl;
            cout << "--------------------------------------------------\n";
          }
          else if(typeid(Data)==typeid(double)){
            double a = 0;
            ht.Fold(&FunzioneFold<Data>, &m, &a);
            std::cout << "\nFunzione Fold Applicata";
            std::cout << "\nIl Risultato e': " << a << std::endl;
            cout << "--------------------------------------------------\n";
          }
          else if(typeid(Data)==typeid(string)){
            string a = "";
            ht.Fold(&FunzioneFold<Data>, &m, &a);
            std::cout << "\nFunzione Fold Applicata";
            std::cout << "\nIl Risultato e': " << a << std::endl;
            cout << "--------------------------------------------------\n";
          }
        FunzioniCLS(ht);
      }
      break;

      case 6:
        ht.Clear();
        SceltaStrutturaDati();
      break;

      case 7:
        ht.Clear();
        return;
      break;

      default:
        FunzioniCLS(ht);
      break;
    }
  }

  void SceltaTipoOPN(){

    int scelta, n, m;
    cout << "\n--------------Scegli il Tipo di HashTableOpnAdr-----------------";
    cout << "\n 1)Intero \n 2)Double \n 3)String \n 4)Torna Indietro \n 5)Esci\n";
    cin >> scelta;



    switch(scelta){
      case 1:{
        cout << "\nScegli la Grandezza del Vettore: ";
        cin >> n;
        lasd::Vector<int> vec(n);
        RandomHash(vec);
        cout << "\nScegli la Grandezza della HashTable: ";
        cin >> m;
        lasd::HashTableOpnAdr<int> opn(m, vec);
        FunzioniOPN(opn);
      break;}

      case 2:{
        cout << "\nScegli la Grandezza del Vettore: ";
        cin >> n;
        lasd::Vector<double> vec(n);
        RandomHash(vec);
        cout << "\nScegli la Grandezza della HashTable: ";
        cin >> m;
        lasd::HashTableOpnAdr<double> opn(m, vec);
        FunzioniOPN(opn);
      break;}

      case 3:{
        cout << "\nScegli la Grandezza del Vettore: ";
        cin >> n;
        lasd::Vector<string> vec(n);
        RandomHash(vec);
        cout << "\nScegli la Grandezza della HashTable: ";
        cin >> m;
        lasd::HashTableOpnAdr<string> opn(m, vec);
        FunzioniOPN(opn);
      break;}

      case 4:
        SceltaTipoOPN();
      break;

      case 5:
        return;
      break;

      default:
        SceltaTipoOPN();
      break;
    }
  }

  template <typename Data>
  void FunzioniOPN(lasd::HashTableOpnAdr<Data>& ht){

    int scelta;
    Data g, el;
    std::cout << "\n--------------Scegli la funzione da eseguire-----------------";
    cout << "\n\n 1)Stampa il Vettore \n 2)Verifica l'Esistenza di un Valore \n 3)Insersci un Elemento \n 4)Elimina un elemento \n 5)Applica Funzione Fold \n 6)Torna Indietro \n 7)Esci\n";
    cin >> scelta;

    switch(scelta) {

      case 1:
        cout << "-----------------------\n";
        ht.Map(MapPrint<Data>,0);
        cout << "\n-----------------------\n";
        FunzioniOPN(ht);
      break;

      case 2:{
        Data g;
        cout << "\nInserisci un valore: ";
        cin >> g;
        if(ht.Exists(g)){
          cout << "------------------------------------------ \n Il Valore è presente nella HashTable\n------------------------------------------";
        }
        else cout << "------------------------------------------ \n Il Valore non è presente nella HashTable\n------------------------------------------";
        FunzioniOPN(ht);
      }
      break;

      case 3:{
        cout << "Inserisci il Valore: ";
        cin >> el;
        if(ht.Exists(el)){
          cout << "------------------------------------------ \n Il Valore già è presente nella HashTable\n------------------------------------------";
        }
        else {
          ht.Insert(el);
          cout << "--------------------------------- \n Il Valore è stato Inserito\n---------------------------------";
        }
        FunzioniOPN(ht);
      }
      break;

      case 4:{
        cout << "Inserisci il Valore da Rimuovere: ";
        cin >> el;
        if(ht.Exists(el)) {
          ht.Remove(el);
          cout << "--------------------------- \n Il Valore è stato Rimosso\n---------------------------";
        }
        else cout << "------------------------- \n Il Valore Non esiste\n-------------------------";
        FunzioniOPN(ht);
      }
      break;

      case 5:{
        int n,m = 0;
        cout << "--------------------------------------------------";
        std::cout << "\nInserisci il parametro per la Funzione: ";
        std::cin >> m;
          if(typeid(Data)==typeid(int)){
            int a = 1;
            ht.Fold(&FunzioneFold<Data>, &m, &a);
            std::cout << "\nFunzione Fold Applicata";
            std::cout << "\nIl Risultato e': " << a << std::endl;
            cout << "--------------------------------------------------\n";
          }
          else if(typeid(Data)==typeid(double)){
            double a = 0;
            ht.Fold(&FunzioneFold<Data>, &m, &a);
            std::cout << "\nFunzione Fold Applicata";
            std::cout << "\nIl Risultato e': " << a << std::endl;
            cout << "--------------------------------------------------\n";
          }
          else if(typeid(Data)==typeid(string)){
            string a = "";
            ht.Fold(&FunzioneFold<Data>, &m, &a);
            std::cout << "\nFunzione Fold Applicata";
            std::cout << "\nIl Risultato e': " << a << std::endl;
            cout << "--------------------------------------------------\n";
          }
        FunzioniOPN(ht);
      }
      break;

      case 6:
        ht.Clear();
        SceltaStrutturaDati();
      break;

      case 7:
        ht.Clear();
        return;
      break;

      default:
        FunzioniOPN(ht);
      break;
    }
  }
