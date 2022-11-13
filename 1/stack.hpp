#ifndef STACK_HPP
#define STACK_HPP

#include "vector.hpp"

namespace ft {
template <class T, class Container = ft::vector<T> >
class stack {
   public:
    typedef Container                                container_type;
    typedef typename container_type::value_type      value_type;
    typedef typename container_type::reference       reference;
    typedef typename container_type::const_reference const_reference;
    typedef typename container_type::size_type       size_type;

    explicit stack(const container_type& ctnr = container_type()) : _c(ctnr) {}
    ~stack() {}
    bool              empty() const { return _c.empty(); }
    size_type         size() const { return _c.size(); }
    value_type&       top() { return _c.back(); }
    const value_type& top() const { return _c.back(); }
    void              push(const value_type& val) { _c.push_back(val); }
    void              pop() { _c.pop_back(); }
    void              swap(stack& x);

   protected:
    container_type _c;
    template <class T1, class _C1>
    friend bool operator==(const stack<T1, _C1>& __x, const stack<T1, _C1>& __y);
    template <class T1, class _C1>
    friend bool operator<(const stack<T1, _C1>& __x, const stack<T1, _C1>& __y);
};

template <class T, class Container>
bool operator==(const stack<T, Container>& lhs, const stack<T, Container>& rhs) {
    return lhs._c == rhs._c;
}
template <class T, class Container>
bool operator!=(const stack<T, Container>& lhs, const stack<T, Container>& rhs) {
    return !(lhs == rhs);
}
template <class T, class Container>
bool operator<(const stack<T, Container>& lhs, const stack<T, Container>& rhs) {
    return lhs._c < rhs._c;
}
template <class T, class Container>
bool operator<=(const stack<T, Container>& lhs, const stack<T, Container>& rhs) {
    return !(rhs < lhs);
}
template <class T, class Container>
bool operator>(const stack<T, Container>& lhs, const stack<T, Container>& rhs) {
    return rhs < lhs;
}
template <class T, class Container>
bool operator>=(const stack<T, Container>& lhs, const stack<T, Container>& rhs) {
    return !(lhs < rhs);
}
}  // namespace ft

#endif
