/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doreshev <doreshev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 16:03:32 by doreshev          #+#    #+#             */
/*   Updated: 2022/11/03 18:51:02 by doreshev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

# include <stdexcept>
# include "iterators/TreeIterator.hpp"
# include "algorithm.hpp"
# include "type_traits.hpp"
# include "utility.hpp"
# include "tree.hpp"

namespace ft {
template<class Key, class T, class Compare = std::less<Key>,
		class Allocator = std::allocator<ft::pair<const Key, T>>>
class map {

public:
	typedef	Key											key_type;
	typedef	T											mapped_type;
	typedef	Compare										key_compare;
	typedef	typename pair<const Key, T>					value_type;
	// typedef												value_compare; /////////
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

	class value_compare : std::binary_function<value_type, value_type, bool>
	{
	private:
		friend class map;
	protected:
		Compare		comp;
		value_compare	(Compare c) : comp(c) {}
	public:
		// typedef bool		result_type;
		// typedef value_type	first_argument_type;
		// typedef value_type	second_argument_type;

		bool	operator() (const value_type& x, const value_type& y) const {
			return comp(x.first, y.first);
	  }
	}

private:
	key_compare													_comp;
	value_compare												_vcomp;
	allocator_type												_alloc;
	tree<key_type, mapped_type, key_compare, allocator_type>	_tree;
	
public:
// MEMBER FUNCTIONS
	// CONSTRUCTORS
		// 1) Empty
	explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
				: _comp(comp), _alloc(alloc), _tree(), _vcomp(comp) { }
		// 2) Range
	template <class InputIterator> 
	map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(),
		const allocator_type& alloc = allocator_type()) : _comp(comp), _alloc(alloc), _tree() {
			
	}
		// 3) Copy
	map (const map& x) : _comp(), _tree(x.tree),{
	}
	// DESTRUCTOR
	~map () { }
	// ASSIGN OPERATOR
		//assigns values to the container
	map& operator= (const map& x) {
		
	}
	// ALLOCATOR GETTER -> Returns allocator
	allocator_type get_allocator() const { return _alloc; }

// ELEMENT ACCESS
	// AT -> access specified element with bounds checking
	mapped_type& at (const key_type& k) {
		Node* tmp = _tree->find(k);
		if (tmp == nullptr)
			throw std::out_of_range;
		return (tmp->value->second);
	}
	const mapped_type& at (const key_type& k) const {
		Node* tmp = _tree->find(k);
		if (tmp == nullptr)
			throw std::out_of_range;
		return (tmp->value->second);
	}
	// [] -> access or insert specified element
	mapped_type& operator[] (const key_type& key) {
		return insert(std::make_pair(key, T())).first->second;
	}
// ITERATORS
	// 1) begin -> returns an iterator to the beginning
	iterator begin() {
		return iterator(_tree->node_minimum(_tree->_root));
	}
	const_iterator begin() const {
		return const_iterator(_tree->node_minimum(_tree->_root));
	}
	iterator end() {
		return iterator(_tree->_base);
	}
	const_iterator end() {
		return const_iterator(_tree->_base);
	}
	reverse_iterator rbegin() {
		return reverse_iterator(_tree->_base);
	}
	reverse_iterator rbegin() {
		return reverse_iterator(_tree->_base);
	}
	const_reverse_iterator rbegin() const {
		return const_reverse_iterator(_tree->_base);
	}
	reverse_iterator rend() {
		return reverse_iterator(_tree->node_minimum(_tree->_root));
	}
	const_reverse_iterator rend() const {
		return const_reverse_iterator(_tree->node_minimum(_tree->_root));
	}
// Capacity
	// empty -> checks whether the container is empty
	
	
	key_compare key_comp() const { return _comp; }
};
}

#endif