#pragma once
#include <exception>
#include <iostream>
#include <iterator>
#include "utils.hpp"
#include "iterator.hpp"

// std::ostream& operator<< (std::ostream &out, const std::vector<T> &vec)
// {
    // int size = vec.size();
    // for (int i = 0; i < size; i++)
        // out << "++" << vec[i] << std::endl;
    // return out;
// }

namespace ft
{

template <class T, class Alloc = std::allocator<T> >
class vector
{
public:
    typedef T   type_name;
    typedef Alloc allocator_type;
    typedef typename allocator_type::reference  reference;
    typedef typename allocator_type::const_reference    const_reference;
    typedef typename allocator_type::pointer            pointer;
    typedef typename allocator_type::const_pointer      const_pointer;
    typedef ft::RandomAccessIterator<type_name>               iterator;
    typedef ft::RandomAccessIterator<const type_name>            const_iterator;
    typedef ft::reverse_iterator<iterator>             reverse_iterator;
    typedef ft::reverse_iterator<const_iterator>       const_reverse_iterator;
    typedef typename ft::iterator_traits<iterator>::difference_type    difference_type;
    typedef typename allocator_type::size_type          size_type;


    explicit vector (const allocator_type& alloc = allocator_type())
	:
        _arr(nullptr),
        _size(0),
        _capacity(0),
		_allocator(alloc)
	{}

    explicit vector (size_type n, const type_name& val = type_name(),
        const allocator_type& alloc = allocator_type())
	:
        _arr(nullptr),
        _size(0),
        _capacity(0),
		_allocator(alloc)
	{
		this->_arr = this->_allocator.allocate(n);
		this->_capacity = n;
        this->_size = n;
		for (int i = 0; i < n; i++)
			this->_allocator.construct(this->_arr + i, val);
	}

	template <class InputIterator>
	vector (InputIterator first, InputIterator last,
			const allocator_type& alloc = allocator_type(),
				typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = nullptr)
	:
		_allocator(alloc)
	{
		// bool is_valid;
		// if (!(is_valid = ft::is_ft_iterator_tagged<typename ft::iterator_traits<InputIterator>::iterator_category >::value))
			// throw (ft::InvalidIteratorException<typename ft::is_ft_iterator_tagged<typename ft::iterator_traits<InputIterator>::iterator_category >::type>());
		difference_type n = ft::distance(first, last);
		this->_arr = this->_allocator.allocate(n);
		this->_capacity = n;
        this->_size = n;
        iterator it = this->begin();
		while (n--)
			this->_allocator.construct(&(*it), *first++);
	}

    size_type size() const
    {
        return (this->_size);
    }

    size_type capacity() const
    {
        return (this->_capacity);
    }

    bool empty (void) const
    {
        return (size() == 0 ? true : false);
    }

    reference operator[](size_type n)
    {
        return (*(this->_arr + n));
    }

    const_reference operator[] (size_type n) const
    {
        return (*(this->_arr + n));
    }

    reference at(size_type i)
    {
        if (i >= this->_size)
            throw std::out_of_range("Out of range");
        return (this->_arr[i]);
    }

    const_reference at(size_type i) const
    {
        if (i >= this->_size)
            throw std::out_of_range("Out of range");
        return (this->_arr[i]);
    }

    iterator begin()
    {
        return (iterator(this->_arr));
    }

    const_iterator begin() const
    {
        return(iterator(this->_arr));
    }

    iterator end()
    {
        if (this->empty())
            return (this->begin());
        return (this->begin() + this->_size - 1);
    }

    const_iterator end() const
    {
        if (this->empty())
            return (this->begin());
        return (this->begin() + this->_size - 1);
    }

    reverse_iterator rbegin()
    {
        return (reverse_iterator(this->end()));
    }

    const_reverse_iterator rbegin() const
    {
        return (reverse_iterator(this->end()));
    }

    reverse_iterator rend()
    {
        return (reverse_iterator(this->begin()));
    }

    const_reverse_iterator rend() const
    {
        return (reverse_iterator(this->begin()));
    }

    reference front ()
    {
        return (*this->_arr);
    }

    reference front () const
    {
        return (*this->_arr);
    }

    reference back ()
    {
        return (*(this->_arr + this->_size - 1));
    }

    const_reference back () const
    {
        return (*(this->_arr + this->_size -1));
    }

    void resize(size_type n, type_name val = type_name())
    {
        size_type old_size = this->_size;
        if (n < this->_size)
        {
            while (this->_size < n)
            {
                this->_allocator.destroy(&this->_arr[this->_size - 1]);//check out of buff
                this->_size--;
            }
        }
        else
        {
            reserve(n);
            for (int i = old_size; i < n; i++)
            {
                push_back(val);
            }
        }
    }

