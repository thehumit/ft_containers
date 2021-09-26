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

template<typename It>
class ReverseIterator:
	public It
{
public:
	using typename It::value_type;
    using typename It::pointer;
    using typename It::const_pointer;
    using typename It::reference;
    using typename It::const_reference;
    using typename It::difference_type;
public:
	ReverseIterator(): It() {}
	ReverseIterator(It const &it): It(it) {}
	ReverseIterator(ReverseIterator const &other): It(other.p) {}
	ReverseIterator &operator=(ReverseIterator const &other) {
		this->p = other.p;
		return (*this);
	}

	reference operator*() {
		It tmp(*this);
		return (*--tmp);
	}
	const_reference operator*() const {
		It tmp(*this);
		return (*--tmp);
	}
	pointer operator->() {
		It tmp(*this);
		return (&*--tmp);
	}
	const_pointer operator->() const {
		It tmp(*this);
		return (&*--tmp);
	}
	ReverseIterator operator++(int) {
		ReverseIterator tmp(*this);
		operator++();
		return (tmp);
	}
	It &operator++() {
		return (this->It::operator--());
	}
	ReverseIterator operator--(int) {
		ReverseIterator tmp(*this);
		operator--();
		return (tmp);
	}
	It &operator--() {
		return (this->It::operator++());
	}
};
}
