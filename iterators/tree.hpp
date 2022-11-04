/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doreshev <doreshev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 16:06:43 by doreshev          #+#    #+#             */
/*   Updated: 2022/11/04 19:16:39 by doreshev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREE_HPP
# define TREE_HPP

# include "../utility.hpp"
# include "TreeIterator.hpp"
# include "../algorithm.hpp"

namespace ft {
//TREE IMPLEMENTATION
template<class T, class Compare, class Allocator>
class tree {
public:
	typedef T														value_type;
	typedef Node<T>													node_type;
	typedef node_type*												pointer;
	typedef Compare													value_compare;
	typedef Allocator												allocator_type;
	typedef typename Allocator::template rebind<Node<T> >::other	node_allocator;
	typedef typename allocator_type::size_type						size_type;
	typedef typename ft::TreeIterator<pointer>			 			iterator;
	typedef typename ft::TreeIterator<const pointer>				const_iterator;
	typedef typename ft::reverse_iterator<iterator>					reverse_iterator;
	typedef typename ft::reverse_iterator<const_iterator>			const_reverse_iterator;

protected:
	pointer					_root;
	pointer					_head;
	node_allocator			_node_alloc;
	allocator_type			_alloc;
	value_compare			_compare;

public:
	//  CONSTRUCTORS AND DESTRUCTOR
	tree(const value_compare& compare = value_compare(), const allocator_type& alloc = allocator_type())
		: _head(nullptr), _root(_null_leaf_alloc()), _compare(compare), _alloc(alloc), _node_alloc(alloc) { }
	tree (const tree& x) :	_root(x._root), _head(x._head), _node_alloc(x._node_alloc),
							_alloc(x._alloc), _compare(x._compare) { }
	~tree() { 
		remove_tree();
		_node_alloc.deallocate(_head, 1);
	}
	tree& operator= (const tree& x) {
		_root = x._root;
		_head = x._head;
		_node_alloc = x._node_alloc;
		_alloc = x._alloc;
		_compare = x._compare;
	}

	size_type	size_max () { return _node_alloc.max_size(); }
	size_type	size () {
		size_type result = 0;
		for (pointer tmp = node_minimum(_head); tmp != _root; tmp = successor(tmp))
			result++;
		return result;
	}
	// 1)Insertion of single element
	ft::pair<iterator, bool> insert(const value_type& val) {
		if (_head == nullptr) {
			_head = _nallocate(val);
			_head->red = false;
			_head->parent = _root;
			return ft::make_pair(iterator(_head), true);
		}
		for ( pointer tmp = _head; tmp != nullptr; ) {
			if (!_compare(tmp->value->key, val->key)) {
				if (!_compare(val->key, tmp->value->key))
					return ft::make_pair(iterator(tmp), false);
				if (tmp->left == nullptr) {
					tmp->left = _nallocate(val);
					_ins_balance(tmp->left, true);
					return ft::make_pair(iterator(tmp->left), true);
				}
				tmp = tmp->left;
			}
			else {
				if (tmp->right == nullptr) {
					tmp->right = _nallocate(val);
					_ins_balance(tmp->right, false);
					return ft::make_pair(iterator(tmp->right), true);
				}
				tmp = tmp->right;
			}
		}
	}
	// 2) Find
	pointer find(const value_type& key) {
		for ( pointer tmp = _head; tmp != nullptr; ) {
			if (!_compare(tmp->value, key)) {
				if (!_compare(key, tmp->value))
					return tmp;
				if (tmp->left == nullptr)
					return nullptr;
				tmp = tmp->left;
			}
			else {
				if (tmp->right == nullptr) {
					return nullptr;
				}
				tmp = tmp->right;
			}
		}
		return nullptr;
	}
	// 3) Deletion
	void	erase (pointer pos) {
		if (pos == nullptr || pos == _root)
			return ;
		_rb_deletion(pos);
	}
	void	clear() {
		for (pointer tmp = node_minimum(_head); tmp != _root; tmp = successor(tmp)) {
			try	{
				_alloc.destroy(tmp->value);
			}
			catch(...) {
				remove_tree();
			}
		}
		_head = nullptr;
	}
	// 4) Swap
	void swap (tree& x) {
		ft::swap(_root, x._root);
		ft::swap(_head, x._head);
		ft::swap(_node_alloc, x._node_alloc);
		ft::swap(_alloc, x._alloc);
		ft::swap(_compare, x._compare);
	}
	// 5) Count
	size_type count (const value_type& k) const {
		if ( find(k) == _root)
			return 0;
		return 1;
	}
	// 6) lower/upper bound
		
	// Min/Max search functions
	pointer	node_maximum (pointer current) {
		while (current->right != nullptr)
			current = current->right;
		return current;
	}
	pointer	node_minimum (pointer current) {
		while (current->left != nullptr)
			current = current->left;
		return current;	
	}
	// Predecessor/successor functions
	pointer	successor (pointer current) {
		if (current->right != nullptr) {
			return node_minimum(current->right);
		}
		pointer	Par = current->parent;
		while (Par != _root && current == Par->right) {
			current = Par;
			Par = Par->parent;
		}
		return Par;
	}
	pointer	predecessor (pointer current) {
		if (current->left != nullptr) {
			return node_maximum(current->left);
		}
		pointer	Par = current->parent;
		while (Par != _root && current == Par->left) {
			current = Par;
			Par = Par->parent;
		}
		return Par;
	}
private:
	//TREE MANIPULATION
		//1)Left Rotation
	void	rotate_left(pointer x) {
		pointer y = x->right;

		if (y) {
			x->right = y->left;
			if (y->left)
				y->left->parent = x;
			y->left = x;
			y->parent = x->parent;
			if (x->parent) {
				if (x->parent->left == x)
					x->parent->left = y;
				else
					x->parent->right = y;
			}
			else
				_head = y;
			x->parent = y;
		}
	}
		//2)Right Rotation
	void	rotate_right(pointer x) {
		pointer y = x->left;

		if (y) {
			x->left = y->right;
			if (y->right)
				y->right->parent = x;
			y->right = x;
			y->parent = x->parent;
			if (x->parent) {
				if (x->parent->left == x)
					x->parent->left = y;
				else
					x->parent->right = y;
			}
			else
				_head = y;
			x->parent = y;
		}
	}
		//3)Recolour
	void	recolor_node(const node_type& x) {
		if (x.red == true)
			x.red = false;
		else
			x.red = true;
	}
	void remove_tree() {
		for (pointer tmp = node_minimum(_head); tmp != _root; tmp = successor(tmp)) {
			try	{
				_del_node(tmp);
			}
			catch(...) {
				if (_head != nullptr)
					remove_tree();
			}
		}
		_head = nullptr;
	}
	// UTILS
		// 1) Node Allocation
			// a) red node allocation
	pointer	_nallocate (const value_type& val) {
		pointer new_node = _node_alloc.allocate(1);
		try	{
			_alloc.construct(&(new_node->value), val);
		}
		catch(...) {
			_node_alloc.deallocate(new_node, 1);
		}
		new_node->red = true; new_node->left = nullptr;
		new_node->right = nullptr; new_node->parent = nullptr;
		return (new_node);
	}
			// b) Null leaf allocation
	pointer	_null_leaf_alloc() {
		pointer new_node = _node_alloc.allocate(1);
		new_node->red = false; new_node->left = nullptr;
		new_node->right = nullptr; new_node->parent = nullptr;
		return (new_node);
	}
		// 2) Delete Node
	void	_del_node (pointer pos) {
		if (pos->value) {
			try	{
				_alloc.destroy(&(pos->value));
			}
			catch(...) {
				_node_alloc.deallocate(pos, 1);
			}
		}
		_node_alloc.deallocate(pos, 1);
	}
		// 3) Balance Tree after Insertion
	void	_ins_balance (pointer Kid, bool left_child) {
		for ( pointer	Uncle = nullptr; Kid != _head && Kid->parent->red == true; ) {
			if (Kid->parent == Kid->parent->parent->right) {
				Uncle = Kid->parent->parent->left;
				if (Uncle->red == true) {
					balance_case1(Kid, Uncle);
					Kid = Kid->parent->parent;
				}
				else {
					if (left_child == true) {
						Kid = Kid->parent;
						rotate_right(Kid);
					}
					_ins_balance_case2(Kid);
				}
			}
			else {
				Uncle = Kid->parent->parent->right;
				if (Uncle->red == true) {
					_ins_balance_case1(Kid, Uncle);
					Kid = Kid->parent->parent;
				}
				else {
					if (left_child == false) {
						Kid = Kid->parent;
						rotate_left(Kid);
					}
					_ins_balance_case3(Kid);
				}
			}
		}
		_head->red = false;
	}
	// 4) Balncing insertion cases
		 // If Uncle is red colour -> colors to be flipped -> Uncle and Parent become black, Grandparent red
	void	_ins_balance_case1(pointer Kid, pointer Uncle) {
		Kid->parent->red = false;
		Uncle->red = false;
		if (Kid->parent->parent != _head)
			Kid->parent->parent->red = true;
	}
		 //b) Uncle is black, Parent is right child and kid is right child
	void	_ins_balance_case2(pointer Kid) {
		Kid->parent->red = false;
		Kid->parent->parent->red = true;
		rotate_left(Kid->parent->parent);
	}
		 //c) Uncle is black, Parent is right child and kid is left child
	void	_ins_balance_case3(pointer Kid) {
		Kid->parent->red = false;
		Kid->parent->parent->red = true;
		rotate_right(Kid->parent->parent);
	}
	// 5) Deleting Node from tree
	void	_rb_deletion(pointer pos) {
		bool	is_red = pos->red;
		pointer tmp1 = pos;
		if (pos->left == nullptr) {
			pos = pos->right;
			_del_changenodes(pos, pos->right);
		}
		else if (pos->right == nullptr) {
			pos = pos->left;
			_del_changenodes(pos, pos->left);
		}
		else {
			pointer tmp2 = node_minimum(pos->right);
			pos = tmp2->right;
			is_red = tmp1->red;
			if (tmp2->parent == tmp1)
				pos->parent = tmp2;
			else {
				_del_changenodes(tmp2, tmp2->right);
				tmp2->right = tmp1->right;
				tmp2->right->parent = tmp2;
			}
			_del_changenodes(tmp1, tmp2);
			tmp2->left = tmp1->left;
			tmp2->left->parent = tmp2;
			tmp2->red = tmp1->red;
		}
		_del_node(tmp1);
		if (is_red == false)
			_del_rebalance(pos);
	}
		 // a) Rebalancing tree after deletion
	void _del_rebalance(pointer pos) {
		for (pointer sib = nullptr; pos != _root && pos->red == false;) {
			if (pos == pos->parent->left) {
				sib = pos->parent->right;
				if (sib->red == true) {
					sib->red = false;
					pos->parent->red = true;
					rotate_left(pos->parent);
					sib = pos->parent->right;
				}
				if (sib->left->red == false && sib->right->red == false) {
					sib->red = true;
					pos = pos->parent;
				}
				else {
					if (sib->right->red == false) {
						sib->left->red = false;
						sib->red = true;
						rotate_right(sib);
						sib = pos->parent->right;
					}
					sib->red = pos->parent->red;
					pos->parent->red = false;
					sib->right->red = false;
					rotate_left(pos->parent);
					pos = _root;
				}
			}
			else {
				sib = pos->parent->left;
				if (sib->red == true) {
					sib->red = false;
					pos->parent->red = true;
					rotate_right(pos->parent);
					sib = pos->parent->left;
				}
				if (sib->right->red == false && sib->left->red == false) {
					sib->red = true;
					pos = pos->parent;
				}
				else {
					if (sib->left->red == false) {
						sib->right->red = false;
						sib->red = true;
						rotate_left(sib);
						sib = pos->parent->left;
					}
					sib->red = pos->parent->red;
					pos->parent->red = false;
					sib->left->red = false;
					rotate_right(pos->parent);
					pos = _root;
				}
			}
		}
		pos->red = false;
	}
	// Replaces node 'pos' with a node 'other_pos'
	void _del_changenodes(pointer pos, pointer other_pos) {
		if (pos->parent == _root)
			_head = pos;
		else if (pos == pos->parent->left)
			pos->parent->left = other_pos;
		else
			pos->right->parent = other_pos;
		other_pos->parent = pos->parent;
	}
};
}

#endif