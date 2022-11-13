#ifndef RBTREE_HPP
#define RBTREE_HPP

#include <memory>

#include "../iterators/reverse_iterator.hpp"
#include "../iterators/tree_iterator.hpp"
#include "algorithm.hpp"
#include "utility.hpp"

namespace ft {

enum e_color { red, black };

template <class T>
struct TNode {
   public:
    T       data;
    TNode  *parent;
    TNode  *left;
    TNode  *right;
    e_color color;
    TNode(const T &val = T()) : data(val), parent(), left(), right(), color(red) {}
};

template <class T, class Compare = std::less<T>, class Alloc = std::allocator<T> >
class Tree {
   public:
    typedef T                                                          value_type;
    typedef Compare                                                    value_compare;
    typedef Alloc                                                      allocator_type;
    typedef typename Alloc::template rebind<TNode<value_type> >::other node_allocator_type;
    typedef TNode<value_type>                                          Node;

    typedef typename ft::tree_iterator<Node *, Tree, T>             iterator;
    typedef typename ft::tree_iterator<const Node *, Tree, const T> const_iterator;
    typedef typename ft::reverse_iterator<iterator>                 reverse_iterator;
    typedef typename ft::reverse_iterator<const_iterator>           const_reverse_iterator;
    typedef size_t                                                  size_type;

   private:
    Node               *_base;
    Node               *_root;
    allocator_type      _alloc;
    node_allocator_type _node_alloc;
    value_compare       _cmp;
    size_type           _size;
    // private methods
   private:
    Node *_createNode(value_type const &val) {
        Node *ret = _node_alloc.allocate(1);
        _alloc.construct(&(ret->data), val);
        ret->parent = NULL;
        ret->right = NULL;
        ret->left = NULL;
        ret->color = red;
        return ret;
    }

    void _removeNode(Node *root) {
        _alloc.destroy(&(root->data));
        _node_alloc.deallocate(root, 1);
    }

    void _clear(Node *node) {
        if (node == NULL) return;
        _clear(node->left);
        _clear(node->right);
        _removeNode(node);
    }

    Node *_min(Node *root) const {
        while (root && root->left && root != _base) {
            root = root->left;
        }
        return root;
    }

    Node *_max(Node *root) const {
        while (root && root->right) {
            root = root->right;
        }
        return root;
    }

    Node *_successor(Node *curr) {
        if (curr == NULL) return NULL;
        if (curr->right != NULL) return _min(curr->right);
        Node *tmpParent = curr->parent;
        while (tmpParent != NULL && curr == tmpParent->right) {
            curr = tmpParent;
            tmpParent = tmpParent->parent;
        }
        return tmpParent;
    }

    Node *_predecessor(Node *curr) {
        if (curr == NULL) return NULL;
        if (curr->left != NULL) return _max(curr->left);
        Node *tmpParent = curr->parent;
        while (tmpParent != NULL && curr == tmpParent->left) {
            curr = tmpParent;
            tmpParent = tmpParent->parent;
        }
        return tmpParent;
    }

    bool _equals(value_type const &first, value_type const &second) const {
        return (!_cmp(first, second) && !_cmp(second, first));
    }

    Node *_searchHelper(Node *root, value_type const &key) const {
        if (root == NULL || _equals(root->data, key)) {
            return root;
        }
        if (_cmp(key, root->data) && root->left == NULL) {
            return root;
        }
        if (!_cmp(key, root->data) && root->right == NULL) {
            return root;
        }
        if (_cmp(key, root->data)) {
            return (_searchHelper(root->left, key));
        }
        return (_searchHelper(root->right, key));
    }

    void _rotate_right(Node *n) {
        if (n == NULL || n->left == NULL) return;
        Node *tmp = n->left;
        if (n == _root) {
            _root = tmp;
            _root->parent = _base;
            _base->left = _root;
        }
        if (n->parent && n->parent != _base) {
            if (n->parent->left == n)
                n->parent->left = tmp;
            else
                n->parent->right = tmp;
        }
        tmp->parent = n->parent;
        n->parent = tmp;
        n->left = tmp->right;
        if (n->left) n->left->parent = n;
        tmp->right = n;
    }

