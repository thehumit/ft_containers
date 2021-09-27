#pragma once
#include <exception>
#include <iostream>
#include <iterator>

namespace ft
{
    template <class Iterator>
	struct iterator_traits
    {
        typedef typename Iterator::difference_type       difference_type;
        typedef typename Iterator::value_type            value_type;
        typedef typename Iterator::pointer               pointer;
        typedef typename Iterator::reference             reference;
        typedef typename Iterator::iterator_category     iterator_category;
    };
    

    template <class T> struct iterator_traits<T*>
    {
        typedef ptrdiff_t                       difference_type;
        typedef T                               value_type;
        typedef T*                              pointer;
        typedef T&                              reference;
        typedef ft::random_access_iterator_tag  iterator_category;
    };

    template <class T> class iterator_traits<const T*>
    {
        typedef ptrdiff_t                       difference_type;
        typedef T                               value_type;
        typedef const T*                        pointer;
        typedef const T&                        reference;
        typedef ft::random_access_iterator_tag  iterator_category;
    };

	template <class C, class T, class Dist = ptrdiff_t, class Pt = T *, class Rt = T&>
	struct iterator
	{
		typedef C iterator_category;
		typedef T value_type;
		typedef Dist difference_type;
		typedef Pt pointer;
		typedef Rt reference;
	};

	struct input_iterator_tag {};
	struct forward_iterator_tag 
		: public input_iterator_tag {};
	struct biderectional_iterator_tag
		: public forward_iterator_tag {};
	struct random_access_iterator_tag
		: public biderectional_iterator_tag {};
	

	
	 
}
