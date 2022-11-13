
#ifndef Vector
#define Vector

#include <exception>
#include <iostream>
#include <limits>
#include <memory>

#include "iterators/iterator.hpp"
#include "iterators/random_access_iterator.hpp"
#include "iterators/reverse_iterator.hpp"
#include "iterators/type_traits.hpp"
#include "utils/algorithm.hpp"

namespace ft {
template <class T, class Allocator = std::allocator<T> >
class vector {
   public:
    typedef T                                            value_type;
    typedef Allocator                                    allocator_type;
    typedef typename allocator_type::reference           reference;
    typedef typename allocator_type::const_reference     const_reference;
    typedef typename allocator_type::pointer             pointer;
    typedef typename allocator_type::const_pointer       const_pointer;
    typedef ft::random_access_iterator<value_type>       iterator;
    typedef ft::random_access_iterator<const value_type> const_iterator;
    typedef ft::reverse_iterator<iterator>               reverse_iterator;
    typedef ft::reverse_iterator<const_iterator>         const_reverse_iterator;
    typedef typename allocator_type::size_type           size_type;
    typedef typename allocator_type::difference_type     difference_type;

   private:
    pointer        _begin;
    pointer        _end;
    pointer        _cap_end;
    allocator_type _a;

   public:
    // constructor
    explicit vector(const allocator_type &alloc = allocator_type())
        : _begin(NULL), _end(NULL), _cap_end(NULL), _a(alloc) {}
    explicit vector(size_type n, const value_type &val = value_type(),
                    const allocator_type &alloc = allocator_type())
        : _begin(NULL), _end(NULL), _cap_end(NULL), _a(alloc) {
        _vallocate(n);
        for (size_type i = 0; i < n; i++) {
            _a.construct(_end, val);
            ++_end;
        }
    }

    template <class InputIterator>
    vector(InputIterator first, InputIterator last, const allocator_type &alloc = allocator_type(),
           typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type * =
               NULL)
        : _begin(NULL), _end(NULL), _cap_end(NULL), _a(alloc) {
        _a = alloc;
        assign(first, last);
    };
    vector(const vector &x) : _begin(NULL), _end(NULL), _cap_end(NULL), _a(x._a) {
        _vallocate(x.capacity());
        for (size_type i = 0; i < x.size(); i++) {
            _a.construct(_end, *(x._begin + i));
            _end++;
        }
    }

    // destructor
    ~vector() {
        if (_begin != nullptr) _vdeallocate();
    }

    // operator overloads
    vector<T, Allocator> &operator=(const vector<T, Allocator> &x) {
        if (this != &x) {
            if (_begin != NULL) {
                clear();
                _a.deallocate(_begin, capacity());
            }
            _a = x._a;
            _begin = _a.allocate(x.capacity());
            _cap_end = _begin + x.capacity();
            _end = _begin;
            for (size_type i = 0; i < size_type(x._end - x._begin); i++) {
                _a.construct(_end, *(x._begin + i));
                _end++;
            }
        }
        return *this;
    }
    reference       operator[](size_type n) { return this->_begin[n]; }
    const_reference operator[](size_type n) const { return this->_begin[n]; }

    // iterators
    iterator               begin() { return iterator(_begin); }
    const_iterator         begin() const { return const_iterator(_begin); }
    iterator               end() { return iterator(_end); }
    const_iterator         end() const { return const_iterator(_end); }
    reverse_iterator       rbegin() { return reverse_iterator(_end); }
    const_reverse_iterator rbegin() const { return const_reverse_iterator(_end); }
    reverse_iterator       rend() { return reverse_iterator(_begin); }
    const_reverse_iterator rend() const { return const_reverse_iterator(_begin); }

    // capacity
    size_type size() const { return static_cast<size_type>(_end - _begin); }
    size_type max_size() const {
        size_type _amax = _a.max_size();
        size_type _nmax = std::numeric_limits<size_type>::max() / 2;
        return ((_amax < _nmax) ? _amax : _nmax);
    }
    size_type capacity() const { return static_cast<size_type>(_cap_end - _begin); }
    bool      empty() const { return _begin == _end; }