    void reserve(size_type n)
    {
        size_type old_capacity = this->_capacity;
        if (n <= this->_capacity)
            return; //need to test with setting values;
        if (this->_capacity == 0)
        {
            this->_arr = this->_allocator.allocate(n);
            this->_capacity = n;
        }
        else if (this->_capacity < n)
        {
            if ((this->_capacity * 2) > n)
                this->_capacity *= 2;
            else
                this->_capacity = n;
            type_name* newarr = this->_allocator.allocate(this->_capacity);
            for (size_type i = 0; i < this->_size; i++)
            {
                this->_allocator.construct(newarr + i, this->_arr[i]);
                this->_allocator.destroy(this->_arr + i);
            }
            this->_allocator.deallocate(this->_arr, old_capacity);
            this->_arr = newarr;
        }
    }

    void push_back(const type_name& val)
    {
        this->reserve(this->_size + 1);
        this->_allocator.construct(this->_arr + this->_size, val);
        this->_size++;
    }

    void pop_back()
    {
        _allocator.destroy(&this->back());
        this->_size--;
    }

    allocator_type get_allocator() const 
    {
        return (this->_allocator);
    }

    size_type max_size() const 
    {
        return (this->_allocator.max_size()); 
    }

    iterator insert(iterator position, const type_name &val)
    {
        difference_type dist = position - this->begin();
		this->insert(position, 1, val);
		return (this->begin() + dist);
	}

    void insert(iterator position, size_type n, const type_name &val)
    {
        iterator it = this->begin();
        size_type old_capacity = this->_capacity;
        size_type old_arr_i = 0;
        size_type tmp_i = 0;

        if (this->_size + n >= this->_capacity)
        {
            if ((this->_capacity * 2) > n + this->_size)
                this->_capacity *= 2;
            else
                this->_capacity = this->_size + n;
        }
        type_name* newarr = this->_allocator.allocate(this->_capacity);
        for (size_type i = 0; it != position; i++)
        {
            this->_allocator.construct(newarr + i, this->_arr[i]);
            this->_allocator.destroy(this->_arr + i);
            old_arr_i++;
            it++;
        }
        tmp_i = old_arr_i;
        for (size_type i = old_arr_i + n; i < this->_size + n; i++)
        {
            this->_allocator.construct(newarr + i, this->_arr[old_arr_i]);
            this->_allocator.destroy(this->_arr + old_arr_i);
            old_arr_i++;
        }
        for (size_type j = 0; j < n; j++)
        {
            this->_allocator.construct(newarr + tmp_i, val);
            tmp_i++;
        }
        this->_allocator.deallocate(this->_arr, old_capacity);
        this->_arr = newarr;
    }

    template <class InputIterator>
    void insert (iterator position, InputIterator first,
		typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type last)
	{
		size_type	n = last - first;

		size_type	begin_capacity = this->_capacity;
		if (this->_capacity == 0)
		{
			this->_capacity = 1;
		}
		while (this->_capacity < this->_size + n)
		{
			this->_capacity *= 2;
		}

		pointer	tmp;
		pointer	tmp_last;

		tmp = this->_allocator.allocate(this->_capacity);
		
		tmp_last = tmp;

		pointer		left = this->_arr;
		iterator	left_iter(left);

		while (this->_arr && left_iter < position)
		{
			this->_allocator.construct(tmp_last, *left_iter);
			this->_allocator.destroy(left);

			tmp_last++;
			left++;
			left_iter++;
		}
		while (n > 0)
		{
			this->_allocator.construct(tmp_last, *first);
			this->_size++;
			tmp_last++;
			first++;
			n--;
		}
		while (this->_arr && left_iter < this->end())
		{
			this->_allocator.construct(tmp_last, *left);
			this->_allocator.destroy(left);

			tmp_last++;
			left++;
			left_iter++;
		}
		if (this->_arr)
		{
			this->_allocator.deallocate(this->_arr, begin_capacity);
		}
		this->_arr = tmp;
		// this->_end = this->_arr + this->_size;
	}


    // template <class InputIterator>
    // void insert(iterator position, InputIterator first, InputIterator last,
    //     typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = nullptr)
    // {
    //     iterator it = this->begin();
    //     int i = 0;
    //     int old_arr_i = 0;
    //     int old_capacity = this->_size;
    //     difference_type dist = ft::distance(first, last);
        
    //     if (this->_size + dist >= this->_capacity)
    //     {
    //         if ((this->_capacity * 2) > dist + this->_size)
    //             this->_capacity *= 2;
    //         else
    //             this->_capacity = this->_size + dist;
    //     }
    //     type_name* newarr = this->_allocator.allocate(this->_capacity);
    //     for (; it != position; i++)
    //     {
    //         this->_allocator.construct(newarr + i, this->_arr[i]);
    //         this->_allocator.destroy(this->_arr + i);
    //         it++;
    //     }
    //     old_arr_i = i;
    //     for (size_type j = i + dist - 1; i < this->_size + dist - 1; j++)//////
    //     {
    //         this->_allocator.construct(newarr + j, this->_arr[i]);
    //         this->_allocator.destroy(this->_arr + i);
    //         i++;
    //     }
    //     for (size_type j = 0; j < dist; j++)
    //     {
    //         this->_allocator.construct(newarr + old_arr_i, *first++);
    //         old_arr_i++;
    //     }
    //     this->_allocator.deallocate(this->_arr, old_capacity);
    // }

