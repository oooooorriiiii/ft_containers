//
// Created by yuumo on 2023/02/02.
//

#ifndef FT_CONTAINERS_INCLUDES_FT_VECTOR_HPP_
#define FT_CONTAINERS_INCLUDES_FT_VECTOR_HPP_

#include <cstddef> // NULL
#include <memory>

#include "utils.hpp"

namespace ft {
template<class T, class Allocator = std::allocator<T> >
class vector {
 public:
  typedef T value_type;
  typedef T *pointer;
  typedef const pointer const_pointer;
  typedef value_type &reference;
  typedef const value_type &const_reference;
  typedef Allocator allocator_type;
  typedef std::size_t size_type;
  typedef std::ptrdiff_t difference_type;
  typedef pointer iterator;
  typedef const_pointer const_iterator;
//  typedef ft::random_access_iterator<value_type> iterator;
//  typedef ft::random_access_iterator<const value_type> const_iterator;
  typedef std::reverse_iterator<iterator> reverse_iterator;
  typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

//  https://en.cppreference.com/w/cpp/container/vector/vector
  vector()
      : first_(NULL),
        last_(NULL),
        reserved_last_(NULL),
        alloc_(allocator_type()) {}
  explicit vector(const allocator_type &alloc) : first_(NULL),
                                                 last_(NULL),
                                                 reserved_last_(NULL),
                                                 alloc_(alloc) {}
  explicit vector(size_type count,
                  const T &value = T(),
                  const Allocator &alloc = Allocator())
      : first_(NULL), last_(NULL), reserved_last_(NULL), alloc_(alloc) {
    resize(count, value);
  }

  template<typename InputIterator>
  vector(InputIterator first,
         InputIterator last,
         const Allocator &allocator = Allocator(),
         typename ft::enable_if<!ft::is_integral<InputIterator>::value,
                                InputIterator>::type * = NULL) : first_(
      NULL), last_(NULL), reserved_last_(NULL), alloc_(allocator) {
    reserve(std::distance(first, last));
    for (pointer i = first; i != last; ++i) {
      push_back(*i);
    }
  }

  /*
   * destructor
   */

  ~vector() {
    clear();
    deallocate();
  };

  /*
   * copy constructor
   */

  vector(const vector &r)
      : first_(NULL),
        last_(NULL),
        reserved_last_(NULL),
        alloc_(r.alloc_) {
    reserve(r.size());
    for (pointer dest = first_, src = r.begin(), last = r.end(); src != last;
         ++dest, ++src) {
      construct(dest, *src);
    }
    last_ = first_ + r.size();
  }

  /*
   * operator
   */

  vector &operator=(const vector &r) {
    if (this == &r) {
      return *this;
    }

    if (size() == r.size()) {
      std::copy(r.begin(), r.end(), begin());
    } else if (capacity() >= r.size()) {
      std::copy(r.begin(), r.begin() + r.size(), begin());
      for (const_iterator src_iter = r.begin() + r.size(), src_end = r.end();
           src_iter != src_end; ++src_iter, ++last_) {
        construct(last_, *src_iter);
      }
    } else {
      destroy_until(rbegin());
      reserve(r.size());
      for (const_iterator src_iter = r.begin(), src_end = r.end(),
               dest_iter = begin();
           src_iter != src_end; ++dest_iter, ++last_) {
        construct(dest_iter, *src_iter);
      }
    }
    return *this;
  };

  /*
   *
   */

  size_type size() const { return end() - begin(); }
  bool empty() const { return begin() == end(); }
  size_type capacity() const { return reserved_last_ - first_; }

  /*
   *
   */

  void push_back(const_reference value) {
    if (size() + 1 > capacity()) {
      size_type c = size();
      if (c == size()) {
        c = 1;
      } else {
        c *= 2;
      }
      reserve(c);
    }
    construct(last_, value);
    ++last_;
  }

  /*
   *
   */

  reference operator[](size_type i) { return first_[i]; }
  const_reference operator[](size_type i) const { return first_[i]; }
  reference at(size_type i) {
    if (i >= size()) {
      throw std::out_of_range("index is out of range.");
    }
    return first_[i];
  }
  const_reference at(size_type i) const {
    if (i >= size()) {
      throw std::out_of_range("index is out of range.");
    }
    return first_[i];
  }

  /*
   *
   */

  reference front() { return *first_; }
  const_reference front() const { return *first_; }
  reference back() { return *(last_ - 1); }
  const_reference back() const { return *(last_ - 1); }

  /*
   *
   */

  pointer data() { return first_; }
  const_pointer data() const { return first_; }

  /*
   * iterator
   */

  iterator begin() { return first_; }
  iterator begin() const { return first_; }
  iterator end() { return last_; }
  iterator end() const { return last_; }
  const_iterator cbegin() const { return first_; }
  const_iterator cend() const { return last_; }
  reverse_iterator rbegin() { return reverse_iterator(last_); }
  const_reverse_iterator rbegin() const {
    return reverse_iterator(last_);
  }
  reverse_iterator rend() { return reverse_iterator(first_); }
  const_reverse_iterator rend() const {
    return reverse_iterator(first_);
  }

  /*
   *
   */

  void clear() { destroy_until(rend()); }

  void reserve(size_type sz) {
    if (sz <= capacity()) {
      return;
    }

    pointer ptr = allocate(sz);

    pointer old_first = first_;
    pointer old_last = last_;
    size_type old_capacity = capacity();

    first_ = ptr;
    last_ = first_;
    reserved_last_ = first_ + sz;

    for (pointer old_iter = old_first; old_iter != old_last;
         ++old_iter, ++last_) {
      construct(last_, *old_iter);
    }

    for (reverse_iterator r_iter = reverse_iterator(old_last),
             r_end = reverse_iterator(old_first); r_iter != r_end; ++r_iter) {
      destroy(&(*r_iter));
    }

    alloc_.deallocate(old_first, old_capacity);
  }

  void resize(size_type sz) {
    if (sz < size()) {
      difference_type diff = size() - sz;
      destroy_until(rbegin() + diff);
      last_ = first_ + sz;
    } else if (sz > size()) {
      reserve(sz);
      for (; last_ != reserved_last_; ++last_) {
        construct(last_);
      }
    }
  }

  void resize(size_type sz, const_reference value) {
    if (sz < size()) {
      difference_type diff = size() - sz;
      destroy_until(rbegin() + diff);
      last_ = first_ + sz;
    } else if (sz > size()) {
      reserve(sz);
      for (; last_ != reserved_last_; ++last_) {
        construct(last_, value);
      }
    }
  }

 private:
  pointer first_;
  pointer last_;
  pointer reserved_last_;
  allocator_type alloc_;

  /*
   *
   */

  pointer allocate(size_type n) {
    return alloc_.allocate(n);
  }
  void deallocate() {
    alloc_.deallocate(first_, capacity());
  }
  void construct(pointer ptr) {
    alloc_.construct(ptr, 0);
  }
  void construct(pointer ptr, const_reference value) {
    alloc_.construct(ptr, value);
  }
//  void construct(pointer ptr, value_type &&value) {
//    traits::construct(alloc_,
//                      ptr,
//                      std::move(value));
//  }
  void destroy(pointer ptr) {
    alloc_.destroy(ptr);
  }
  void destroy_until(reverse_iterator rend) {
    for (reverse_iterator r_iter = rbegin(); r_iter != rend;
         ++r_iter, --last_) {
      destroy(&(*r_iter));
    }
  }
};

} // ft

#endif //FT_CONTAINERS_INCLUDES_FT_VECTOR_HPP_
