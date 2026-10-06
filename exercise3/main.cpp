
#include "zlasdtest/test.hpp"

#include "zmytest/test.hpp"

#include "iterator/iterator.hpp"

#include "vector/vector.hpp"

#include "binarytree/binarytree.hpp"

#include "binarytree/vec/binarytreevec.hpp"

#include "binarytree/lnk/binarytreelnk.hpp"

/* ************************************************************************** */

#include <iostream>
#include <random>

/* ************************************************************************** */
using namespace std;
int main() {
  cout << "Lasd Libraries 2022" << endl;
  // SceltaPrincipale();

  //Test Iteratori

  lasd::Vector<int> vec1(4);
  vec1[0]=0;
  vec1[1]=1;
  vec1[2]=2;
  vec1[3]=3;


  lasd::Vector<int> vec2(4);


  lasd::BinaryTreeVec<int> bt1(vec1);

  lasd::BinaryTreeVec<int> bt2(vec2);

  bt2 = bt1;

  std::cout << "Confronto due BinaryTreeVec con copy Assignement:";

  std::cout << (bt1==bt2);



  std::cout << "\n Confronto due BinaryTreeLnk con copy Assignement:";

  lasd::BinaryTreeLnk<int> bt3(vec1);

  lasd::BinaryTreeLnk<int> bt4(vec2);

  bt4 = bt3;

  std::cout << (bt3==bt4);
  std::cout << bt3.Size() << bt4.Size();

  // lasd::BTInOrderIterator<int> itr1(bt);
  //
  // std::cout << *(itr1) << '\n';
  // ++itr1;
  // std::cout << *(itr1) << '\n';
  // ++itr1;
  // std::cout << *(itr1) << '\n';
  // ++itr1;
  // std::cout << *(itr1) << '\n';
  // ++itr1;
  //
  // itr1.Reset();
  // lasd::BTInOrderIterator<int> newitr1(std::move(itr1));
  // itr1.Reset();
  //
  // std::cout << *(itr1) << '\n';
  // ++itr1;
  // std::cout << *(itr1) << '\n';
  // ++itr1;
  // std::cout << *(itr1) << '\n';
  // ++itr1;
  // std::cout << *(itr1) << '\n';
  // ++itr1;


  return 0;
}
