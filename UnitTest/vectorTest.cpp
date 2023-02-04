//
// Created by yuumo on 2023/02/02.
//

#include <gtest/gtest.h>
#include <vector>

#include "../includes/ft_vector.hpp"

namespace SimpleVectorTest {

TEST(VectorTest, PushBack) {
  ft::vector<int> ft_vec;
  ft_vec.push_back(1);
  ft_vec.push_back(2);
  ft_vec.push_back(3);

  std::vector<int> std_vec;
  std_vec.push_back(1);
  std_vec.push_back(2);
  std_vec.push_back(3);

  EXPECT_EQ(ft_vec.size(), std_vec.size());
  EXPECT_EQ(ft_vec[0], std_vec[0]);
  EXPECT_EQ(ft_vec[1], std_vec[1]);
  EXPECT_EQ(ft_vec[2], std_vec[2]);
}

TEST(VectorTest, PopBack) {
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

TEST(VectorTest, Clear) {
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

TEST(VectorTest, assign) {
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

TEST(VectorTest, brackets) {
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

TEST(VectorTest, AtMethodThrowsOutOfRange) {
  ft::vector<int> ft_v;
  ft_v.push_back(1);
  ft_v.push_back(2);
  ft_v.push_back(3);

  EXPECT_THROW(ft_v.at(3), std::out_of_range);
  EXPECT_THROW(ft_v.at(46), std::out_of_range);
}

TEST(VectorTest, MaxSize) {
  ft::vector<int> ft_v;
  std::vector<int> std_v;
//  std::cout << "max_size(): " << ft_v.max_size() << std::endl;
  EXPECT_EQ(ft_v.max_size(), std_v.max_size());
}


//TEST(VectorTest, PopBack) {
//  ft::vector<int> v;
//  v.push_back(1);
//  v.push_back(2);
//  v.push_back(3);
//  v.pop_back();
//  EXPECT_EQ(v.size(), 2);
//  EXPECT_EQ(v[0], 1);
//  EXPECT_EQ(v[1], 2);
//}

//TEST(VectorTest, Insert) {
//  ft::vector<int> v;
//  v.push_back(1);
//  v.push_back(2);
//  v.push_back(3);
//  v.insert(v.begin() + 1, 4);
//  EXPECT_EQ(v.size(), 4);
//  EXPECT_EQ(v[0], 1);
//  EXPECT_EQ(v[1], 4);
//  EXPECT_EQ(v[2], 2);
//  EXPECT_EQ(v[3], 3);
//}

//TEST(VectorTest, Erase) {
//  ft::vector<int> v;
//  v.push_back(1);
//  v.push_back(2);
//  v.push_back(3);
//  v.erase(v.begin() + 1);
//  EXPECT_EQ(v.size(), 2);
//  EXPECT_EQ(v[0], 1);
//  EXPECT_EQ(v[1], 3);
//}

}