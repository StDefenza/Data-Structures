
#ifndef MYTEST_HPP
#define MYTEST_HPP

#include "../zlasdtest/test.hpp"
#include "../hashtable/clsadr/htclsadr.hpp"
#include "../hashtable/opnadr/htopnadr.hpp"
#include "../vector/vector.hpp"

/* ************************************************************************** */

void SceltaPrincipale();

void SceltaStrutturaDati();

template <typename Data>
void RandomHash(lasd::Vector<Data>&);

template <typename Data>
void FunzioneMap(Data&, void*);

template <typename Data>
void FunzioneFold(const Data&, const void*, void*);

/*PROTOTIPI HASHMAPCLS */

void SceltaTipoCLS();

template <typename Data>
void FunzioniCLS(lasd::HashTableClsAdr<Data>&);

/*PROTOTIPI HASHMAPOPN */

void SceltaTipoOPN();

template <typename Data>
void FunzioniOPN(lasd::HashTableOpnAdr<Data>&);

/* ************************************************************************** */

#endif
