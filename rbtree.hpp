#pragma once
#include "utils.hpp"
#include <queue>
// #include "rbiter.hpp"
#define RED_node "\x1b[37;41m"
#define BLACK_node "\x1b[37;40m"
#define CLEAR_COLOR "\x1b[m"

enum Colors
{
	RED, BLACK
};

namespace ft
{
template <class T, class P = T*, class R = T&, class diff = ptrdiff_t>
	class	red_black_tree_iterator;
template <class iter>
	class reverse_iterator_rbtree;
}

template <class Iter> class reverse_iterator_rbtree;

template <class T, class Compare = ft::less<T>, class Alloc = std::allocator<T> >
    class red_black_tree
    {

    public:
        class red_black_node;
        typedef typename Alloc::value_type value_type;
	    typedef	Alloc allocator_type;
        typedef typename Alloc::reference reference;
	    typedef typename Alloc::const_reference	const_reference;
        typedef typename Alloc::pointer pointer;
        typedef typename Alloc::const_pointer const_pointer;
    	typedef typename Alloc::size_type   size_type;
        typedef typename Alloc::template rebind<red_black_node>::other allocator_node;
        typedef red_black_node	node;
        typedef typename ft::red_black_tree_iterator<value_type, pointer, reference>    iterator;
	    typedef typename ft::red_black_tree_iterator<value_type, const_pointer, const_reference>    const_iterator;
        typedef typename ft::reverse_iterator<iterator> reverse_iterator;
	    typedef typename ft::reverse_iterator<const_iterator> const_reverse_iterator;
    class red_black_node
	{
		// typedef T value_type;
		friend class red_black_tree;
	// private:
	public:
		value_type	_data;
		Colors		_color;

	public:
		red_black_node		*prev;
		red_black_node		*left;
		red_black_node		*right;

		red_black_node(const value_type& _data, Colors _color,
			red_black_node *prev = nullptr, red_black_node *left = nullptr, red_black_node *right = nullptr)
			: _data(_data), _color(_color), prev(prev), left(left), right(right) {}
		
		bool	operator!() const
		{ return (!this->prev); }

		static Colors	color(const red_black_node* node)
		{
			if (!node)
				return (BLACK);
			return (node->_color);
		}

		static bool		is_node(red_black_node* node)
		{
			if (!node || !(*node))
				return (false);
			return (true);
		}
    public:
		static void	print_node(red_black_node *node, int level = 0)
		{
			for (int i = 0; i < level; i++)
				std::cout << "\t";
			if (node && red_black_node::color(node) == RED)
				std::cout << RED_node;
			else
				std::cout << BLACK_node;
			if (node)
				std::cout << node->_data << CLEAR_COLOR << std::endl;
			else
				std::cout << "(null)" << CLEAR_COLOR << std::endl;
			// if (red_black_node::is_node(node))
				// printf(" %p %p\n", node, node->prev);
			if (node)
			{
				red_black_node::print_node(node->left, level + 1);
				red_black_node::print_node(node->right, level + 1);
			}
		}

		bool		is_on_left()
			{ return (this == this->prev->left); }
		bool		is_on_right()
			{ return (this == this->prev->right); }
		static bool	is_on_left(red_black_node *node)
			{ return (node == node->prev->left); }
		static bool	is_on_right(red_black_node *node)
			{ return (node == node->prev->right); }

		red_black_node	*get_far_left()
		{
			red_black_node	*cpy;

			cpy = this;
			while (red_black_node::is_node(cpy->left))
				cpy = cpy->left;
			return (cpy);
		}

		red_black_node	*get_far_right()
		{
			red_black_node	*cpy;

			cpy = this;
			while (red_black_node::is_node(cpy->right))
				cpy = cpy->right;
			return (cpy);
		}

		red_black_node	*uncle()
		{
			if (!red_black_node::is_node(this) || !red_black_node::is_node(this->prev)
				|| !red_black_node::is_node(this->prev->prev))
				return (nullptr);
			if (red_black_node::is_node(this->prev->is_on_left()))
				return (this->prev->prev->right);
			return (this->prev->prev->left);
		}

		red_black_node	*sibling()
		{
			if (!red_black_node::is_node(this->prev))
				return (nullptr);
			if (this->is_on_left)
				return (this->prev->right);
			return (this->prev->left);
		}
    };


    private:
        node	*new_node(const T& value, Colors _color = RED)
	    {
	    	node	*tmp = this->_allocator_node.allocate(1);

	    	this->_allocator_node.construct(tmp, node(value, _color));
	    	return (tmp);
	    }

	    bool	less(const_reference v1, const_reference v2)
	    { return (this->_comparator(v1, v2)); }

	    bool	equal(const_reference v1, const_reference v2)
	    { return (!less(v1, v2) && !less(v2, v1)); }

	
public:
    allocator_type		_allocator;
    allocator_node	_allocator_node;
    Compare				_comparator;
    size_type			_size;
    node			*_head;
    node			*_root;
public:
	iterator	begin()
	{
		return (this->_head->get_far_left());
	}

	const_iterator	begin() const
	{
		return (this->_head->get_far_left());
	}

	iterator	end()
	{
		return (this->_head);
	}

	const_iterator	end() const
	{
		return (this->_head);
	}

	reverse_iterator		rbegin()
	{
		return (iterator(this->_head->right));
	}

	const_reverse_iterator	rbegin() const
	{
		return (const_iterator(this->_head->right));
	}

	reverse_iterator		rend()
	{
		return (iterator(this->_head));
	}

	const_reverse_iterator	rend() const
	{
		return (const_iterator(this->_head));
	}

    node* BSTInsert(node* root, node *pt)
    {
        /* If the tree is empty, return a new node */
        if (root == NULL)
           return pt;
    
        /* Otherwise, recur down the tree */
        if (pt->_data < root->_data)
        {
            root->left  = BSTInsert(root->left, pt);
            root->left->prev = root;
        }
        else if (pt->_data > root->_data)
        {
            root->right = BSTInsert(root->right, pt);
            root->right->prev = root;
        }
        return root;
    }

	void levelOrderHelper(node *root)
	{
	    if (root == NULL)
	        return;
	
	    std::queue<node *> q;
	    q.push(root);
	
	    while (!q.empty())
	    {
	        node *temp = q.front();
	        std::cout << temp->_data << "  ";
	        q.pop();
	
	        if (temp->left != NULL)
	            q.push(temp->left);
	
	        if (temp->right != NULL)
	            q.push(temp->right);
	    }
	}
	
	void rotateLeft(node *&root, node *&pt)
	{
	    node *pt_right = pt->right;
	
	    pt->right = pt_right->left;
	
	    if (pt->right != NULL)
	        pt->right->prev = pt;
	
	    pt_right->prev = pt->prev;
	
	    if (pt->prev == NULL)
	        root = pt_right;
	
	    else if (pt == pt->prev->left)
	        pt->prev->left = pt_right;
	
	    else
	        pt->prev->right = pt_right;
	
	    pt_right->left = pt;
	    pt->prev = pt_right;
	}
	
	void rotateRight(node *&root, node *&pt)
	{
	    node *pt_left = pt->left;
	
	    pt->left = pt_left->right;
	
	    if (pt->left != NULL)
	        pt->left->prev = pt;
	
	    pt_left->prev = pt->prev;
	
	    if (pt->prev == NULL)
	        root = pt_left;
	
	    else if (pt == pt->prev->left)
	        pt->prev->left = pt_left;
	
	    else
	        pt->prev->right = pt_left;
	
	    pt_left->right = pt;
	    pt->prev = pt_left;
	}
	
	// This function fixes violations
	// caused by BST insertion
	void fixViolation(node *&root, node *&pt)
	{
	    node *parent_pt = NULL;
	    node *grand_parent_pt = NULL;
	
	    while ((pt != root) && (pt->_color != BLACK) &&
	           (pt->prev->_color == RED))
	    {
		
	        parent_pt = pt->prev;
	        grand_parent_pt = pt->prev->prev;
	
	        /*  Case : A
	            Parent of pt is left child
	            of Grand-prev of pt */
	        if (parent_pt == grand_parent_pt->left)
	        {
			
	            node *uncle_pt = grand_parent_pt->right;
	
	            /* Case : 1
	               The uncle of pt is also red
	               Only Recoloring required */
	            if (uncle_pt != NULL && uncle_pt->_color ==
	                                                   RED)
	            {
	                grand_parent_pt->_color = RED;
	                parent_pt->_color = BLACK;
	                uncle_pt->_color = BLACK;
	                pt = grand_parent_pt;
	            }
	
	            else
	            {
	                /* Case : 2
	                   pt is right child of its prev
	                   Left-rotation required */
	                if (pt == parent_pt->right)
	                {
	                    rotateLeft(root, parent_pt);
	                    pt = parent_pt;
	                    parent_pt = pt->prev;
	                }
	
	                /* Case : 3
	                   pt is left child of its prev
	                   Right-rotation required */
	                rotateRight(root, grand_parent_pt);
	                ft::swap(parent_pt->_color,
	                           grand_parent_pt->_color);
	                pt = parent_pt;
	            }
	        }
	
	        /* Case : B
	           Parent of pt is right child
	           of Grand-prev of pt */
	        else
	        {
	            node *uncle_pt = grand_parent_pt->left;
	
	            /*  Case : 1
	                The uncle of pt is also red
	                Only Recoloring required */
	            if ((uncle_pt != NULL) && (uncle_pt->_color ==
	                                                    RED))
	            {
	                grand_parent_pt->_color = RED;
	                parent_pt->_color = BLACK;
	                uncle_pt->_color = BLACK;
	                pt = grand_parent_pt;
	            }
	            else
	            {
	                /* Case : 2
	                   pt is left child of its prev
	                   Right-rotation required */
	                if (pt == parent_pt->left)
	                {
	                    rotateRight(root, parent_pt);
	                    pt = parent_pt;
	                    parent_pt = pt->prev;
	                }
	
	                /* Case : 3
	                   pt is right child of its prev
	                   Left-rotation required */
	                rotateLeft(root, grand_parent_pt);
	                ft::swap(parent_pt->_color,
	                         grand_parent_pt->_color);
	                pt = parent_pt;
	            }
	        }
	    }
	
	    root->_color = BLACK;
	}
	
	// Function to insert a new node with given _data
	void insert(value_type _data)
	{
	    // node *pt = new node(_data, BLACK);	
		node *pt = new_node(_data);
	    // Do a normal BST insert
	    this->_root = BSTInsert(this->_root, pt);
	
	    // fix Red Black Tree violations
	    fixViolation(this->_root, pt);
	}
 
    };
// } // namespace ft
