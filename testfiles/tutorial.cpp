//
// Created by yuumo on 2023/02/02.
//

#include "tester.hpp"
#include <array>

template <typename T>
void pout(T s) {
  static int no;
  std::cout << std::endl;
  std::cout << "===[" << "]:" << s << "===" << std::endl;
}

void tutorial_test() {
  std::cout << "TEST" << std::endl;
  {
    ft::vector<int> v(1);
    auto i = v.begin();
    *i = 0;
    auto const& cv = v;
    auto ci = cv.begin();
    std::cout << *ci << std::endl;
  }
  {
    ft::vector<int> v(1);
    auto i = v.cbegin();
    std::cout << *i << std::endl;
  }
  {
    ft::vector<int> v;
    for (int i = 1; i <= 5; ++i) {
      v.push_back(i);
    }
    auto i = v.begin();
    std::cout << *i << std::endl;

    auto r = v.rbegin();
    std::cout << *r << std::endl;
  }
  {
    ft::vector<int> v;
    bool a = v.empty();
    std::cout << a << std::endl;
    v.push_back(0);
    bool b = v.empty();
    std::cout << b << std::endl;
    auto s = v.size();
    std::cout << s << std::endl;
    auto c = v.capacity();
    std::cout << c << std::endl;
  }
  {
    ft::vector<int> v;
    for (int i = 1; i <= 5; ++i) {
      v.push_back(i);
    }
    std::cout << "expected: 2" << v[1] << std::endl;
    std::cout << "expected: 4" << v[3] << std::endl;
  }
  {
    try {
      ft::vector<int> v;
      for (int i = 1; i <= 5; ++i) {
        v.push_back(i);
      }
      std::cout << "expected: 2" << v[0] << std::endl;
      std::cout << "expected: 4" << v[3] << std::endl;
      std::cout << "error: " << v[5] << std::endl;
    } catch (std::out_of_range e) {
      std::cout << e.what() << std::endl;
    }
  }
  {
    ft::vector<int> v;
    for (int i = 1; i <= 5; ++i) {
      v.push_back(i);
    }
    std::cout << "front(): " << v.front() << std::endl;
    std::cout << "back(): " << v.back() << std::endl;
  }
  {
    ft::vector<int> v;
    for (int i = 1; i <= 3; ++i) {
      v.push_back(i);
    }
    int* ptr = v.data();
    std::cout << "*ptr: " << *ptr << std::endl;
  }
  {
    ft::vector<int> v;
    std::cout << "empty: " << v.empty() << std::endl;
  }
  {
    ft::vector<int> v(100);
    std::cout << "size: " << v.size() << std::endl;
  }
  {
    ft::vector<int> v(100, 42);
    std::cout << "v[0]: " << v[0] << std::endl;
    std::cout << "v[42]: " << v[42] << std::endl;
    std::cout << "v[99]: " << v[99] << std::endl;
  }
  {
    ft::vector<int> v;
    v.resize(10);
    std::cout << "size: " << v.size() << std::endl;
    v.resize(5);
    std::cout << "size: " << v.size() << std::endl;
  }
  {
    ft::vector<int> v;
    v.resize(3, 123);
    std::cout << "v[0]: " << v[0] << std::endl;
    std::cout << "size: " << v.size() << std::endl;
  }
  {
    ft::vector<int> v;
    v.reserve(3);
    std::cout << "size: " << v.size() << std::endl;
    std::cout << "capacity: " << v.capacity() << std::endl;
    v.push_back(1);
    v.push_back(1);
    v.push_back(1);
    v.push_back(1);
    std::cout << "size: " << v.size() << std::endl;
    std::cout << "capacity: " << v.capacity() << std::endl;
  }
  {
    ft::vector<int> v;
    for (int i = 1; i <= 3; ++i) {
      v.push_back(i);
    }
    v.clear();
    std::cout << "size: " << v.size() << std::endl;
  }
  {
    std::allocator<int> alloc;
    ft::vector<int> v1(alloc);
    ft::vector<int> v3(5, 123, alloc);
  }
  {
    std::array<int, 5> a{1, 2, 3, 4, 5};
    ft::vector<int> v(std::begin(a), std::end(a));
    std::cout << "v[0]: " << v[0] << std::endl;
    std::cout << "v[1]: " << v[1] << std::endl;
    std::cout << "v[2]: " << v[2] << std::endl;
  }
  {
    ft::vector<int> v;
    for(int i = 1; i <= 5; ++i) {
      v.push_back(i);
    }
    ft::vector<int> w = v;
    std::cout << "w[0]: " << w[0] << std::endl;
    std::cout << "w[1]: " << w[1] << std::endl;
    std::cout << "w[2]: " << w[2] << std::endl;
  }
  std::cout << "FIN" << std::endl;
}

int main() {
  tutorial_test();
  return 0;
}
