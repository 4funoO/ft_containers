#ifndef REVERSE_ITERATOR
#define REVERSE_ITERATOR

#include <iostream>

#include "iterator.hpp"
#include "random_access_iterator.hpp"

namespace ft {
template <class Iterator>
class reverse_iterator {
   public:
    typedef Iterator                                                   iterator_type;
    typedef typename iterator_traits<iterator_type>::value_type        value_type;
    typedef typename iterator_traits<iterator_type>::difference_type   difference_type;
    typedef typename iterator_traits<iterator_type>::reference         reference;
    typedef typename iterator_traits<iterator_type>::pointer           pointer;
    typedef typename iterator_traits<iterator_type>::iterator_category iterator_category;

    reverse_iterator() : _iter() {}
    reverse_iterator(const iterator_type it) : _iter(it) {}
    template <typename T>
    reverse_iterator(const reverse_iterator<T> &x) : _iter(x.base()) {}
    ~reverse_iterator() {}

    reference operator*() const {
        Iterator tmp = _iter;
        --tmp;
        return *tmp;
    }
    pointer operator->() const { return &(operator*()); }

    reverse_iterator &operator++() {
        --_iter;
        return *this;
    }
    reverse_iterator operator++(int) {
        reverse_iterator tmp(*this);
        --_iter;
        return tmp;
    }
    reverse_iterator &operator--() {
        ++_iter;
        return *this;
    }
    reverse_iterator operator--(int) {
        reverse_iterator tmp(*this);
        ++_iter;
        return tmp;
    }
    reverse_iterator operator+(difference_type n) const {
        reverse_iterator tmp(_iter - n);
        return tmp;
    }

    reverse_iterator &operator+=(difference_type n) {
        _iter -= n;
        return *this;
    }

    reverse_iterator operator-(difference_type n) const {
        reverse_iterator tmp(_iter + n);
        return tmp;
    }

    reverse_iterator &operator-=(difference_type n) {
        _iter += n;
        return *this;
    }
    reference operator[](difference_type n) const { return *(*this + n); }

    iterator_type base() const { return _iter; }

   private:
    iterator_type _iter;

   public:
    operator reverse_iterator<const Iterator>() const { return (this->_iter); }
};
template <class T>
bool operator==(const reverse_iterator<T> x, const reverse_iterator<T> y) {
    return x.base() == y.base();
}

template <class T, class T1>
bool operator==(const reverse_iterator<T> x, const reverse_iterator<T1> y) {
    return (x.base() == y.base());
}

template <class T>
bool operator!=(const reverse_iterator<T> x, const reverse_iterator<T> y) {
    return x.base() != y.base();
}

template <class T, class T1>
bool operator!=(const reverse_iterator<T> x, const reverse_iterator<T1> y) {
    return x.base() != y.base();
}

template <class T>
bool operator<(const reverse_iterator<T> x, const reverse_iterator<T> y) {
    return x.base() > y.base();
}

template <class T, class T1>
bool operator<(const reverse_iterator<T> x, const reverse_iterator<T1> y) {
    return x.base() > y.base();
}

template <class T>
bool operator>(const reverse_iterator<T> x, const reverse_iterator<T> y) {
    return x.base() < y.base();
}

template <class T, class T1>
bool operator>(const reverse_iterator<T> x, const reverse_iterator<T1> y) {
    return x.base() < y.base();
}

template <class T>
bool operator<=(const reverse_iterator<T> x, const reverse_iterator<T> y) {
    return x.base() >= y.base();
}

template <class T, class T1>
bool operator<=(const reverse_iterator<T> x, const reverse_iterator<T1> y) {
    return x.base() >= y.base();
}

template <class T>
bool operator>=(const reverse_iterator<T> x, const reverse_iterator<T> y) {
    return x.base() <= y.base();
}

template <class T, class T1>
bool operator>=(const reverse_iterator<T> x, const reverse_iterator<T1> y) {
    return x.base() <= y.base();
}

template <class Iterator1, class Iterator2>
typename reverse_iterator<Iterator1>::difference_type operator+(
    const reverse_iterator<Iterator1> x, const reverse_iterator<Iterator2> y) {
    return y.base() + x.base();
}

template <class Iterator1, class Iterator2>
typename reverse_iterator<Iterator1>::difference_type operator-(
    const reverse_iterator<Iterator1> x, const reverse_iterator<Iterator2> y) {
    return y.base() - x.base();
}

template <class Iterator>
reverse_iterator<Iterator> operator+(const typename reverse_iterator<Iterator>::difference_type n,
                                     const reverse_iterator<Iterator>                          &y) {
    return reverse_iterator<Iterator>(y.base() - n);
}
}  // namespace ft
#endif