#include <list>
#include "map.hpp"
#include <iostream>

// template <typename T>
// class foo {
// 	public:
// 		typedef T	value_type;

// 		foo(void) : value(), _verbose(false) { };
// 		foo(value_type src, const bool verbose = false) : value(src), _verbose(verbose) { };
// 		foo(foo const &src, const bool verbose = false) : value(src.value), _verbose(verbose) { };
// 		~foo(void) { if (this->_verbose) std::cout << "~foo::foo()" << std::endl; };
// 		void m(void) { std::cout << "foo::m called [" << this->value << "]" << std::endl; };
// 		void m(void) const { std::cout << "foo::m const called [" << this->value << "]" << std::endl; };
// 		foo &operator=(value_type src) { this->value = src; return *this; };
// 		foo &operator=(foo const &src) {
// 			if (this->_verbose || src._verbose)
// 				std::cout << "foo::operator=(foo) CALLED" << std::endl;
// 			this->value = src.value;
// 			return *this;
// 		};
// 		value_type	getValue(void) const { return this->value; };
// 		void		switchVerbose(void) { this->_verbose = !(this->_verbose); };

// 		operator value_type(void) const {
// 			return value_type(this->value);
// 		}
// 	private:
// 		value_type	value;
// 		bool		_verbose;
// };

// template <typename T>
// std::string	printPair(const T &iterator, bool nl = true, std::ostream &o = std::cout)
// {
// 	o << "key: " << iterator->first << " | value: " << iterator->second;
// 	if (nl)
// 		o << std::endl;
// 	return ("");
// }

// template <typename T_MAP>
// void	printSize(T_MAP const &mp, bool print_content = 1)
// {
// 	std::cout << "size: " << mp.size() << std::endl;
// 	std::cout << "max_size: " << mp.max_size() << std::endl;
// 	if (print_content)
// 	{
// 		typename T_MAP::const_iterator it = mp.begin(), ite = mp.end();
// 		std::cout << std::endl << "Content is:" << std::endl;
// 		for (; it != ite; ++it)
// 			std::cout << "- " << printPair(it, false) << std::endl;
// 	}
// 	std::cout << "###############################################" << std::endl;
// }

// template <typename T1, typename T2>
// void	printReverse(ft::map<T1, T2> &mp)
// {
// 	typename ft::map<T1, T2>::iterator it = mp.end(), ite = mp.begin();

// 	std::cout << "printReverse:" << std::endl;
// 	while (it != ite) {
// 		it--;
// 		std::cout << "-> " << printPair(it, false) << std::endl;
// 	}
// 	std::cout << "_______________________________________________" << std::endl;
// }

// #define T1 int
// #define T2 std::string
// typedef ft::map<T1, T2>::value_type T3;

// static int iter = 0;

// template <typename MAP>
// void	ft_erase(MAP &mp, const T1 param)
// {
// 	std::cout << "\t-- [" << iter++ << "] --" << std::endl;
// 	mp.erase(param);
// 	printSize(mp);
// }

// int		main(void)
// {
// 	ft::map<T1, T2> mp;

// 	mp[42] = "lol";

// 	mp[50] = "mdr";
// 	mp[25] = "funny";

// 	mp[46] = "bunny";
// 	mp[21] = "fizz";
// 	mp[30] = "buzz";
// 	mp[55] = "fuzzy";

// 	mp[18] = "bee";
// 	mp[23] = "coconut";
// 	mp[28] = "diary";
// 	mp[35] = "fiesta";
// 	mp[44] = "hello";
// 	mp[48] = "world";
// 	mp[53] = "this is a test";
// 	mp[80] = "hey";

// 	mp[12] = "no";
// 	mp[20] = "idea";
// 	mp[22] = "123";
// 	mp[24] = "345";
// 	mp[27] = "27";
// 	mp[29] = "29";
// 	mp[33] = "33";
// 	mp[38] = "38";

// 	mp[43] = "1";
// 	mp[45] = "2";
// 	mp[47] = "3";
// 	mp[49] = "4";
// 	mp[51] = "5";
// 	mp[54] = "6";
// 	mp[60] = "7";
// 	mp[90] = "8";

// 	printSize(mp);

// 	/* A classic btree should give this:
// 	 *                                      42
// 	 *                     /                                            \
// 	 *                    25                                            50
// 	 *           /                 \                         /                       \
// 	 *          21                 30                       46                       55
// 	 *      /       \           /      \                /       \             /           \
// 	 *     18       23        28        35            44         48         53             80
// 	 *   /   \    /    \    /    \     /   \        /   \       /   \     /    \         /     \
// 	 *  12   20  22    24  27    29  33    38     43    45    47    49   51    54       60      90
// 	 *
// 	 * */

