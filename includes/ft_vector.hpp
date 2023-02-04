//
// Created by yuumo on 2023/02/02.
//

#ifndef FT_CONTAINERS_INCLUDES_FT_VECTOR_HPP_
#define FT_CONTAINERS_INCLUDES_FT_VECTOR_HPP_

#include <cstddef> // NULL
#include <memory>
#include <limits> // std::min

#include "utils.hpp"
#include "ft_iterator.hpp"

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
//  typedef pointer iterator;
//  typedef const_pointer const_iterator;
  typedef ft::random_access_iterator<value_type> iterator;
  typedef ft::random_access_iterator<const value_type> const_iterator;
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
    for (InputIterator i = first; i != last; ++i) {
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
    pointer dest = first_;
    for (const_iterator src = r.begin(), last = r.end(); src != last;
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
    } else {
      if (capacity() >= r.size()) {
//        std::copy(r.begin(), r.begin() + r.size(), begin());
        destroy_until(rend());
        for (
            const_iterator src_iter = r.begin(), src_end = r.begin() + r.size();
            src_iter != src_end; ++src_iter, ++last_) {
          construct(last_, *src_iter);
        }
      } else {
        destroy_until(rend());
        reserve(r.size());
        for (const_iterator src_iter = r.begin(), src_end = r.end();
             src_iter != src_end; ++src_iter, ++last_) {
          construct(last_, *src_iter);
        }
      }
    }
    return *this;
  };

  /*
   *
   */

  size_type size() const {
    return std::distance(first_, last_);
  }

  bool empty() const {
    return begin() == end();
  }

  size_type capacity() const {
    return reserved_last_ - first_;
  }

  size_type max_size() const {
    return std::min<size_type>(alloc_.max_size(),
                               std::numeric_limits<difference_type>::max());
  }

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

  void pop_back() {
    alloc_.destroy(--last_);
  }

  /*
   * []
   */

  reference operator[](size_type i) {
    return first_[i];
  }
  const_reference operator[](size_type i) const {
    return first_[i];
  }

  /*
   * at
   */

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
   * front, back
   */

  reference front() {
    return *first_;
  }
  const_reference front() const {
    return *first_;
  }
  reference back() {
    return *(last_ - 1);
  }
  const_reference back() const {
    return *(last_ - 1);
  }

  /*
   * data
   */

  pointer data() {
    return first_;
  }
  const_pointer data() const {
    return first_;
  }

  /*
   * iterator
   *
   * begin, end, rbegin, rend
   */

  iterator begin() {
    return first_;
  }
  iterator end() {
    return last_;
  }
  const_iterator begin() const {
    return first_;
  }
  const_iterator end() const {
    return last_;
  }
  reverse_iterator rbegin() {
    return reverse_iterator(last_);
  }
  reverse_iterator rend() {
    return reverse_iterator(first_);
  }
  const_reverse_iterator rbegin() const {
    return reverse_iterator(last_);
  }
  const_reverse_iterator rend() const {
    return reverse_iterator(first_);
  }

  /*
   * clear
   */

  void clear() { destroy_until(rend()); }

  /*
   * reserve
   */

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

  /*
   * resize
   */

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

  /*
   * assign
   */

  void assign(size_type count, const T &value) {
    if (count > capacity()) {
      clear();
      deallocate();

      first_ = allocate(count);
      last_ = first_;
      reserved_last_ = first_ + count;

      for (size_type i = 0; i < count; ++i) {
        construct(last_++, value);
      }
    } else if (count > size()) {
      pointer ptr = first_;
      for (size_type i = 0; i < count; ++i) {
        if (i < size()) {
          *(ptr++) = value;
        } else {
          construct(last_++, value);
        }
      }
    } else {
      clear();
      for (size_type i = 0; i < count; ++i) {
        construct(last_++, value);
      }
    }
  }

  template<class InputIterator>
  void assign(InputIterator src_first,
              InputIterator src_last,
              typename ft::enable_if<!ft::is_integral<InputIterator>::value,
                                     InputIterator>::type * = NULL) {
    size_type count = src_last - src_first;
    if (count > capacity()) {
      clear();
      deallocate();

      first_ = allocate(count);
      last_ = first_;
      reserved_last_ = first_ + count;
      for (InputIterator head = src_first; head != src_last; ++head) {
        construct(last_++, *head);
      }
    } else if (count > size()) {
      pointer ptr = first_;
      for (size_type i = 0; i < count; ++i) {
        if (i < size()) {
          *(ptr++) = *src_first++;
        } else {
          construct(last_++, *src_first++);
        }
      }
    } else {
      clear();
      for (InputIterator head = src_first; head != src_last; ++head) {
        construct(last_++, *head);
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
