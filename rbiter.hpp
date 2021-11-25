#pragma once
#include "iterator.hpp"
#include "iterator_traits.hpp"
#include "rbtree.hpp"

namespace ft
{

template <class T, class P, class R, class diff >
class red_black_tree_iterator 
    : public ft::iterator<T, ft::biderectional_iterator_tag, P, R, diff>
	{
	public:
		typedef typename red_black_tree<T>::red_black_node	red_black_node;
		typedef P pointer;
		typedef R reference;
		typedef diff difference_type;
	private:
		red_black_node* _curr;
	public:
		red_black_tree_iterator()
		{ this->_curr = nullptr; }
		red_black_tree_iterator(red_black_node* p)
		{ this->_curr = p; }
		
		red_black_tree_iterator(const red_black_tree_iterator<T, P, R, diff>& copy)
		{ this->_curr = copy._curr; }

		~red_black_tree_iterator()
		{ }

		red_black_tree_iterator&	operator=(const red_black_tree_iterator<T, P, R, diff>& copy)
		{ if (this != &copy) this->_curr = copy.curr; return (*this); }

		operator red_black_tree_iterator<T, const T*, const T&>()
		{ return red_black_tree_iterator<T, const T*, const T&>(this->_curr); }

		red_black_tree_iterator&	operator++(void)
		{
			if (!this->_curr->prev)
			{
				this->_curr = this->_curr->left;
			}
			else if (this->_curr->right)
			{
				this->_curr = this->_curr->right;
				this->_curr = this->_curr->get_far_left();
			}
			else if (this->_curr->prev)
			{
				while (this->_curr->prev && red_black_node::is_on_right(this->_curr))
				{
					this->_curr = this->_curr->prev;
				}
				if (this->_curr->prev)
					this->_curr = this->_curr->prev;
			}
			return (*this);
		}

		red_black_tree_iterator		operator++(int)
		{
			red_black_tree_iterator	iter(this->_curr);

			++(*this);
			return (iter);
		}

		reference		operator*() const
		{ return (this->_curr->_data); }

		friend bool	operator==(const red_black_tree_iterator& left, const red_black_tree_iterator& right)
		{ return (left._curr == right._curr); }

		friend bool	operator!=(const red_black_tree_iterator& left, const red_black_tree_iterator& right)
		{ return (left._curr != right._curr); }

		
		pointer			operator->() const
		{ return (&(this->_curr->data)); }
		
		red_black_tree_iterator&	operator--(void)
		{
			if (!this->_curr->prev)
			{
				this->_curr = this->_curr->right;
			}
			else if (this->_curr->left)	
			{
				this->_curr = this->_curr->left;
				this->_curr = this->_curr->get_far_right();
			}
			else if (this->_curr->prev)
			{
				while (this->_curr->prev && red_black_node::is_on_left(this->_curr))
					this->_curr = this->_curr->prev;
				if (this->_curr->prev)
					this->_curr = this->_curr->prev;
			}
			return (*this);
		}

		red_black_tree_iterator	operator--(int)
		{
			red_black_tree_iterator iter(*this);

			--(*this);
			return (iter);

		}
	};

}