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

namespace ft {
	//NODE STRUCT
	template <typename T>
	struct Node
	{
		T			value;
		Node*		left;
		Node*		right;
		Node*		parent;
		bool		red;
	};
	//MAP ITERATORS
	template <class T>
	class TreeIterator {
	public:
		typedef T															value_type;
		typedef	Node<T>														node_type;
    	typedef node_type*													pointer;
		typedef node_type&													reference;
    	typedef const node_type&											const_reference;
    	typedef ptrdiff_t													difference_type;
		typedef typename ft::bidirectional_iterator_tag						iterator_category;
		typedef size_t														size_type;

	// CONSTRUCTORS
		// 1) Default
		TreeIterator() : _ptr() { }
		// 2) Initialization
		TreeIterator(const_reference ptr) : _ptr(ptr) { }
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
			if (_ptr->right != nullptr) {
				_ptr = _ptr->right;
				while (_ptr->left != nullptr)
					_ptr = _ptr->left;
				return *this;
			}
			for (pointer tmp = _ptr, _ptr = _ptr->parent; _ptr != nullptr && tmp == _ptr->right; tmp = _ptr) 
				_ptr = _ptr->parent;
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
			return _ptr->value;
		}
		reference	operator*() {
			return _ptr->value;
		}
		// Dereference iterator
		pointer operator->() const {
			return &(_ptr->value);
		}
		pointer operator->() {
			return &(_ptr->value);
		}
		// Pre-decrement iterator position
		TreeIterator&	operator--() {
			if (_ptr->left != nullptr) {
				_ptr = _ptr->left;
				while (_ptr->right != nullptr)
					_ptr = _ptr->right;
				return *this;
			}
			for (pointer tmp = _ptr, _ptr = _ptr->parent; _ptr != nullptr && tmp == _ptr->left; tmp = _ptr)
				_ptr = _ptr->parent;
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
			TreeIterator temp = *this;
			for (size_type i = 0; i < n; i++)
				temp++;
			return temp;
		}
		// Subtraction operator
		TreeIterator	operator- (difference_type n) const {
			TreeIterator temp = *this;
			for (size_type i = 0; i < n; i++)
				temp--;
			return temp;
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
}

#endif