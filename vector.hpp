/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doreshev <doreshev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 16:03:14 by doreshev          #+#    #+#             */
/*   Updated: 2022/10/16 13:44:54 by doreshev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <iostream>

namespace ft {
	template<class T, class Allocator = std::allocator<T>>
	class vector {
		public:
			typedef	T											value_type;
			typedef	Allocator									allocator_type;
			typedef	typename std::_size_t						size_type;
			typedef typename std::ptrdiff_t						difference_type;
			typedef	typename allocator_type::reference			reference;
			typedef	typename allocator_type::const_reference	const_reference;
			typedef	typename Allocator::pointer					pointer;
			typedef	typename Allocator::const_pointer			const_pointer;
			////////////////////////////////////	
			typedef	Allocator::const_pointer					iterator;
			typedef	Allocator::const_pointer					const_iterator;
			typedef	std::reverse_iterator<iterator>				reverse_iterator;
			typedef	std::reverse_iterator<const_iterator>		const_reverse_iterator;

		private:
			size_type		_size;
			size_type		_cap;
			pointer			_begin;
			pointer			_end;
			allocator_type	_alloc;

		public:
		// ******CONSTRUCTORS*****
		// 1) default
			explicit vector (const allocator_type& alloc = allocator_type())
							: _size(0), _cap(0), _begin(NULL), _end(NULL), _alloc(alloc) { }
		// 2) fill
			explicit vector (size_type n, const value_type& val = value_type(),
							const allocator_type& alloc = allocator_type())
								: _size(0), _cap(n), _begin(NULL), _end(NULL), _alloc(alloc) {
				_begin = _alloc.allocate(_cap);
				_end = _begin;
				for ( _size = 0; i < _size; _size++, _end++ )
				{
					try
					{
						_alloc.construct(_end, val);
					}
					catch(...)
					{
						clear();
						_alloc.deallocate(_begin, _cap);
						_cap = 0; _begin = NULL;
						throw;
					}
				}				
			}
		// 3) range
			template <class InputIterator>
			vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type())
					: _alloc(alloc), _begin(first), _end(NULL), _size(0), _cap(0) {
				for ( ; first != last; _size++, first++);
				if (_cap == 0 && first)
					_cap = 1;
				first = _begin;
				_begin = _alloc.allocate(_cap);
				_end = begin;
				for ( ; first != last; _size++, first++, _end++)
				{
					try
					{
						_alloc.construct(_end, *first);
					}
					catch(...)
					{
						clear();
						_alloc.deallocate(_begin, _cap);
						_cap = 0; _begin = NULL;
					}
				}				
			}
		// 4) copy
			vector (const vector& x) {	*this = x; }
		// DESTRUCTOR
			~vector() {
				clear();
				if (_cap > 0)
					_alloc.deallocate(_begin, _cap);
			}
		// OPERATOR OVERLOAD
			vector& operator=(const vector& x) {
				if (*this == x)
					return (*this);
				clear();
				if (_cap != x.capacity())
				{
					_alloc.deallocate(_begin, _cap);
					_cap = x.capacity();
					begin = _alloc.allocate(_cap);
				}
				_end = _begin;
				for (_size = 0; _size < x.size(); _size++, _end++)
				{
					try
					{
						_alloc.construct(_end, x[_size]);
					}
					catch(...)
					{
						clear();
						_alloc.deallocate(_begin, _cap);
						_cap = 0; _begin = NULL;
						throw;
					}
				}
				return (*this);
			}
		// CAPACITY FUNCTIONS
			void	clear() {
				for ( ; _size > 0; _size--, _end-- )
					_alloc.destroy(_end);
			}

			size_type	size() const {
				return(_size);
			}

			size_type	capacity() const {
				return (_cap);
			}

			size_type	max_size() const {
				return ( ((2 << (64 - size(type))) - 1 ));
			}

			bool	empty() const {
				if (_size == 0)
					return (true);
				return (false);
			}

			void	reserve( size_type new_cap ) {
				if (new_cap > _cap)
				{
					pointer	tmp = _alloc.allocate(new_cap);
					pointer	end = tmp;
					size_type i = 0
					for ( ; i < _size; i++, end++)
					{
						try
						{
							_alloc.construct(end, this[i]);
						}
						catch(...)
						{
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

			void	shrink_to_fit() {
				if (_size == 0 && _cap != 0)
				{
					_alloc.deallocate(_begin, _cap);
					_begin = 0; _cap = 0; _end = NULL; _begin = NULL;
				}
				else if (_size < _cap)
				{
					pointer	tmp = _alloc.allocate(_size);
					pointer	end = tmp;
					size_type i = 0;

					for ( ; i < _size; i++, end++)
					{
						try
						{
							_alloc.construct(end, this[i]);
						}
						catch(...)
						{
							for ( ; i > 0; i--, end--)
								_alloc.destroy(end);
							_alloc.deallocate(tmp, _size);
							throw;
						}
					}
					clear();
					_alloc.deallocate(_begin, _cap);
					_begin = tmp; _cap = new_cap; _end = end; _size = i;
				}
			}
	};
}

#endif