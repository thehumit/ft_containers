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
        : current(P) {}
    RandomAccessIterator (const RandomAccessIterator<T, Dist, Pt, Rt>& X)
        : current(X.base ()) {}
    Pt base() const
    {
        return (current);
    }
    Rt operator*() const
    {
        return (*current); 
    }
    Pt operator->() const
    {
        return (&**this);
    }
    RanIt& operator++()
    {
        ++current;
        return (*this); 
    }
    RanIt operator++ (int)
    {
        RanIt Tmp = *this;
        ++current;
        return (Tmp);
    }
    RanIt& operator--()
    {
        --current;
        return (*this);
    }
    RanIt operator-- (int)
    {
        RanIt Tmp = *this;
        --current;
        return (Tmp);
    }
    bool operator==(int Y) const
    {
        return (current == (Pt)Y); 
    }
    bool operator==(const RanIt& Y) const
    {
        return (current == Y.current); 
    }

    bool operator!=(const RanIt& Y) const
    {
        return (!(*this == Y));
    }
    RanIt& operatort+=(Dist N)
    {
        current += N;
        return (*this);
    }
    RanIt operator+(Dist N) const
    {
        return (RanIt(current + N));
    }
    RanIt& operator-=(Dist N)
    {
        current -= N;
        return (*this); 
    }
    RanIt operator-(Dist N) const
    {
        return (RanIt(current - N));
    }
    Rt operator[] (Dist N) const
    {
        return (*(*this + N));
    }
    bool operator<(const RanIt& Y) const
    {
        return (current < Y.current);
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
        return (current - Y.current);
    }
protected:
    Pt current;
};

template<class RanIt>
class reverse_iterator
    :public iterator<iterator_traits<RanIt>::iter_category,
                    iterator_traits<RanIt>::value_type, 
                    iterator_traits<RanIt>::difference_type,
                    iterator_traits<RanIt>::pointer,
                    iterator_traits<RanIt>::reference>
{
public:
    typedef reverse_iterator<RanIt> RevIt;
    typedef typename iterator_traits<RanIt>::difference_type Diff;
    typedef typename iterator_traits<RanIt>::pointer Pt;
    typedef typename iterator_traits<RanIt>::reference Rt; 
    typedef RanIt iterator_type;
    reverse_iterator() {}
    explicit reverse_iterator(RanIt X)
        :current(X) {}
    template<class U>
        reverse _iterator (const reverse_iterator<U>& X)
            : current (X.base()) {}
    RanIt base() const
    {
        return (current); 
    }
    Rt operator*() const
    {
        RanIt Tmp = current;
        return (*--Tmp);
    }
    Pt operator->() const
    {
        return (&**this);
    }
    RevIt& operator++()
    {
        --current;
        return (*this);
    }
    RevIt operator++ (int)
    {
        RevIt Tmp = *this;
        --current;
        return (Tmp);
    }
    RevIt& operator--()
    {
        ++current;
        return (*this);
    }
    RevIt operator-- (int)
    {
        RevIt Tmp = *this;
        ++current;
        return (Tmp);
    }
    bool Eq(const RevIt& Y) const
    {
        return (current == Y.current);
    }
    RevIt& operator+=(Diff N)
    {
        current -= N;
        return (*this);
    }
    RevIt operator*(Diff N) const
    {
        return (RevIt(current - N));
    }
    RevIt& operator-=(Diff N)
    {
        current += N;
        return (*this);
    }
    RevIt operator-(Diff N) const
    {
        return (RevIt(current + N));
    }
    Rt operator [] (DN) const
    {
        return (*(*this + N));
    }
    bool Lt (const RevIt& Y) const
    {
        return (Y. current < current);
    }
    Diff Mi (const RevIt& Y) const
    {
        return (Y. cur rent - current);
    }
protected:
    RanIt current;
};
}
