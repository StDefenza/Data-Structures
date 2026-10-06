
#ifndef MYTEST_HPP
#define MYTEST_HPP
#include "../zlasdtest/test.hpp"
#include "../stack/lst/stacklst.hpp"
#include "../stack/stack.hpp"
#include "../stack/vec/stackvec.hpp"

#include "../queue/lst/queuelst.hpp"
#include "../queue/queue.hpp"
#include "../queue/vec/queuevec.hpp"

/* ************************************************************************** */

void SceltaPrincipale();

void SceltaStrutturaDati();


/*PROTOTIPI STACK */

void SceltaStack();

void SceltaTipoStackList();

template <typename Data>
void FunzioniStackList(lasd::StackLst<Data>&);

template <typename Data>
void RandomStackList(lasd::StackLst<Data>&);


void SceltaTipoStackVector();

template <typename Data>
void FunzioniStackVector(lasd::StackVec<Data>&);

template <typename Data>
void RandomStackVector(lasd::StackVec<Data>&);


/*PROTOTIPI QUEUE */

void SceltaQueue();

void SceltaTipoQueueList();

template <typename Data>
void FunzioniQueueList(lasd::QueueLst<Data>&);

template <typename Data>
void RandomQueueList(lasd::QueueLst<Data>&);


void SceltaTipoQueueVector();

template <typename Data>
void FunzioniQueueVector(lasd::QueueVec<Data>&);

template <typename Data>
void RandomQueueVector(lasd::QueueVec<Data>&);

/* ************************************************************************** */

#endif
