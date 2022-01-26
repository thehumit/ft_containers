#pragma once
#include "utils.hpp"
#include <queue>
// #include "rbiter.hpp"
#define RED_NODE "\x1b[37;41m"
#define BLACK_NODE "\x1b[37;40m"
#define CLEAR_COLOR "\x1b[m"


namespace   ft
{
    template<class U, class Compare, class Allocator> class _RB_tree;

    enum _RB_node_color
    {
        _RB_color_black = false,
        _RB_color_red
    };

    enum _RB_node_branch
    {
        _RB_branch_left = false,
        _RB_branch_right,
        _RB_branch_undef
    };

    template<class U>
    struct _RB_node
    {
        typedef U       value_type;

        value_type      _value;
        _RB_node_color  _color;
        _RB_node<U>*    _parent;
        _RB_node<U>*    _left;
        _RB_node<U>*    _right;

        _RB_node( const U& value)
            : _value(value), _color(_RB_color_red),
            _parent(NULL), _left(NULL), _right(NULL)
        {}

        ~_RB_node( void )
        {}


        void    swap_children(void)
        {
            _RB_node<U> *tmp;

            tmp = this->_left;
            this->_left = this->_right;
            this->_right = tmp;
        }


        void    swap_values(_RB_node<U>* node)
        {
           
            char    buffer[sizeof(value_type)];
            void*   this_ptr = reinterpret_cast<void *>(&this->_value);
            void*   node_ptr = reinterpret_cast<void *>(&node->_value);

            memcpy(buffer, this_ptr, sizeof(value_type));
            memcpy(this_ptr, node_ptr, sizeof(value_type));
            memcpy(node_ptr, buffer, sizeof(value_type));
        }


        void    swap_colors(_RB_node<U>* node)
        {
            _RB_node_color   tmp;

            tmp = this->_color;
            this->_color = node->_color;
            node->_color = tmp;
        }


        static _RB_node_color   get_color(const _RB_node<U>* node)
        {
            if (node == NULL || node->_color == _RB_color_black)
                return (_RB_color_black);
            return (_RB_color_red);
        }

        static _RB_node_branch  get_branch(const _RB_node<U>* node)
        {
            if (node->_parent->_left == node)
                return _RB_branch_left;
            else if (node->_parent->_right == node)
                return _RB_branch_right;
            return _RB_branch_undef;
        }


        static _RB_node<U>*     get_uncle(_RB_node<U>* node)
        {
            if (get_branch(node->_parent) == _RB_branch_left)
                return (node->_parent->_parent->_right);
            return (node->_parent->_parent->_left);
        }

        
        static _RB_node<U>*     get_minimal(_RB_node<U>* node)
        {
            if (!node)
                return node;
            while (node->_left)
                node = node->_left;
            return node;
        }

        static _RB_node<U>*     get_maximal(_RB_node<U>* node)
        {
            if (!node)
                return node;
            while (node->_right)
                node = node->_right;
            return node;
        }

		static void				print(_RB_node<U>* node, int level=0)
		{
			for (int i = 0; i < level; i++)
				std::cout << "\t";
			if (node && get_color(node) == _RB_color_red)
				std::cout << RED_NODE;
			else
				std::cout << BLACK_NODE;
			if (node)
				std::cout << node->_value << CLEAR_COLOR << std::endl;
			else
				std::cout << "(null)" << CLEAR_COLOR << std::endl;
			if (node)
			{
				print(node->_left, level + 1);
				print(node->_right, level + 1);
			}
		}

    };



    template<class T>
    struct _RB_tree_const_iterator;

    template<class T>
    struct _RB_tree_iterator : ft::iterator<ft::BidirectionalIteratorTag, T>
    {
        friend struct _RB_tree_const_iterator<T>;

    public:
        template<
            class U,
            class Compare,
            class Allocator>
        friend class _RB_tree;

        typedef typename T::value_type  value_type;
        typedef value_type*             pointer;
        typedef value_type&             reference;

