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
  for (typename T::iterator iter = V.begint(); iter != V.end(); ++iter) {
    std::cout << *iter << " ";
  }
  std::cout << "}" << std::endl;
}

void vector_test() {

}
