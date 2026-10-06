
#ifndef MYTEST_HPP
#define MYTEST_HPP
#include "../zlasdtest/test.hpp"
#include "../vector/vector.hpp"
#include "../list/list.hpp"


/* ************************************************************************** */

void SceltaPrincipale();

void SceltaStrutturaDati();

/*PROTOTIPI VETTORI */

void SceltaTipoVettore();

template <typename Data>
void FunzioniVettore(lasd::Vector<Data>&);

template <typename Data>
void RandomVettore(lasd::Vector<Data>&);

template <typename Data>
void SearchVettore(lasd::Vector<Data>&);

/*FUNZIONI MAP E FOLD*/

template <typename Data>
void FunzioneMap(Data&, void*);

template <typename Data>
void FunzioneFold(const Data&, const void*, void*);



/*PROTOTIPI LISTE */

void SceltaTipoLista();

template <typename Data>
void FunzioniLista(lasd::List<Data>&);

template <typename Data>
void RandomLista(lasd::List<Data>&);

template <typename Data>
void SearchList(lasd::List<Data>&);

template <typename Data>
void InserisciValore(lasd::List<Data>&);

template <typename Data>
void RimuoviValore(lasd::List<Data>&);




/* ************************************************************************** */


#endif
