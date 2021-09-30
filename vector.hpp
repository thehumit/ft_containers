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
    // void reszie
    void reserve(size_t n)
    {
        if (n <= cap)
    }
private:
    T* _arr;
    size_t _size;
    size_t _capacity;

};

}