// 	ft_erase(mp, 25); // right != NULL; left != NULL
// 	ft_erase(mp, 55); // right != NULL; left != NULL

// 	/* After deleting 25 and 55, I would get:
// 	 *                                      42
// 	 *                     /                                            \
// 	 *                    24                                            50
// 	 *           /                 \                         /                      \
// 	 *          21                 30                       46                      54
// 	 *      /       \           /      \                /       \             /           \
// 	 *     18       23        28        35            44         48         53             80
// 	 *   /   \    /         /    \     /   \        /   \       /   \     /              /     \
// 	 *  12   20  22        27    29  33    38     43    45    47    49   51             60      90
// 	 *
// 	 * */

// 	ft_erase(mp, 24); // right != NULL; left != NULL
// 	ft_erase(mp, 54); // right != NULL; left != NULL

// 	/* After deleting 24 and 54, I would get:
// 	 *                                      42
// 	 *                     /                                            \
// 	 *                    23                                            50
// 	 *           /                 \                         /                      \
// 	 *          21                 30                       46                      53
// 	 *      /       \           /      \                /       \             /           \
// 	 *     18       22        28        35            44         48         51             80
// 	 *   /   \              /    \     /   \        /   \       /   \                    /     \
// 	 *  12   20            27    29  33    38     43    45    47    49                  60      90
// 	 *
// 	 * */

// 	ft_erase(mp, 22); // right == NULL; left == NULL
// 	ft_erase(mp, 51); // right == NULL; left == NULL

// 	ft_erase(mp, 21); // right == NULL; left != NULL
// 	ft_erase(mp, 53); // right != NULL; left == NULL

// 	/* After deleting 22, 51 and then 21, 53, I would get:
// 	 *                                      42
// 	 *                     /                                            \
// 	 *                    23                                            50
// 	 *           /                 \                         /                      \
// 	 *          20                 30                       46                      80
// 	 *      /                   /      \                /       \                /        \
// 	 *     18                 28        35            44         48             60         90
// 	 *   /                  /    \     /   \        /   \       /   \
// 	 *  12                 27    29  33    38     43    45    47    49
// 	 *
// 	 * */

// 	ft_erase(mp, 20); // right == NULL; left != NULL

// 	/* After deleting 20, I would get:
// 	 *                                      42
// 	 *                     /                                            \
// 	 *                    23                                            50
// 	 *           /                 \                         /                      \
// 	 *          18                 30                       46                      80
// 	 *      /                   /      \                /       \                /        \
// 	 *     12                 28        35            44         48             60         90
// 	 *                      /    \     /   \        /   \       /   \
// 	 *                     27    29  33    38     43    45    47    49
// 	 *
// 	 * */

// 	ft_erase(mp, 23); // right != NULL; left != NULL

// 	/* After deleting 23, I would get:
// 	 *                                      42
// 	 *                     /                                            \
// 	 *                    18                                            50
// 	 *           /                 \                         /                      \
// 	 *          12                 30                       46                      80
// 	 *                          /      \                /       \                /        \
// 	 *                        28        35            44         48             60         90
// 	 *                      /    \     /   \        /   \       /   \
// 	 *                     27    29  33    38     43    45    47    49
// 	 *
// 	 * */

// 	ft_erase(mp, 42); // right != NULL; left != NULL; parent == NULL

// 	/* After deleting 42, I would get:
// 	 *                                      38
// 	 *                     /                                            \
// 	 *                    18                                            50
// 	 *           /                 \                         /                      \
// 	 *          12                 30                       46                      80
// 	 *                          /      \                /       \                /        \
// 	 *                        28        35            44         48             60         90
// 	 *                      /    \     /            /   \       /   \
// 	 *                     27    29  33           43    45    47    49
// 	 *
// 	 * */

// 	ft_erase(mp, 38); // right != NULL; left != NULL; parent == NULL

// 	/* After deleting 38, I would get:
// 	 *                                      35
// 	 *                     /                                            \
// 	 *                    18                                            50
// 	 *           /                 \                         /                      \
// 	 *          12                 30                       46                      80
// 	 *                          /      \                /       \                /        \
// 	 *                        28        33            44         48             60         90
// 	 *                      /    \                  /   \       /   \
// 	 *                     27    29               43    45    47    49
// 	 *
// 	 * */

// 	ft_erase(mp, 35); // right != NULL; left != NULL; parent == NULL

// 	/* After deleting 35, I would get:
// 	 *                                      33
// 	 *                     /                                            \
// 	 *                    18                                            50
// 	 *           /                 \                         /                      \
// 	 *          12                 30                       46                      80
// 	 *                          /                       /       \                /        \
// 	 *                        28                      44         48             60         90
// 	 *                      /    \                  /   \       /   \
// 	 *                     27    29               43    45    47    49
// 	 *
// 	 * */