    void assign(size_type n, const type_name &val)
    {
        this->clear();
        if (n == 0)
            return ;
        if (this->_capacity >= n)
        {
            for (int i = 0; i < n; i++)
            {
                this->_allocator.construct(this->_arr + i, val);
            }
        }
        else
        {
            this->_allocator.deallocate(this->_arr, this->_capacity);
            this->_arr = this->_allocator.allocate(n);
            this->_size = n;
            this->_capacity = n;
            for (int i = 0; i < n; i++)
            {
                this->_allocator.construct(this->_arr + i, val);
            }
        }
    }

    template <class InputIterator>
    void assign (InputIterator first, InputIterator last,
        typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = nullptr)
    {
        this->clear();
        size_type dist = ft::distance(first, last);
        if (this->_capacity >= dist)
        {
            for(int i = 0; &(*first) != &(*last); first++, i++)
                this->_allocator.construct(this->_arr + i, *first);
        }
        else
        {
            type_name *newarr = this->_allocator.allocate(dist);
            for(int i = 0; &(*first) != &(*last); first++, i++)
                this->_allocator.construct(newarr + i, *first);
            this->_allocator.deallocate(this->_arr, this->capacity());
            this->_arr = newarr;
            this->_capacity = dist;
            this->_size = dist;
        }
    }

    iterator erase (iterator position)
	{
        return (erase(position, position + 1)); 
    }

	iterator erase (iterator first, iterator last)
	{
		if (last <= first)
			return (last);
		iterator	cpy = first;
		iterator	end = this->end();
		iterator	ans = first;

		while (first != last)
		{

			this->_allocator.destroy(&(*first));
			first++;
		}
		while (first != end)
		{
			this->_allocator.construct(&(*cpy), *first);
			first++;
			cpy++;
		}
		while (cpy != end)
		{
			this->_allocator.destroy(&(*cpy));
			this->_size--;
			cpy++;
		}
		return (ans);
	}

    void clear()
	{
		size_type size = this->size();
		for (size_type i = 0; i < size; i++)
			this->_allocator.destroy(this->_arr + i);
	}
    void swap (vector& x)
	{
		if (x == *this)
			return;
		
        pointer tmp_arr = x._arr;
		size_type tmp_size = x._size;
        size_type tmp_capacity = x._capacity;
		allocator_type tmp_allocator = x._allocator;

        x._arr = this->_arr;
        x._size = this->_size;
        x._capacity = this->_capacity;
        x._allocator = this->_allocator;

		this->_arr = tmp_arr;
		this->_size = tmp_size;
		this->_capacity = tmp_capacity;
		this->_allocator = tmp_allocator;
	}


private:
    pointer _arr;
    size_type _size;
    size_type _capacity;
    allocator_type _allocator;
};

template<class InputIt1, class InputIt2>
bool lexicographical_compare(InputIt1 first1, InputIt1 last1,
                             InputIt2 first2, InputIt2 last2)
{
    for ( ; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2 ) {
        if (*first1 < *first2) return true;
        if (*first2 < *first1) return false;
    }
    return (first1 == last1) && (first2 != last2);
}

template<class InputIt1, class InputIt2, class Compare>
bool lexicographical_compare(InputIt1 first1, InputIt1 last1,
                             InputIt2 first2, InputIt2 last2,
                             Compare comp)
{
    for ( ; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2 ) {
        if (comp(*first1, *first2)) return true;
        if (comp(*first2, *first1)) return false;
    }
    return (first1 == last1) && (first2 != last2);
}

template<class InputIt1, class InputIt2>
bool equal(InputIt1 first1, InputIt1 last1, 
           InputIt2 first2)
{
    for (; first1 != last1; ++first1, ++first2) {
        if (!(*first1 == *first2)) {
            return false;
        }
    }
    return true;
}

template<typename T>
bool operator==(vector<T> const &lhs, vector<T> const &rhs) {
	if (lhs.size() != rhs.size())
		return (false);
	for (size_t i = 0; i < lhs.size(); i++)
		if (lhs[i] != rhs[i])
			return (false);
	return (true);
}

template<typename T>
bool operator!=(vector<T> const &lhs, vector<T> const &rhs) {
	return (!(lhs == rhs));
}

template<typename T>
bool operator!=(vector<T> &lhs, vector<T> &rhs) {
	return (!(lhs == rhs));
}

template<typename T>
bool operator<(vector<T> const &lhs, vector<T> const &rhs) {
	return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
}

template<typename T>
bool operator<=(vector<T> const &lhs, vector<T> const &rhs) {
	return (!(rhs < lhs));
}

template<typename T>
bool operator>(vector<T> const &lhs, vector<T> const &rhs) {
	return (rhs < lhs);
}

template<typename T>
bool operator>=(vector<T> const &lhs, vector<T> const &rhs) {
	return (!(lhs < rhs));
}

template<typename T, class Alloc>
void swap(vector<T, Alloc> const &lhs, vector<T, Alloc> const &rhs)
{
    lhs.swap(rhs);
}

template<typename T, class Alloc>
void swap(vector<T, Alloc> &lhs, vector<T, Alloc> &rhs)
{
    lhs.swap(rhs);
}

}