        typedef
            typename ft::iterator<ft::BidirectionalIteratorTag, T>::iterator_category
            iterator_category;
        typedef
            typename ft::iterator<ft::BidirectionalIteratorTag, T>::difference_type
            difference_type;

    private:
        T*      _node; 

    public:
        _RB_tree_iterator( void )
            : _node(NULL)
        {}

        _RB_tree_iterator( T* node )
            : _node(node)
        {}


        _RB_tree_iterator( const _RB_tree_iterator& iter)
            : _node(iter._node)
        {}


        ~_RB_tree_iterator( void )
        {}


        _RB_tree_iterator&  operator=(const _RB_tree_iterator& iter)
        {
            if (this == &iter)
                return (*this);
            this->_node = iter._node;
            return (*this);
        }

       
        reference       operator*(void) const
        { return (this->_node->_value); }

        
        pointer         operator->(void) const
        { return (&this->_node->_value); }

        
        _RB_tree_iterator& operator++(void)
        {
            if (this->_node->_right)
                this->_node = T::get_minimal(this->_node->_right);
            else if (this->_node->_parent)
            {
                while (T::get_branch(this->_node) == _RB_branch_right)
                    this->_node = this->_node->_parent;
                if (this->_node->_right != this->_node->_parent)
                    this->_node = this->_node->_parent;
            }
            return (*this);
        }

       
        _RB_tree_iterator& operator--(void)
        {
            if (this->_node->_parent && this->_node->_color == _RB_color_red &&
                    this->_node == this->_node->_parent->_parent)
                this->_node = this->_node->_right;
            else if (this->_node->_left)
                this->_node = T::get_maximal(this->_node->_left);
            else if (this->_node->_parent)
            {
                while (T::get_branch(this->_node) == _RB_branch_left)
                    this->_node = this->_node->_parent;
                if (this->_node->_right != this->_node->_parent)
                    this->_node = this->_node->_parent;
            }
            return (*this);
        }

        
        _RB_tree_iterator   operator++(int)
        {
            _RB_tree_iterator<T>   out(*this);
            this->operator++();
            return (out);
        }

        _RB_tree_iterator   operator--(int)
        {
            _RB_tree_iterator<T>   out(*this);
            this->operator--();
            return (out);
        }


        friend bool     operator==(const _RB_tree_iterator& it1,
                                   const _RB_tree_iterator& it2)
        { return (it1._node == it2._node); }

        friend bool     operator!=(const _RB_tree_iterator& it1,
                                   const _RB_tree_iterator& it2)
        { return (it1._node != it2._node); }

    };


    template<class T>
    struct _RB_tree_const_iterator : ft::iterator<ft::BidirectionalIteratorTag, T>
    {
    public:
        template<
            class U,
            class Compare,
            class Allocator>
        friend class _RB_tree;

        typedef typename T::value_type  value_type;
        typedef const value_type*       pointer;
        typedef const value_type&       reference;

        typedef
            typename ft::iterator<ft::BidirectionalIteratorTag, T>::iterator_category
            iterator_category;
        typedef
            typename ft::iterator<ft::BidirectionalIteratorTag, T>::difference_type
            difference_type;


    private:
        T*      _node;

    public:
        _RB_tree_const_iterator( void )
            : _node(NULL)
        {}

        _RB_tree_const_iterator( T* node )
            : _node(node)
        {}

        _RB_tree_const_iterator( const _RB_tree_const_iterator& iter)
            : _node(iter._node)
        {}

       _RB_tree_const_iterator( const _RB_tree_iterator<T>& iter)
            : _node(iter._node)
        {}

        ~_RB_tree_const_iterator( void )
        {}

        _RB_tree_const_iterator&  operator=(const _RB_tree_const_iterator& iter)
        {
            if (this == &iter)
                return (*this);
            this->_node = iter._node;
            return (*this);
        }


        reference       operator*(void) const
        { return (this->_node->_value); }

        pointer         operator->(void) const
        { return (&this->_node->_value); }

