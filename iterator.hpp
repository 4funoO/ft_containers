/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doreshev <doreshev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 16:04:32 by doreshev          #+#    #+#             */
/*   Updated: 2022/10/20 11:23:25 by doreshev         ###   ########.fr       */
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
}

#endif