/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doreshev <doreshev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 16:04:32 by doreshev          #+#    #+#             */
/*   Updated: 2022/10/25 18:24:55 by doreshev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
# define ITERATOR_HPP

namespace ft {

	//ITERATOR TRAITS
	template <class Iterator>
	class iterator_traits {
		
	};
	
	template <class T>
	class iterator_traits<T*> {
		
	};
	
	template <class T>
	class iterator_traits<const T*> {
		
	};
	//REVERSE ITERATOR
	template <class Iterator>
	class reverse_iterator {
		
	};

	template<class It>
	typename ft::iterator_traits<It>::difference_type 
	    do_distance(It first, It last, ft::input_iterator_tag)
	{
	    typename ft::iterator_traits<It>::difference_type result = 0;
	    while (first != last) {
	        ++first;
	        ++result;
	    }
	    return result;
	}
	
	template<class It>
	typename ft::iterator_traits<It>::difference_type
	    do_distance(It first, It last, ft::random_access_iterator_tag) {
	    return last - first;
	}
	template<class It>
	typename ft::iterator_traits<It>::difference_type 
	    distance(It first, It last) {
	    return ft::do_distance(first, last,
	                               typename ft::iterator_traits<It>::iterator_category());
	}

}

#endif