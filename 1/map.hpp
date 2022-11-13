#ifndef MAP_HPP
#define MAP_HPP

#include "utils/RBTree.hpp"
#include "utils/utility.hpp"

namespace ft {

template <class Key, class T, class Compare = std::less<Key>,
          class Alloc = std::allocator<ft::pair<const Key, T> > >
class map {
   public:
    typedef Key                                      key_type;
    typedef T                                        mapped_type;
    typedef ft::pair<const key_type, mapped_type>    value_type;
    typedef Compare                                  key_compare;
    typedef Alloc                                    allocator_type;
    typedef typename allocator_type::reference       reference;
    typedef typename allocator_type::const_reference const_reference;
    typedef typename allocator_type::pointer         pointer;
    typedef typename allocator_type::const_pointer   const_pointer;
    typedef typename allocator_type::size_type       size_type;

    class value_compare {
        friend class map;

       protected:
        key_compare comp;
        value_compare(Compare c) : comp(c) {}

       public:
        typedef bool       result_type;
        typedef value_type first_argument_type;
        typedef value_type second_argument_type;
        bool               operator()(const value_type& x, const value_type& y) const {
                          return comp(x.first, y.first);
        }
    };

   private:
    typedef ft::Tree<value_type, value_compare, allocator_type> Tree;

   public:
    typedef typename Tree::iterator                                 iterator;
    typedef typename Tree::const_iterator                           const_iterator;
    typedef typename Tree::reverse_iterator                         reverse_iterator;
    typedef typename Tree::const_reverse_iterator                   const_reverse_iterator;
    typedef typename ft::iterator_traits<iterator>::difference_type difference_type;

   private:
    key_compare    _comp;
    allocator_type _alloc;
    Tree           _tree;

    // constructors & destructor
   public:
    explicit map(const key_compare&    comp = key_compare(),
                 const allocator_type& alloc = allocator_type())
        : _tree(value_compare(comp), alloc) {}
    template <class InputIterator>
    map(InputIterator first, InputIterator last, const key_compare& comp = key_compare(),
        const allocator_type& alloc = allocator_type())
        : _tree(value_compare(comp), alloc) {
        for (; first != last; ++first) insert(*first);
    }
    map(const map& x) : _tree(x._tree) {}
    ~map() {}

    map& operator=(const map& x) {
        _tree = x._tree;
        return *this;
    }
    // iterators
    iterator               begin() { return _tree.begin(); }
    const_iterator         begin() const { return _tree.begin(); }
    iterator               end() { return _tree.end(); }
    const_iterator         end() const { return _tree.end(); }
    reverse_iterator       rbegin() { return _tree.rbegin(); }
    const_reverse_iterator rbegin() const { return _tree.rbegin(); }
    reverse_iterator       rend() { return _tree.rend(); }
    const_reverse_iterator rend() const { return _tree.rend(); }
    const_iterator         cbegin() const { return _tree.begin(); }
    const_iterator         cend() const { return _tree.end(); }
    const_reverse_iterator crbegin() const { return _tree.rbegin(); }
    const_reverse_iterator crend() const { return _tree.rend(); }

    // capacity
    bool      empty() const { return _tree.empty(); }
    size_type size() const { return _tree.size(); }
    size_type max_size() const { return _tree.max_size(); }

    // element access
    mapped_type& operator[](const key_type& k) {
        iterator it = insert(ft::make_pair(k, mapped_type())).first;
        return it->second;
    }

    // modifiers
    pair<iterator, bool> insert(const value_type& val) { return _tree.insert(val); }
    iterator             insert(iterator position, const value_type& val) {
                    return _tree.insert(position, val);
    }
    template <class InputIterator>
    void insert(InputIterator first, InputIterator last) {
        _tree.insert(first, last);
    }

    void      erase(iterator position) { _tree.deleteNode(position.base()->data); }
    size_type erase(const key_type& k) { return _tree.deleteNode(ft::make_pair(k, mapped_type())); }
    void      erase(iterator first, iterator last) { _tree.deleteNode(first, last); }
    void      swap(map& x) { _tree.swap(x._tree); }
    void      clear() { _tree.clear(); }

    // observers
    key_compare   key_comp() const { return (_tree.value_comp().comp); }
    value_compare value_comp() const { return value_compare(_tree.value_comp()); }

    mapped_type& at(const key_type& k) {
        iterator it = find(k);
        if (it == end() || it == NULL) throw std::out_of_range("map::at");
        return (*it).second;
    }
    const mapped_type& at(const key_type& k) const {
        const_iterator it = find(k);
        if (it == end() || it == NULL) throw std::out_of_range("map::at");
        return (*it).second;
    }
    // operations
    iterator       find(const key_type& k) { return (_tree.find(ft::make_pair(k, mapped_type()))); }
    const_iterator find(const key_type& k) const {
        return _tree.find(ft::make_pair(k, mapped_type()));
    }
    size_type count(const key_type& k) const {
        return _tree.count(ft::make_pair(k, mapped_type()));
    }
    iterator lower_bound(const key_type& k) {
        return _tree.lower_bound(ft::make_pair(k, mapped_type()));
    }
    const_iterator lower_bound(const key_type& k) const {
        return _tree.lower_bound(ft::make_pair(k, mapped_type()));
    }
    iterator upper_bound(const key_type& k) {
        return _tree.upper_bound(ft::make_pair(k, mapped_type()));
    }
    const_iterator upper_bound(const key_type& k) const {
        return _tree.upper_bound(ft::make_pair(k, mapped_type()));
    }
    pair<const_iterator, const_iterator> equal_range(const key_type& k) const {
        return _tree.equal_range(ft::make_pair(k, mapped_type()));
    }
    pair<iterator, iterator> equal_range(const key_type& k) {
        return _tree.equal_range(ft::make_pair(k, mapped_type()));
    }

    // allocator
    allocator_type get_allocator() const { return _tree.get_allocator(); }
};
template <class Key, class T, class Compare, class Alloc>
void swap(map<Key, T, Compare, Alloc>& x, map<Key, T, Compare, Alloc>& y) {
    x.swap(y);
}

template <class Key, class T, class Compare, class Alloc>
bool operator==(const ft::map<Key, T, Compare, Alloc>& lhs,
                const ft::map<Key, T, Compare, Alloc>& rhs) {
    if (lhs.size() != rhs.size()) return false;
    return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
}

template <class Key, class T, class Compare, class Alloc>
bool operator!=(const ft::map<Key, T, Compare, Alloc>& lhs,
                const ft::map<Key, T, Compare, Alloc>& rhs) {
    return !(lhs == rhs);
}
template <class Key, class T, class Compare, class Alloc>
bool operator<(const ft::map<Key, T, Compare, Alloc>& lhs,
               const ft::map<Key, T, Compare, Alloc>& rhs) {
    return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template <class Key, class T, class Compare, class Alloc>
bool operator<=(const ft::map<Key, T, Compare, Alloc>& lhs,
                const ft::map<Key, T, Compare, Alloc>& rhs) {
    return !(rhs < lhs);
}

template <class Key, class T, class Compare, class Alloc>
bool operator>(const ft::map<Key, T, Compare, Alloc>& lhs,
               const ft::map<Key, T, Compare, Alloc>& rhs) {
    return rhs < lhs;
}

template <class Key, class T, class Compare, class Alloc>
bool operator>=(const ft::map<Key, T, Compare, Alloc>& lhs,
                const ft::map<Key, T, Compare, Alloc>& rhs) {
    return !(rhs > lhs);
}
}  // namespace ft
#endif