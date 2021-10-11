#pragma once
#include <exception>
#include <iostream>
#include <iterator>
#include <vector>

namespace ft
{
    struct input_iterator_tag {};
	struct forward_iterator_tag 
		: public input_iterator_tag {};
	struct biderectional_iterator_tag
		: public forward_iterator_tag {};
	struct random_access_iterator_tag
		: public biderectional_iterator_tag {};

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


	

	
	//  std::iterator_traits< std::vector<std::string>::const_reverse_iterator >::
}
