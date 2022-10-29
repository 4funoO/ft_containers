/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TreeIterator.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doreshev <doreshev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 15:52:31 by doreshev          #+#    #+#             */
/*   Updated: 2022/10/29 16:26:03 by doreshev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TreeIterator.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doreshev <doreshev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 13:51:15 by doreshev          #+#    #+#             */
/*   Updated: 2022/10/28 17:33:01 by doreshev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREEITERATOR_HPP
# define TREEITERATOR_HPP

# include "iterator.hpp"
# include "../map.hpp"

namespace ft{
	//VECTOR ITERATORS
	template <class T>
	class TreeIterator {
	public:
		typedef	T*															iterator_type;
		typedef typename iterator_traits<iterator_type>::value_type			value_type;
    	typedef typename iterator_traits<iterator_type>::difference_type	difference_type;
    	typedef typename iterator_traits<iterator_type>::pointer			pointer;
    	typedef typename iterator_traits<iterator_type>::reference			reference;
		typedef typename iterator_traits<iterator_type>::iterator_category	iterator_category;

	// CONSTRUCTORS
		// 1) Default
		TreeIterator() : _ptr() { }
		// 2) Initialization
		TreeIterator(const iterator_type& ptr) : _ptr(ptr) { }
		// 3) Copy
		TreeIterator ( const TreeIterator& x ) { _ptr = x.base(); }
	// ASSIGN OPERATOR
		TreeIterator& operator=( const TreeIterator& x ) {
			if (*this != x)
				_ptr = x.base();
			return	*this;
		}
	// DESTRUCTOR
		~TreeIterator() { }
	// MEMBER FUNCTIONS
		// Base - returns base iterator
		pointer	base() const {
			return _ptr;
		}
		// Pre-increment iterator position
		TreeIterator&	operator++() {
			++_ptr;
			return *this;
		}
		// Post-increment iterator position
		TreeIterator	operator++(int) {
			TreeIterator temp = *this;
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
		TreeIterator&	operator--() {
			--_ptr;
			return *this;
		}
		// Post-decrement iterator position
		TreeIterator	operator--(int) {
			TreeIterator temp = *this;
			--_ptr;
			return temp;
		}
		// Addition operator
		TreeIterator	operator+ (difference_type n) const {
			return TreeIterator(_ptr + n);
		}
		// Advance iterator
		TreeIterator&	operator+= (difference_type n) {
			_ptr += n;
			return *this;
		}
		// Subtraction operator
		TreeIterator	operator- (difference_type n) const {
			return TreeIterator(_ptr - n);
		}
		// Retrocede iterator
		TreeIterator&	operator-= (difference_type n) {
			_ptr -= n;
			return *this;
		}
		// Dereference iterator with offset
		reference	operator[] (difference_type n) const {
			return *(_ptr + n);
		}
		// Constant cast overload
		operator TreeIterator<const T>() const {
			return (_ptr);
		}
	protected:
		pointer		_ptr;
	};

	//RELATIONAL OPERATORS 
	template <class T>
	bool operator==(const TreeIterator<T>& lhs, const TreeIterator<T>& rhs) {
		return lhs.base() == rhs.base();
	}
	template <class T, class T1>
	bool operator==(const TreeIterator<T>& lhs, const TreeIterator<T1>& rhs) {
		return lhs.base() == rhs.base();
	}
	template <class T>
	bool operator!=(const TreeIterator<T>& lhs, const TreeIterator<T>& rhs) {
		return lhs.base() != rhs.base();
	}
	template <class T, class T1>
	bool operator!=(const TreeIterator<T>& lhs, const TreeIterator<T1>& rhs) {
		return lhs.base() != rhs.base();
	}
	template <class T>
	bool operator>(const TreeIterator<T>& lhs, const TreeIterator<T>& rhs) {
		return lhs.base() > rhs.base();
	}
	template <class T, class T1>
	bool operator>(const TreeIterator<T>& lhs, const TreeIterator<T1>& rhs) {
		return lhs.base() > rhs.base();
	}
	template <class T>
	bool operator<(const TreeIterator<T>& lhs, const TreeIterator<T>& rhs) {
		return lhs.base() < rhs.base();
	}
	template <class T, class T1>
	bool operator<(const TreeIterator<T>& lhs, const TreeIterator<T1>& rhs) {
		return lhs.base() < rhs.base();
	}
	template <class T>
	bool operator<=(const TreeIterator<T>& lhs, const TreeIterator<T>& rhs) {
		return lhs.base() <= rhs.base();
	}
	template <class T, class T1>
	bool operator<=(const TreeIterator<T>& lhs, const TreeIterator<T1>& rhs) {
		return lhs.base() <= rhs.base();
	}
	template <class T>
	bool operator>=(const TreeIterator<T>& lhs, const TreeIterator<T>& rhs) {
		return lhs.base() >= rhs.base();
	}
	template <class T, class T1>
	bool operator>=(const TreeIterator<T>& lhs, const TreeIterator<T1>& rhs) {
		return lhs.base() >= rhs.base();
	}
	// COMPUTES THE DISTANCE BETWEEN TWO ITERATOR ADAPTORS
	template<class Iterator>
	typename TreeIterator<Iterator>::difference_type
		operator-(	const TreeIterator<Iterator>& lhs, const TreeIterator<Iterator>& rhs ) {
			return lhs.base() - rhs.base();
	}
	template<class Iterator, class Iterator2>
	typename TreeIterator<Iterator>::difference_type
		operator-(	const TreeIterator<Iterator>& lhs, const TreeIterator<Iterator2>& rhs ) {
			return lhs.base() - rhs.base();
	}
	// ADVANCES THE ITERATOR
	template<class Iterator>
	TreeIterator<Iterator>operator+( typename TreeIterator<Iterator>::difference_type n,
										const TreeIterator<Iterator>& it ) {
			return TreeIterator<Iterator>(it.base() + n);
	}
	template<class Iterator, class Iterator2>
	TreeIterator<Iterator>operator+( typename TreeIterator<Iterator>::difference_type n,
										const TreeIterator<Iterator2>& it ) {
			return TreeIterator<Iterator>(it.base() + n);
	}
}

#endif