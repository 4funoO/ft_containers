#ifndef SET_HPP
#define SET_HPP

#include "iterators/reverse_iterator.hpp"
#include "utils/RBTree.hpp"
#include "utils/algorithm.hpp"

namespace ft {
template <class T, class Compare = std::less<T>, class Alloc = std::allocator<T> >
class set {
   public:
    typedef T                                        key_type;
    typedef T                                        value_type;
    typedef Compare                                  key_compare;
    typedef key_compare                              value_compare;
    typedef Alloc                                    allocator_type;
    typedef typename allocator_type::reference       reference;
    typedef typename allocator_type::const_reference const_reference;
    typedef typename allocator_type::size_type       size_type;
    typedef typename allocator_type::difference_type difference_type;
    typedef typename allocator_type::pointer         pointer;
    typedef typename allocator_type::const_pointer   const_pointer;

   private:
    typedef Tree<value_type, value_compare, allocator_type> Tree;

   public:
    typedef typename Tree::const_iterator         iterator;
    typedef typename Tree::const_iterator         const_iterator;
    typedef typename Tree::const_reverse_iterator reverse_iterator;
    typedef typename Tree::const_reverse_iterator const_reverse_iterator;

   private:
    Tree _tree;

   public:
    explicit set(const key_compare&    comp = key_compare(),
                 const allocator_type& alloc = allocator_type())
        : _tree(value_compare(comp), alloc) {}

    template <class InputIterator>
    set(InputIterator first, InputIterator last, const key_compare& comp = key_compare(),
        const allocator_type& alloc = allocator_type())
        : _tree(value_compare(comp), alloc) {
        for (; first != last; ++first) _tree.insert(*first);
    }

    set(const set& x) : _tree(x._tree) {}

    ~set() {}

    set& operator=(const set& x) {
        _tree = x._tree;
        return *this;
    }

    iterator               begin() { return _tree.begin(); }
    const_iterator         begin() const { return _tree.begin(); }
    const_iterator         cbegin() const { return _tree.begin(); }
    iterator               end() { return _tree.end(); }
    const_iterator         end() const { return _tree.end(); }
    const_iterator         cend() const { return _tree.end(); }
    reverse_iterator       rbegin() { return _tree.rbegin(); }
    const_reverse_iterator rbegin() const { return _tree.rbegin(); }
    const_reverse_iterator crbegin() const { return _tree.rbegin(); }
    reverse_iterator       rend() { return _tree.rend(); }
    const_reverse_iterator rend() const { return _tree.rend(); }
    const_reverse_iterator crend() const { return _tree.rend(); }

    bool      empty() const { return _tree.empty(); }
    size_type size() const { return _tree.size(); }
    size_type max_size() const { return _tree.max_size(); }

    pair<iterator, bool> insert(const value_type& val) { return _tree.insert(val); }
    iterator             insert(iterator position, const value_type& val) {
                    (void)position;
                    return _tree.insert(_tree.begin(), val);
    }
    template <class InputIterator>
    void insert(InputIterator first, InputIterator last) {
        return _tree.insert(first, last);
    }

    void      erase(iterator position) { _tree.deleteNode(*position); }
    size_type erase(const value_type& val) { return _tree.deleteNode(val); }
    void      erase(iterator first, iterator last) {
             while (first != last) {
                 _tree.deleteNode(*first++);
        }
    }

    void swap(set& x) { _tree.swap(x._tree); }

    void clear() { _tree.clear(); }

    key_compare   key_comp() const { return _tree.value_comp(); }
    value_compare value_comp() const { return _tree.value_comp(); }

    iterator  find(const value_type& val) const { return _tree.find(val); }
    size_type count(const value_type& val) const { return _tree.count(val); }
    iterator  lower_bound(const value_type& val) const { return _tree.lower_bound(val).base(); }
    iterator  upper_bound(const value_type& val) const { return _tree.upper_bound(val).base(); }
    pair<iterator, iterator> equal_range(const value_type& val) const {
        return _tree.equal_range(val);
    }
    allocator_type get_allocator() const { return _tree.get_allocator(); }
};
template <class T, class Compare, class Alloc>
void swap(set<T, Compare, Alloc>& x, set<T, Compare, Alloc>& y) {
    x.swap(y);
}

template <class T, class Compare, class Alloc>
bool operator==(const ft::set<T, Compare, Alloc>& lhs, const ft::set<T, Compare, Alloc>& rhs) {
    if (lhs.size() != rhs.size()) return false;
    return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
}

template <class T, class Compare, class Alloc>
bool operator!=(const ft::set<T, Compare, Alloc>& lhs, const ft::set<T, Compare, Alloc>& rhs) {
    return !(lhs == rhs);
}
template <class T, class Compare, class Alloc>
bool operator<(const ft::set<T, Compare, Alloc>& lhs, const ft::set<T, Compare, Alloc>& rhs) {
    return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template <class T, class Compare, class Alloc>
bool operator<=(const ft::set<T, Compare, Alloc>& lhs, const ft::set<T, Compare, Alloc>& rhs) {
    return !(rhs < lhs);
}

template <class T, class Compare, class Alloc>
bool operator>(const ft::set<T, Compare, Alloc>& lhs, const ft::set<T, Compare, Alloc>& rhs) {
    return rhs < lhs;
}

template <class T, class Compare, class Alloc>
bool operator>=(const ft::set<T, Compare, Alloc>& lhs, const ft::set<T, Compare, Alloc>& rhs) {
    return !(rhs > lhs);
}

}  // namespace ft

#endif
