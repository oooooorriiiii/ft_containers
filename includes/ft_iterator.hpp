//
// Created by yuumo on 2023/02/03.
//

#ifndef FT_CONTAINERS_INCLUDES_FT_ITERATOR_HPP_
#define FT_CONTAINERS_INCLUDES_FT_ITERATOR_HPP_

#include <cstddef>

namespace ft {
struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag : public input_iterator_tag {};
struct bidirectional_iterator_tag : public forward_iterator_tag {};
struct random_access_iterator_tag : public bidirectional_iterator_tag {};

template<class Iterator>
struct iterator_traits {
  typedef typename Iterator::iterator_category iterator_category;
  typedef typename Iterator::value_type value_type;
  typedef typename Iterator::difference_type difference_type;
  typedef typename Iterator::pointer pointer;
  typedef typename Iterator::reference reference;
};

template<class T>
struct iterator_traits<T *> {
  typedef ptrdiff_t difference_type;
  typedef T value_type;
  typedef T *pointer;
  typedef T &reference;
  typedef ft::random_access_iterator_tag iterator_category;
};

template<class T>
struct iterator_traits<const T *> {
  typedef ptrdiff_t difference_type;
  typedef T value_type;
  typedef T *pointer;
  typedef T &reference;
  typedef ft::random_access_iterator_tag iterator_category;
};

template<class Category, class T, class Distance = std::ptrdiff_t, class Pointer = T *, class Reference = T &>
struct iterator {
  typedef Category iterator_category;
  typedef T value_type;
  typedef Distance difference_type;
  typedef Pointer pointer;
  typedef Reference reference;
};

/*
 * reverse_iterator
 */

template<class Iter>
class reverse_iterator
    : public iterator<typename ft::iterator_traits<Iter>::iterator_category,
                      typename ft::iterator_traits<Iter>::value_type,
                      typename ft::iterator_traits<Iter>::difference_type,
                      typename ft::iterator_traits<Iter>::pointer,
                      typename ft::iterator_traits<Iter>::reference> {
 protected:
  Iter _current;
  typedef ft::iterator_traits<Iter> traits_type;

 public:
  typedef Iter iterator_type;
  typedef typename traits_type::iterator_category iterator_category;
  typedef typename traits_type::value_type value_type;
  typedef typename traits_type::difference_type difference_type;
  typedef typename traits_type::pointer pointer;
  typedef typename traits_type::reference reference;

  reverse_iterator() : _current() {}
  explicit reverse_iterator(iterator_type x) : _current(x) {}
  template<class U>
  reverse_iterator(const reverse_iterator<U> &other) : _current(other.base()) {}

  template<class U>
  reverse_iterator &operator=(const ft::reverse_iterator<U> &other) {
    _current = other.base();
    return *this;
  }

  virtual ~reverse_iterator() {}

  /*
   *
   */

  iterator_type base() const { return _current; }

  /*
   *
   */

  reference operator*() const {
    Iter rv = _current;
    return *(--rv);
  }
  pointer operator->() const {
    return &(operator*());
  }
  reference operator[](difference_type n) const {
    return *(*this + n);
  }
  reverse_iterator &operator++() {
    --_current;
    return *this;
  }
  reverse_iterator &operator++(int) {
    reverse_iterator rv(*this);
    ++(*this);
    return rv;
  }
  reverse_iterator &operator--() {
    ++_current;
    return *this;
  }
  reverse_iterator &operator--(int) {
    reverse_iterator rv(*this);
    --(*this);
    return rv;
  }
  reverse_iterator operator+(difference_type n) const {
    return reverse_iterator(_current - n);
  }
  reverse_iterator operator-(difference_type n) const {
    return reverse_iterator(_current + n);
  }
  reverse_iterator &operator+=(difference_type n) {
    _current -= n;
    return *this;
  }
  reverse_iterator &operator-=(difference_type n) {
    _current += n;
    return *this;
  }
};

/*
 *
 */

template<class Iterator1, class Iterator2>
bool operator==(const ft::reverse_iterator<Iterator1> &lhs,
                const ft::reverse_iterator<Iterator2> &rhs) {
  return lhs.base() == rhs.base();
}
template<class Iterator1, class Iterator2>
bool operator!=(const ft::reverse_iterator<Iterator1> &lhs,
                const ft::reverse_iterator<Iterator2> &rhs) {
  return lhs.base() != rhs.base();
}
template<class Iterator1, class Iterator2>
bool operator<(const ft::reverse_iterator<Iterator1> &lhs,
               const ft::reverse_iterator<Iterator2> &rhs) {
  return lhs.base() > rhs.base();
}
template<class Iterator1, class Iterator2>
bool operator>(const ft::reverse_iterator<Iterator1> &lhs,
               const ft::reverse_iterator<Iterator2> &rhs) {
  return lhs.base() < rhs.base();
}
template<class Iterator1, class Iterator2>
bool operator<=(const ft::reverse_iterator<Iterator1> &lhs,
                const ft::reverse_iterator<Iterator2> &rhs) {
  return lhs.base() >= rhs.base();
}
template<class Iterator1, class Iterator2>
bool operator>=(const ft::reverse_iterator<Iterator1> &lhs,
                const ft::reverse_iterator<Iterator2> &rhs) {
  return lhs.base() <= rhs.base();
}

/*
 * random_access_iterator
 */

template<class T>
class random_access_iterator
    : public ft::iterator<ft::random_access_iterator_tag, T> {
 protected:
  T *_current;

 public:
  typedef typename ft::iterator<ft::random_access_iterator_tag,
                                T>::iterator_category iterator_category;
  typedef typename ft::iterator<ft::random_access_iterator_tag, T>::value_type
      value_type;
  typedef typename ft::iterator<ft::random_access_iterator_tag,
                                T>::difference_type difference_type;
  typedef T *pointer;
  typedef T &reference;

  random_access_iterator() : _current(NULL) {}
  random_access_iterator(pointer x) : _current(x) {}
  random_access_iterator(const random_access_iterator &other) : _current(other
                                                                             ._current) {}
  random_access_iterator &operator=(const random_access_iterator &other) {
    if (this == &other) {
      return (*this);
    }
    _current == other._current;
    return (*this);
  }
  ~random_access_iterator() {}

  /*
   *
   */

  pointer base() const {
    return _current;
  }

  /*
   *
   */

  reference operator*() const {
    return *_current;
  }
  pointer operator->() const {
    return &(operator*());
  }
  reference operator[](difference_type n) const {
    return *(*this + n);
  }
  random_access_iterator &operator++() {
    ++_current;
    return (*this);
  }
  random_access_iterator operator++(int) {
    random_access_iterator rv(*this);
    ++(*this);
    return rv;
  }
  random_access_iterator &operator--() {
    --_current;
    return (*this);
  }
  random_access_iterator operator--(int) {
    random_access_iterator rv(*this);
    --(*this);
    return rv;
  }
  random_access_iterator operator+(difference_type n) const {
    return random_access_iterator(_current + n);
  }
  random_access_iterator operator-(difference_type n) const {
    return random_access_iterator(_current - n);
  }
  random_access_iterator &operator+=(difference_type n) {
    _current += n;
    return (*this);
  }
  random_access_iterator &operator-=(difference_type n) {
    _current -= n;
    return (*this);
  }
};

template<class Iterator1, class Iterator2>
bool operator==(const ft::random_access_iterator<Iterator1> &lhs,
                const ft::random_access_iterator<Iterator2> &rhs) {
  return lhs.base() == rhs.base();
}
template<class Iterator1, class Iterator2>
bool operator!=(const ft::random_access_iterator<Iterator1> &lhs,
                const ft::random_access_iterator<Iterator2> &rhs) {
  return lhs.base() != rhs.base();
}
template<class Iterator1, class Iterator2>
bool operator<(const ft::random_access_iterator<Iterator1> &lhs,
               const ft::random_access_iterator<Iterator2> &rhs) {
  return lhs.base() < rhs.base();
}
template<class Iterator1, class Iterator2>
bool operator>(const ft::random_access_iterator<Iterator1> &lhs,
               const ft::random_access_iterator<Iterator2> &rhs) {
  return lhs.base() > rhs.base();
}
template<class Iterator1, class Iterator2>
bool operator<=(const ft::random_access_iterator<Iterator1> &lhs,
                const ft::random_access_iterator<Iterator2> &rhs) {
  return lhs.base() <= rhs.base();
}
template<class Iterator1, class Iterator2>
bool operator>=(const ft::random_access_iterator<Iterator1> &lhs,
                const ft::random_access_iterator<Iterator2> &rhs) {
  return lhs.base() >= rhs.base();
}

}; // ft

#endif //FT_CONTAINERS_INCLUDES_FT_ITERATOR_HPP_
