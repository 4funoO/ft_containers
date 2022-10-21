/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doreshev <doreshev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 16:03:14 by doreshev          #+#    #+#             */
/*   Updated: 2022/10/20 18:12:43 by doreshev         ###   ########.fr       */
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
			typedef	typename std::size_t						size_type;
			typedef typename std::ptrdiff_t						difference_type;
			typedef	typename allocator_type::reference			reference;
			typedef	typename allocator_type::const_reference	const_reference;
			typedef	typename allocator_type::pointer			pointer;
			typedef	typename allocator_type::const_pointer		const_pointer;
			////////////////////////////////////	
			typedef	Allocator::const_pointer					iterator;
			typedef	Allocator::const_pointer					const_iterator;
			typedef	ft::reverse_iterator<iterator>				reverse_iterator;
			typedef	ft::reverse_iterator<const_iterator>		const_reverse_iterator;

		private:
			size_type		_size;
			size_type		_cap;
			pointer			_begin;
			pointer			_end;
			allocator_type	_alloc;

		public:
		// ******CONSTRUCTORS******
			// 1) Default
			explicit vector ( const allocator_type& alloc = allocator_type() )
							: _size(0), _cap(0), _begin(NULL), _end(NULL), _alloc(alloc) { }
			// 2) Fill
			explicit vector ( size_type n, const value_type& val = value_type(),
							const allocator_type& alloc = allocator_type() )
								: _size(0), _cap(n), _begin(NULL), _end(NULL), _alloc(alloc) {
				_begin = _alloc.allocate(_cap);
				_end = _begin;
				for ( _size = 0; i < _size; _size++, _end++ ) {
					try {
						_alloc.construct(_end, val);
					}
					catch(...) {
						clear();
						_alloc.deallocate(_begin, _cap);
						_cap = 0; _begin = NULL;
						throw;
					}
				}				
			}
			//?????????????????????????? 3) Range
			template <class InputIterator>
			vector ( InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type() )
					: _size(0), _cap(0), _begin(first), _end(NULL), _alloc(alloc) {
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
							_cap = 0; _begin = NULL;
						}
					}
				}
			}
		// 4) copy
			vector ( const vector& x ) {	*this = x; }
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
				clear();
				if (_cap != x.capacity()) {
					_alloc.deallocate(_begin, _cap);
					_cap = x.capacity();
					begin = _alloc.allocate(_cap);
				}
				_end = _begin;
				for (_size = 0; _size < x.size(); _size++, _end++) {
					try {
						_alloc.construct(_end, x[_size]);
					}
					catch(...) {
						clear();
						_alloc.deallocate(_begin, _cap);
						_cap = 0; _begin = NULL;
						throw;
					}
				}
				return (*this);
			}

		// ITERATORS
			// 1) Begin
			iterator begin() { return this->_begin; }
			const_iterator begin() const { return this->_begin; }
			// 2) End
			iterator end() { return this->_end; }
			const_iterator end() const { return this->_end; }
			// 3) Reverse Begin
			reverse_iterator rbegin() { return this->end; }
			const_reverse_iterator rbegin() const { return this->end; }
			// 4) Reverse End
			reverse_iterator rend() { return (this->begin - 1); }
			const_reverse_iterator rend() const { return (this->begin - 1); }

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
				return ( ((2 << (64 - size(type))) - 1 ));
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
					pointer	end = tmp;
					size_type i = 0
					for ( ; i < _size; i++, end++)
					{
						try {
							_alloc.construct(end, this[i]);
						}
						catch(...) {
							for ( ; i > 0; i--, end--)
								_alloc.destroy(end);
							_alloc.deallocate(tmp, new_cap);
							throw;
						}
					}
					clear();
					_alloc.deallocate(_begin, _cap);
					_begin = tmp; _cap = new_cap; _end = end; _size = i;
				}
			}
			// 6)  Making capacity of the vector equal to it's size
			void	shrink_to_fit() {
				if (_size < _cap) {
					ft::vector	tmp(_begin, _end);

					clear();
					_alloc.deallocate(_begin, _cap);
					*this = tmp;
				}
			}
		// MODIFIERS
			// 1) Clearing array, calling destructor to all members;
			void	clear() {
				for ( ; _size > 0; _size--, _end-- )
					_alloc.destroy(_end);
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