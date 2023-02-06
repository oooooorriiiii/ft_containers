//
// Created by yuumo on 2023/02/06.
//

#include <gtest/gtest.h>
#include <stack>

#include "../includes/ft_stack.hpp"

namespace StackTest {
 class StackTest : public ::testing::Test {
  protected:

 };

TEST_F(StackTest, constructor) {
  // ft
  ft::vector<int> ft_v (2,200);        // vector with 2 elements

  ft::stack<int> ft_first;                    // empty stack

  ft::stack<int,ft::vector<int> > ft_third;  // empty stack using vector
  ft::stack<int,ft::vector<int> > ft_fourth (ft_v);

//  std::cout << "size of ft_first: " << ft_first.size() << '\n';
//  std::cout << "size of ft_third: " << ft_third.size() << '\n';
//  std::cout << "size of ft_fourth: " << ft_fourth.size() << '\n';

  // STL
  std::vector<int> std_v (2,200);        // vector with 2 elements

  std::stack<int> std_first;                    // empty stack

  std::stack<int,std::vector<int> > std_third;  // empty stack using vector
  std::stack<int,std::vector<int> > std_fourth (std_v);

//  std::cout << "size of std_first: " << std_first.size() << '\n';
//  std::cout << "size of std_third: " << std_third.size() << '\n';
//  std::cout << "size of std_fourth: " << std_fourth.size() << '\n';

  // TEST
  EXPECT_EQ(ft_first.size(), std_first.size());
  EXPECT_EQ(ft_third.size(), std_third.size());
  EXPECT_EQ(ft_fourth.size(), std_fourth.size());
}

TEST_F(StackTest, empty) {
  // ft
  ft::stack<int> ft_stack;
  int ft_sum(0);

  for (int i = 1; i <= 10; i++) {
    ft_stack.push(i);
  }

  while (!ft_stack.empty()) {
    ft_sum += ft_stack.top();
    ft_stack.pop();
  }

//  std::cout << "total: " << ft_sum << std::endl;

  // STL
  std::stack<int> std_stack;
  int sum(0);

  for (int i = 1; i <= 10; i++) {
    std_stack.push(i);
  }

  while (!std_stack.empty()) {
    sum += std_stack.top();
    std_stack.pop();
  }

//  std::cout << "total: " << sum << std::endl;

  // TEST
  EXPECT_EQ(ft_sum, sum);
}

TEST_F(StackTest, size) {
  // ft
  ft::stack<int> ft_ints;
//  std::cout << "size: " << ft_ints.size() << std::endl;
  for (int i = 0; i < 5; i++) {
    ft_ints.push(i);
  }
//  std::cout << "size: " << ft_ints.size() << std::endl;
  ft_ints.pop();
//  std::cout << "size: " << ft_ints.size() << std::endl;

  // STL
  std::stack<int> std_ints;
//  std::cout << "size: " << std_ints.size() << std::endl;
  for (int i = 0; i < 5; i++) {
    std_ints.push(i);
  }
//  std::cout << "size: " << std_ints.size() << std::endl;
  std_ints.pop();
//  std::cout << "size: " << std_ints.size() << std::endl;

// TEST
  EXPECT_EQ(ft_ints.size(), std_ints.size());
}

TEST_F(StackTest, top) {
  // STL
  ft::stack<int> ft_stack;

  ft_stack.push(10);
  ft_stack.push(20);
  ft_stack.top() -= 5;

//  std::cout << "ft_stack.top: " << ft_stack.top() << std::endl;

  // STL
  std::stack<int> std_stack;

  std_stack.push(10);
  std_stack.push(20);
  std_stack.top() -= 5;

//  std::cout << "std_stack.top: " << std_stack.top() << std::endl;

  // TEST
  EXPECT_EQ(ft_stack.top(), std_stack.top());
}

TEST_F(StackTest, push_pop) {
  // ft
  ft::stack<int> ft_stack;

  for (int i = 0; i < 5; ++i) {
    ft_stack.push(i);
  }

//  std::cout << "Popping out elements...";
  while (!ft_stack.empty()) {
//    std::cout << ' ' << ft_stack.top();
    ft_stack.pop();
  }
//  std::cout << std::endl;

  // STL
  std::stack<int> std_stack;

  for (int i = 0; i < 5; ++i) {
    std_stack.push(i);
  }

//  std::cout << "Popping out elements...";
  while (!std_stack.empty()) {
//    std::cout << ' ' << std_stack.top();
    std_stack.pop();
  }
//  std::cout << std::endl;

  // TEST
  EXPECT_EQ(ft_stack.size(), std_stack.size());
}

TEST_F(StackTest, swap) {
  // ft
  ft::stack<int> ft_foo, ft_bar;
  ft_foo.push(10);
  ft_foo.push(20);
  ft_foo.push(30);
  ft_bar.push(111);
  ft_bar.push(222);
  ft_foo.swap(ft_bar);
//  std::cout << "size: " << ft_foo.size() << std::endl;
//  std::cout << "size: " << ft_bar.size() << std::endl;

  // STL
  std::stack<int> std_foo, std_bar;
  std_foo.push(10);
  std_foo.push(20);
  std_foo.push(30);
  std_bar.push(111);
  std_bar.push(222);
  std_foo.swap(std_bar);
//  std::cout << "size: " << std_foo.size() << std::endl;
//  std::cout << "size: " << std_bar.size() << std::endl;

  // TEST
  EXPECT_EQ(ft_foo.size(), std_foo.size());
  EXPECT_EQ(ft_bar.size(), std_bar.size());
}



}