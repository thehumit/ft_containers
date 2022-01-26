#pragma once
#include "iterator_traits.hpp"
#include "iterator.hpp"

namespace ft
{

template <class T1, class T2>
class pair
{
public:
	typedef T1 first_type;
	typedef T2 second_type;

	first_type  first;
	second_type second;


	pair() : first(first_type()), second(second_type()) {}
	
	template<class U, class V>
	pair (const pair<U, V>& pr) : first(pr.first), second(pr.second)
	{
	}

	pair (const first_type& a, const second_type& b) : first(a), second(b)
	{
	}

	pair&	operator=(const pair& pr)
	{
		if (this == &pr)
			return (*this);
		this->first = pr.first;
		this->second = pr.second;
		return (*this);
	}


};

template <class T1, class T2>
ft::pair<T1, T2>	make_pair(T1 first, T2 second)
{
	return (ft::pair<T1, T2>(first, second));
}

template <class T>
void	swap(T &a, T &b)
{
	T	x = a;
	a = b;
	b = x;
}

template<class InputIterator>
typename ft::iterator_traits<InputIterator>::difference_type
distance (InputIterator first, InputIterator last)
{
    typename ft::iterator_traits<InputIterator>::difference_type rtn = 0;
    while (first != last)
    {
        first++;
        rtn++;
    }
    return (rtn);
}


template<bool Cond, class T = void> 
struct enable_if {};

template<class T>
struct enable_if<true, T>
{
    typedef T type;
};

template <bool is_integral, typename T>
struct is_integral_res
{
    typedef T type;
    static const bool value = is_integral;
};

template <typename>
struct is_integral_type : public is_integral_res<false, bool> {};

template <>
struct is_integral_type<bool> : public is_integral_res<true, bool> {};

template <>
struct is_integral_type<char> : public is_integral_res<true, char> {};

template <>
struct is_integral_type<signed char> : public is_integral_res<true, signed char> {};

template <>
struct is_integral_type<short int> : public is_integral_res<true, short int> {};

template <>
struct is_integral_type<int> : public is_integral_res<true, int> {};

template <>
struct is_integral_type<long int> : public is_integral_res<true, long int> {};

template <>
struct is_integral_type<long long int> : public is_integral_res<true, long long int> {};

template <>
struct is_integral_type<unsigned char> : public is_integral_res<true, unsigned char> {};

template <>
struct is_integral_type<unsigned short int> : public is_integral_res<true, unsigned short int> {};

template <>
struct is_integral_type<unsigned int> : public is_integral_res<true, unsigned int> {};

template <>
struct is_integral_type<unsigned long int> : public is_integral_res<true, unsigned long int> {};

template <>
struct is_integral_type<unsigned long long int> : public is_integral_res<true, unsigned long long int> {};

template <typename T>
    struct is_integral : public is_integral_type<T> { };

template <class T>
struct less
{
	bool operator()( const T& lhs, const T& rhs ) const
	{ return (lhs < rhs); }
};

}
