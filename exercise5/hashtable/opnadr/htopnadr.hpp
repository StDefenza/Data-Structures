
#ifndef HTOPNADR_HPP
#define HTOPNADR_HPP

/* ************************************************************************** */

#include "../hashtable.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class HashTableOpnAdr : virtual public HashTable<Data>{ // Must extend HashTable<Data>

private:

  // ...

protected:

  using HashTable<Data>::tsize;
  using HashTable<Data>::size;
  using HashTable<Data>::HashKey;
  using HashTable<Data>::primo;
  using HashTable<Data>::a;
  using HashTable<Data>::b;
  Vector<Data> vec;
  Vector<char> stato;
  ulong c = 59;

public:


  // Default constructor
  HashTableOpnAdr();

  /* ************************************************************************ */

  // Specific constructors
  HashTableOpnAdr(const ulong); // A hash table of a given size
  HashTableOpnAdr(const LinearContainer<Data>&); // A hash table obtained from a LinearContainer
  HashTableOpnAdr(const ulong, const LinearContainer<Data>&); // A hash table of a given size obtained from a LinearContainer

  /* ************************************************************************ */

  // Copy constructor
  HashTableOpnAdr(const HashTableOpnAdr&);

  // Move constructor
  HashTableOpnAdr(HashTableOpnAdr&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~HashTableOpnAdr() = default;

  /* ************************************************************************ */

  // Copy assignment
  HashTableOpnAdr& operator=(const HashTableOpnAdr&);

  // Move assignment
  HashTableOpnAdr& operator=(HashTableOpnAdr&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const HashTableOpnAdr&) const noexcept;
  bool operator!=(const HashTableOpnAdr&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from HashTable)

  void Resize(const ulong) override; // Resize the hashtable to a given size

  /* ************************************************************************ */

  // Specific member functions (inherited from DictionaryContainer)

  void Insert(const Data&) override; // Override DictionaryContainer member (Copy of the value)
  void Insert(Data&&) noexcept override; // Override DictionaryContainer member (Move of the value)
  void Remove(const Data&) override; // Override DictionaryContainer member

  /* ************************************************************************ */

  // Specific member functions (inherited from TestableContainer)

  bool Exists(const Data&) const noexcept override; // Override TestableContainer member

  /* ************************************************************************ */

  // Specific member functions (inherited from MappableContainer)
  using typename MappableContainer<Data>::MapFunctor;

  void Map(MapFunctor, void*) override; // Override MappableContainer member


  /* ************************************************************************ */

  // Specific member functions (inherited from FoldableContainer)
  using typename FoldableContainer<Data>::FoldFunctor;

  void Fold(const FoldFunctor, const void*, void*) const override; // Override FoldableContainer member

  /* ************************************************************************ */

  // Specific member functions (inherited from Container)

  void Clear() override; // Override Container member

protected:

  // Auxiliary member functions

   //Find();
   //Remove();
   ulong FindEmpty(ulong) const noexcept;
   ulong HashKey(const ulong&, const Data&) const noexcept;
   ulong FindNearestPrimeNumber(ulong) const;
   bool isPrime(const ulong&) const;

};

/* ************************************************************************** */

}

#include "htopnadr.cpp"

#endif
