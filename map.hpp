#include "utils.hpp"

#include <memory>
#include "rbtree.hpp"
#include <exception>

template <class Key, template <class Keyx> class less>
struct map_comparer
{
	template <class T>
	bool operator()(ft::pair<const Key, T> lhs, ft::pair<const Key, T> rhs)
	{
		return less<Key>().operator()(lhs.first, rhs.first);
	}
};


namespace   ft
{


template <	class Key, class T,
			class Compare = ft::less<const Key>,
			class Alloc = std::allocator<ft::pair<const Key, T> > >
class map
{

public:
	typedef Key key_type;
	typedef T mapped_type;
	typedef ft::pair<const key_type, mapped_type> value_type;
	typedef Compare key_compare;
	class value_comparer
	{
		friend class map;
		protected:
			Compare comp;
			value_comparer(Compare c = Compare()) : comp(c) {}
		public:
			typedef bool result_type;
			typedef value_type first_argument_type;
			typedef value_type second_argument_type;
			bool operator() (const value_type& x, const value_type& y) const
				{ return comp(x.first, y.first); }
	};
	typedef value_comparer value_compare;

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

private:
	tree_type	tree;

public:
	explicit map (const key_compare& comp = key_compare(),
              const allocator_type& alloc = allocator_type()) : tree(comp, alloc) {}
	
	template <class InputIterator>
  		map (InputIterator first, InputIterator last,
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

		map (const map& x) : tree(tree_type(x.tree)) {}

		~map()
		{}

		map& operator= (const map& x)
		{ this->tree = x.tree; }

        mapped_type&    operator[](const key_type& key)
        {
            value_type  tmp_pair = ft::make_pair(key, mapped_type());
            node_type*  searched = tree.search(tmp_pair);

            if (!searched)
				searched = tree.push(tmp_pair);
            return searched->_value.second;
        }

		mapped_type&	at(const key_type& key)
		{
            value_type  tmp_pair = ft::make_pair(key, mapped_type());
            node_type*  searched = tree.search(tmp_pair);

            if (!searched)
				throw std::out_of_range("index out of range");
            return searched->_value.second;
		}

		const mapped_type&	at(const key_type& key) const
		{
            value_type  tmp_pair = ft::make_pair(key, mapped_type());
            node_type*  searched = tree.search(tmp_pair);

            if (!searched)
				throw std::out_of_range("index out of range");
            return searched->_value.second;
		}


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

		size_type	count(const key_type& key) const
		{ return static_cast<int>(tree.search(ft::make_pair(key, mapped_type())) > 0); }

		bool empty() const
		{ return (tree.size() == 0); }

		ft::pair<const_iterator,const_iterator> equal_range (const key_type& k) const
		{
            ft::pair<key_type, mapped_type> tmp_pair(k, mapped_type());
            return (ft::make_pair(tree.lower_bound(tmp_pair),
                                  tree.upper_bound(tmp_pair)));
		}

		ft::pair<iterator,iterator>             equal_range (const key_type& k)
		{
            ft::pair<key_type, mapped_type> tmp_pair(k, mapped_type());
            return (ft::make_pair(tree.lower_bound(tmp_pair),
                                  tree.upper_bound(tmp_pair)));
		}

		void erase (iterator position)
		{ tree.erase(position); }
		size_type erase (const key_type& k)
		{ return tree.erase(k); }
     	void erase (iterator first, iterator last)
		{
			while (first != last)
			{
				tree.erase(*first);
				first++;
			}
		}



    	iterator find (const key_type& k)
		{
			node_type	*tmp_ptr = tree.search(ft::make_pair(k, mapped_type()));
			if (tmp_ptr)
				return tmp_ptr;
			return tree.end();
		}

		const_iterator find (const key_type& k) const
		{
			node_type	*searched = tree.search(ft::make_pair(k, mapped_type()));
			if (searched)
				return searched;
			return tree.end();
		}

		allocator_type	get_allocator() const
		{ return tree.get_allocator(); }

		pair<iterator,bool> insert (const value_type& val)
		{
			node_type	*searched = tree.search(val);
			if (searched)
				return ft::make_pair(searched, false);
			return  ft::make_pair(tree.push(val), true);
		}

		iterator insert (iterator position, const value_type& val)
		{
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

		iterator lower_bound (const key_type& k)
		{ return tree.lower_bound(k); }
		const_iterator lower_bound (const key_type& k) const
		{ return tree.lower_bound(k); }

		size_type max_size() const
		{ return tree.get_allocator().max_size(); }

		size_type size() const
		{ return tree.size(); }

		void swap (map& x)
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

template<class Key, class T>
bool    operator==( const ft::map<Key, T>& lhs,
					const ft::map<Key, T>& rhs)
{
	return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
}

template<class Key, class T>
bool    operator!=( const ft::map<Key, T>& lhs,
					const ft::map<Key, T>& rhs)
{
	return !(lhs == rhs);
}

template<class Key, class T>
bool    operator<( const ft::map<Key, T>& lhs,
					const ft::map<Key, T>& rhs)
{
	return ft::lexicographical_compare(lhs.begin(), lhs.end(),
										rhs.begin(), rhs.end());
}

template<class Key, class T>
bool    operator>( const ft::map<Key, T>& lhs,
					const ft::map<Key, T>& rhs)
{
	return (rhs < lhs);
}

template<class Key, class T>
bool    operator<=( const ft::map<Key, T>& lhs,
					const ft::map<Key, T>& rhs)
{
	return !(rhs < lhs);
}

template<class Key, class T>
bool    operator>=( const ft::map<Key, T>& lhs,
					const ft::map<Key, T>& rhs)
{
	return !(lhs < rhs);
}

template<class Key, class T>
void swap( ft::map<Key, T>& lhs,
			ft::map<Key, T>& rhs )
{
	lhs.swap(rhs);
}

}