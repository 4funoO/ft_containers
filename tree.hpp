/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doreshev <doreshev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 16:06:43 by doreshev          #+#    #+#             */
/*   Updated: 2022/11/02 12:27:04 by doreshev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREE_HPP
# define TREE_HPP

# include "utility.hpp"
# include "TreeIterator.hpp"

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
//TREE IMPLEMENTATION
template<class Key, class T, class Compare,	class Allocator>
class tree {
public:
	typedef	T			value_type;
	typedef Compare		value_compare;
	typedef Allocator	allocator_type;

private:
	Node*				_root;
	allocator_type		_alloc;
	value_compare		_compare;

public:
	tree(const allocator_type& compare = value_compare,
		const allocator_type& alloc = allocator_type())
		: _root(nullptr), _alloc(alloc), _compare(compare) { }
	~tree() {
		// for (TreeIterator it = begin(), TreeIterator end = end(); it != end(); it++) {
		// 	_alloc.destroy(&(*it));
		// 	_alloc.deallocate(&(*it), 1);
		// }
	}
	//TREE MANIPULATION
		//1)Left Rotation
	void	rotate_left(Node* x) {
		Node* y = x->right;

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
				_root = y;
			x->parent = y;
		}
	}
		//2)Right Rotation
	void	rotate_right(Node* x) {
		Node* y = x->left;

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
				_root = y;
			x->parent = y;
		}
	}
		//3)Recolour
	void	recolor_node(const Node& x) {
		if (x.red == true)
			x.red = false;
		else
			x.red = true;
	}
		//4)Insertion
	void	insert_node(const value_type& val) {
		if (_root == nullptr) {
			_root = _nallocate(val);
			_root->red = false;
			return;
		}
		for ( Node* tmp = _root; tmp != nullptr; ) {
			if (!_compare(tmp->value->key, val->key)) {
				if (!_compare(val->key, tmp->value->key))
					return ;
				if (tmp->left == nullptr) {
					tmp->left = _nallocate(val);
					_insertbalance(tmp->left, true)
					return ;
				}
				tmp = tmp->left;
			}
			else {
				if (tmp->right == nullptr) {
					tmp->left = _nallocate(val);
					_insertbalance(tmp->left, false)
					return ;
				}
				tmp = tmp->right;
			}
		}
	}
		//5) Find
	Node*	find(const Key& key) {
		for ( Node* tmp = _root; tmp != nullptr; ) {
			if (!_compare(tmp->value->key, val->key)) {
				if (!_compare(val->key, tmp->value->key))
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
	}
		//6) Deletion
	void	delete_node (Node* position) {
		if (position->red == true || (position->left == nullptr && position->right == nullptr))
			_no_rebalancing_deletion(position);
		else
			_rebalancing_deletion(position);
	}

private:
	// UTILS
		// 1) Node Allocation
	Node*	_nallocate (const value_type& val) {
		Node *new_node = _alloc.allocate(1);
		try	{
			_alloc.construct(new_node, val);
		}
		catch(...) {
			_alloc.deallocate(new_node);
		}
		new_node->red = true; new_node->left = nullptr;
		new_node->right = nullptr; new_node->parent = nullptr;
		return (new_node);
	}
		// 2) Delete Node
	void	_ndelete (Node* position) {
		try	{
				_alloc.destroy(&(*position));
			}
			catch(...) {
				_alloc.deallocate(position, 1);
			}
			_alloc.deallocate(position, 1);
	}
		// 3) Balance Tree Insertion
	void	_insertbalance (Node* Kid, bool left_child) {
		for ( Node*	Uncle = nullptr; Kid != _root && Kid->parent->red == true; ) {
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
					_balance_case2(Kid);
				}
			}
			else {
				Uncle = Kid->parent->parent->right;
				if (Uncle->red == true) {
					_balance_case1(Kid, Uncle);
					Kid = Kid->parent->parent;
				}
				else {
					if (left_child == false) {
						Kid = Kid->parent;
						rotate_left(Kid);
					}
					_balance_case3(Kid);
				}
			}
		}
		_root->red = false;
	}
		// 3) Balncing insertion cases
		 // If Uncle is red colour -> colors to be flipped -> Uncle and Parent become black, Grandparent red
	void	_balance_case1(Node* Kid, Node* Uncle) {
		Kid->parent->red = false;
		Uncle->red = false;
		if (Kid->parent->parent != _root)
			Kid->parent->parent->red = true;
	}
		 //b) Uncle is black, Parent is right child and kid is right child
	void	_balance_case2(Node* Kid) {
		Kid->parent->red = false;
		Kid->parent->parent->red = true;
		rotate_left(Kid->parent->parent);
	}
		 //c) Uncle is black, Parent is right child and kid is left child
	void	_balance_case3(Node* Kid) {
		Kid->parent->red = false;
		Kid->parent->parent->red = true;
		rotate_right(Kid->parent->parent);
	}
		// 2) Balance Tree Deletion
	void	_insertbalance (Node* Kid, bool left_child) {
		for ( Node*	Uncle = nullptr; Kid != _root && Kid->parent->red == true; ) {
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
					_balance_case2(Kid);
				}
			}
			else {
				Uncle = Kid->parent->parent->right;
				if (Uncle->red == true) {
					_balance_case1(Kid, Uncle);
					Kid = Kid->parent->parent;
				}
				else {
					if (left_child == false) {
						Kid = Kid->parent;
						rotate_left(Kid);
					}
					_balance_case3(Kid);
				}
			}
		}
		_root->red = false;
	}
		// 3) Deleting Node from tree regular
	void _no_rebalancing_deletion(Node* position) {
		if (position == _root)
			_root = nullptr;
		else {
			if (position->left == nullptr) {
				if (position == position->parent->left)
					position->parent->left = position->right;
				else
					position->parent->right = position->right;
				if (position->right != nullptr)
					position->right->parent = position->parent;
			}
			else if (position->right == nullptr) {
				if (position == position->parent->left)
					position->parent->left = position->left;
				else
					position->parent->right = position->left;
				position->left->parent = position->parent;
			}
			else {
				Node* tmp = node_minimum(position->right);
				position->value = tmp->value;
				tmp->parent->right = nullptr;
				position = tmp;
			}
		}
		_ndelete (position);
	}
		// 4) Rebalancing tree after deletion
	void _rebalancing_deletion(Node* position) {
		
	}
	// Min/Max search functions
	Node*	node_maximum (Node* current) {
		while (current->right != nullptr)
			current = current->right;
		return current;
	}
	Node*	node_minimum (Node* current) {
		while (current->left != nullptr)
			current = current->left;
		return current;	
	}
	// Predecessor/successor functions
	Node*	successor (Node* current) {
		if (current->right != nullptr) {
			return node_minimum(current->right);
		}
		Node*	Par = current->parent;
		while (Par != nullptr && current == Par->right) {
			current = Par;
			Par->Par->parent;
		}
		return Par;
	}
	Node*	predecessor (Node* current) {
		if (current->left != nullptr) {
			return node_maximum(current->left);
		}
		Node*	Par = current->parent;
		while (Par != nullptr && current == Par->left) {
			current = Par;
			Par->Par->parent;
		}
		return Par;
	}
};
}

#endif