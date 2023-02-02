//
// Created by yuumo on 2023/02/02.
//

#ifndef FT_CONTAINERS_INCLUDES_FT_VECTOR_HPP_
#define FT_CONTAINERS_INCLUDES_FT_VECTOR_HPP_

#include <memory>

namespace ft {
template<class T, class Allocator = std::allocator<T>>
class vector {
 public:
  using value_type = T;
  using pointer = T *;
  using const_pointer = const pointer;
  using reference = value_type &;
  using const_reference = const value_type &;
  using allocator_type = Allocator;
  using size_type = std::size_t;
  using difference_type = std::ptrdiff_t;
  using iterator = pointer;
  using const_iterator = const_pointer;
  using reverse_iterator = std::reverse_iterator<iterator>;
  using const_reverse_iterator = std::reverse_iterator<const_iterator>;

//  https://en.cppreference.com/w/cpp/container/vector/vector
  vector() : vector(allocator_type()) {};
  explicit vector(const allocator_type &alloc) noexcept: first(NULL),
                                                         last(NULL),
                                                         reserved_last(NULL),
                                                         alloc(alloc) {};
  explicit vector(size_type count,
                  const T &value = T(),
                  const Allocator &alloc = Allocator()) : vector(alloc) {
    resize(count, value);
  };

  template<typename InputIterator>
  vector(InputIterator first,
         InputIterator last,
         const Allocator &allocator = Allocator(),
         typename std::enable_if<!std::is_integral<InputIterator>::value,
                                 InputIterator>::type * = nullptr) : first(
      nullptr), last(nullptr), reserved_last(nullptr), alloc(allocator) {
    reserve(std::distance(first, last));
    for (auto i = first; i != last; ++i) {
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
      : first(NULL),
        last(NULL),
        reserved_last(NULL),
        alloc(traits::select_on_container_copy_construction(r.alloc)) {
    reserve(r.size());
    for (auto dest = first, src = r.begin(), last = r.end(); src != last;
         ++dest, ++src) {
      construct(dest, *src);
    }
    last = first + r.size();
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
      for (auto src_iter = r.begin() + r.size(), src_end = r.end();
           src_iter != src_end; ++src_iter, ++last) {
        construct(last, *src_iter);
      }
    } else {
      destroy_until(rbegin());
      reserve(r.size());
      for (auto src_iter = r.begin(), src_end = r.end(), dest_iter = begin();
           src_iter != src_end; ++dest_iter, ++last) {
        construct(dest_iter, *src_iter);
      }
    }
    return *this;
  };

  /*
   *
   */

  size_type size() const noexcept { return end() - begin(); }
  bool empty() const noexcept { return begin() == end(); }
  size_type capacity() const noexcept { return reserved_last - first; }

  /*
   *
   */

  void push_back(const_reference value) {
    if (size() + 1 > capacity()) {
      auto c = size();
      if (c == size()) {
        c = 1;
      } else {
        c *= 2;
      }
      reserve(c);
    }
    construct(last, value);
    ++last;
  }

  /*
   *
   */

  reference operator[](size_type i) { return first[i]; }
  const_reference operator[](size_type i) const { return first[i]; }
  reference at(size_type i) {
    if (i >= size()) {
      throw std::out_of_range("index is out of range.");
    }
    return first[i];
  }
  const_reference at(size_type i) const {
    if (i >= size()) {
      throw std::out_of_range("index is out of range.");
    }
    return first[i];
  }

  /*
   *
   */

  reference front() { return *first; }
  const_reference front() const { return *first; }
  reference back() { return *(last - 1); }
  const_reference back() const { return *(last - 1); }

  /*
   *
   */

  pointer data() noexcept { return first; }
  const_pointer data() const noexcept { return first; }

  /*
   * iterator
   */

  iterator begin() noexcept { return first; }
  iterator begin() const noexcept { return first; }
  iterator end() noexcept { return last; }
  iterator end() const noexcept { return last; }
  const_iterator cbegin() const noexcept { return first; }
  const_iterator cend() const noexcept { return last; }
  reverse_iterator rbegin() noexcept { return reverse_iterator{last}; }
  const_reverse_iterator rbegin() const noexcept {
    return reverse_iterator{last};
  }
  reverse_iterator rend() noexcept { return reverse_iterator{first}; }
  const_reverse_iterator rend() const noexcept {
    return reverse_iterator{first};
  }

  /*
   *
   */

  void clear() noexcept { destroy_until(rend()); }

  void reserve(size_type sz) {
    if (sz <= capacity()) {
      return;
    }

    auto ptr = allocate(sz);

    auto old_first = first;
    auto old_last = last;
    auto old_capacity = capacity();

    first = ptr;
    last = first;
    reserved_last = first + sz;

    for (auto old_iter = old_first; old_iter != old_last; ++old_iter, ++last) {
      construct(last, std::move(*old_iter));
    }

    for (auto r_iter = reverse_iterator(old_last),
             r_end = reverse_iterator(old_first); r_iter != r_end; ++r_iter) {
      destroy(&(*r_iter));
    }

    alloc.deallocate(old_first, old_capacity);
  }

  void resize(size_type sz) {
    if (sz < size()) {
      auto diff = size() - sz;
      destroy_until(rbegin() + diff);
      last = first + sz;
    } else if (sz > size()) {
      reserve(sz);
      for (; last != reserved_last; ++last) {
        construct(last);
      }
    }
  }

  void resize(size_type sz, const_reference value) {
    if (sz < size()) {
      auto diff = size() - sz;
      destroy_until(rbegin() + diff);
      last = first + sz;
    } else if (sz > size()) {
      reserve(sz);
      for (; last != reserved_last; ++last) {
        construct(last, value);
      }
    }
  }

 private:
  pointer first;
  pointer last;
  pointer reserved_last;
  allocator_type alloc;


  /*
   *
   */

  using traits = std::allocator_traits<allocator_type>;
  pointer allocate(size_type n) { return traits::allocate(alloc, n); }
  void deallocate() { traits::deallocate(alloc, first, capacity()); }
  void construct(pointer ptr) { traits::construct(alloc, ptr); }
  void construct(pointer ptr, const_reference value) {
    traits::construct(alloc,
                      ptr,
                      value);
  }
  void construct(pointer ptr, value_type &&value) {
    traits::construct(alloc,
                      ptr,
                      std::move(value));
  }
  void destroy(pointer ptr) { traits::destroy(alloc, ptr); }
  void destroy_until(reverse_iterator rend) {
    for (auto r_iter = rbegin(); r_iter != rend; ++r_iter, --last) {
      destroy(&(*r_iter));
    }
  }

};

}

#endif //FT_CONTAINERS_INCLUDES_FT_VECTOR_HPP_
