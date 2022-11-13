#include <list>
#include <iostream>
#if 1  // CREATE A REAL STL EXAMPLE
#include <map>
#include <stack>
#include <vector>
namespace ft = std;
#else
#include <map.hpp>
#include <stack.hpp>
#include <vector.hpp>
#endif

template <class T>
void print(ft::vector<T> &y) {
    typename ft::vector<T>::iterator  it = y.begin();
    while (it != y.end()) {
        std::cout << *it << std::endl;
        ++it;
    }
}

int main() {

	std::cout << "VECTOR" << std::endl;

    try {
        ft::vector<int> v;
        v.assign("uvg6KqtcgduR31n3ajsv", "wbiAcjgojb9JOagZwyMn");
        v.assign("QExoqp0nICr0sXsHqty2", "naax9QcpJhvaL7DezsNQ");
        v.assign("l0IIcWWHhOcPzoxEamQM", "bE1RYclskwXlhCm46YFs");
        ft::vector<int> svec(3, 42);
        ft::vector<int> sveca(svec.begin(), svec.end());
        ft::vector<int> svecb(sveca);
        std::cout << "-------v-------" << std::endl;
        print(v);
        std::cout << sveca.size() << std::endl;
        std::cout << "-------b-------" << std::endl;
        print(svecb);
        std::cout << svecb.size() << std::endl;
    } catch (...) {
        std::cout << "exception caught" << std::endl;
    }

    std::list<int>           lst;
    std::list<int>::iterator lst_it;
    for (int i = 1; i < 5; ++i) lst.push_back(i * 3);

    ft::vector<int> vct(lst.begin(), lst.end());
	std::cout << vct.size() << std::endl;
	std::cout << vct.capacity() << std::endl;

    lst_it = lst.begin();
    for (int i = 1; lst_it != lst.end(); ++i) *lst_it++ = i * 5;
    vct.assign(lst.begin(), lst.end());
	std::cout << vct.size() << std::endl;
	std::cout << vct.capacity() << std::endl;

    vct.insert(vct.end(), lst.rbegin(), lst.rend());
	std::cout << vct.size() << std::endl;
	std::cout << vct.capacity() << std::endl;

    std::cout << "MAP" << std::endl;
	ft::map<int, int> m;

	typedef ft::map<int, int>::iterator iterator;

	for (int i = 0; i < 5; ++i) {
		m.insert(ft::make_pair(i, i));
	}

	std::cout << "########## from begin to end ##########" << std::endl;
	for (iterator it = m.begin(); it != m.end(); it = m.begin()) {
		std::cout << (*it).first << std::endl;
		m.erase(it);
	}

	for (int i = 0; i < 10; ++i) {
		m.insert(ft::make_pair(i, i));
	}
	std::cout << "########## normal iter ##########" << std::endl;
	ft::map<int, int>::iterator it = m.begin();

	std::cout << "++iter" << std::endl;
	while (it != m.end()) {
		std::cout << (*it).first << std::endl;
		++it;
	}
	it = m.begin();
	std::cout << "iter++" << std::endl;
	while (it != m.end()) {
		std::cout << (*it).first << std::endl;
		it++;
	}
	it = m.end();
	std::cout << "iter--" << std::endl;
	while (it != m.begin()) {
		it--;
		std::cout << (*it).first << std::endl;
	}
	it = m.end();
	std::cout << "--iter" << std::endl;
	while (it != m.begin()) {
		--it;
		std::cout << (*it).first << std::endl;
	}
	std::cout << "reverse iter" << std::endl;
	ft::map<int, int>::reverse_iterator rit = m.rbegin();

	std::cout << "++iter" << std::endl;
	while (rit != m.rend()) {
		std::cout << (*rit).first << std::endl;
		++rit;
	}
    rit = m.rbegin();
    std::cout << "iter++" << std::endl;
	while (rit != m.rend()) {
		std::cout << (*rit).first << std::endl;
		rit++;
	}

	rit = m.rend();
	std::cout << "--iter" << std::endl;
	while (rit != m.rbegin()) {
		--rit;
		std::cout << (*rit).first << std::endl;
	}
        rit = m.rend();
        std::cout << "iter--" << std::endl;
	while (rit != m.rbegin()) {
		rit--;
		std::cout << (*rit).first << std::endl;
	}
}
