// #include "vector.hpp"
// #include <iostream>

// int	main ()
// {
// 	ft::vector<int> tmp;
// 	ft::vector<int> tmp2(10, 24);
// 	ft::vector<int> tmp3(1, 5);

// 	// std::cout << tmp2.size() << '\n';
// 	// std::cout << tmp2.capacity() << '\n';
// 	// std::cout << tmp2[0] << '\n';
// 	// // tmp2.erase(tmp.begin());
// 	tmp.assign(tmp3.begin(), tmp3.end());
// 	std::cout << "tmp size: " << tmp.size() << "; capacity: " << tmp.capacity() << '\n';
// 	tmp.push_back(1);
// 	tmp.erase(tmp.begin());
// 	std::cout << "tmp size: " << tmp.size() << "; capacity: " << tmp.capacity() << '\n';
// 	// tmp2.swap(tmp);
// 	// std::cout << tmp.size() << '\n';
// 	// std::cout << tmp.capacity() << '\n';
// 	// std::cout << tmp[0] << '\n';
// 	return 0;
// }

#include <iostream>       // std::cout
// #include <stack>          // std::stack
// #include <vector>         // std::vector
// #include <deque>          // std::deque
// #include <list>
// #include <iomanip> //temporal para main 2
// #include "stack.hpp"
// #include "vector.hpp"


// int		main(void)
// {
// 	const int size = 5;
// 	ft::vector<int> vct(size);
// 	ft::vector<int>::reverse_iterator it = vct.rbegin();
// 	ft::vector<int>::const_reverse_iterator ite = vct.rbegin();

// 	for (int i = 0; i < size; ++i)
// 		it[i] = (size - i) * 5;

// 	it = it + 5;
// 	it = 1 + it;
// 	it = it - 4;
// 	std::cout << *(it += 2) << std::endl;
// 	std::cout << *(it -= 1) << std::endl;

// 	*(it -= 2) = 42;
// 	*(it += 2) = 21;

// 	std::cout << "const_ite +=/-=: " << *(ite += 2) << " | " << *(ite -= 2) << std::endl;

// 	std::cout << "(it == const_it): " << (ite == it) << std::endl;
// 	std::cout << "(const_ite - it): " << (ite - it) << std::endl;
// 	std::cout << "(ite + 3 == it): " << (ite + 3 == it) << std::endl;

// 	printSize(vct, true);
// 	return (0);
// }

#include "map.hpp"

int main () 
{
	ft::map<int, char>	map;

	map[3] = 't';
	return 0;
}