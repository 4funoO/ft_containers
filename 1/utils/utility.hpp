#pragma once

namespace ft {

template <class T1, class T2>
struct pair {
   public:
    T1 first;
    T2 second;

    pair() : first(), second() {}

    template <class U1, class U2>
    pair(const pair<U1, U2> &p) : first(p.first), second(p.second) {}
    pair(const T1 &x, const T2 &y) : first(x), second(y) {}
    pair &operator=(const pair &p) {
        first = p.first;
        second = p.second;
        return *this;
    };
};

template <class T1, class T2>
pair<T1, T2> make_pair(T1 x, T2 y) {
    return pair<T1, T2>(x, y);
}

template <class T1, class T2>
bool operator==(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
    return (lhs.first == rhs.first && lhs.second == rhs.second);
}
template <class T1, class T2>
bool operator!=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
    return !(lhs == rhs);
}
template <class T1, class T2>
bool operator<(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
    return (lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second));
}
template <class T1, class T2>
bool operator<=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
    return !(lhs < rhs);
}
template <class T1, class T2>
bool operator>(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
    return (lhs < rhs);
}
template <class T1, class T2>
bool operator>=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
    return !(lhs < rhs);
}
}  // namespace ft