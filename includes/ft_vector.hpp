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
      using value_type                = T;
      using pointer                   = T*;
      using const_pointer             = const pointer;
      using reference                 = value_type&;
      using const_reference           = value_type&;
      using allocator_type            = Allocator;
      using size_type                 = std::size_t;
      using difference_type           = std::ptrdiff_t;
      using iterator                  = pointer ;
      using const_iterator            = const_pointer ;
      using reverse_iterator          = std::reverse_iterator<iterator> ;
      using const_reverse_iterator    = std::reverse_iterator<const_iterator> ;

      vector(std::size_t n = 0, Allocator a = Allocator());
      ~vector();
      vector(const vector& x);
      vector& operator=(const vector& x);

      void push_back(const T& x);
      T& operator[](std::size_t i) noexcept;

      iterator begin() noexcept;
      iterator end() noexcept;

     private:
      pointer first = nullptr;
      pointer last = nullptr;
      pointer reserved_last = nullptr;
      allocator_type alloc;
    };



}

#endif //FT_CONTAINERS_INCLUDES_FT_VECTOR_HPP_