    void _rotate_left(Node *n) {
        if (n == NULL || n->right == NULL) return;
        Node *tmp = n->right;
        if (n == _root) {
            _root = tmp;
            _root->parent = _base;
            _base->left = _root;
        }
        if (n->parent && n->parent != _base) {
            if (n->parent->left == n)
                n->parent->left = tmp;
            else
                n->parent->right = tmp;
        }
        tmp->parent = n->parent;
        n->parent = tmp;
        n->right = tmp->left;
        if (n->right) n->right->parent = n;
        tmp->left = n;
    }

    void _insert_fix(Node *root) {
        Node *tmp;
        while (root->parent && root->parent != _base && root->parent->color == red) {
            if (root->parent == root->parent->parent->left) {
                tmp = root->parent->parent->right;
                if (tmp && tmp->color == red) {
                    root->parent->color = black;
                    tmp->color = black;
                    root->parent->parent->color = red;
                    root = root->parent->parent;
                } else if (root == root->parent->right) {
                    root = root->parent;
                    _rotate_left(root);
                } else {
                    root->parent->color = black;
                    root->parent->parent->color = red;
                    _rotate_right(root->parent->parent);
                }
            } else {
                tmp = root->parent->parent->left;
                if (tmp && tmp->color == red) {
                    root->parent->color = black;
                    tmp->color = black;
                    root->parent->parent->color = red;
                    root = root->parent->parent;
                } else if (root == root->parent->left) {
                    root = root->parent;
                    _rotate_right(root);
                } else {
                    root->parent->color = black;
                    root->parent->parent->color = red;
                    _rotate_left(root->parent->parent);
                }
            }
        }
        _root->color = black;
    }

    // find node that does not have a left child
    //  in the subtree of the given node
    Node *_successor_in_subtree(Node *x) {
        Node *tmp = x;
        while (tmp->left != NULL) {
            tmp = tmp->left;
        }
        return (tmp);
    }

    Node *_sibling(Node *x) {
        if (x->parent == NULL) return (NULL);
        if (x->parent->left == x)
            return (x->parent->right);
        else
            return (x->parent->left);
    }

    Node *_replace(Node *x) {
        // when node has 2 children
        if (x->left != NULL && x->right != NULL) {
            return (_successor_in_subtree(x->right));
        }
        // when node is leaf
        if (x->left == NULL && x->right == NULL) {
            return (NULL);
        }
        // when node has single child
        if (x->left != NULL) {
            return (x->left);
        } else {
            return (x->right);
        }
    }

    bool _hasredChild(Node *x) {
        return ((x->left != NULL && x->left->color == red) ||
                (x->right != NULL && x->right->color == red));
    }

    void _fixDoubleBlack(Node *x) {
        if (x == _root) return;

        Node *sibling = _sibling(x);
        Node *parent = x->parent;
        if (sibling == NULL) {
            // No sibling, double black pushed up
            _fixDoubleBlack(parent);
        } else {
            if (sibling->color == red) {
                parent->color = red;
                sibling->color = black;
                if (sibling == sibling->parent->left) {
                    _rotate_right(parent);
                } else {
                    _rotate_left(parent);
                }
                _fixDoubleBlack(x);
            } else {
                // Sibling black
                if (_hasredChild(sibling)) {
                    // at least 1 red children
                    if (sibling->left != NULL && sibling->left->color == red) {
                        if (sibling == sibling->parent->left) {
                            // left left
                            sibling->left->color = sibling->color;
                            sibling->color = parent->color;
                            _rotate_right(parent);
                        } else {
                            // right left
                            sibling->left->color = parent->color;
                            _rotate_right(sibling);
                            _rotate_left(parent);
                        }
                    } else {
                        if (sibling == sibling->parent->left) {
                            // left right
                            sibling->right->color = parent->color;
                            _rotate_left(sibling);
                            _rotate_right(parent);
                        } else {
                            // right right
                            sibling->right->color = sibling->color;
                            sibling->color = parent->color;
                            _rotate_left(parent);
                        }
                    }
                    parent->color = black;
                } else {
                    // 2 black children
                    sibling->color = red;
                    if (parent->color == black) {
                        _fixDoubleBlack(parent);
                    } else
                        parent->color = black;
                }
            }
        }
    }

