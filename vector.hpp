#pragma once
#include <exception>
#include <iostream>
#include <iterator>
#include "vector.hpp"

namespace ft
{
template typename<T, Alloc = std::allocator<T>>
class Vector
{
private:
    T* _arr;
    size_t _size;
    size_t capacity;
    T 



}