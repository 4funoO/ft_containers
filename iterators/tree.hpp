/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doreshev <doreshev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 16:06:43 by doreshev          #+#    #+#             */
/*   Updated: 2022/11/03 17:18:42 by doreshev         ###   ########.fr       */
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
template<class T, class Compare,	class Allocator>
class tree {
public:
	typedef	T															value_type;
	typedef Compare														value_compare;
	typedef Allocator													allocator_type;
	typedef typename Alloc::template rebind<TNode<value_type> >::other	node_allocator;

private:
	Node*					_root;
	Node*					_base;
	node_allocator			_alloc;
	value_compare			_compare;

public:
	tree(const value_compare& compare = value_compare)
		: _base(nullptr), _root(_vallocate()), _compare(compare) { 
			_root->red = false;
	}
	~tree() {}
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
				_base = y;
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
				_base = y;
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
	bool	insert_node(const value_type& val) {
		if (_base == nullptr) {
			_base = _nallocate(val);
			_base->red = false;
			_base->parent = _root;
			return true;
		}
		for ( Node* tmp = _base; tmp != nullptr; ) {
			if (!_compare(tmp->value->key, val->key)) {
				if (!_compare(val->key, tmp->value->key))
					return false;
				if (tmp->left == nullptr) {
					tmp->left = _nallocate(val);
					_ins_balance(tmp->left, true)
					return true;
				}
				tmp = tmp->left;
			}
			else {
				if (tmp->right == nullptr) {
					tmp->left = _nallocate(val);
					_ins_balance(tmp->left, false)
					return true;
				}
				tmp = tmp->right;
			}
		}
		return false;
	}
		//5) Find
	Node*	find(const Key& key) {
		for ( Node* tmp = _base; tmp != nullptr; ) {
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
		return nullptr;
	}
		//6) Deletion
	void	delete_node (Node* pos) {
		if (pos == nullptr || pos == _root)
			return ;
		_rb_deletion(pos);
	}

protected:
	// UTILS
		// 1) Node Allocation
	Node*	_nallocate (const value_type& val) {
		Node* new_node = _alloc.allocate(1);
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
	void	_del_node (Node* pos) {
		try	{
				_alloc.destroy(pos);
			}
			catch(...) {
				_alloc.deallocate(pos, 1);
			}
			_alloc.deallocate(pos, 1);
	}
		// 3) Balance Tree Insertion
	void	_ins_balance (Node* Kid, bool left_child) {
		for ( Node*	Uncle = nullptr; Kid != _base && Kid->parent->red == true; ) {
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
		_base->red = false;
	}
		// 4) Balncing insertion cases
		 // If Uncle is red colour -> colors to be flipped -> Uncle and Parent become black, Grandparent red
	void	_ins_balance_case1(Node* Kid, Node* Uncle) {
		Kid->parent->red = false;
		Uncle->red = false;
		if (Kid->parent->parent != _base)
			Kid->parent->parent->red = true;
	}
		 //b) Uncle is black, Parent is right child and kid is right child
	void	_ins_balance_case2(Node* Kid) {
		Kid->parent->red = false;
		Kid->parent->parent->red = true;
		rotate_left(Kid->parent->parent);
	}
		 //c) Uncle is black, Parent is right child and kid is left child
	void	_ins_balance_case3(Node* Kid) {
		Kid->parent->red = false;
		Kid->parent->parent->red = true;
		rotate_right(Kid->parent->parent);
	}
		// 5) Deleting Node from tree
	void	_del_node(Node* pos) {
		bool	is_red = pos->red;

		if (pos->left == nullptr) {
			pos = pos->right;
			_del_changenodes(pos, pos->right);
		}
		else if (pos->right == nullptr) {
			pos = pos->left;
			_del_changenodes(pos, pos->left);
		}
		else {
			Node* tmp1 = node_minimum(pos->right);
			Node* tmp2 = tmp1->right;
			is_red = tmp1->red;
			if (tmp1->parent == pos)
				tmp2->parent = tmp1;
			else {
				_del_changenodes(tmp1, tmp1->right);
				tmp1->right = pos->right;
				tmp1->right->parent = tmp1
			}
			_del_changenodes(pos, tmp1);
			tmp1->left = pos->left;
			tmp1->left->parent = tmp1;
			tmp1->red = pos->red;
		}
		_ndealloc (tmp);
		if (is_red == false)
			_del_rebalance(pos);
	}
		 // a) Rebalancing tree after deletion
	void _del_rebalance(Node* pos) {
		for (Node* sib = nullptr; pos != _root && pos->red == false;) {
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
					s->right->red = false;
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
	void _del_changenodes(Node* pos, Node* other_pos) {
		if (pos->parent == _root)
			_base = pos;
		else if (pos == pos->parent->left)
			pos->parent->left = other_pos;
		else
			pos->right->parent = other_pos;
		other_pos->parent = pos->parent;
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
		while (Par != _base && current == Par->right) {
			current = Par;
			Par = Par->parent;
		}
		return Par;
	}
	Node*	predecessor (Node* current) {
		if (current->left != nullptr) {
			return node_maximum(current->left);
		}
		Node*	Par = current->parent;
		while (Par != _base && current == Par->left) {
			current = Par;
			Par = Par->parent;
		}
		return Par;
	}
};
}

#endif