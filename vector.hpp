#pragma once
#include <exception>
#include <iostream>
#include <iterator>

namespace ft
{
template typename <T, Alloc = std::allocator<T>>
class Vector
{
private:
    T* _arr;
    size_t _size;
    size_t capacity;



}