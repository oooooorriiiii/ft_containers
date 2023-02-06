//
// Created by yuumo on 2023/02/06.
//

#ifndef FT_CONTAINERS_INCLUDES_FT_STACK_HPP_
#define FT_CONTAINERS_INCLUDES_FT_STACK_HPP_

#include "ft_vector.hpp"

namespace ft {
template<typename T, typename C = ft::vector<T>>
class stack {
 public:
  typedef typename C::value_type value_type;
  typedef typename C::reference reference;
  typedef typename C::const_reference const_reference;
  typedef typename C::size_type size_type;
  typedef C container_type;
 public:
  stack(const C &c = container_type()) : c(c) {}
//      explicit stack(C&& = C{});
  stack(const stack &other) : c(other.c) {}
  ~stack() {}
  stack &operator=(const stack &other) {
    c = other.c;
    return *this;
  }

  bool empty() const { return c.empty(); }
  size_type size() const { return c.size(); }
  reference top() { return c.back(); }
  const_reference top() const { return c.back(); }
  void push(const value_type &x) { c.push_back(x); }
  void push(value_type &&x) { c.push_back(std::move(x)); }
  void pop() { c.pop_back(); }

  void swap(stack &s) {
    using std::swap;
    swap(c, s.c);
  }

 protected:
  C c;
};

template <class T, class C>
inline void swap(stack<T, C> &lhs, stack<T, C> &rhs) {
  lhs.swap(rhs);
}
}

#endif //FT_CONTAINERS_INCLUDES_FT_STACK_HPP_