// 	ft_erase(mp, 33); // right != NULL; left != NULL; parent == NULL

// 	/* After deleting 33, I would get:
// 	 *                                      30
// 	 *                     /                                            \
// 	 *                    18                                            50
// 	 *           /                 \                         /                      \
// 	 *          12                 28                       46                      80
// 	 *                          /      \                /       \                /        \
// 	 *                        27       29             44         48             60         90
// 	 *                                              /   \       /   \
// 	 *                                            43    45    47    49
// 	 *
// 	 * */

// 	return (0);
// }
template <typename T>
void init_array_int_str(ft::pair<int, std::string>* arr, std::size_t size)
{
    std::string x[64] = { "CBCId4lUU6oYms60JkNr", "V5sbXjlqYRAV1C1LgJbt", "TPcK94z2htaoK5hWpR1j",
                          "WA1JMsjadjyjQjJLxVkE", "aDhJUsH7AVnKLfzQGcPC", "DPpRIm6G9C5CWSWYLwnt",
                          "aKyxvwuxzUAksmm7s8o3", "d8NpBFRFI87WxlYiRzJB", "5RDlRrY8OFBkqtlD5R33",
                          "W4dsiGdNWranxT1qbPt9", "uUxBDNzk3Tpg1bIow0uf", "FiKAXgTFhhPhmRkfXci9",
                          "02Fxrj1KnMufOpH1gbxw", "hSV7LrNPzTKHS6h7BRW6", "YzIjmI4i4Fum1gzs9QFy",
                          "6jjGwGu20C7dXFRgdCU8", "bej1zTuyCJGa0b4KXgQO", "ckkK36lt3kBVH1PYvbib",
                          "Gs9kLamEeSWqM9ORSlzF", "oJTGXtRpq4rz6IBt2Gc2", "6XSQM096yPnzWqydO7Fl",
                          "Kw91n77jigS09IQEYFw0", "K0Qj3EOV96U6xbBDMkaP", "i0b4NYygRb7ZuT3HOE61",
                          "C6KyCaoRm5MncGCjjP0I", "6xxl5c88m0Rq5CkTPsTU", "xtZ16NJzNU4IEnzsily8",
                          "2ofwuG2e80JGsK8VdB6r", "UjhRe94EahPlXuBbIV0q", "be5WTfjjKVBU8cezAjH8",
                          "zOWJPAQLV4wgVGJTC0uV", "nuqgXoNhZpL8uMvbDcT7", "HdCk0Gm8Gn3eqcVYxcYD",
                          "PuIS5xPbBpGe3MHG7SNm", "ZY6finqJMbHpB6dKlenn", "VJfBTOFj9reLm3iGU2Fs",
                          "UFWOX8UzTSzSAGMvGRIC", "cZfcw5yVwFprkH2v3FQO", "V34DSjjaiDianUKjRFCj",
                          "j7SHtomH6GvAY8y0nL9E", "3z82NvciqTwWW2Lp7MET", "S1BDCdeUHLIVB6I8zaIc",
                          "OkuQPNHq0AnYY9Pemxpn", "yH5J2tI4oQzVsPBB226z", "aafwp6lvuOxv5JkUBUlA",
                          "RjRwqlQ0hnxYnglid2x3", "3RBzhOIHFtRtZBHNlCVv", "lttYCjRWSXYKeyIgvpJv",
                          "6KhIc7LvaTTwklmmbjBO", "IDlAqFCEdFTJcVW36RsY", "pDGkqtvKVRReq19BFVwN",
                          "88UJAeNtrlAwEu4BGiSb", "eFN5bxsWa4dAnvZdzToE", "B3cqY0IqO2IH2yGMnX7e",
                          "BRcU6oFTAC8IWuiSrTEa", "dtBZVLQMx9MBw1eak8SB", "zM2XVrazn2fXAsRHDc16",
                          "qqlM2sERpGhcZJAv3qPR", "4Lru0dOIQpWGYlcx9oyn", "HSH0O0igQruyLC1FmQVs",
                          "mXHcnXiXhKJwJ0BUSpje", "sXhbSe7MQHhvJ9XQcrrX", "aTejup4iQw70n78erKEB",
                          "1IRLC9sfQI5AzDYeotLd" };

    for (std::size_t i = 0; i < size; ++i) {
        arr[i] = ft::make_pair(rand(), x[i]);
    }
}

