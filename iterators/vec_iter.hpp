/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_iter.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doreshev <doreshev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 13:51:15 by doreshev          #+#    #+#             */
/*   Updated: 2022/10/25 17:26:05 by doreshev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC_ITER_HPP
# define VEC_ITER_HPP

# include "iterator.hpp"


namespace ft{
	//VECTOR ITERATORS
	template <typename T>
	class VectorIterator {
	public:
		typedef typename iterator_traits<iterator_type>::value_type			value_type;
    	typedef typename iterator_traits<iterator_type>::difference_type	difference_type;
    	typedef typename iterator_traits<iterator_type>::pointer			pointer;
    	typedef typename iterator_traits<iterator_type>::reference			reference;
	protected:
		pointer	_ptr;
	public:
		VectorIterator() : _ptr(nullptr) { }
		VectorIterator(pointer ptr) : _ptr(ptr) { }
		VectorIterator ( const VectorIterator& x ) { _ptr = x._ptr; }
		VectorIterator& operator=( const VectorIterator& x ) {
			_ptr = x._ptr;
			return	*this;
		}
		~VectorIterator() { }
		
		VectorIterator& operator++() { 
			_ptr++;
			return *this;
		}
		
		VectorIterator& operator--() { 
			_ptr--;
			return *this;
		}

		reference	operator[]( size_type index ) {
			return *(_ptr + index);
		}
		
		pointer	operator->() {
			return _ptr;
		}
		
		reference	operator*() {
			return *_ptr;
		}
	};

		template <class T>
		bool operator==(const VectorIterator& lhs, const vector<T,Alloc>& rhs) {
			return lhs.size() == rhs.size() &&ft::equal(lhs.begin(), lhs.end(), rhs.begin());		
		}
		template <class T, class Alloc>
		bool operator<(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
			return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
		}
		template <class T, class Alloc>
		bool	operator>(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) { 
			return rhs < lhs;
		}
		template <class T, class Alloc>
		bool	operator!=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
			return !(lhs == rhs);
		}
		template <class T, class Alloc>
		bool	operator<=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
			return !(rhs < lhs);
		}
		template <class T, class Alloc>
		bool	operator>=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
			return !(lhs < rhs);
		}


}

#endif