    void _deleteNode(Node *v) {
        if (v == NULL) return;
        Node *u = _replace(v);
        // True when u and v are both black
        bool  uvblack = ((u == NULL || u->color == black) && v->color == black);
        Node *parent = v->parent;

        if (u == NULL) {
            // u is NULL therefore v is leaf
            if (v == _root) {
                // v is root, makeing root NULL
                _root = NULL;
                _base->left = _base;
            } else {
                if (uvblack) {
                    // u and v are both black
                    // v is leaf, fix double black at v
                    _fixDoubleBlack(v);
                } else {
                    // u or v is red
                    if (_sibling(v) != NULL) {
                        // sibling is not null, make it red
                        _sibling(v)->color = red;
                    }
                }
                // delete v from the tree
                if (v->parent->left == v)
                    parent->left = NULL;
                else
                    parent->right = NULL;
            }
            _removeNode(v);
            return;
        }

        if (v->left == NULL || v->right == NULL) {
            // v has one child
            if (v == _root) {
                // v is root, assign the value of u to v, and delete u
                _root = u;
                _root->parent = _base;
                _base->left = _root;
                u->left = NULL;
                u->right = NULL;
                u->color = black;
                _removeNode(v);
            } else {
                // Detach v from tree and move u up
                if (v->parent->left == v) {
                    parent->left = u;
                } else {
                    parent->right = u;
                }
                _removeNode(v);
                u->parent = parent;
                if (uvblack) {
                    // u and v both are black, fix double black at u
                    _fixDoubleBlack(u);
                } else {
                    // u or v are red, color u black
                    u->color = black;
                }
            }
            // std::cout << "root: " << _root->data.first << std::endl;
            return;
        }

        // v has 2 children, swap values with successor and recurse
        if (v == _root) {
            _root = u;
        }
        if (v->parent && v == v->parent->left) {
            v->parent->left = u;
        } else if (v->parent && v->parent->right == v) {
            v->parent->right = u;
        }
        if (v->right) {
            v->right->parent = u;
        }
        if (v->left) {
            v->left->parent = u;
        }
        if (u->parent && u == u->parent->left) {
            u->parent->left = v;
        }
        if (u->parent && u == u->parent->right) {
            u->parent->right = v;
        }
        ft::swap(u->parent, v->parent);
        ft::swap(u->left, v->left);
        ft::swap(u->right, v->right);
        ft::swap(u->color, v->color);
        _deleteNode(v);
    }

    void _insert_range_pre(Tree &tree, Node *node) {
        if (node == NULL) return;
        tree.insert(node->data);
        _insert_range_pre(tree, node->left);
        _insert_range_pre(tree, node->right);
    }

    void _inorder(Node *node) {
        if (node != NULL) {
            if (node->left) _inorder(node->left);
            std::cout << " " << node->data << " ";
            if (node->right) _inorder(node->right);
        } else {
        }
    }

    void _preorder(Node *node) {
        if (node != NULL) {
            std::cout << " " << node->data << " ";
            if (node->left) _preorder(node->left);
            if (node->right) _preorder(node->right);
        } else {
        }
    }

    void _postorder(Node *node) {
        if (node != NULL) {
            if (node->left) _postorder(node->left);
            if (node->right) _postorder(node->right);
            std::cout << " " << node->data << " ";
        } else {
        }
    }

   public:
    explicit Tree(const value_compare  &cmp = value_compare(),
                  const allocator_type &alloc = allocator_type())
        : _base(), _root(NULL), _alloc(alloc), _node_alloc(alloc), _cmp(cmp), _size(0) {
        _base = new Node;
        _base->left = _base;
        _base->right = NULL;
    }

    Tree(Tree const &x)
        : _base(), _root(), _alloc(x._alloc), _node_alloc(x._node_alloc), _cmp(x._cmp), _size() {
        _base = new Node;
        _base->left = _base;
        _base->right = NULL;
        _insert_range_pre(*this, x._root);
    }

    ~Tree() {
        clear();
        delete _base;
    }

    Tree &operator=(Tree const &x) {
        this->clear();
        _cmp = x._cmp;
        _alloc = x._alloc;
        _node_alloc = x._node_alloc;
        _insert_range_pre(*this, x._root);
        return *this;
    }

    ft::pair<iterator, bool> insert(value_type const &new_val) {
        Node *tmp;
        Node *ret;

        if (empty()) {
            Node *newNode = _createNode(new_val);
            _root = newNode;
            _root->parent = _base;
            _base->left = _root;
            _root->color = black;
            _size++;
            return (ft::make_pair(iterator(_root), true));
        }
        tmp = _searchHelper(_root, new_val);
        if (_equals(new_val, tmp->data)) {
            return (ft::make_pair(iterator(tmp), false));
        } else if (_cmp(new_val, tmp->data)) {
            tmp->left = _createNode(new_val);
            ret = tmp->left;
            tmp->left->parent = tmp;
            _insert_fix(tmp->left);
            _size++;
            return (ft::make_pair(iterator(ret), true));
        } else {
            tmp->right = _createNode(new_val);
            ret = tmp->right;
            tmp->right->parent = tmp;
            _insert_fix(tmp->right);
            _size++;
            return (ft::make_pair(iterator(ret), true));
        }
    }

