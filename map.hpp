#ifndef MAP_HPP
# define MAP_HPP

#include "./utils/utils.hpp"
#include "./utils/binary_search_tree.hpp"

namespace ft
{
	template < class Key, class T, class Compare = ft::less<Key>,
				class Alloc = std::allocator<ft::pair<const Key, T> > >
	class map
	{
		public:
			typedef Key     key_type;

			typedef T       mapped_type;

			typedef ft::pair<key_type, mapped_type> value_type;

			typedef Compare     key_compare;

			class value_compare : ft::binary_function<value_type, value_type, bool>
			{
				friend class map<key_type, mapped_type, key_compare, Alloc>;
				
				protected:
					Compare comp;
					value_compare (Compare c) : comp(c) {}
				
				public:
					bool operator() (const value_type& x, const value_type& y) const
					{ return (comp(x.first, y.first)); }
			};

			typedef Alloc  allocator_type;

			typedef typename allocator_type::const_reference const_reference;

			typedef typename allocator_type::pointer     pointer;

			typedef typename allocator_type::const_pointer const_pointer;

			typedef typename ft::Binary_search_tree<value_type, key_compare>::iterator iterator;

			typedef typename ft::Binary_search_tree<value_type, key_compare>::const_iterator const_iterator;

			typedef typename ft::reverse_iterator<iterator>    reverse_iterator;

			typedef typename ft::reverse_iterator<const_iterator> const_reverse_iterator;
		
			typedef typename ft::iterator_traits<iterator>::difference_type difference_type;

			typedef size_t size_type;

			explicit map (const key_compare& comp = key_compare(),
				const allocator_type& alloc = allocator_type())
			:
				_alloc(alloc),
				_comp(comp),
				_bst()
			{}

			template <class InputIterator>
				map (InputIterator first, InputIterator last,
					const key_compare& comp = key_compare(),
					const allocator_type& alloc = allocator_type(),
					typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = u_nullptr)
			:	
				_alloc(alloc),
				_comp(comp),
				_bst()
			{
				bool is_valid;
				if (!(is_valid = ft::is_input_iterator_tagged<typename ft::iterator_traits<InputIterator>::iterator_category >::value))
					throw (ft::InvalidIteratorException<typename ft::is_input_iterator_tagged<typename ft::iterator_traits<InputIterator>::iterator_category >::type>());
				this->insert(first, last);
			}
			

			map(const map& x)
			:
				_alloc(x._alloc),
				_comp(x._comp),
				_bst()
			{
				this->insert(x.begin(), x.end());
			}

			~map()
			{ this->clear(); }

			map& operator= (const map& x)
			{
				if (&x == this)
					return (*this);
				this->clear();
				this->insert(x.begin(), x.end());
				return (*this);
			}

			iterator begin()
			{ return (iterator(_bst._last_node->left, _bst._last_node)); }

			const_iterator begin() const
			{
				return (const_iterator(_bst._last_node->left, _bst._last_node)); 
			}

			iterator end()
			{
				return (iterator(_bst._last_node, _bst._last_node));
			}

			const_iterator end() const
			{ return (const_iterator(_bst._last_node, _bst._last_node)); }

			reverse_iterator rbegin()
			{
				return (reverse_iterator(this->end()));
			}

			const_reverse_iterator rbegin() const
			{
				return (const_reverse_iterator(this->end()));
			}

			reverse_iterator rend()
			{
				return (reverse_iterator(this->begin()));
			}

			const_reverse_iterator rend() const
			{
				return (const_reverse_iterator(this->begin()));
			}

			bool empty() const
			{
				return (_bst._last_node->parent == _bst._last_node);
			}

			size_type size() const
			{
				return (_bst._last_node->value.first);
			}

			size_type max_size() const
			{
				return (_bst.max_size());
			}

			mapped_type& operator[] (const key_type& k)
			{
				iterator tmp = this->find(k);

				if (tmp == this->end())
					this->insert(ft::make_pair(k, mapped_type()));
				tmp = this->find(k);
				return ((*tmp).second);
			} 

			pair<iterator,bool> insert (const value_type& val)
			{ return (_bst.insertPair(val)); }

			iterator insert (iterator position, const value_type& val)
			{
				(void)position;
				return (_bst.insertPair(val).first);
			}

			template <class InputIterator>
				void insert (InputIterator first, InputIterator last,
				typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = u_nullptr)
			{
				bool is_valid;
				if (!(is_valid = ft::is_input_iterator_tagged<typename ft::iterator_traits<InputIterator>::iterator_category >::value))
					throw (ft::InvalidIteratorException<typename ft::is_input_iterator_tagged<typename ft::iterator_traits<InputIterator>::iterator_category >::type>());

				difference_type n = ft::distance(first, last);
				while (n--)
					this->insert(*(first++));
			}

			void erase (iterator position)
			{ this->erase((*position).first); }

			size_type erase (const key_type& k)
			{
				if (this->find(k) == this->end())
					return (0);
				_bst.removeByKey(ft::make_pair(k, mapped_type()));
				return (1);
			}

			void erase (iterator first, iterator last)
			{
				while (first != last)
					this->erase((*(first++)).first);
			}

			void swap (map& x)
			{ _bst.swap(x._bst); }

			void clear()
			{ this->erase(this->begin(), this->end()); }

			key_compare key_comp() const
			{ return (key_compare()); }

			value_compare value_comp() const
			{ return (value_compare(key_compare())); }

			iterator find (const key_type& k)
			{ return (iterator(_bst.searchByKey(ft::make_pair(k, mapped_type())), _bst._last_node)); }

			const_iterator find (const key_type& k) const
			{ return (const_iterator(_bst.searchByKey(ft::make_pair(k, mapped_type())), _bst._last_node)); }

			size_type count (const key_type& k) const
			{
				const_iterator beg = this->begin();
				const_iterator end = this->end();

				while (beg != end)
					if ((*(beg++)).first == k)
						return (1);
				return (0);
			}

			iterator lower_bound (const key_type& k)
			{
				iterator beg = this->begin();
				iterator end = this->end();

				while (beg != end)
				{
					if (_comp((*beg).first, k) == false)
						break;
					beg++;
				}
				return (beg);
			}

			const_iterator lower_bound (const key_type& k) const
			{ return (const_iterator(this->lower_bound(k))); }

			iterator upper_bound (const key_type& k)
			{
				iterator beg = this->begin();
				iterator end = this->end();

				while (beg != end)
				{
					if (_comp(k, (*beg).first))
						break;
					beg++;
				}
				return (beg);
			}

			const_iterator upper_bound (const key_type& k) const
			{ return (const_iterator(this->upper_bound(k))); }

			ft::pair<const_iterator, const_iterator> equal_range (const key_type& k) const
			{ return (ft::make_pair(this->lower_bound(k), this->upper_bound(k))); }

			ft::pair<iterator, iterator> equal_range (const key_type& k)
			{ return (ft::make_pair(this->lower_bound(k), this->upper_bound(k))); }

		private:

			allocator_type                          _alloc;
			Compare                                 _comp;
			Binary_search_tree<value_type, Compare>  _bst;

	};
}

#endif