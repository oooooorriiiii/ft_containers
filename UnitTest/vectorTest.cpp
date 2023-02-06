//
// Created by yuumo on 2023/02/02.
//

#include <gtest/gtest.h>
#include <vector>

#include "../includes/ft_vector.hpp"

namespace VectorTest {
class VectorTest : public ::testing::Test {
 protected:

  template<typename V>
  void print_vector_info(V &vec) {
    std::cout << "*****************" << std::endl;
    std::cout << "Vector capacity: " << vec.capacity() << std::endl;
    std::cout << "Vector size:     " << vec.size() << std::endl;
    std::cout << "Vector elements: ";
    for (const auto &elem : vec) {
      std::cout << elem << " ";
    }
    std::cout << std::endl;
    std::cout << "*****************" << std::endl;
  }
};

TEST_F(VectorTest, Resize) {

  // ft
  ft::vector<int> ft_v;

  for (int i = 1; i < 10; i++) { // ft_v:  1 2 3 4 5 6 7 8 9
    ft_v.push_back(i);
  }
  ft_v.resize(5); // ft_v:  1 2 3 4 5
  ft_v.resize(8, 100); // ft_v:  1 2 3 4 5 100 100 100
  ft_v.resize(12); // ft_v:  1 2 3 4 5 100 100 100 0 0 0 0

  // STL
  std::vector<int> std_v;

  for (int i = 1; i < 10; i++) { // std_v:  1 2 3 4 5 6 7 8 9
    std_v.push_back(i);
  }
  std_v.resize(5); // std_v:  1 2 3 4 5
  std_v.resize(8, 100); // std_v:  1 2 3 4 5 100 100 100
  std_v.resize(12); // std_v:  1 2 3 4 5 100 100 100 0 0 0 0

  // TEST
  for (int i = 0; i < std_v.size(); i++) {
    EXPECT_EQ(ft_v.at(i), std_v.at(i));
  }
  EXPECT_EQ(ft_v.capacity(), std_v.capacity());
}

TEST_F(VectorTest, Resize2) {
  ft::vector<int> ft_v;
  ft_v.resize(5, 42);
  ft_v.resize(6, 42);

  std::vector<int> std_v;
  std_v.resize(5, 42);
  std_v.resize(6, 42);

  for (int i = 0; i < std_v.size(); i++) {
    EXPECT_EQ(ft_v.at(i), std_v.at(i));
  }
}

TEST_F(VectorTest, PushBack) {
  // ft
  ft::vector<int> ft_vec;
  ft_vec.push_back(1);
  ft_vec.push_back(2);
  ft_vec.push_back(3);

  // STL
  std::vector<int> std_vec;
  std_vec.push_back(1);
  std_vec.push_back(2);
  std_vec.push_back(3);

  // TSET
  EXPECT_EQ(ft_vec.size(), std_vec.size());
  EXPECT_EQ(ft_vec[0], std_vec[0]);
  EXPECT_EQ(ft_vec[1], std_vec[1]);
  EXPECT_EQ(ft_vec[2], std_vec[2]);
}

TEST_F(VectorTest, PopBack) {
  ft::vector<int> ft_vec;
  ft_vec.push_back(1);
  ft_vec.push_back(2);
  ft_vec.push_back(3);
  ft_vec.pop_back();

  std::vector<int> std_vec;
  std_vec.push_back(1);
  std_vec.push_back(2);
  std_vec.push_back(3);
  std_vec.pop_back();

  EXPECT_EQ(ft_vec.size(), std_vec.size());
  EXPECT_EQ(ft_vec[0], std_vec[0]);
  EXPECT_EQ(ft_vec[1], std_vec[1]);
  // THROW
  EXPECT_THROW(ft_vec.at(2), std::out_of_range);
  EXPECT_THROW(std_vec.at(2), std::out_of_range);
}

TEST_F(VectorTest, Insert) {
  // FT
  ft::vector<int> ft_v(3, 100);
  ft::vector<int>::iterator ft_iter;
  ft_iter = ft_v.begin(); // 100<- 100 100
//  std::cerr << "ft_iter: " << *ft_v.begin() << std::endl;
//  std::cerr << "ft_iter: " << *ft_iter << std::endl;
  ft_iter = ft_v.insert(ft_iter, 200); // 200<- 100 100 100
  ft_v.insert(ft_iter, 2, 300); // 300<- 300 200 100 100 100
  ft_iter = ft_v.begin(); // 300<- 300 200 100 100 100
  std::vector<int> ft_another_v(2, 400);
  ft_v.insert(ft_iter + 2, ft_another_v.begin(), ft_another_v.end()); // 300 300 400 400 200 100 100 100

  int ft_arr[] = {501, 502, 503};
  ft_v.insert(ft_v.begin(), ft_arr, ft_arr + 3); // 501 502 503 300 300 400 400 200 100 100 100

  // STL
  std::vector<int> std_v(3, 100); // 100 100 100
  std::vector<int>::iterator iter;
  iter = std_v.begin(); // 100<- 100 100
//  std::cerr << "std_iter: " << *iter << std::endl;
  iter = std_v.insert(iter, 200); // 200<- 100 100 100
  std_v.insert(iter, 2, 300); // 300<- 300 200 100 100 100
  iter = std_v.begin(); // 300<- 300 200 100 100 100
  std::vector<int> std_another_v(2, 400);
  std_v.insert(iter + 2, std_another_v.begin(), std_another_v.end()); // 300 300 400 400 200 100 100 100

  int myarray[] = {501, 502, 503};
  std_v.insert(std_v.begin(), myarray, myarray + 3); // 501 502 503 300 300 400 400 200 100 100 100


  // TEST
  for (int i = 0; i < std_v.size(); i++) {
    EXPECT_EQ(ft_v.at(i), std_v.at(i));
  }
  EXPECT_EQ(ft_v.capacity(), std_v.capacity());
}

TEST_F(VectorTest, Clear) {
  ft::vector<int> ft_v;
  ft_v.push_back(1);
  ft_v.push_back(2);
  ft_v.push_back(3);
  ft_v.clear();

  std::vector<int> std_v;
  std_v.push_back(1);
  std_v.push_back(2);
  std_v.push_back(3);
  std_v.clear();

  EXPECT_EQ(ft_v.size(), std_v.size());
}

TEST_F(VectorTest, assign) {
  ft::vector<char> ft_characters;
  ft_characters.assign(5, 'x');
  const std::string ft_extra(6, 'y');
  ft_characters.assign(ft_extra.begin(), ft_extra.end());

  std::vector<char> std_characters;
  std_characters.assign(5, 'x');
  const std::string std_extra(6, 'y');
  std_characters.assign(std_extra.begin(), std_extra.end());

  EXPECT_EQ(ft_characters.size(), std_characters.size());
  EXPECT_EQ(ft_characters.at(5), std_characters.at(5));
}

TEST_F(VectorTest, swap) {
  // ft
  ft::vector<int> ft_foo (3, 100);   // three ints with a value of 100
  ft::vector<int> ft_bar (5, 200);   // five ints with a value of 200

  ft_foo.swap(ft_bar);

  // STL
  std::vector<int> std_foo (3, 100);   // three ints with a value of 100
  std::vector<int> std_bar (5, 200);   // five ints with a value of 200

  std_foo.swap(std_bar);

  // TEST
  for (int i = 0; i < std_foo.size(); i++) {
    EXPECT_EQ(ft_foo.at(i), std_foo.at(i));
  }
  for (int i = 0; i < std_bar.size(); i++) {
    EXPECT_EQ(ft_bar.at(i), std_bar.at(i));
  }
  EXPECT_EQ(ft_foo.capacity(), std_foo.capacity());
  EXPECT_EQ(ft_bar.capacity(), std_bar.capacity());
}

TEST_F(VectorTest, brackets) {
  ft::vector<int> ft_numbers(4);
  for (int i = 0; i < 4; ++i) {
    ft_numbers[i] = (i + 1) * 2;
  }

  std::vector<int> std_numbers(4);
  for (int i = 0; i < 4; ++i) {
    std_numbers[i] = (i + 1) * 2;
  }

  EXPECT_EQ(ft_numbers.at(2), std_numbers.at(2));
}

TEST_F(VectorTest, AtMethodThrowsOutOfRange) {
  // ft
  ft::vector<int> ft_v;
  ft_v.push_back(1);
  ft_v.push_back(2);
  ft_v.push_back(3);

  // STL
  std::vector<int> std_v;
  std_v.push_back(1);
  std_v.push_back(2);
  std_v.push_back(3);

  // TEST
  EXPECT_THROW(ft_v.at(3), std::out_of_range);
  EXPECT_THROW(ft_v.at(46), std::out_of_range);

  EXPECT_THROW(std_v.at(3), std::out_of_range);
  EXPECT_THROW(std_v.at(46), std::out_of_range);
}

TEST_F(VectorTest, MaxSize) {
  ft::vector<int> ft_v;
  std::vector<int> std_v;
//  std::cout << "max_size(): " << ft_v.max_size() << std::endl;
  EXPECT_EQ(ft_v.max_size(), std_v.max_size());
}

TEST_F(VectorTest, operator) {
  // ft
  ft::vector<int> ft_foo;
  ft::vector<int> ft_bar;
  ft_foo.push_back(2);
  ft_bar.push_back(3);
  // TRUE
  EXPECT_TRUE(ft_foo != ft_bar);
  EXPECT_TRUE(ft_foo < ft_bar);
  EXPECT_TRUE(ft_foo <= ft_bar);
  // FALSE
  EXPECT_FALSE(ft_foo == ft_bar);
  EXPECT_FALSE(ft_foo > ft_bar);
  EXPECT_FALSE(ft_foo >= ft_bar);

  // STL
  std::vector<int> std_foo;
  std::vector<int> std_bar;
  std_foo.push_back(2);
  std_bar.push_back(3);
  // TRUE
  EXPECT_TRUE(std_foo != std_bar);
  EXPECT_TRUE(std_foo < std_bar);
  EXPECT_TRUE(std_foo <= std_bar);
  // FALSE
  EXPECT_FALSE(std_foo == std_bar);
  EXPECT_FALSE(std_foo > std_bar);
  EXPECT_FALSE(std_foo >= std_bar);
}

}