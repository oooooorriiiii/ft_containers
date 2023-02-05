//
// Created by yuumo on 2023/02/04.
//

#include <gtest/gtest.h>
#include <iterator>

#include "../includes/ft_iterator.hpp"
#include "../includes/ft_vector.hpp"

namespace IteratorSimpleTest{

 class StdIterator : public std::iterator<std::input_iterator_tag, int> {
   int *p;
  public:
   StdIterator(int *x) : p(x) {}
   StdIterator(const StdIterator& mit) : p(mit.p) {}
   StdIterator& operator++() {++p;return *this;}
   StdIterator operator++(int) {StdIterator tmp(*this); operator++(); return tmp;}
   bool operator==(const StdIterator& rhs) const {return p==rhs.p;}
   bool operator!=(const StdIterator& rhs) const {return p!=rhs.p;}
   int& operator*() {return *p;}
 };

class FtIterator : public ft::iterator<std::input_iterator_tag, int> {
  int *p;
 public:
  FtIterator(int *x) : p(x) {}
  FtIterator(const FtIterator& mit) : p(mit.p) {}
  FtIterator& operator++() {++p;return *this;}
  FtIterator operator++(int) {FtIterator tmp(*this); operator++(); return tmp;}
  bool operator==(const FtIterator& rhs) const {return p==rhs.p;}
  bool operator!=(const FtIterator& rhs) const {return p!=rhs.p;}
  int& operator*() {return *p;}
};

TEST(IteratorTest, ALL) {
  // ft
  ft::vector<int> ft_v;
  int ft_numbers[] = {10, 20, 30, 40, 50};
  FtIterator ft_from(ft_numbers);
  FtIterator ft_until(ft_numbers + 5);
  for (FtIterator iter = ft_from; iter != ft_until; iter++) {
    std::cout << *iter << ' ';
    ft_v.push_back(*iter);
  }
  std::cout << std::endl;

  // STL
  std::vector<int> std_v;
  int std_numbers[] = {10, 20, 30, 40, 50};
  StdIterator from(std_numbers);
  StdIterator until(std_numbers + 5);
  for (StdIterator iter = from; iter != until; iter++) {
    std::cout << *iter << ' ';
    std_v.push_back(*iter);
  }
  std::cout << std::endl;

  // TEST
  for (int i = 0; i < ft_v.size(); i++) {
    EXPECT_EQ(ft_v.at(i), std_v.at(i));
  }
}

}

