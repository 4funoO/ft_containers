/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doreshev <doreshev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 16:03:14 by doreshev          #+#    #+#             */
/*   Updated: 2022/10/22 19:07:56 by doreshev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <iostream>
# include <iterator.hpp>

namespace ft {
	template<class T, class Allocator = std::allocator<T>>
	class vector {
		public:
			typedef	T											value_type;
			typedef	Allocator									allocator_type;
			typedef	typename allocator_type::size_type			size_type;
			typedef typename allocator_type::difference_type	difference_type;
			typedef	typename allocator_type::reference			reference;
			typedef	typename allocator_type::const_reference	const_reference;
			typedef	typename allocator_type::pointer			pointer;
			typedef	typename allocator_type::const_pointer		const_pointer;
			////////////////////////////////////
			typedef	Allocator::const_pointer					iterator;
			typedef	Allocator::const_pointer					const_iterator;
			typedef	ft::reverse_iterator<iterator>				reverse_iterator;
			typedef	ft::reverse_iterator<const_iterator>		const_reverse_iterator;

		protected:
			size_type		_size;
			size_type		_cap;
			pointer			_begin;
			allocator_type	_alloc;

		public:
		// ******CONSTRUCTORS******
			// 1) Default
			explicit vector ( const allocator_type& alloc = allocator_type() )
							: _size(0), _cap(0), _begin(nullptr), _alloc(alloc) { }
			// 2) Fill
			explicit vector ( size_type n, const value_type& val = value_type(),
							const allocator_type& alloc = allocator_type() )
								: _size(0), _cap(n), _begin(nullptr), _alloc(alloc) {
				_begin = _alloc.allocate(_cap);	
				for ( ; _size <= _cap; _size++ ) {
					try {
						_alloc.construct(&(_begin[_size]), val);
					}
					catch(...) {
						clear();
						_alloc.deallocate(_begin, _cap);
					}
				}
			}
			//?????????????????????????? 3) Range
			template <class InputIterator>
			vector ( InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type() )
					: _size(0), _cap(0), _begin(first), _alloc(alloc) {
				for ( ; first != last; _cap++, first++);
				if (_cap > 0) {
					first = _begin;
					_begin = _alloc.allocate(_cap);
					_end = begin;
					for ( ; first != last; _size++, first++, _end++) {
						try {
							_alloc.construct(_end, *first);
						}
						catch(...) {
							clear();
							_alloc.deallocate(_begin, _cap);
							_cap = 0; _begin = nullptr;
						}
					}
				}
			}
			// 4) copy
			vector ( const vector& x ) { *this = x; }
		// DESTRUCTOR
			~vector() {
				clear();
				if (_cap > 0)
					_alloc.deallocate(_begin, _cap);
			}
		// OPERATOR OVERLOAD
			vector& operator=( const vector& x ) {
				if (*this == x)
					return (*this);
				size_type	xsize = x.size();
				size_type	xcap = x.capacity();
				pointer		tmp = nullptr;

				if (xcap > 0) {
					tmp =_alloc.allocate(xcap);
					for (size_type i = 0; i < xsize; i++) {
						try {
							_alloc.construct(&tmp[i], x[i]);
						}
						catch(...) {
							for (size_type j = 0; j < i; j++)
								_alloc.destroy(&tmp[j]);
							_alloc.deallocate(tmp, xcap);
						}
					}
				}
				clear();
				if (_cap > 0)
					_alloc.deallocate(_begin, _cap);
				_cap = xcap; _size = xsize; _begin = tmp;
				return (*this);
			}

		// ITERATORS
			// 1) Begin
			iterator begin() { return iterator(_begin); }
			const_iterator begin() const { return const_iterator(_begin); }
			// 2) End
			iterator end() { return iterator(_begin + _size); }
			const_iterator end() const { return const_iterator(_begin + _size); }
			// 3) Reverse Begin
			reverse_iterator rbegin() { return reverse_iterator(_begin); }
			const_reverse_iterator rbegin() const { return reverse_iterator(_begin + _size); }
			// 4) Reverse End
			reverse_iterator rend() { return reverse_iterator(_begin); }
			const_reverse_iterator rend() const { return const_reverse_iterator(_begin); }

		// CAPACITY FUNCTIONS
			// 1) Size of the vector
			size_type	size() const {
				return(_size);
			}
			// 2) Capacity of the vector
			size_type	capacity() const {
				return (_cap);
			}
			// 3) Max possible size of the vector
			size_type	max_size() const {
				return ( ((2 << (64 - size(value_type))) - 1 ));
			}
			// 4) Checks if the current vector is empty
			bool	empty() const {
				if (_size == 0)
					return (true);
				return (false);
			}
			// 5) Creating memory with given capacity
			void	reserve( size_type new_cap ) {
				if (new_cap > _cap) {
					pointer	tmp = _alloc.allocate(new_cap);
					for ( size_type i = 0; i < _size; i++) {
						try {
							_alloc.construct(&tmp[i], _begin[i]);
						}
						catch(...) {
							for (size_type j = 0; j < i; j++)													
								_alloc.destroy(&tmp[i]);
							_alloc.deallocate(tmp, new_cap);
						}
					}
					clear();
					_alloc.deallocate(_begin, _cap);
					_begin = tmp; _cap = new_cap;
				}
			}
			// 6)  Making capacity of the vector equal to it's size
			void	shrink_to_fit() {
				if (_size < _cap) {
					pointer	tmp = _alloc.allocate(_size);
					for ( size_type i = 0; i < _size; i++) {
						try {
							_alloc.construct(&tmp[i], _begin[i]);
						}
						catch(...) {
							for (size_type j = 0; j < i; j++)	
								_alloc.destroy(&tmp[i]);
							_alloc.deallocate(tmp, _size);
						}
					}
					clear();
					_alloc.deallocate(_begin, _cap);
					_begin = tmp; _cap = _size;
				}
			}
		// MODIFIERS
			// 1) Clearing array, calling destructor to all members;
			void	clear() {
				for (size_type i = 0; i < _size; i++)
					_alloc.destroy(&begin[i]);
			}
			// 2) Swap values of the vector with given one;
			void	swap( vector& x ) {
				vector	tmp(x);

				x = *this;
				*this = tmp;
			}
			// 3) Inserting value to the given position
			iterator	insert( iterator position, const value_type& val ) {
				iterator		tmp = position;
				value_type		tmpval;
				difference_type	diff = position - begin;

				if (_cap == _size || diff + 1 > _cap) {
					clear();
					_alloc.deallocate(_begin, _cap);
					_cap = _cap << 1;
					if (diff + 1 > _cap )
						_cap = diff + 1;
					_begin = _alloc.allocate(_cap);
					_end = _begin;
				}
				if (position == _end + 1) {
					push_back(val);
					return (_end);
				}
				tmp
				for ( ; tmp <= _end; tmp++ ) {
					tmpval = *tmp;
					
				}
				return (tmp);
			}
	};
}

#endif