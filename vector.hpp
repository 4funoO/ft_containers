/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doreshev <doreshev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 16:03:14 by doreshev          #+#    #+#             */
/*   Updated: 2022/10/23 19:00:11 by doreshev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <iostream>
# include <stdexcept>
# include "iterator.hpp"
# include "algorithm.hpp"

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
								: _size(0), _cap(0), _begin(nullptr), _alloc(alloc) {
				assign(n, val);
			}
			// 3) Range
			template <class InputIterator>
			vector ( InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type() )
					: _size(0), _cap(0), _begin(nullptr), _alloc(alloc) {
				assign(first, last);
			}
			// 4) Copy
			vector ( const vector& x ) { *this = x; }

		// DESTRUCTOR
			~vector() { _vdeallocate() }

		// ASSIGN CONTENT
			vector& operator=( const vector& x ) {
				if (*this == x)
					return (*this);
				clear();
				if (_cap != x.capacity()) {
					_alloc.deallocate(_begin, _cap);
					_vallocate(x.capacity());
				}
				for ( ; _size < x._size; _size++) {
					try {
						_alloc.construct(_begin + _size, x[_size]);
					}
					catch(...) {
						_vdeallocate();
					}
				}
				return (*this);
			}

		// ASSIGN - Assigns new contents to the vector, replacing its current contents
			// 1) Range
			template <class InputIterator>
			void	assign(InputIterator first, InputIterator last) {
				size_type	count = std::distance(first, last);

				clear();
				if (dist > _cap) {
					_alloc.deallocate(_begin, _cap);
					_vallocate(count);
				}
				for ( ; first != last; first++, _size++) {
					try {
						_alloc.construct(_begin + _size, *first);
					}
					catch(...) {
						_vdeallocate();
					}
				}
			}
			// 2) Fill
			void	assign(size_type count, const value_type& val) {
				clear();
				if (count > _cap) {
					_alloc.deallocate(_begin, _cap);
					_vallocate(count);
				}
				for ( ; _size < count, _size++) {
					try {
						_alloc.construct(_begin + _size, val);
					}
					catch(...) {
						_vdeallocate();
					}
				}
			}

		// ALLOCATOR
			// Returns the allocator associated with the container
			allocator_type get_allocator() const { return _alloc; }

		// ELEMENT ACCESS
			// 1) "at" - Returns a reference to the element at position n in the vector
			reference	at(size_type pos) {
				if (pos >= size())			
					throw std::std::out_of_range("ft::vector");
				return *(_begin + pos);
			}
			const_reference at(size_type pos) const {
				if (pos >= size())			
					throw std::std::out_of_range("ft::vector");
				return *(_begin + pos);
			}
			// 2) "[]" - The same behavior as 'at' operator function, but no bounds checking is performed
			reference	operator[](size_type pos)			{ return *(_begin + pos); }
			const_reference	operator[](size_type pos) const	{ return *(_begin + pos); }
			// 3) "front" - Returns a reference to the first element in the vector
			reference front()				{ return *_begin; }
			const_reference front() const	{ return *_begin; }
			// 4) "back" - Returns a reference to the last element in the vector
			reference		back() 			{ return *_begin + (_size - 1); }
			const_reference	back() const	{ return *_begin + (_size - 1); }
			// 5) "data" - Returns a direct pointer to the memory array used internally by the vector
			value_type*			data() 			{ return _begin; }
			const value_type*	data() const	{ return _begin; }

		// ITERATORS
			// 1) Begin - iterator pointing first element position
			iterator begin() { return iterator(_begin); }
			const_iterator begin() const { return const_iterator(_begin); }
			// 2) End - iterator pointing last element position
			iterator end() { return iterator(_begin + _size); }
			const_iterator end() const { return const_iterator(_begin + _size); }
			// 3) Reverse Begin - iterator pointing after the last element position
			reverse_iterator rbegin() { return reverse_iterator(_begin + _size); }
			const_reverse_iterator rbegin() const { return reverse_iterator(_begin + _size); }
			// 4) Reverse End - iterator pointing first element position
			reverse_iterator rend() { return reverse_iterator(_begin); }
			const_reverse_iterator rend() const { return const_reverse_iterator(_begin); }

		// CAPACITY FUNCTIONS
			// 1) Checks if the current vector is empty
			bool	empty() const {
				if (_size == 0)
					return (true);
				return (false);
			}
			// 2) Size of the vector
			size_type	size() const {
				return(_size);
			}
			// 3) Max possible size of the vector
			size_type	max_size() const {
				return ( std::numeric_limits<difference_type>::max() );
			}
			// 4) Creating memory with given capacity
			void	reserve( size_type new_cap ) {
				if (new_cap > max_size())
					throw std::length_error("ft::vector");
				else if (new_cap > _cap) {
					pointer	tmp = _alloc.allocate(new_cap);
					size_type i = 0;
					for ( ; i < _size; i++) {
						try {
							_alloc.construct(tmp + i, _begin[i]);
						}
						catch(...) {
							for (size_type j = 0; j < i; j++)	
								_alloc.destroy(tmp + i);
							_alloc.deallocate(tmp, new_cap);
						}
					}
					_vdeallocate();
					_begin = tmp; _size = i; _cap = new_cap;
				}
			}
			// 5) Capacity of the vector
			size_type	capacity() const {
				return (_cap);
			}

		// MODIFIERS
			// 1) Clearing array, calling destructor to all members;
			void	clear() {
				for (size_type i = 0; i < _size; i++)
					_alloc.destroy(_begin + i);
				_size = 0;
			}
			// 2) Inserting value to the given position
				// a) Single Element
			iterator	insert( iterator position, const value_type& val ) {
				pointer		tmp;
				size_type	cap = _cap;
				size_type	dist = static_cast<size_type>(std::distance(begin(), position()));

				if (dist > _cap)
					dist = _cap;
				if (_cap == _size)
					cap = _vaddcap();
				tmp = _alloc.allocate(cap);
				for ( size_type i = 0; i <= _size; i++) {
					try {
						if (i == position)
							
						_alloc.construct(tmp + i, _begin[i]);
					}
					catch(...) {
						for (size_type j = 0; j < i; j++)	
							_alloc.destroy(tmp + i);
						_alloc.deallocate(tmp, new_cap);
					}
				}
				_vdeallocate();
				_begin = tmp; _size = i; _cap = cap;
			}
				// b) Fill
			void insert (iterator position, size_type n, const value_type& val) {
				
			}
				// c) Range
			template <class InputIterator>
			void insert (iterator position, InputIterator first, InputIterator last) {
				
			}
			// 3) Removing element from given position
				// a) Single Element
			iterator	erase(iterator position) {
				
			}
				//b) Range 
			iterator	erase(iterator first, iterator last) {
				
			}
			// 4) Adds the last element of the container
			void push_back (const value_type& val) {
				if (_cap == _size)
					reserve(_cap * 2);
				_alloc.construct(_begin + _size, _begin[_size++]);
			}
			// 5) Removes the last element of the container
			void	pop_back() {
				if (_size != 0)
					_alloc.destroy(_begin + _size, _begin[_size--]);
			}
			// 6) Resizes the container so that it contains n elements
			void	resize(size_type n, value_type val = value_type()) {
				if (n < _size) {
					for ( ; _size < n; _size--)
						_alloc.destroy(_begin + _size - 1);
				}
				else if (n > _size) {
					reserve(n);
					for ( ; _size < n; _size++)
						_alloc.construct(_begin + _size, val);
				}
			}
			// 7) Swap values of the vector with given one;
			void	swap( vector& x ) {
				ft::swap(_begin, x._begin);
				ft::swap(_cap, x._cap);
				ft::swap(_size, x._size);
			}

		// UTILS
		private:
			// 1) Vector allocation
			void	_vallocate(size_type n) {
				if (n > max_size())
					throw std::length_error("ft::vector");
				_begin = _alloc.allocate(n);
				_cap = n;
			}
			// 2) Vector deallocation
			void	_vdeallocate() {
				if (_begin != nullptr) {
					clear();
					_alloc.deallocate(_begin, _cap);
					_begin = nullptr;
					_cap = 0;
				}
			}
			size_type	_vaddcap() {
				size_type	cap;

				if (_cap != 0)
					cap = _cap * 2;
				else
					cap = 1;
				return (cap)
			}
	}; // vector

	// SWAP (vectors)
	template <class T, class Alloc> 
	void	swap(vector<T,Alloc>& x, vector<T,Alloc>& y) {
		x.swap(y);
	}

	// RELATIONAL OPERATORS (vectors)
	template <class T, class Alloc>
	bool operator==(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
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
} // ft

#endif