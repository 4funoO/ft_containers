#pragma once

#include "../iterators/iterator.hpp"

namespace ft {
template <class Iterator>
typename iterator_traits<Iterator>::difference_type distance_helper(Iterator first, Iterator last,
                                                                    random_access_iterator_tag) {
    return (last - first);
}
template <class Iterator>
typename iterator_traits<Iterator>::difference_type distance_helper(Iterator first, Iterator last,
                                                                    input_iterator_tag) {
    typename iterator_traits<Iterator>::difference_type diff = 0;
    for (; first != last; ++first) ++diff;
    return (diff);
}
template <class Iterator>
typename iterator_traits<Iterator>::difference_type distance(Iterator first, Iterator last) {
    return (distance_helper(first, last, typename iterator_traits<Iterator>::iterator_category()));
}

template <class T>
void swap(T &a, T &b) {
    T tmp = a;
    a = b;
    b = tmp;
}

template <class InputIterator, class OutputIterator>
OutputIterator copy(InputIterator first, InputIterator last, OutputIterator result) {
    while (first != last) {
        *result = *first;
        ++result;
        ++first;
    }
    return result;
}

template <class BidirectionalIterator, class BidirectionalIterator1>
BidirectionalIterator1 copy_from_back(BidirectionalIterator first, BidirectionalIterator1 last,
                                      BidirectionalIterator1 res) {
    while (last != first) {
        --res, --last;
        *res = *last;
    }
    return res;
}

template <class Iterator, class T>
void fill(Iterator first, Iterator last, T &val) {
    for (; first != last; ++first) *first = val;
}

template <class InputIt1, class InputIt2>
bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2) {
    for (; first1 != last1; ++first1, ++first2) {
        if (!(*first1 == *first2)) {
            return false;
        }
    }
    return true;
}

template <typename InputIterator1, typename InputIterator2>
bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2,
                             InputIterator2 last2) {
    while (first1 != last1) {
        if (first2 == last2 || *first2 < *first1)
            return false;
        else if (*first1 < *first2)
            return true;
        ++first1;
        ++first2;
    }
    return first2 != last2;
}

}  // namespace ft