    iterator insert(iterator pos, value_type const &to_insert) {
        (void)pos;
        return insert(to_insert).first;
    }

    template <class InputIterator>
    void insert(InputIterator first, InputIterator last) {
        while (first != last) {
            insert(*first);
            ++first;
        }
    }

    size_type deleteNode(value_type const &to_delete) {
        Node *v = _root;
        while (v != NULL) {
            if (_cmp(to_delete, v->data))
                v = v->left;
            else if (_cmp(v->data, to_delete))
                v = v->right;
            else
                break;
        }
        if (_root == NULL || v == NULL) {
            return 0;
        }
        _deleteNode(v);
        _size--;
        return 1;
    }

    void deleteNode(iterator first, iterator last) {
        while (first != last) {
            deleteNode(first++.base()->data);
        }
    }

    void swap(Tree &x) {
        ft::swap(_base, x._base);
        ft::swap(_root, x._root);
        ft::swap(_alloc, x._alloc);
        ft::swap(_node_alloc, x._node_alloc);
        ft::swap(_cmp, x._cmp);
        ft::swap(_size, x._size);
    }

    void clear() {
        _clear(_root);
        _base->left = _base;
        _root = NULL;
        _size = 0;
    }
    // iterators
    iterator begin() { return (iterator(_min(_base->left))); }

    const_iterator begin() const { return (const_iterator(_min(_base->left))); }

    iterator end() { return (iterator(_base)); }

    const_iterator end() const { return (const_iterator(_base)); }

    reverse_iterator rbegin() { return (reverse_iterator(end())); }

    const_reverse_iterator rbegin() const { return (const_reverse_iterator(end())); }

    reverse_iterator rend() { return (reverse_iterator(begin())); }

    const_reverse_iterator rend() const { return (const_reverse_iterator(begin())); }

    // capacity
    bool empty() const { return (begin() == end()); }

    size_type size() const { return _size; }

    size_type max_size() const { return _node_alloc.max_size(); }

    Node *getRoot() const { return _root; }
    // allocator
    allocator_type get_allocator() const { return _alloc; }

    node_allocator_type get_node_allocator() const { return _node_alloc; }

    value_compare value_comp() const { return _cmp; }

    // Operations
    iterator find(value_type const &key) {
        Node *res = _searchHelper(_root, key);
        if (res == NULL || !_equals(res->data, key)) return (end());
        return (iterator(res));
    }

    const_iterator find(value_type const &key) const {
        Node *res = _searchHelper(_root, key);
        if (res == NULL || !_equals(res->data, key)) return (end());
        return (const_iterator(res));
    }

    size_type count(value_type const &key) const { return (find(key) != end()); }

    iterator lower_bound(value_type const &key) {
        iterator b = begin();
        iterator e = end();
        while (b != e && !_equals(*b, key) && !_cmp(key, *b)) ++b;
        return b;
    }

    const_iterator lower_bound(value_type const &key) const {
        const_iterator b = begin();
        const_iterator e = end();
        while (b != e && !_equals(*b, key) && !_cmp(key, *b)) ++b;
        return b;
    }

    iterator upper_bound(value_type const &key) {
        reverse_iterator rb = rbegin();
        reverse_iterator re = rend();
        while (rb != re && !_equals(*rb, key) && _cmp(key, *rb)) ++rb;
        return rb.base();
    }

    const_iterator upper_bound(value_type const &key) const {
        const_reverse_iterator rb = rbegin();
        const_reverse_iterator re = rend();
        while (rb != re && !_equals(*rb, key) && _cmp(key, *rb)) {
            rb++;
        }
        return rb.base();
    }

    ft::pair<const_iterator, const_iterator> equal_range(value_type const &key) const {
        return ft::make_pair(lower_bound(key), upper_bound(key));
    }

    ft::pair<iterator, iterator> equal_range(value_type const &key) {
        return ft::make_pair(lower_bound(key), upper_bound(key));
    }

};

}  // namespace ft
#endif