    void resize(size_type n, value_type val = value_type()) {
        size_type s = size();
        if (s < n) {
            if (n > capacity()) reserve(n);
            for (; s < n; ++s) {
                _a.construct((_begin + s), val);
                ++_end;
            }
        } else if (s > n)
            _destruct_at_end(_begin + n);
    }

    void reserve(size_type n) {
        if (n > capacity()) {
            vector _v(_a);
            _v._vallocate(n);
            _v._construct_at_end(begin(), end());
            swap(_v);
        }
    }
    // element access
    reference at(size_type n) {
        if (n < 0 || n >= size()) throw std::out_of_range("");
        return this->_begin[n];
    }
    const_reference at(size_type n) const {
        if (n < 0 || n >= size()) throw std::out_of_range("");
        return this->_begin[n];
    }
    reference       front() { return *_begin; }
    const_reference front() const { return *_begin; }
    reference       back() { return *(_end - 1); }
    const_reference back() const { return *(_end - 1); }

    // modifiers

    template <class Iterator>
    void assign(
        Iterator first, Iterator last,
        typename ft::enable_if<!ft::is_integral<Iterator>::value, Iterator>::type * = NULL) {
        return (
            assign_helper(first, last, typename iterator_traits<Iterator>::iterator_category()));
    }

	private:
    template <class Iterator>
    void assign_helper(Iterator first, Iterator last, random_access_iterator_tag) {
        size_type n = static_cast<size_type>(ft::distance(first, last));
        if (n > capacity()) {
            _vdeallocate();
            _vallocate(n);
        } else
            clear();
        for (; first != last; ++first) push_back(*first);
    }

    template <class Iterator>
    void assign_helper(Iterator first, Iterator last, input_iterator_tag) {
        clear();
        for (; first != last; ++first) push_back(*first);
    }

	public:
    void assign(size_type n, const value_type &val) {
        clear();
        if (n < capacity()) {
            size_type s = size();
            if (n > s)
                _construct_at_end(n - s, val);
            else
                _destruct_at_end(_begin + n);
        } else {
            _vdeallocate();
            _vallocate(n);
            _construct_at_end(n, val);
        }
    }

    void push_back(const value_type &val) {
        reserve(size() + 1);
        _a.construct(_end, val);
        ++_end;
    }
    void pop_back() {
        --_end;
        _a.destroy(_end);
    }

    iterator insert(iterator position, const value_type &val) {
        pointer   pos = &(*position);
        size_type dis = static_cast<size_type>(ft::distance(_begin, pos));
        if (pos == _end) {
            push_back(val);
        } else
            insert(position, 1, val);
        return iterator(_begin + dis);
    }

    void insert(iterator position, size_type n, const value_type &val) {
        if (n <= 0) return;
        pointer   pos = &(*position);
        size_type dis = static_cast<size_type>(ft::distance(_begin, pos));
        size_type old_size = size();
        resize(old_size + n);
        ft::copy_from_back(_begin + dis, _begin + old_size, _begin + old_size + n);
        ft::fill(_begin + dis, _begin + dis + n, val);
    }

    template <class Iterator>
    void insert(
        iterator position, Iterator first, Iterator last,
        typename ft::enable_if<!ft::is_integral<Iterator>::value, Iterator>::type * = NULL) {
        return (insert_helper(position, first, last,
                              typename iterator_traits<Iterator>::iterator_category()));
    }

	private:
    template <class Iterator>
    void insert_helper(iterator position, Iterator first, Iterator last,
                       random_access_iterator_tag) {
        if (first == last) return;
        pointer   pos = &(*position);
        size_type n = static_cast<size_type>(ft::distance(first, last));
        size_type dis = static_cast<size_type>(ft::distance(_begin, pos));
        size_type old_size = size();
        resize(old_size + n);
        ft::copy_from_back(_begin + dis, _begin + old_size, _begin + old_size + n);
        ft::copy(first, last, _begin + dis);
    }

