//
// Created by yuumo on 2023/02/02.
//

#include <gtest/gtest.h>
#include <vector>

namespace SimpleVectorTest {

TEST(VectorTest, PushBack) {
  std::vector<int> v;
  v.push_back(1);
  v.push_back(2);
  v.push_back(3);
  EXPECT_EQ(v.size(), 3);
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[1], 2);
  EXPECT_EQ(v[2], 3);
}

TEST(VectorTest, PopBack) {
  std::vector<int> v;
  v.push_back(1);
  v.push_back(2);
  v.push_back(3);
  v.pop_back();
  EXPECT_EQ(v.size(), 2);
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[1], 2);
}

TEST(VectorTest, Clear) {
  std::vector<int> v;
  v.push_back(1);
  v.push_back(2);
  v.push_back(3);
  v.clear();
  EXPECT_EQ(v.size(), 0);
}

TEST(VectorTest, Insert) {
  std::vector<int> v;
  v.push_back(1);
  v.push_back(2);
  v.push_back(3);
  v.insert(v.begin() + 1, 4);
  EXPECT_EQ(v.size(), 4);
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[1], 4);
  EXPECT_EQ(v[2], 2);
  EXPECT_EQ(v[3], 3);
}

TEST(VectorTest, Erase) {
  std::vector<int> v;
  v.push_back(1);
  v.push_back(2);
  v.push_back(3);
  v.erase(v.begin() + 1);
  EXPECT_EQ(v.size(), 2);
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[1], 3);
}

}