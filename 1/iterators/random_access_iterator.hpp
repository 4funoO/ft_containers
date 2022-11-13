#ifndef RANDOM_ACCESS_ITERATOR
#define RANDOM_ACCESS_ITERATOR

#include <iostream>

#include "iterator.hpp"

namespace ft {
template <class T>
class random_access_iterator {
   public:
    typedef T                                                         *iterator_type;
    typedef typename iterator_traits<iterator_type>::value_type        value_type;
    typedef typename iterator_traits<iterator_type>::difference_type   difference_type;
    typedef typename iterator_traits<iterator_type>::reference         reference;
    typedef typename iterator_traits<iterator_type>::pointer           pointer;
    typedef typename iterator_traits<iterator_type>::iterator_category iterator_category;

    random_access_iterator() : _ptr() {}
    random_access_iterator(const random_access_iterator &x) : _ptr(x.base()) {}
    random_access_iterator(const iterator_type &ptr) : _ptr(ptr) {}
    ~random_access_iterator() {}

    random_access_iterator &operator=(const random_access_iterator &x) {
        if (this != &x) {
            _ptr = x.base();
        }
        return (*this);
    }

    reference               operator*() const { return *this->_ptr; }
    pointer                 operator->() const { return this->_ptr; }
    random_access_iterator &operator++() {
        ++_ptr;
        return *this;
    }
    random_access_iterator operator++(int) {
        random_access_iterator tmp(*this);
        ++this->_ptr;
        return tmp;
    }
    random_access_iterator &operator--() {
        --_ptr;
        return *this;
    }
    random_access_iterator operator--(int) {
        random_access_iterator tmp(*this);
        --this->_ptr;
        return tmp;
    }
    random_access_iterator operator+(difference_type n) const {
        random_access_iterator tmp = _ptr + n;
        return tmp;
    }
    random_access_iterator &operator+=(difference_type n) {
        _ptr += n;
        return *this;
    }
    random_access_iterator operator-(difference_type n) const {
        random_access_iterator tmp = _ptr - n;
        return tmp;
    }
    random_access_iterator &operator-=(difference_type n) {
        _ptr -= n;
        return *this;
    }
    reference operator[](difference_type n) const { return *(_ptr + n); }
    pointer   base() const { return _ptr; }

   private:
    pointer _ptr;

   public:
    operator random_access_iterator<const T>() const { return (this->_ptr); }
};

template <class T>
bool operator==(const random_access_iterator<T> x, const random_access_iterator<T> y) {
    return x.base() == y.base();
}

template <class T, class T1>
bool operator==(const random_access_iterator<T> x, const random_access_iterator<T1> y) {
    return x.base() == y.base();
}

template <class T>
bool operator!=(const random_access_iterator<T> x, const random_access_iterator<T> y) {
    return x.base() != y.base();
}

template <class T, class T1>
bool operator!=(const random_access_iterator<T> x, const random_access_iterator<T1> y) {
    return x.base() != y.base();
}

template <class T>
bool operator<(const random_access_iterator<T> x, const random_access_iterator<T> y) {
    return x.base() < y.base();
}

template <class T, class T1>
bool operator<(const random_access_iterator<T> x, const random_access_iterator<T1> y) {
    return x.base() < y.base();
}

template <class T>
bool operator>(const random_access_iterator<T> x, const random_access_iterator<T> y) {
    return x.base() > y.base();
}

template <class T, class T1>
bool operator>(const random_access_iterator<T> x, const random_access_iterator<T1> y) {
    return x.base() > y.base();
}

template <class T>
bool operator<=(const random_access_iterator<T> x, const random_access_iterator<T> y) {
    return x.base() <= y.base();
}

template <class T, class T1>
bool operator<=(const random_access_iterator<T> x, const random_access_iterator<T1> y) {
    return x.base() <= y.base();
}

template <class T>
bool operator>=(const random_access_iterator<T> x, const random_access_iterator<T> y) {
    return x.base() >= y.base();
}

template <class T, class T1>
bool operator>=(const random_access_iterator<T> x, const random_access_iterator<T1> y) {
    return x.base() >= y.base();
}

template <class Iterator1, class Iterator2>
typename random_access_iterator<Iterator1>::difference_type operator+(
    const random_access_iterator<Iterator1> &x, const random_access_iterator<Iterator2> &y) {
    return x.base() + y.base();
}
template <class Iterator>
random_access_iterator<Iterator> operator+(
    const typename random_access_iterator<Iterator>::difference_type n,
    const random_access_iterator<Iterator>                          &y) {
    return y.base() + n;
}

template <class Iterator1, class Iterator2>
typename random_access_iterator<Iterator1>::difference_type operator-(
    const random_access_iterator<Iterator1> &x, const random_access_iterator<Iterator2> &y) {
    return x.base() - y.base();
}

}  // namespace ft
#endif