#include "utils.hpp"
#include <memory>
#include "rbtree.hpp"
#include <exception>

namespace   ft
{


template <	class T,
			class Compare = ft::less<const T>,
			class Alloc = std::allocator<T> >
class set
{

public:
	typedef T value_type;
	typedef T key_type;
	typedef Compare value_compare;
	typedef Compare key_compare;

	typedef Alloc allocator_type;

	typedef typename allocator_type::reference			reference;
	typedef typename allocator_type::const_reference	const_reference;
	typedef typename allocator_type::pointer			pointer;
	typedef typename allocator_type::const_pointer		const_pointer;
private:
	typedef _RB_tree<value_type, value_compare, Alloc>	tree_type;
	typedef typename tree_type::_node_type				node_type;
public:

	typedef typename tree_type::iterator				iterator;
	typedef typename tree_type::const_iterator			const_iterator;
	typedef typename tree_type::reverse_iterator		reverse_iterator;
	typedef typename tree_type::const_reverse_iterator	const_reverse_iterator;

    typedef typename tree_type::size_type          size_type;
    typedef typename tree_type::difference_type    difference_type;

// private:
public:
	tree_type	tree;

public:
	explicit set (const value_compare& comp = value_compare(),
              const allocator_type& alloc = allocator_type()) : tree(comp, alloc) {}
	
	template <class InputIterator>
  		set (InputIterator first, InputIterator last,
    	const key_compare& comp = key_compare(),
    	const allocator_type& alloc = allocator_type(),
			typename ft::enable_if<!ft::is_integral<InputIterator>::value, char>::type* = NULL) : tree(comp, alloc)
		{
			while (first != last)
			{
				tree.push(*first);
				++first;
			}
		}

		set (const set& x) : tree(x.tree) {}

		~set()
		{}

		set& operator= (const set& x)
		{ this->tree = x.tree; }

		iterator begin()
		{ return tree.begin(); }

		const_iterator begin() const
		{ return tree.begin(); }

		iterator end()
		{ return tree.end(); }

		const_iterator end() const
		{ return tree.end(); }

		reverse_iterator rbegin()
		{ return tree.rbegin(); }

		const_reverse_iterator rbegin() const
		{ return tree.rbegin(); }

		reverse_iterator rend()
		{ return tree.rend(); }

		const_reverse_iterator rend() const
		{ return tree.rend(); }



		void clear()
		{ tree.clear(); }

		size_type	count(const value_type& value) const
		{ return static_cast<int>(tree.search(value) > 0); }

		bool empty() const
		{ return (tree.size() == 0); }

		ft::pair<iterator,iterator> equal_range (const value_type& val) const
		{
			return ft::make_pair(tree.lower_bound(val), tree.upper_bound(val));
		}

		void erase (iterator position)
		{ tree.erase(position); }
		size_type erase (const value_type& val)
		{ return tree.erase(val); }
     	void erase (iterator first, iterator last)
		{
			while (first != last)
			{
				tree.erase(first++);
			}
		}


    	iterator find (const value_type& val)
		{
			node_type	*tmp_ptr = tree.search(val);
			if (tmp_ptr)
				return tmp_ptr;
			return tree.end();
		}

		allocator_type	get_allocator() const
		{ return tree.get_allocator(); }

		ft::pair<iterator,bool> insert (const value_type& val)
		{
			node_type	*searched = tree.search(val);
			if (searched)
				return ft::make_pair(searched, false);
			return  ft::make_pair(tree.push(val), true);
		}

		iterator insert (iterator position, const value_type& val)
		{
			(void)position;
			node_type	*searched = tree.search(val);
			if (searched)
				return ft::make_pair(searched, false);
			return  ft::make_pair(tree.push(val), true);
		}

		template <class InputIterator>
		typename ft::enable_if<
            !ft::is_integral<InputIterator>::value, void
        >::type insert (InputIterator first, InputIterator last)
		{
			while (first != last)
			{
				tree.push(*first);
				first++;
			}
		}

		key_compare key_comp() const
		{ return key_compare(); }

		iterator lower_bound (const value_type& val)
		{ return tree.lower_bound(val); }
		const_iterator lower_bound (const value_type& val) const
		{ return tree.lower_bound(val); }

		size_type max_size() const
		{ return tree.get_allocator().max_size(); }

		size_type size() const
		{ return tree.size(); }

		void swap (set& x)
		{ tree.swap(x.tree); }

		iterator upper_bound (const key_type& k)
		{ return tree.upper_bound(k); }
		const_iterator upper_bound (const key_type& k) const
		{ return tree.upper_bound(k); }

		value_compare value_comp() const
		{
			return value_compare();
		}









			

};

template<class T>
bool    operator==( const ft::set<T>& lhs,
					const ft::set<T>& rhs)
{
	return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
}

template<class T>
bool    operator!=( const ft::set<T>& lhs,
					const ft::set<T>& rhs)
{
	return !(lhs == rhs);
}

template<class T>
bool    operator<( const ft::set<T>& lhs,
					const ft::set<T>& rhs)
{
	return ft::lexicographical_compare(lhs.begin(), lhs.end(),
										rhs.begin(), rhs.end());
}

template<class T>
bool    operator>( const ft::set<T>& lhs,
					const ft::set<T>& rhs)
{
	return (rhs < lhs);
}

template<class T>
bool    operator<=( const ft::set<T>& lhs,
					const ft::set<T>& rhs)
{
	return !(rhs < lhs);
}

template<class T>
bool    operator>=( const ft::set<T>& lhs,
					const ft::set<T>& rhs)
{
	return !(lhs < rhs);
}

template<class T>
void swap( ft::set<T>& lhs,
			ft::set<T>& rhs )
{
	lhs.swap(rhs);
}

}