        _RB_tree_const_iterator& operator++(void)
        {
            if (this->_node->_right)
                this->_node = T::get_minimal(this->_node->_right);
            else if (this->_node->_parent)
            {
                while (T::get_branch(this->_node) == _RB_branch_right)
                    this->_node = this->_node->_parent;
                if (this->_node->_right != this->_node->_parent)
                    this->_node = this->_node->_parent;
            }
            return (*this);
        }

        _RB_tree_const_iterator& operator--(void)
        {
            if (this->_node->_parent && this->_node->_color == _RB_color_red &&
                    this->_node == this->_node->_parent->_parent)
                this->_node = this->_node->_right;
            else if (this->_node->_left)
                this->_node = T::get_maximal(this->_node->_left);
            else if (this->_node->_parent)
            {
                while (T::get_branch(this->_node) == _RB_branch_left)
                    this->_node = this->_node->_parent;
                if (this->_node->_right != this->_node->_parent)
                    this->_node = this->_node->_parent;
            }
            return (*this);
        }

        _RB_tree_const_iterator   operator++(int)
        {
            _RB_tree_const_iterator<T>   out(*this);
            this->operator++();
            return (out);
        }

        _RB_tree_const_iterator   operator--(int)
        {
            _RB_tree_const_iterator<T>   out(*this);
            this->operator--();
            return (out);
        }

        friend bool     operator==(const _RB_tree_const_iterator& it1,
                                   const _RB_tree_const_iterator& it2)
        { return (it1._node == it2._node); }

        friend bool     operator!=(const _RB_tree_const_iterator& it1,
                                   const _RB_tree_const_iterator& it2)
        { return (it1._node != it2._node); }

    };

