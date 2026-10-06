#include "../zlasdtest/test.hpp"
#include "test.hpp"

#include <iostream>
#include <random>

using namespace std;

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

void SceltaStrutturaDati(){

  int scelta;

  cout << "Scegli un'opzione \n 1)Stack \n 2)Queue \n 3)Torna Indietro\n 4)Esci\n";
  cin >> scelta;

  switch(scelta){
    case 1:
      SceltaStack();
    break;

    case 2:
      SceltaQueue();
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


void SceltaStack(){

  int scelta;
  cout << "\n------------------Scegli il Tipo di Stack---------------------";
  cout << "\n 1)StackList \n 2)StackVector \n 3)Torna Indietro\n 4)Esci\n";
  cin >> scelta;

  switch(scelta){
    case 1:
      SceltaTipoStackList();
    break;

    case 2:
      SceltaTipoStackVector();
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

void SceltaTipoStackList(){

  int scelta, n;
  cout << "\n--------------Scegli il Tipo dello StackList-----------------";
  cout << "\n 1)Intero \n 2)Double \n 3)String \n 4)Torna Indietro \n 5)Esci\n";
  cin >> scelta;


  switch(scelta){
    case 1:{
      lasd::StackLst<int> stkint;
      FunzioniStackList(stkint);
    break;}

    case 2:{
      lasd::StackLst<double> stkdouble;
      FunzioniStackList(stkdouble);
    break;}

    case 3:{
      lasd::StackLst<string> stkstring;
      FunzioniStackList(stkstring);
    break;}

    case 4:
      SceltaStrutturaDati();
    break;

    case 5:
      return;
    break;

    default:
      SceltaTipoStackList();
    break;
  }
}

template <typename Data>
void FunzioniStackList(lasd::StackLst<Data>& stklst){

  int scelta;
  cout << "\n--------------Scegli la funzione da eseguire-----------------";
  cout << "\n 1)Riempi lo StackList Randomicamente \n 2)Inserisci un Elemento \n 3)Rimuovi un Elemento \n 4)Rimuovi un Elemento con Lettura \n 5)Stampa Valore in Testa \n 6)Test di Vuotezza \n 7)Stampa la Dimensione dello StackList \n 8)Svuota lo StackList \n 9)Torna Indietro \n 10)Esci\n";
  cin >> scelta;

  switch(scelta) {
    case 1:
      RandomStackList(stklst);
      cout << "-------------------\nStackList Riempito\n-------------------\n";
      FunzioniStackList(stklst);
    break;

    case 2:{
      Data inserimento;
      cout << "-----------------------------\n";
      cout << "Inserisci un Elemento: ";
      cin >> inserimento;
      cout << "-----------------------------\n";
      stklst.Push(inserimento);
      FunzioniStackList(stklst);
    break;}

    case 3:
      try{
        stklst.Pop();
        cout << "----------------------------------------------\n";
        cout << "Ho rimosso l'elemento subito Accessibile \n";
        cout << "----------------------------------------------\n";
      }catch(length_error l){
        cout << "----------------------------------------------\n";
        cout << "Non esiste nessun valore nello StackList \n";
        cout << "----------------------------------------------\n";
      }
      FunzioniStackList(stklst);
    break;

    case 4:
      try{
        Data temp = stklst.TopNPop();
        cout << "----------------------------------------------\n";
        cout << "Ho rimosso: " << temp << endl;
        cout << "----------------------------------------------\n";
      }catch(length_error l){
        cout << "----------------------------------------------\n";
        cout << "Non esiste nessun valore nello StackList \n";
        cout << "----------------------------------------------\n";
      }
      FunzioniStackList(stklst);
    break;

    case 5:
      try{
        Data temp = stklst.Top();
        cout << "-------------------------------------------------\n";
        cout << "L'Elemento subito Accessibile e': " << temp << endl;
        cout << "-------------------------------------------------\n";
      }catch(length_error l){
        cout << "----------------------------------------------\n";
        cout << "Non esiste nessun valore nello StackList \n";
        cout << "----------------------------------------------\n";
      }
      FunzioniStackList(stklst);
    break;

    case 6:
      if(stklst.Size()==0){
        cout << "--------------------------\n";
        cout << "Lo StackList è Vuoto" << endl;
        cout << "--------------------------\n";
      }
      else{
      cout << "-----------------------------\n";
      cout << "Lo StackList non è Vuoto" << endl;
      cout << "-----------------------------\n";
      }
      FunzioniStackList(stklst);
    break;

    case 7:
      cout << "----------------------------------------------\n";
      cout << "La dimensione dello StackList e': " << stklst.Size() << endl;
      cout << "----------------------------------------------\n";
      FunzioniStackList(stklst);
    break;

    case 8:
      stklst.Clear();
      cout << "----------------------------------\n";
      cout << "La Struttura e'stata svuotata" << endl;
      cout << "----------------------------------\n";
      FunzioniStackList(stklst);
    break;

    case 9:
      stklst.Clear();
      SceltaStrutturaDati();
    break;

    case 10:
      stklst.Clear();
      return;
    break;

    default:
      FunzioniStackList(stklst);
    break;

  }
}

template <typename Data>
void RandomStackList(lasd::StackLst<Data>& stklst){

  int n=0;
  cout << "----------------------------------\n";
  cout << "Quanti valori vuoi inserire? : ";
  cin >> n;
  cout << "----------------------------------\n";

  if(typeid(Data)==typeid(int)){
    Data g;

    default_random_engine gen(random_device{}());
    uniform_int_distribution<uint> random (1,1000);

    for(ulong i=0; i<n; i++){
      g=random(gen);
      stklst.Push(g);
    }
  }
  else if(typeid(Data)==typeid(double)){
    Data g;

    default_random_engine gen(random_device{}());
    uniform_real_distribution<double> random (1.00,1000.00);

    for(ulong i=0; i<n; i++){
      g=random(gen);
      stklst.Push(g);
    }
  }
  else if(typeid(Data)==typeid(string)){
    default_random_engine gen(random_device{}());
    uniform_int_distribution<int> random ('a', 'z');

    for(ulong i=0; i<n; i++){
      Data app;
      for(ulong j=0; j<5; j++){
        app+=random(gen);
      }
      stklst.Push(app);
    }
  }
}

void SceltaTipoStackVector(){

  int scelta, n;
  cout << "\n--------------Scegli il Tipo dello StackVector-----------------";
  cout << "\n 1)Intero \n 2)Double \n 3)String \n 4)Torna Indietro \n 5)Esci\n";
  cin >> scelta;


  switch(scelta){
    case 1:{
      lasd::StackVec<int> stkint;
      FunzioniStackVector(stkint);
    break;}

    case 2:{
      lasd::StackVec<double> stkdouble;
      FunzioniStackVector(stkdouble);
    break;}

    case 3:{
      lasd::StackVec<string> stkstring;
      FunzioniStackVector(stkstring);
    break;}

    case 4:
      SceltaStrutturaDati();
    break;

    case 5:
      return;
    break;

    default:
      SceltaTipoStackVector();
    break;
  }
}

template <typename Data>
void FunzioniStackVector(lasd::StackVec<Data>& stkvec){

  int scelta;
  cout << "\n--------------Scegli la Funzione da Eseguire-----------------";
  cout << "\n 1)Riempi lo StackVector Randomicamente \n 2)Inserisci un Elemento \n 3)Rimuovi un Elemento \n 4)Rimuovi un Elemento con Lettura \n 5)Stampa Valore in Testa \n 6)Test di Vuotezza \n 7)Stampa la Dimensione dello StackVector \n 8)Svuota lo StackVector \n 9)Torna Indietro \n 10)Esci\n";
  cin >> scelta;

  switch(scelta) {
    case 1:
      RandomStackVector(stkvec);
      FunzioniStackVector(stkvec);
    break;

    case 2:{
      Data inserimento;
      cout << "----------------------------\n";
      cout << "Inserisci un Elemento: ";
      cin >> inserimento;
      cout << "----------------------------\n";
      stkvec.Push(inserimento);
      FunzioniStackVector(stkvec);
    break;}

    case 3:
      try{
        stkvec.Pop();
        cout << "---------------------------------\n";
        cout << "Ho rimosso l'elemento subito Accessibile \n";
        cout << "---------------------------------\n";
      }catch(length_error l){
        cout << "----------------------------------------------\n";
        cout << "Non esiste nessun valore nello StackVector \n";
        cout << "----------------------------------------------\n";
      }
      FunzioniStackVector(stkvec);
    break;

    case 4:
      try{
        Data temp = stkvec.TopNPop();
        cout << "-------------------------\n";
        cout << "Ho rimosso: " << temp << endl;
        cout << "-------------------------\n";
      }catch(length_error l){
        cout << "------------------------------------------------\n";
        cout << "Non esiste nessun valore nello StackVector \n";
        cout << "------------------------------------------------\n";
      }
      FunzioniStackVector(stkvec);
    break;

    case 5:
      try{
        Data temp = stkvec.Top();
        cout << "--------------------------------------------\n";
        cout << "L'Elemento subito Accessibile e': " << temp << endl;
        cout << "--------------------------------------------\n";
      }catch(length_error l){
        cout << "----------------------------------------------\n";
        cout << "Non esiste nessun valore nello StackVector \n";
        cout << "----------------------------------------------\n";
      }
      FunzioniStackVector(stkvec);
    break;

    case 6:
      if(stkvec.Empty()){
        cout << "----------------------------------------------\n";
        cout << "Lo StackVector è Vuoto" << endl;
        cout << "----------------------------------------------\n";
      }
      else{
        cout << "----------------------------------------------\n";
        cout << "Lo StackVector non è Vuoto" << endl;
        cout << "----------------------------------------------\n";
      }
      FunzioniStackVector(stkvec);
    break;

    case 7:
      cout << "----------------------------------------------\n";
      cout << "La dimensione dello StackVector e': " << stkvec.Size() << endl;
      cout << "----------------------------------------------\n";
      FunzioniStackVector(stkvec);
    break;

    case 8:
      stkvec.Clear();
      cout << "----------------------------------------------\n";
      cout << "La Struttura e'stata svuotata" << endl;
      cout << "----------------------------------------------\n";
      SceltaStrutturaDati();
    break;

    case 9:
      stkvec.Clear();
      SceltaStrutturaDati();
    break;

    case 10:
      stkvec.Clear();
      return;
    break;

    default:
      FunzioniStackVector(stkvec);
    break;

  }
}

template <typename Data>
void RandomStackVector(lasd::StackVec<Data>& stkvec){

  int n=0;
  cout << "--------------------------------------------\n";
  cout << "Quanti valori vuoi inserire? : ";
  cin >> n;
  cout << "--------------------------------------------\n";

  if(typeid(Data)==typeid(int)){
    Data g;

    default_random_engine gen(random_device{}());
    uniform_int_distribution<uint> random (1,1000);

    for(ulong i=0; i<n; i++){
      g=random(gen);
      stkvec.Push(g);
    }
  }
  else if(typeid(Data)==typeid(double)){
    Data g;

    default_random_engine gen(random_device{}());
    uniform_real_distribution<double> random (1.00,1000.00);

    for(ulong i=0; i<n; i++){
      g=random(gen);
      stkvec.Push(g);
    }
  }
  else if(typeid(Data)==typeid(string)){
    default_random_engine gen(random_device{}());
    uniform_int_distribution<int> random ('a', 'z');

    for(ulong i=0; i<n; i++){
      Data app;
      for(ulong j=0; j<5; j++){
        app+=random(gen);
      }
      stkvec.Push(app);
    }
  }
}


void SceltaQueue(){

  int scelta;
  cout << "\n--------------Scegli un'opzione-----------------";
  cout << "\n 1)QueueList \n 2)QueueVector \n 3)Torna Indietro\n 4)Esci\n";
  cin >> scelta;

  switch(scelta){
    case 1:
      SceltaTipoQueueList();
    break;

    case 2:
      SceltaTipoQueueVector();
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

void SceltaTipoQueueList(){

  int scelta, n;
  std::cout << "\n--------------Scegli la funzione da eseguire-----------------";
  cout << "\n 1)Intero \n 2)Double \n 3)String \n 4)Torna Indietro \n 5)Esci\n";
  cin >> scelta;


  switch(scelta){
    case 1:{
      lasd::QueueLst<int> queint;
      FunzioniQueueList(queint);
    break;}

    case 2:{
      lasd::QueueLst<double> quedouble;
      FunzioniQueueList(quedouble);
    break;}

    case 3:{
      lasd::QueueLst<string> questring;
      FunzioniQueueList(questring);
    break;}

    case 4:
      SceltaStrutturaDati();
    break;

    case 5:
      return;
    break;

    default:
      SceltaTipoQueueList();
    break;
  }
}

template <typename Data>
void FunzioniQueueList(lasd::QueueLst<Data>& quelst){

  int scelta;
  Data g;
  cout << "\n--------------Scegli la funzione da eseguire-----------------";
  cout << "\n 1)Riempi la QueueList Randomicamente \n 2)Inserisci un Elemento \n 3)Rimuovi un Elemento \n 4)Rimuovi un Elemento con Lettura \n 5)Stampa Valore in Testa \n 6)Test di Vuotezza \n 7)Stampa la Dimensione della QueueList \n 8)Svuota la QueueList \n 9)Torna Indietro \n 10)Esci\n";
  cin >> scelta;

  switch(scelta) {
    case 1:
      RandomQueueList(quelst);
      FunzioniQueueList(quelst);
    break;

    case 2:{
      Data inserimento;
      cout << "---------------------------------\n";
      cout << "Inserisci un Elemento: ";
      cin >> inserimento;
      cout << "---------------------------------\n";
      quelst.Enqueue(inserimento);
      FunzioniQueueList(quelst);
    break;}

    case 3:
      try{
        quelst.Dequeue();
        cout << "---------------------------------\n";
        cout << "Ho rimosso l'elemento in Testa ";
        cout << "\n---------------------------------\n";
      }catch(length_error l){
        cout << "------------------------------------------\n";
        cout << "Non esiste nessun valore nella QueueList";
        cout << "\n------------------------------------------\n";
      }
      FunzioniQueueList(quelst);
    break;

    case 4:
      try{
        Data temp = quelst.HeadNDequeue() ;
        cout << "---------------------------------\n";
        cout << "Ho rimosso: " << temp;
        cout << "\n---------------------------------\n";
      }catch(length_error l){
        cout << "--------------------------------------------\n";
        cout << "Non esiste nessun valore nella QueueList";
        cout << "\n--------------------------------------------\n";
      }
      FunzioniQueueList(quelst);
    break;

    case 5:
      try{
        Data temp = quelst.Head();
        cout << "--------------------------------------------\n";
        cout << "L'Elemento subito Accessibile e': " << temp;
        cout << "\n--------------------------------------------\n";
      }catch(length_error l){
        cout << "--------------------------------------------\n";
        cout << "Non esiste nessun valore nella QueueList";
        cout << "\n--------------------------------------------\n";
      }
      FunzioniQueueList(quelst);
    break;

    case 6:
      if(quelst.Size()==0){
        cout << "---------------------------\n";
        cout << "La QueueList è Vuota";
        cout << "\n---------------------------\n";
      }
      else{
        cout << "---------------------------\n";
        cout << "La QueueList non e'Vuota";
        cout << "\n---------------------------\n";
      }
      FunzioniQueueList(quelst);
    break;

    case 7:
      cout << "----------------------------------------\n";
      cout << "La dimensione della QueueList e': " << quelst.Size();
      cout << "\n----------------------------------------\n";
      FunzioniQueueList(quelst);
    break;

    case 8:
      quelst.Clear();
      cout << "----------------------------------------\n";
      cout << "La Struttura e'stata svuotata";
      cout << "\n----------------------------------------\n";
      FunzioniQueueList(quelst);
    break;

    case 9:
      quelst.Clear();
      SceltaStrutturaDati();
    break;

    case 10:
      quelst.Clear();
      return;
    break;

    default:
      FunzioniQueueList(quelst);
    break;

  }
}

template <typename Data>
void RandomQueueList(lasd::QueueLst<Data>& quelst){

  int n=0;
  cout << "--------------------------------------\n";
  cout << "Quanti valori vuoi inserire? : ";
  cin >> n;
  cout << "\n--------------------------------------\n";

  if(typeid(Data)==typeid(int)){
    Data g;

    default_random_engine gen(random_device{}());
    uniform_int_distribution<uint> random (1,1000);

    for(ulong i=0; i<n; i++){
      g=random(gen);
      quelst.Enqueue(g);
    }
  }
  else if(typeid(Data)==typeid(double)){
    Data g;

    default_random_engine gen(random_device{}());
    uniform_real_distribution<double> random (1.00,1000.00);

    for(ulong i=0; i<n; i++){
      g=random(gen);
      quelst.Enqueue(g);
    }
  }
  else if(typeid(Data)==typeid(string)){
    default_random_engine gen(random_device{}());
    uniform_int_distribution<int> random ('a', 'z');

    for(ulong i=0; i<n; i++){
      Data app;
      for(ulong j=0; j<5; j++){
        app+=random(gen);
      }
      quelst.Enqueue(app);
    }
  }
}


void SceltaTipoQueueVector(){

  int scelta, n;
  cout << "\n--------------Scegli il Tipo della QueueVector-----------------";
  cout << "\n 1)Intero \n 2)Double \n 3)String \n 4)Torna Indietro \n 5)Esci\n";
  cin >> scelta;


  switch(scelta){
    case 1:{
      lasd::QueueVec<int> queint;
      FunzioniQueueVector(queint);
    break;}

    case 2:{
      lasd::QueueVec<double> quedouble;
      FunzioniQueueVector(quedouble);
    break;}

    case 3:{
      lasd::QueueVec<string> questring;
      FunzioniQueueVector(questring);
    break;}

    case 4:
      SceltaStrutturaDati();
    break;

    case 5:
      return;
    break;

    default:
      SceltaTipoQueueVector();
    break;
  }
}

template <typename Data>
void FunzioniQueueVector(lasd::QueueVec<Data>& quevec){

  int scelta;
  Data g;
  cout << "\n--------------Scegli la funzione da eseguire-----------------";
  cout << "\n 1)Riempi la QueueVector Randomicamente \n 2)Inserisci un Elemento \n 3)Rimuovi un Elemento \n 4)Rimuovi un Elemento con Lettura \n 5)Stampa Valore in Testa \n 6)Test di Vuotezza \n 7)Stampa la Dimensione della QueueVector \n 8)Svuota la QueueVector \n 9)Torna Indietro \n 10)Esci\n";
  cin >> scelta;

  switch(scelta) {
    case 1:
      RandomQueueVector(quevec);
      FunzioniQueueVector(quevec);
    break;

    case 2:{
      Data inserimento;
      cout << "------------------------------\n";
      cout << "Inserisci un Elemento: ";
      cin >> inserimento;
      cout << "------------------------------\n";
      quevec.Enqueue(inserimento);
      FunzioniQueueVector(quevec);
    break;}

    case 3:
      try{
        quevec.Dequeue();
        cout << "---------------------------------\n";
        cout << "Ho rimosso l'elemento in Testa ";
        cout << "\n---------------------------------\n";
      }catch(length_error l){
        cout << "-------------------------------------------------\n";
        cout << "Non esiste nessun valore nella QueueVector \n";
        cout << "-------------------------------------------------\n";
      }
      FunzioniQueueVector(quevec);
    break;

    case 4:
      try{
        Data temp = quevec.HeadNDequeue();
        cout << "-----------------------\n";
        cout << "Ho rimosso: " << temp << endl;
        cout << "-----------------------\n";
      }catch(length_error l){
        cout << "----------------------------------------------------\n";
        cout << "Non esiste nessun valore nella QueueVector \n";
        cout << "----------------------------------------------------\n";
      }
      FunzioniQueueVector(quevec);
    break;

    case 5:
      try{
        Data temp = quevec.Head();
        cout << "----------------------------------------------------\n";
        cout << "L'Elemento in Testa e': " << temp << endl;
        cout << "----------------------------------------------------\n";
      }catch(length_error l){
        cout << "----------------------------------------------------\n";
        cout << "Non esiste nessun valore nella QueueVector \n";
        cout << "----------------------------------------------------\n";
      }
      FunzioniQueueVector(quevec);
    break;

    case 6:
      if(quevec.Empty()){
        cout << "--------------------------------\n";
        cout << "La QueueVector è Vuota" << endl;
        cout << "--------------------------------\n";
      }
      else{
        cout << "----------------------------------------------------\n";
        cout << "La QueueVector non e'Vuota" << endl;
        cout << "----------------------------------------------------\n";
      }
      FunzioniQueueVector(quevec);
    break;

    case 7:
      cout << "---------------------------------------\n";
      cout << "La dimensione della QueueVector e': " << quevec.Size() << endl;
      cout << "---------------------------------------\n";
      FunzioniQueueVector(quevec);
    break;

    case 8:
      quevec.Clear();
      cout << "---------------------------------------\n";
      cout << "La Struttura e'stata svuotata" << endl;
      cout << "---------------------------------------\n";
      SceltaStrutturaDati();
    break;

    case 9:
      quevec.Clear();
      SceltaStrutturaDati();
    break;

    case 10:
      quevec.Clear();
      return;
    break;

    default:
      FunzioniQueueVector(quevec);
    break;

  }
}

template <typename Data>
void RandomQueueVector(lasd::QueueVec<Data>& quevec){

  int n=0;
  cout << "-------------------------------------\n";
  cout << "Quanti valori vuoi inserire? : ";
  cin >> n;
  cout << "\n-------------------------------------\n";

  if(typeid(Data)==typeid(int)){
    Data g;

    default_random_engine gen(random_device{}());
    uniform_int_distribution<uint> random (1,1000);

    for(ulong i=0; i<n; i++){
      g=random(gen);
      quevec.Enqueue(g);
    }
  }
  else if(typeid(Data)==typeid(double)){
    Data g;

    default_random_engine gen(random_device{}());
    uniform_real_distribution<double> random (1.00,1000.00);

    for(ulong i=0; i<n; i++){
      g=random(gen);
      quevec.Enqueue(g);
    }
  }
  else if(typeid(Data)==typeid(string)){
    default_random_engine gen(random_device{}());
    uniform_int_distribution<int> random ('a', 'z');

    for(ulong i=0; i<n; i++){
      Data app;
      for(ulong j=0; j<5; j++){
        app+=random(gen);
      }
      quevec.Enqueue(app);
    }
  }
}

// ...
