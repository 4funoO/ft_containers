/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VectorIterator.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doreshev <doreshev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 13:51:15 by doreshev          #+#    #+#             */
/*   Updated: 2022/10/27 13:02:31 by doreshev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTORITERATOR_HPP
# define VECTORITERATOR_HPP

# include "iterator.hpp"
# include "../vector.hpp"

namespace ft{
	//VECTOR ITERATORS
	template <class T>
	class VectorIterator {
	public:
		typedef	T*															iterator_type;
		typedef typename iterator_traits<iterator_type>::value_type			value_type;
    	typedef typename iterator_traits<iterator_type>::difference_type	difference_type;
    	typedef typename iterator_traits<iterator_type>::pointer			pointer;
    	typedef typename iterator_traits<iterator_type>::reference			reference;

	public:
	// CONSTRUCTORS
		// 1) Default
		VectorIterator() : _ptr(nullptr) { }
		// 2) Initialization
		VectorIterator(pointer ptr) : _ptr(ptr) { }
		// 3) Copy
		VectorIterator ( const VectorIterator& x ) { _ptr = x._ptr; }
	// ASSIGN OPERATOR
		VectorIterator& operator=( const VectorIterator& x ) {
			if (*this != x)
				_ptr = x.base();
			return	*this;
		}
	// DESTRUCTOR
		~VectorIterator() { }
	// MEMBER FUNCTIONS
		// Base - returns base iterator
		pointer	base() const {
			return _ptr;
		}
		// Pre-increment iterator position
		VectorIterator&	operator++() {
			++_ptr;
			return *this;
		}
		// Post-increment iterator position
		VectorIterator	operator++(int) {
			VectorIterator temp = *this;
			++_ptr;
			return temp;
		}
		// Dereference iterator
		reference	operator*() const {
			return *_ptr;
		}
		// Dereference iterator
		pointer operator->() const {
			return _ptr;
		}
		// Pre-decrement iterator position
		VectorIterator&	operator--() {
			--_ptr;
			return *this;
		}
		// Post-decrement iterator position
		VectorIterator	operator--(int) {
			VectorIterator temp = *this;
			--_ptr;
			return temp;
		}
		// Addition operator
		VectorIterator	operator+ (difference_type n) const {
			return VectorIterator(_ptr + n);
		}
		// Advance iterator
		VectorIterator&	operator+= (difference_type n) {
			_ptr += n;
			return *this;
		}
		// Subtraction operator
		VectorIterator	operator- (difference_type n) const {
			return VectorIterator(_ptr - n);
		}
		// Retrocede iterator
		VectorIterator&	operator-= (difference_type n) {
			_ptr -= n;
			return *this;
		}
		// Dereference iterator with offset
		reference	operator[] (difference_type n) const {
			return *(_ptr + n);
		}

	protected:
		pointer		_ptr;
	};

	//RELATIONAL OPERATORS 
	template <class T>
	bool operator==(const VectorIterator<T>& lhs, const VectorIterator<T>& rhs) {
		return lhs.base() == rhs.base();
	}
	template <class T>
	bool operator!=(const VectorIterator<T>& lhs, const VectorIterator<T>& rhs) {
		return lhs.base() != rhs.base();
	}
	template <class T>
	bool operator>(const VectorIterator<T>& lhs, const VectorIterator<T>& rhs) {
		return lhs.base() > rhs.base();
	}
	template <class T>
	bool operator>=(const VectorIterator<T>& lhs, const VectorIterator<T>& rhs) {
		return lhs.base() >= rhs.base();
	}
	template <class T>
	bool operator<(const VectorIterator<T>& lhs, const VectorIterator<T>& rhs) {
		return lhs.base() < rhs.base();
	}
	template <class T>
	bool operator<=(const VectorIterator<T>& lhs, const VectorIterator<T>& rhs) {
		return lhs.base() <= rhs.base();
	}
	// COMPUTES THE DISTANCE BETWEEN TWO ITERATOR ADAPTORS
	template<class Iterator>
	typename VectorIterator<Iterator>::difference_type
		operator-(	const VectorIterator<Iterator>& lhs, const VectorIterator<Iterator>& rhs ) {
			return rhs.base() - lhs.base();
	}
	// ADVANCES THE ITERATOR
	template<class Iterator>
	VectorIterator<Iterator>
		operator+( typename VectorIterator<Iterator>::difference_type n, const VectorIterator<Iterator>& it ) {
			return VectorIterator<Iterator>(it.base() + n);
	}
}

#endif