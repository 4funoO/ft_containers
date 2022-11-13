#ifndef TREE_ITERATOR_HPP
#define TREE_ITERATOR_HPP

#include <iostream>

#include "type_traits.hpp"

namespace ft {

template <class T, class con, class value>
class tree_iterator {
   public:
    typedef T                              Node;
    typedef value                          value_type;
    typedef value_type                    *pointer;
    typedef value_type                    &reference;
    typedef ptrdiff_t                      difference_type;
    typedef ft::bidirectional_iterator_tag iterator_category;

   private:
    Node _curr;

   public:
    tree_iterator() : _curr() {}
    tree_iterator(Node const &n) : _curr(n) {}
    tree_iterator(const tree_iterator<typename con::Node *, con, typename con::value_type> &x)
        : _curr(x.base()) {}
    ~tree_iterator() {}

    Node       &base() { return _curr; }
    const Node &base() const { return _curr; }

    tree_iterator &operator=(tree_iterator const &x) {
        _curr = x._curr;
        return *this;
    }

    tree_iterator &operator++() {
        if (_curr == NULL) {
        } else if (_curr->right != NULL) {
            _curr = _curr->right;
            while (_curr->left != NULL) _curr = _curr->left;
        } else {
            Node p = _curr->parent;
            while (p != NULL && _curr == p->right) {
                _curr = p;
                p = p->parent;
            }
            _curr = p;
        }
        return *this;
    }

    tree_iterator operator++(int) {
        tree_iterator cpy(_curr);
        if (_curr == NULL) {
        } else if (_curr->right != NULL) {
            _curr = _curr->right;
            while (_curr->left) {
                _curr = _curr->left;
            }
        } else {
            Node p = _curr->parent;
            while (p != NULL && _curr == p->right) {
                _curr = p;
                p = p->parent;
            }
            _curr = p;
        }
        return cpy;
    }

    tree_iterator &operator--() {
        if (_curr == NULL) {
        } else if (_curr->left != NULL) {
            _curr = _curr->left;
            while (_curr->right != NULL) {
                _curr = _curr->right;
            }
        } else {
            Node p = _curr->parent;
            while (p != NULL && _curr == p->left) {
                _curr = p;
                p = p->parent;
            }
            _curr = p;
        }
        return *this;
    }

    tree_iterator operator--(int) {
        tree_iterator cpy(_curr);
        if (_curr == NULL) {
        } else if (_curr->left != NULL) {
            _curr = _curr->left;
            while (_curr->right) {
                _curr = _curr->right;
            }
        } else {
            Node p = _curr->parent;
            while (p != NULL && _curr == p->left) {
                _curr = p;
                p = p->parent;
            }
            _curr = p;
        }
        return cpy;
    }
    tree_iterator operator-(int const &i) const {
        tree_iterator ret = *this;
        for (int j = 0; j > i; j++) {
            ret--;
        }
        return ret;
    }

    tree_iterator operator+(int const &i) const {
        tree_iterator ret = *this;
        for (int j = 0; j > i; j++) {
            ret++;
        }
        return ret;
    }

    reference operator*() { return _curr->data; }

    reference operator*() const { return _curr->data; }

    pointer operator->() { return &(this->operator*()); }

    pointer operator->() const { return &(this->operator*()); }

    bool operator==(tree_iterator const &x) const { return _curr == x._curr; }

    bool operator!=(tree_iterator const &x) const { return !(_curr == x._curr); }
};

// external operator overloads

template <class T, class con, class value>
inline bool operator==(const tree_iterator<T, con, value> &rhs,
                       const tree_iterator<T, con, value> &lhs) {
    return rhs.base() == lhs.base();
}

template <class T, class T2, class con, class con2, class value, class value2>
inline bool operator==(const tree_iterator<T, con, value>    &rhs,
                       const tree_iterator<T2, con2, value2> &lhs) {
    return rhs.base() == lhs.base();
}

template <class T, class con, class value>
inline bool operator!=(const tree_iterator<T, con, value> &rhs,
                       const tree_iterator<T, con, value> &lhs) {
    return rhs.base() != lhs.base();
}

template <class T, class T2, class con, class con2, class value, class value2>
inline bool operator!=(const tree_iterator<T, con, value>    &rhs,
                       const tree_iterator<T2, con2, value2> &lhs) {
    return rhs.base() != lhs.base();
}

}  // namespace ft
#endif