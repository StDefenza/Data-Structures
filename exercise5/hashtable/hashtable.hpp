
#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP

/* ************************************************************************** */

#include <random>
#include <string>

/* ************************************************************************** */

#include "../container/container.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */



template <typename Data>
class Hash {

public:

  ulong operator()(const int&) const noexcept; // (concrete function should not throw exceptions)
  ulong operator()(const double&) const noexcept;
  ulong operator()(const std::string&) const noexcept;

};

/* ************************************************************************** */

template <typename Data>
class HashTable : virtual public DictionaryContainer<Data>,
                  virtual public MappableContainer<Data>,
                  virtual public FoldableContainer<Data>{ // Must extend DictionaryContainer<Data>,
                                                          //             MappableContainer<Data>,
                                                          //             FoldableContainer<Data>

private:

  // ...

protected:

  using DictionaryContainer<Data>::size;
  ulong tsize = 65537;
  ulong primo = 77557;
  ulong a=0;
  ulong b=0;
  //Hash<Data> encode;

public:

  // Destructor
  virtual ~HashTable() = default;

  // Comparison operators
  bool operator==(const HashTable&) const noexcept = delete; // Comparison of abstract binary tree is possible.
  bool operator!=(const HashTable&) const noexcept = delete; // Comparison of abstract binary tree is possible.

  /* ************************************************************************ */

  // Specific member function

  virtual void Resize(const ulong) = 0; // Resize the hashtable to a given size

protected:

  /* ************************************************************************ */

  //Constructor
  HashTable();

  //Copy Constructor
  HashTable(const HashTable&);

  //Move Constructor
  HashTable(HashTable&&) noexcept;

  // Copy assignment
  HashTable& operator=(const HashTable&); // Copy assignment of abstract types should not be possible.

  // Move assignment
  HashTable& operator=(HashTable&&) noexcept; // Move assignment of abstract types should not be possible.

  /* ************************************************************************ */

  // Auxiliary member functions

  ulong HashKey(const Data&) const noexcept;

};

/* ************************************************************************** */

}

#include "hashtable.cpp"

#endif