    template<
        class U,
        class Compare = ft::less<U>,
        class Allocator = std::allocator<U>
    > class _RB_tree
    {
    public:
        typedef _RB_node<U>     _node_type;
        typedef U               value_type;

        typedef
            typename Allocator::template rebind<_node_type>::other
            _node_allocator;


        typedef typename _node_allocator::size_type          size_type;
        typedef typename _node_allocator::difference_type    difference_type;
        typedef typename _node_allocator::reference          reference;
        typedef typename _node_allocator::const_reference    const_reference;
        typedef typename _node_allocator::pointer            pointer;
        typedef typename _node_allocator::const_pointer      const_pointer;

        typedef typename ft::_RB_tree_iterator<_node_type>          iterator;
        typedef typename ft::_RB_tree_const_iterator<_node_type>    const_iterator;

        typedef typename ft::reverse_iterator<iterator>         reverse_iterator;
        typedef typename ft::reverse_iterator<const_iterator>   const_reverse_iterator;

    private:
        _node_allocator _node_alloc;
        Compare         _cmp;
        size_type       _size;

        _node_type*     __header;

    public:
        _RB_tree( const Compare& comp = Compare(),
                  const Allocator& alloc = Allocator())
            : _node_alloc(alloc), _cmp(comp), _size(0)
        {
            this->__header = this->_node_alloc.allocate(1);
            this->_node_alloc.construct(this->__header, value_type());
        }

        _RB_tree( const _RB_tree& tree )
            : _node_alloc(tree._node_alloc),
              _cmp(tree._cmp), _size(0)
        {
            this->__header = this->_node_alloc.allocate(1);
            this->_node_alloc.construct(this->__header, value_type());

            this->_dfs_copy(&this->__header->_parent, this->__header, tree.__header->_parent);
            this->__header->_left = _node_type::get_minimal(this->__header->_parent);
            this->__header->_right = _node_type::get_maximal(this->__header->_parent);
        }

        ~_RB_tree( void )
        {
            this->_dfs_delete(this->__header->_parent);
            this->_node_alloc.destroy(this->__header);
            this->_node_alloc.deallocate(this->__header, 1);
        }

        _RB_tree&   operator=(const _RB_tree& tree)
        {
            if (this == &tree)
                return (*this);
            this->_dfs_delete(this->__header->_parent);
            this->_dfs_copy(&this->__header->_parent, this->__header, tree.__header->_parent);
            this->__header->_left = _node_type::get_minimal(this->__header->_parent);
            this->__header->_right = _node_type::get_maximal(this->__header->_parent);
            return (*this);
        }

        void		print()
        {
            _node_type::print(this->__header->_parent);
        }

		bool	is_red_black_tree()
		{
			ft::vector<ft::pair<int, _node_type*> >	vec;

			vec.push_back(ft::make_pair(0, this->__header->_parent));

			int i = 0;
			while (1)
			{
				if (vec[i].second)
				{
					if (vec[i].second && (_node_type::get_color(vec[i].second) == _RB_color_red) &&
						((vec[i].second->_left && _node_type::get_color(vec[i].second->_left) == _RB_color_red) ||
						(vec[i].second->_right && _node_type::get_color(vec[i].second->_right) == _RB_color_red)))
						return (false);
					if (vec[i].second && _node_type::get_color(vec[i].second) == _RB_color_red)
					{
						vec.push_back(ft::make_pair(vec[i].first, vec[i].second->_left));
						vec.push_back(ft::make_pair(vec[i].first, vec[i].second->_right));
					}
					else if (vec[i].second)
					{
						vec.push_back(ft::make_pair(vec[i].first + 1, vec[i].second->_left));
						vec.push_back(ft::make_pair(vec[i].first + 1, vec[i].second->_right));
					}
					vec.erase(vec.begin() + i);
					i = 0;
				}
				else
					i++;
				if (i == vec.size())
					break ;
			}
			i = vec[0].first;
			for (int j = 1; j < vec.size(); j++)
			{
				if (vec[j].first != i)
					return (false);
			}
			return (true);
		}

        _node_allocator get_allocator() const
        {
            return (this->_node_alloc);
        }

        _node_type*    push(const U& value)
        {
            if (!this->__header->_parent)
                return this->_add_node(&this->__header->_parent, value, this->__header);

            _node_type* iter = this->__header->_parent;
            _node_type* prev;
            while (iter)
            {
                prev = iter;
                if (this->_cmp(value, iter->_value))
                    iter = iter->_left;
                else if (this->_cmp(iter->_value, value))
                    iter = iter->_right;
                else
                    return iter;
            }

            if (this->_cmp(value, prev->_value))
                return this->_add_node(&prev->_left, value, prev);
            return this->_add_node(&prev->_right, value, prev);
        }


        _node_type*    push(const_iterator hint, const U& value)
        {
            _node_type* iter = hint._node;
            _node_type* prev;

            if (iter != this->__header->_parent &&
                !this->_cmp(value, iter->_parent->_value))
                iter = this->__header->_parent;

            while (iter)
            {
                prev = iter;
                if (this->_cmp(value, iter->_value))
                    iter = iter->_left;
                else if (this->_cmp(iter->_value, value))
                    iter = iter->_right;
                else
                    return iter;
            }

            if (this->_cmp(value, prev->_value))
                return this->_add_node(&prev->_left, value, prev);
            return this->_add_node(&prev->_right, value, prev);
        }

        _node_type*     search(const U& value)
        {
            _node_type*     iter = this->__header->_parent;

            while (iter)
            {
                if (this->_cmp(value, iter->_value))
                    iter = iter->_left;
                else if (this->_cmp(iter->_value, value))
                    iter = iter->_right;
                else
                    break;
            }
            return (iter);
        }

        const _node_type*     search(const U& value) const
        {
            _node_type*     iter = this->__header->_parent;

            while (iter)
            {
                if (this->_cmp(value, iter->_value))
                    iter = iter->_left;
                else if (this->_cmp(iter->_value, value))
                    iter = iter->_right;
                else
                    break;
            }
            return (iter);
        }


        _node_type*     search(const_iterator hint, const U& value)
        {
            _node_type*     iter = hint._node;

            if (iter != this->__header->_parent &&
                !this->_cmp(value, iter->_parent->_value))
                iter = this->__header->_parent;

            while (iter)
            {
                if (this->_cmp(value, iter->_value))
                    iter = iter->_left;
                else if (this->_cmp(iter->_value, value))
                    iter = iter->_right;
                else
                    break;
            }
            return (iter);
        }

        const _node_type*     search(const_iterator hint, const U& value) const
        {
            _node_type*     iter = hint._node;

            while (iter)
            {
                if (this->_cmp(value, iter->_value))
                    iter = iter->_left;
                else if (this->_cmp(iter->_value, value))
                    iter = iter->_right;
                else
                    break;
            }
            return (iter);
        }

        size_type       erase(const U& value)
        {
            _node_type*     node_ptr = this->search(value);
            size_type       deleted = 0;

            while (node_ptr)
            {
                this->_erase(node_ptr);
                deleted += 1;
                node_ptr = this->search(value);
            }
            this->_size -= deleted;
            return deleted;
        }

        void            erase(iterator pos)
        {
            this->_erase(pos._node);
            this->_size -= 1;
        }

        void            erase(const_iterator pos)
        {
            this->_erase(pos._node);
            this->_size -= 1;
        }

        void    clear()
        {
            this->_dfs_delete(this->__header->_parent);
            this->__header->_parent = NULL;
            this->__header->_left = NULL;
            this->__header->_right = NULL;
        }

        void    swap(_RB_tree& other)
        {
            _node_type  *tmp_node = this->__header;
            this->__header = other.__header;
            other.__header = tmp_node;

            size_type   tmp_size = this->_size;
            this->_size = other._size;
            other._size = tmp_size;

            Compare     tmp_cmp = this->_cmp;
            this->_cmp = other._cmp;
            other._cmp = tmp_cmp;
        }

        size_type       size(void) const
        { return this->_size; }

        iterator    lower_bound(const value_type& value)
        {
            _node_type*   tmp;
            tmp = this->_lower_bound(this->__header->_parent, value);
            if (!tmp)
                return (this->__header);
            return (tmp);
        }

        const_iterator    lower_bound(const value_type& value) const
        {
            const _node_type*   tmp;
            tmp = this->_lower_bound(this->__header->_parent, value);
            if (!tmp)
                return (this->__header);
            return (tmp);
        }

        iterator    upper_bound(const value_type& value)
        {
            _node_type*   tmp;
            tmp = this->_upper_bound(this->__header->_parent, value);
            if (!tmp)
                return (this->__header);
            return (tmp);
        }

        const_iterator    upper_bound(const value_type& value) const
        {
            const _node_type*   tmp;
            tmp = this->_upper_bound(this->__header->_parent, value);
            if (!tmp)
                return (this->__header);
            return (tmp);
        }

        iterator        begin()
        {
            if (!this->_size)
                return (this->__header);
            return (this->__header->_left);
        }

        const_iterator  begin() const
        {
            if (!this->_size)
                return (this->__header);
            return (this->__header->_left);
        }

        iterator        end()
        { return (this->__header); }

        const_iterator  end() const
        { return (this->__header); }

        reverse_iterator rbegin()
        {
            if (!this->_size)
                return (this->end());
            return (--this->end());
        }

        const_reverse_iterator rbegin() const
        {
            if (!this->_size)
                return (this->end());
            return (--this->end());
        }

        reverse_iterator rend()
        { return (this->end()); }

        const_reverse_iterator rend() const
        { return (this->end()); }


    private:
        void    _dfs_delete(_node_type *node)
        {
            if (!node)
                return;
            _dfs_delete(node->_left);
            _dfs_delete(node->_right);
            this->_node_alloc.destroy(node);
            this->_node_alloc.deallocate(node, 1);
            this->_size -= 1;
        }

        void    _dfs_copy(_node_type **dest, _node_type *prev,
                          const _node_type *to_copy)
        {
            if (!to_copy)
            {
                *dest = NULL;
                return;
            }
            *dest = this->_node_alloc.allocate(1);
            this->_node_alloc.construct(*dest, to_copy->_value);
            (*dest)->_parent = prev;
            (*dest)->_color = to_copy->_color;
            this->_size += 1;
            this->_dfs_copy(&(*dest)->_left, *dest, to_copy->_left);
            this->_dfs_copy(&(*dest)->_right, *dest, to_copy->_right);
        }

        _node_type *    _add_node(_node_type **dest, const value_type& value,
                                  _node_type *parent)
        {
            *dest = this->_node_alloc.allocate(1);
            this->_node_alloc.construct(*dest, value);
            (*dest)->_parent = parent;
            this->_size += 1;

            _node_type* out_ptr = *dest;
            if (parent != this->__header)
            {
                this->_check_balance(*dest);

                if (this->__header->_left->_left)
                    this->__header->_left = this->__header->_left->_left;
                if (this->__header->_right->_right)
                    this->__header->_right = this->__header->_right->_right;
            }
            else
            {
                this->__header->_left = (*dest);
                this->__header->_right = (*dest);
            }

            this->__header->_parent->_color = _RB_color_black;

            return out_ptr;
        }

        void    _check_balance(_node_type *target)
        {
            if (!target || target == this->__header->_parent || target == this->__header)
                return;

            if (target->_parent->_color != _RB_color_red)
                return;

            if (_node_type::get_color(_node_type::get_uncle(target)) == _RB_color_red)
                _balance_case1(target);
            else
            {
                if (_node_type::get_branch(target) != _node_type::get_branch(target->_parent))
                    _balance_case2(target);
                else
                    _balance_case3(target);
            }
        }

        inline void    _balance_case1(_node_type *target)
        {
            target->_parent->_color = _RB_color_black;
            _node_type::get_uncle(target)->_color = _RB_color_black;
            target->_parent->_parent->_color = _RB_color_red;
            this->_check_balance(target->_parent->_parent);
        }

        inline void    _balance_case2(_node_type *target)
        {
            if (_node_type::get_branch(target) == _RB_branch_right)
            {
                this->_rotate_left(target);
                _balance_case3(target->_left);
            }
            else
            {
                this->_rotate_right(target);
                _balance_case3(target->_right);
            }
        }

        inline void    _balance_case3(_node_type *target)
        {
            target->_parent->_color = _RB_color_black;
            target->_parent->_parent->_color = _RB_color_red;
            if (_node_type::get_branch(target) == _RB_branch_right)
                this->_rotate_left(target->_parent);
            else
                this->_rotate_right(target->_parent);
        }
        void     _rotate_right(_node_type *target)
        {
            _node_type* const   grandparent = target->_parent->_parent;

            if (target->_right)
                target->_right->_parent = target->_parent;
            target->_parent->_left = target->_right;

            target->_parent->_parent = target;
            target->_right = target->_parent;

            if (grandparent != this->__header)
            {
                if (grandparent->_left == target->_parent)
                    grandparent->_left = target;
                else
                    grandparent->_right = target;
            }
            else
                this->__header->_parent = target;

            target->_parent = grandparent;
        }

        void     _rotate_left(_node_type *target)
        {
            _node_type* const   grandparent = target->_parent->_parent;

            if (target->_left)
                target->_left->_parent = target->_parent;
            target->_parent->_right = target->_left;

            target->_parent->_parent = target;
            target->_left = target->_parent;

            if (grandparent != this->__header)
            {
                if (grandparent->_left == target->_parent)
                    grandparent->_left = target;
                else
                    grandparent->_right = target;
            }
            else
                this->__header->_parent = target;

            target->_parent = grandparent;
        }

        void    _erase(_node_type *target)
        {
            size_type   count_of_children = 0;
            if (target->_right)
                count_of_children += 1;
            if (target->_left)
                count_of_children += 1;

            if (count_of_children == 2)
                this->_erase_case_rb_2(target);
            else if (count_of_children == 1)
                this->_erase_case_black_1(target);
            else
            {
                if (target->_color == _RB_color_red)
                    this->_erase_case_red_0(target);
                else
                    this->_erase_case_black_0(target);
            }
        }
        inline void    _erase_case_rb_2(_node_type *target)
        {
            _node_type  *min = target->_right;
            _node_type  *max = target->_left;

            while (min && max)
            {
                min = min->_left;
                if (min)
                    max = max->_right;
            }
            while (min && min->_left)
                min = min->_left;
            while (max && max->_right)
                max = max->_right;

            _node_type  *to_swap = max;
            if (min)
                to_swap = min;
            else
                to_swap = max;

            this->_erase_swap_nodes(target, to_swap);

            this->_erase(target);
        }

        inline void    _erase_case_black_1(_node_type *target)
        {
            _node_type  *to_swap;
            if (target->_left)
                to_swap = target->_left;
            else
                to_swap = target->_right;

            this->_erase_swap_nodes(target, to_swap);

            this->_erase_case_red_0(target);
        }


        inline void    _erase_case_red_0(_node_type *target)
        {
            if (_node_type::get_branch(target) == _RB_branch_left)
                target->_parent->_left = NULL;
            else
                target->_parent->_right = NULL;

            if (this->__header->_right == target)
                this->__header->_right = target->_parent;
            else if (this->__header->_left == target)
                this->__header->_left = target->_parent;

            this->_node_alloc.destroy(target);
            this->_node_alloc.deallocate(target, 1);
        }

        inline void    _erase_case_black_0(_node_type *target)
        {
            _node_type  *parent = target->_parent;

            if (parent == this->__header)
                parent->_parent = NULL;
            if (parent->_left == target)
                parent->_left = NULL;
            if (parent->_right == target)
                parent->_right = NULL;

            if (this->__header->_right == target)
                this->__header->_right = parent;
            else if (this->__header->_left == target)
                this->__header->_left = parent;

            this->_node_alloc.destroy(target);
            this->_node_alloc.deallocate(target, 1);
            this->_erase_rebalance(NULL, parent);
        }

        void    _erase_swap_nodes(_node_type *parent, _node_type *descendent)
        {
            if (parent == this->__header->_parent)
                this->__header->_parent = descendent;
            else
            {
                if (_node_type::get_branch(parent) == _RB_branch_left)
                    parent->_parent->_left = descendent;
                else
                    parent->_parent->_right = descendent;
            }

            if (descendent->_parent != parent)
            {
                if (_node_type::get_branch(descendent) == _RB_branch_left)
                    descendent->_parent->_left = parent;
                else
                    descendent->_parent->_right = parent;
            }

            if (parent == this->__header->_left)
                this->__header->_left = descendent;
            else if (descendent == this->__header->_left)
                this->__header->_left = parent;

            if (parent == this->__header->_right)
                this->__header->_right = descendent;
            else if (descendent == this->__header->_right)
                this->__header->_right = parent;

            if (parent->_left && parent->_left != descendent)
                parent->_left->_parent = descendent;
            if (parent->_right && parent->_right != descendent)
                parent->_right->_parent = descendent;

            if (descendent->_left)
                descendent->_left->_parent = parent;
            if (descendent->_right)
                descendent->_right->_parent = parent;

            char    buffer[sizeof(_node_type)];
            memcpy(buffer, parent, sizeof(_node_type));
            memcpy(parent, descendent, sizeof(_node_type));
            memcpy(descendent, buffer, sizeof(_node_type));

            if (parent->_parent == parent)
                parent->_parent = descendent;
            if (descendent->_left == descendent)
                descendent->_left = parent;
            else if (descendent->_right == descendent)
                descendent->_right = parent;

            parent->swap_values(descendent);
        }

        void    _erase_rebalance(_node_type *child, _node_type *parent)
        {
            if (parent == this->__header || !parent)
                return;

            _node_type  *sibling;
            if (parent->_left == child)
                sibling = parent->_right;
            else
                sibling = parent->_left;

            if (sibling->_color == _RB_color_black)
            {
                _node_type  *same_branch_child;
                _node_type  *another_branch_child;

                if (_node_type::get_branch(sibling) == _RB_branch_right)
                {
                    same_branch_child = sibling->_right;
                    another_branch_child = sibling->_left;
                }
                else
                {
                    same_branch_child = sibling->_left;
                    another_branch_child = sibling->_right;
                }

                if (_node_type::get_color(same_branch_child) == _RB_color_red)
                    this->_erase_rebalance_case__black_red_sameb(sibling);
                else if (_node_type::get_color(another_branch_child) == _RB_color_red)
                    this->_erase_rebalance_case__black_red_anotherb(sibling);
                else
                    this->_erase_rebalance_case__black_black(sibling);
            }
            else
                this->_erase_rebalance_case__red(child, parent, sibling);
        }

        inline void     _erase_rebalance_case__black_red_sameb(_node_type *sibling)
        {
            sibling->_color = sibling->_parent->_color;
            sibling->_parent->_color = _RB_color_black;
            if (_node_type::get_branch(sibling) == _RB_branch_right)
            {
                sibling->_right->_color = _RB_color_black;
                this->_rotate_left(sibling);
            }
            else
            {
                sibling->_left->_color = _RB_color_black;
                this->_rotate_right(sibling);
            }
        }

        inline void     _erase_rebalance_case__black_red_anotherb(_node_type *sibling)
        {
            sibling->_color = _RB_color_red;
            if (_node_type::get_branch(sibling) == _RB_branch_right)
            {
                sibling->_left->_color = _RB_color_black;
                this->_rotate_right(sibling->_left);
            }
            else
            {
                sibling->_right->_color = _RB_color_black;
                this->_rotate_left(sibling->_right);
            }
            this->_erase_rebalance_case__black_red_sameb(sibling->_parent);
        }
        inline void     _erase_rebalance_case__black_black(_node_type *sibling)
        {
            sibling->_color = _RB_color_red;
            if (sibling->_parent->_color != _RB_color_red)
                this->_erase_rebalance(sibling->_parent, sibling->_parent->_parent);
            else
                sibling->_parent->_color = _RB_color_black;
        }

        inline void     _erase_rebalance_case__red(_node_type *child, _node_type *parent, _node_type *sibling)
        {
            sibling->_parent->_color = _RB_color_red;
            sibling->_color = _RB_color_black;
            if (_node_type::get_branch(sibling) == _RB_branch_right)
                this->_rotate_left(sibling);
            else
                this->_rotate_right(sibling);
            this->_erase_rebalance(child, parent);
        }


        _node_type* _lower_bound(_node_type* root, const value_type& value)
        {
            _node_type* tmp;

            while (root)
            {
                if (this->_cmp(root->_value, value))
                    root = root->_right;
                else
                {
                    if (root->_left)
                    {
                        tmp = this->_lower_bound(root->_left, value);
                        if (tmp)
                            root = tmp;
                        break;
                    }
                    else
                        break;
                }
            }
            return root;
        }

        const _node_type* _lower_bound(const _node_type* root,
                                 const value_type& value) const
        {
            const _node_type*   tmp;

            while (root)
            {
                if (this->_cmp(root->_value, value))
                    root = root->_right;
                else
                {
                    if (root->_left)
                    {
                        tmp = this->_lower_bound(root->_left, value);
                        if (tmp)
                            root = tmp;
                        break;
                    }
                    else
                        break;
                }
            }
            return root;
        }

        _node_type* _upper_bound(_node_type* root, const value_type& value)
        {
            _node_type* tmp;

            while (root)
            {
                if (!this->_cmp(value, root->_value))
                    root = root->_right;
                else
                {
                    if (root->_left)
                    {
                        tmp = this->_upper_bound(root->_left, value);
                        if (tmp)
                            root = tmp;
                        break;
                    }
                    else
                        break;
                }
            }
            return root;
        }

        const _node_type* _upper_bound(_node_type* root,
                                       const value_type& value) const
        {
            const _node_type* tmp;

            while (root)
            {
                if (!this->_cmp(value, root->_value))
                    root = root->_right;
                else
                {
                    if (root->_left)
                    {
                        tmp = this->_upper_bound(root->_left, value);
                        if (tmp)
                            root = tmp;
                        break;
                    }
                    else
                        break;
                }
            }
            return root;
        }
    }; 

}