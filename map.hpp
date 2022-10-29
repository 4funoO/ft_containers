/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doreshev <doreshev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 16:03:32 by doreshev          #+#    #+#             */
/*   Updated: 2022/10/29 17:27:33 by doreshev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

# include <stdexcept>
# include "iterators/TreeIterator.hpp"
# include "algorithm.hpp"
# include "type_traits.hpp"

namespace ft {
	template<class Key, class T, class Compare = std::less<Key>,
			class Allocator = std::allocator<std::pair<const Key, T>> > class map {
	public:
		typedef	Key											key_type;
		typedef	T											mapped_type;
		typedef	Compare										key_compare;
		typedef	typename pair<const Key, T>					value_type;
		typedef												value_compare; /////////
		typedef	Allocator									allocator_type;
		typedef	typename allocator_type::reference			reference;
		typedef	typename allocator_type::const_reference	const_reference;
		typedef	typename allocator_type::pointer			pointer;
		typedef	typename allocator_type::const_pointer		const_pointer;
		typedef	typename allocator_type::size_type			size_type;
		typedef typename allocator_type::difference_type	difference_type;
		typedef	ft::TreeIterator<value_type>				iterator;
		typedef	ft::TreeIterator<const value_type>			const_iterator;
		typedef	ft::reverse_iterator<iterator>				reverse_iterator;
		typedef	ft::reverse_iterator<const_iterator>		const_reverse_iterator;
	};
}

#endif