template <typename T>
void init_array_str_str(ft::pair<std::string, std::string>* arr, std::size_t size)
{
    std::string x[32] = { "RxWAUMME3GtF9Zbv3a4M", "WC96vs7Z6I6TfdGxObUg", "2beuhrfBZvjdkmfqV9yn",
                          "AuIhF3lUgwT0OMy8DuUx", "dVW2KAL06gB4s7rEf508", "jnsp7MGfl5wZNZVfQSvp",
                          "p26Kfhz0Iof6rJDy27vc", "bnWXfp2eexq7MPpcmRSI", "tMEU0L6RNvqDAaV6HN0e",
                          "POcbaPteUMFfltrwdu7r", "epDGhJZoKoL4i1HO67XS", "o83N1RTIeOafqBfqeAYh",
                          "aYRtwuDT8k7k7iIfTrtU", "fEPXIREoFGKXqnNKySG5", "QrqmIbVVIQzf8WKBxiga",
                          "k5NSg0Dq0b9ewfrhYdy7", "Tf9dsqBADfMeWVQGG3Zk", "dS2LouElpUXsXNCClr4B",
                          "tsvf3JaWNg5JlSDZs1Dm", "oWurB8fBAIBQq1ZnlFiR", "8YllXP80XunEXhqnjkZc",
                          "Spt36tVcEkIFjwogWli0", "c25H1u6DF9RVdagn81DA", "AjWfT7TlXgzSKOywpoTH",
                          "ZwTg8WNnmXOJKdW6ZeJv", "E9aYpoCXd1kbSWhdLOnf", "QN1iAuoSNQ5WvHeSeSSL",
                          "7g5wfNllowIaqMUVjywr", "b38gJrosdk9xEQ2K8Gbu", "KdVdRVLHJg9Bazc4cpM7",
                          "COJeGmQEzjXwqKCAnd6J", "2k6XCpXEkP7QoST6uYoy" };

    std::string y[32] = { "TZ3QuE3ZNUbFrEpQhgcY", "BX2lyPzOWRIznb34T5OT", "v7lPrSeDokdBIUXR9QGh",
                          "nAQxkuEYL5k1Er7FspKu", "r8T4oZaWBI1m7sPBEDz3", "pdxM9tJrYZskZla7L7yM",
                          "dIIx6eKTfygu24SNKa32", "tw04BOo705mdWxuDciNO", "q94icFprhKrrFXLvjEN3",
                          "uM25BWUl14NTlTwFsNIv", "2oTV9fXUESLQqzvsPFmd", "W6ASLRzrlOggx5b7CtYN",
                          "bz4BQ7rLU203RNwwmbMK", "jfWgRPiuy1P3NGDPWmbe", "PgtdYLdGuneYEUgMA8SB",
                          "eaaFugCSOOU5my4y4SkG", "gGd4FiUEJwgvhOCSHu9g", "9K0ZhqlbyDCJXYXHoEIN",
                          "VTmk8m7rbEGl8ntGpTCQ", "eRJ98PUF2tSMX6zpDOi4", "wFMJIDAbjYnJkxMxkAtL",
                          "JCOXV4iPcIt72DcNnbuY", "LsnOUrHHD2FNFH5DMvbc", "YVPp2jPqK3jmif7yY14r",
                          "JBMhRRtLY3QX3x1ZVDCs", "Uwo5PD2RLMx5ByW9Rscq", "O4Q6DPBJHOelMtBKc9GQ",
                          "Bq0H2eqnuCYqyj9F5Lkn", "P2fJf0TYN92iUXkwELjG", "f656ltXlumpc7YyPVjan",
                          "YQfr76LAA1xKokfq8HpL", "6utvLeZ9t0IM4OkdfAQ2" };

    for (std::size_t i = 0; i < size; ++i) {
        arr[i] = ft::make_pair(x[i], y[i]);
    }
}


void map_test_erase()
{
    ft::pair<int, std::string> intstr_arr[64];                                              
    init_array_int_str<void>(intstr_arr, 64);                                                      
    ft::pair<std::string, std::string> strstr_arr[32];                                      
    init_array_str_str<void>(strstr_arr, 32);                                                      
    std::size_t intstr_size = 64;                                                                  
    std::size_t strstr_size = 32;
    
        ft::map<int, std::string> m(intstr_arr, intstr_arr + 25);

        ft::map<int, std::string>::iterator it = m.begin();

        m.erase(it);

        it = m.begin();

        std::advance(it, 21);

        m.erase(it);

        it = m.end();

        std::advance(it, -10);

        m.erase(it);

        it = m.end();

        std::advance(it, -3);

        m.erase(it);

        it = m.end();

        std::advance(it, -1);

        m.erase(it);

        it = m.begin();

        std::advance(it, 1);

        m.erase(it);

        for (it = m.begin(); it != m.end(); it = m.begin()) {
            m.erase(it);
        }
    
}

int main ()
{
	map_test_erase();
}
