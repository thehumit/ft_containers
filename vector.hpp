#pragma once
#include <exception>
#include <iostream>
#include <iterator>
#include "iterator.hpp"

namespace ft
{

template <class T, class Alloc = std::allocator<T> >
class Vector
{
    typedef T   type_name;
    typedef Alloc allocator_type;
    typedef typename allocator_type::reference  reference;
    typedef typename allocator_type::const_reference    const_reference;
    typedef typename allocator_type::pointer            pointer;
    typedef typename allocator_type::const_pointer      const_pointer;
    typedef ft::RandomAccessIterator<value_type>               iterator;
    typedef ft::RandomAccessIterator<const value_type>            const_iterator;
    typedef ft::reverse_iterator<iterator>             reverse_iterator;
    typedef ft::reverse_iterator<const_iterator>       const_reverse_iterator;
    typedef typename ft::iterator_traits<iterator>::difference_type    difference_type;
    typedef typename allocator_type::size_type          size_type;
public:
    size_t size() const
    {
        return (this._size);
    }

    size_t capacity() const
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
        if (i >= this->m_size)
            throw std::out_of_range("Out of range");
        return (this->m_container[i]);
    }

    const_reference at(size_type i) const
    {
        if (i >= this->m_size)
            throw std::out_of_range("Out of range");
        return (this->m_container[i]);
    }

    iterator begin()
    {
        return (this->_arr);
    }

    const_iterator begin() const
    {
        return(this->_arr);
    }

    iterator end()
    {
        if (this->empty())
            return (this->begin());
        return (this->_arr + this->_size - 1);
    }

    const_iterator end() const
    {
        if (this->empty())
            return (this->begin());
        return (this->_arr + this->_size - 1);
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
        return (*(this->_arr + size - 1));
    }

    const_reference back () const
    {
        return (*(this->_arr + size -1));
    }

    void reszie(size_t n, type_name val = type_name())
    {
        size_t old_size = this->_size;
        if (n < this->_size)
        {
            while (this->_size < n)
            {
                this->_allocator.destroy(this->_arr[this->_size - 1]);//check out of buff
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

    void reserve(size_t n)
    {
        size_t old_capacity = this->_capacity;
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
                this->capacity *= 2;
            else
                this->capacity = n;
            type_name* newarr = this->_allocator.allocate(this->_capacity);
            for (int i = 0; i < this->_size, i++)
            {
                this->_allocator.construct(newarr + i, this->_arr[i]);
                this->_allocator.destroy(this->_arr + i);
            }
            this->_allocator.deallocate(this->_arr, old_capacity);
            this->_arr = newarr;
        }
    }

    void push_pack(const type_name& val)
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

    void insert(iterator position, size_t n, const type_name &val)
    {
        iterator it = this->begin();
        size_t old_capacity = this->_capacity;
        size_t old_arr_i = 0;
        size_t tmp_i = 0;

        if (this->_size + n >= this->_capacity)
        {
            if ((this->_capacity * 2) > n)
                this->capacity *= 2;
            else
                this->capacity = this->_size + n;
            type_name* newarr = this->_allocator.allocate(this->_capacity);
            for (int i = 0; it != position, i++)
            {
                this->_allocator.construct(newarr + i, this->_arr[i]);
                this->_allocator.destroy(this->_arr + i);
                old_arr_i++;
                it++;
            }
            tmp_i = old_arr_i;
            for (int i = old_arr_i + n; i < this->_size + n; i++)
            {
                this->_allocator.construct(newarr + i, this->_arr[old_arr_i]);
                this->_allocator.destroy(this->_arr + old_arr_i);
                old_arr_i++;
            }
            for (int j = 0; j < n; j++)
            {
                this->_allocator.construct(newarr + old_arr_i, val);
                old_arr_i++;
            }
            this->_allocator.deallocate(this->_arr, old_capacity);
            this->_arr = newarr;
        }
        else
        {
            while (it != position)
                it++;
            old_arr_i = it - this->begin();
            type_name* newarr = this->_allocator.allocate()

        }
    }

private:
    T* _arr;
    size_t _size;
    size_t _capacity;
    allocator_type _allocator;
};

}
