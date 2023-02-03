//
// Created by yuumo on 2023/02/03.
//

#include "tester.hpp"

template <typename T>
void pout(T s) {
  static int no;
  std::cout << std::endl;
  std::cout << "=== [" << ++no << "]:" << s << " ===" << std::endl;
}

template <class T>
void vdebug(T& V) {
  std::cout << "size:" << V.size() << " capacity:" << V.capacity() << std::endl;
  std::cout << "{ ";
  for (typename T::iterator iter = V.begin(); iter != V.end(); ++iter) {
    std::cout << *iter << " ";
  }
  std::cout << "}" << std::endl;
}

void vector_construct_test() {
  pout(__func__);

  std::allocator<int> alloc;

  ft::vector<int> v0;
  vdebug(v0);

  ft::vector<int> v1(alloc);
  vdebug(v1);

  ft::vector<int> v2(5, 123, alloc);
  vdebug(v2);

  ft::vector<int> v3(v2.begin() + 1, v2.end());
  vdebug(v3);

  ft::vector<int> v4(v2);
  v4[0] = 100;
  vdebug(v4);
}

void vector_copy_construct_test() {
  pout(__func__);

  ft::vector<int> v1(3, 1);
  ft::vector<int> v2(v1);
  ft::vector<int> v3;
  ft::vector<int> v4(10, 42);
  vdebug(v1);
  vdebug(v2);
  v3 = v2;
  vdebug(v3);
  v4 = v2;
  vdebug(v4);
}

void vector_test() {
  vector_construct_test();
  vector_copy_construct_test();
}
