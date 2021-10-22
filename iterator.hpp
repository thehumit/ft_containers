#pragma once
#include "iterator_traits.hpp"

namespace ft
{
	template <class C, class T, class Dist = ptrdiff_t, class Pt = T *, class Rt = T&>
	struct iterator
	{
		typedef C iterator_category;
		typedef T value_type;
		typedef Dist difference_type;
		typedef Pt pointer;
		typedef Rt reference;
	};



template<class T, class Dist = ptrdiff_t, class Pt = T*, class Rt = T&>
class RandomAccessIterator 
    : public iterator<random_access_iterator_tag, T, Dist, Pt, Rt> 
{
public:
    typedef RandomAccessIterator<T, Dist, Pt, Rt> RanIt;
    RandomAccessIterator () {}
    explicit RandomAccessIterator(Pt P)
        : _current(P) {}
    RandomAccessIterator (const RandomAccessIterator<T, Dist, Pt, Rt>& X)
        : _current(X.base()) {}
    
    // operator RandomAccessIterator<T, Dist, T*, T&>()
	// {
	// 	return RandomAccessIterator<T, Dist, T*, T&>(this->_current);
	// }
    
    operator RandomAccessIterator<const T, Dist, const T*, const T&>()
	{
		return RandomAccessIterator<const T, Dist, const T*, const T&>(this->_current);
	}

    Pt base() const
    {
        return (this->_current);
    }
    Rt operator*() const
    {
        return (*this->_current); 
    }
    Pt operator->() const
    {
        return (&**this);
    }
    RanIt& operator++()
    {
        ++this->_current;
        return (*this); 
    }
    RanIt operator++ (int)
    {
        RanIt Tmp = *this;
        ++this->_current;
        return (Tmp);
    }
    RanIt& operator--()
    {
        --this->_current;
        return (*this);
    }
    RanIt operator-- (int)
    {
        RanIt Tmp = *this;
        --this->_current;
        return (Tmp);
    }
    bool operator==(int Y) const
    {
        return (this->_current == (Pt)Y); 
    }
    bool operator==(const RanIt& Y) const
    {
        return (this->_current == Y._current); 
    }

    bool operator!=(const RanIt& Y) const
    {
        return (!(*this == Y));
    }

    RanIt& operator+=(Dist N)
    {
        this->_current += N;
        return (*this);
    }
    RanIt operator+(Dist N) const
    {
        return (RanIt(this->_current + N));
    }
    RanIt& operator-=(Dist N)
    {
        this->_current -= N;
        return (*this); 
    }
    RanIt operator-(Dist N) const
    {
        return (RanIt(this->_current - N));
    }
    Rt operator[] (Dist N) const
    {
        return (*(*this + N));
    }
    bool operator<(const RanIt& Y) const
    {
        return (this->_current < Y._current);
    }
    bool operator>(const RanIt& Y) const
    {
        return (Y < *this);
    }
    bool operator<=(const RanIt& Y) const
    {
        return (!(Y < *this));
    }
    bool operator>=(const RanIt& Y) const
    {
        return (!(*this < Y));
    }
    Dist operator- (const RanIt& Y) const
    {
        return (this->_current - Y._current);
    }
protected:
    Pt _current;
};

template<class RanIt>
class reverse_iterator
    :public  iterator<typename iterator_traits<RanIt>::iterator_category,
                    typename iterator_traits<RanIt>::value_type, 
                    typename iterator_traits<RanIt>::difference_type,
                    typename iterator_traits<RanIt>::pointer,
                    typename iterator_traits<RanIt>::reference>
{
public:
    typedef reverse_iterator<RanIt> RevIt;
    typedef typename iterator_traits<RanIt>::difference_type Dist;
    typedef typename iterator_traits<RanIt>::pointer Pt;
    typedef typename iterator_traits<RanIt>::reference Rt; 
    typedef RanIt iterator_type;
    reverse_iterator() {}

    explicit reverse_iterator(RanIt X)
        : _current(X) {}

    template<class U>
    reverse_iterator (const reverse_iterator<U>& X)
        : _current (X.base()) {}

    RanIt base() const
    {
        return (this->_current); 
    }
    Rt operator*() const
    {
        RanIt Tmp = this->_current;
        return (*--Tmp);
    }
    Pt operator->() const
    {
        return (&**this);
    }
    RevIt& operator++()
    {
        --this->_current;
        return (*this);
    }
    RevIt operator++ (int)
    {
        RevIt Tmp = *this;
        --this->_current;
        return (Tmp);
    }
    RevIt& operator--()
    {
        ++this->_current;
        return (*this);
    }
    RevIt operator-- (int)
    {
        RevIt Tmp = *this;
        ++this->_current;
        return (Tmp);
    }
    ////
    RevIt& operator+=(Dist N)
    {
        this->_current += N;
        return (*this);
    }
    RevIt operator+(Dist N) const
    {
        return (RevIt(this->_current + N));
    }
    RevIt& operator-=(Dist N)
    {
        this->_current += N;
        return (*this); 
    }
    RevIt operator-(Dist N) const
    {
        return (RevIt(this->_current + N));
    }
    ////
    bool Eq(const RevIt& Y) const
    {
        return (this->_current == Y._current);
    }
    RevIt operator*(Dist N) const
    {
        return (RevIt(this->_current - N));
    }
    Rt operator [] (Dist N) const
    {
        return (*(*this + N));
    }
    /////
    bool operator==(int Y) const
    {
        return (this->_current == (Pt)Y); 
    }
    bool operator==(const RevIt& Y) const
    {
        return (this->_current == Y._current); 
    }

    bool operator!=(const RevIt& Y) const
    {
        return (!(*this == Y));
    }

    bool operator<(const RevIt& Y) const
    {
        return (this->_current > Y._current);
    }
    bool operator>(const RevIt& Y) const
    {
        return (Y > *this);
    }
    bool operator<=(const RevIt& Y) const
    {
        return (!(Y > *this));
    }
    bool operator>=(const RevIt& Y) const
    {
        return (!(*this > Y));
    }
    //////
    bool Lt (const RevIt& Y) const
    {
        return (Y._current < this->_current);
    }
    Dist Mi (const RevIt& Y) const
    {
        return (Y._current - this->_current);
    }
protected:
    RanIt _current;
};
}