    template <class Iterator>
    void insert_helper(iterator position, Iterator first, Iterator last, input_iterator_tag) {
        if (first == last) return;
        if (position == end()) {
            for (; first != last; ++first) push_back(*first);
        } else {
            vector v(first, last);
            insert(position, v.begin(), v.end());
        }
    }

	public:
    iterator erase(iterator position) {
        if (position == _make_iter(_end))
            pop_back();
        else {
            pointer pos = &(*position);
            _destruct_at_end(ft::copy(pos + 1, _end, pos));
        }
        return (position);
    }
    iterator erase(iterator first, iterator last) {
        pointer pos = &(*first);
        if (first != last) _destruct_at_end(ft::copy(pos + (last - first), _end, pos));
        return pos;
    }
    void swap(vector &x) {
        ft::swap(_a, x._a);
        ft::swap(_begin, x._begin);
        ft::swap(_end, x._end);
        ft::swap(_cap_end, x._cap_end);
    }

    void clear() { _destruct_at_end(_begin); }

    // allocator
    allocator_type get_allocator() const { return _a; }

	private:
    iterator       _make_iter(pointer _p) { return iterator(_p); }
    const_iterator _make_iter(const_pointer _p) const { return const_iterator(_p); }

    void _destruct_at_end(pointer new_last) {
        pointer soon_end = _end;
        while (new_last != soon_end && _end != NULL) {
            _a.destroy(--soon_end);
        }
        _end = new_last;
    }

    void _construct_at_front(size_type n, const value_type &x) {
        _end = _begin;
        for (; _end != (_begin + n); ++_end) _a.construct(_end, x);
    }

    void _construct_at_end(size_type n, const value_type &v) {
        pointer new_size = _end + n;
        for (; _end != new_size; ++_end) _a.construct(_end, v);
    }

    void _construct_at_end(
        iterator first, iterator last,
        typename ft::enable_if<!ft::is_integral<iterator>::value, iterator>::type * = NULL) {
        for (; first != last; ++first, ++_end) {
            _a.construct(_end, *first);
        }
    }

    size_type _vcalculate(size_type n) {
        const size_type temp_max_size = this->max_size();
        const size_type temp_capacity = this->capacity();
        if (n > temp_max_size) throw std::length_error("ft::vector");
        if (n < temp_capacity)
            return (temp_capacity);
        else if (n >= temp_capacity && n >= temp_max_size / 2)
            return (temp_max_size);
        return (n * 2);
    }
    void _vallocate(size_type n) {
        n = _vcalculate(n);
        _begin = _a.allocate(n);
        _end = _begin;
        _cap_end = _begin + n;
    }

    void _vdeallocate() {
        if (_begin != NULL) {
            clear();
            _a.deallocate(_begin, capacity());
            _begin = _end = _cap_end = NULL;
        }
    }
};

template <class T, class Alloc>
void swap(vector<T, Alloc> &lhs, vector<T, Alloc> &rhs) {
    lhs.swap(rhs);
}

template <class T, class Alloc>
bool operator==(const ft::vector<T, Alloc> &lhs, const ft::vector<T, Alloc> &rhs) {
    return lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin());
}

template <class T, class Alloc>
bool operator!=(const ft::vector<T, Alloc> &lhs, const ft::vector<T, Alloc> &rhs) {
    return !(lhs == rhs);
}
template <class T, class Alloc>
bool operator<(const ft::vector<T, Alloc> &lhs, const ft::vector<T, Alloc> &rhs) {
    return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template <class T, class Alloc>
bool operator>(const ft::vector<T, Alloc> &lhs, const ft::vector<T, Alloc> &rhs) {
    return rhs < lhs;
}
template <class T, class Alloc>
bool operator<=(const ft::vector<T, Alloc> &lhs, const ft::vector<T, Alloc> &rhs) {
    return !(rhs < lhs);
}
template <class T, class Alloc>
bool operator>=(const ft::vector<T, Alloc> &lhs, const ft::vector<T, Alloc> &rhs) {
    return !(lhs < rhs);
}

}  // namespace ft

#endif