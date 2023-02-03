//
// Created by yuumo on 2023/02/03.
//

#ifndef FT_CONTAINERS_INCLUDES_FT_ALGORITHM_HPP_
#define FT_CONTAINERS_INCLUDES_FT_ALGORITHM_HPP_

namespace ft {

/*
 * equal
 */

template<class InputIter1, class InputIter2>
bool equal(InputIter1 first1, InputIter1 last1, InputIter2 first2) {
  for (; first1 != last1; ++first1, ++first2) {
    if (!(bool(*first1 == *first2))) {
      return false;
    }
  }
  return true;
}

template<class InputIter1, class InputIter2, class BinaryPredicate>
bool equal(InputIter1 first1,
           InputIter1 last1,
           InputIter2 first2,
           BinaryPredicate p) {
  for (; first1 != last1; ++first1, ++first2) {
    if (!(bool(p(*first1, *first2)))) {
      return false;
    }
  }
  return true;
}

/*
 * lexicographical_compare
 */

template<class InputIter1, class InputIter2>
bool lexicographical_compare(InputIter1 first1,
                             InputIter1 last1,
                             InputIter2 first2,
                             InputIter2 last2) {
  for (; (first1 != last1) && (first2 != last2); ++first1, (void)++first2) {
    if (*first1 < *first2) {
      return true;
    }
    if (*first1 > *first2) {
      return false;
    }
    return (first1 == last1) && (first2 != last2);
  }
}

template<class InputIter1, class InputIter2, class Compare>
bool lexicographical_compare(InputIter1 first1,
                             InputIter1 last1,
                             InputIter2 first2,
                             InputIter2 last2,
                             Compare comp) {
  for (; (first1 != last1) && (first2 != last2); ++first1, (void)++first2) {
    if (comp(*first1, *first2)) {
      return true;
    }
    if (comp(*first1, *first2)) {
      return false;
    }
    return (first1 == last1) && (first2 != last2);
  }
}

} // ft

#endif //FT_CONTAINERS_INCLUDES_FT_ALGORITHM_HPP_
