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
}

int main() {
  tutorial_test();
  return 0;
}
