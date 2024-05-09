#ifndef WHATEVER_HPP
# define WHATEVER_HPP

#include <iostream>

template <typename T>
void	swap( T &a, T &b)
{
	T value = a;
	a = b;
	b = value;
}

template <typename T>
T	min ( T a, T b)
{
	if ( a < b)
		return (a);
	return (b);
}

template <typename T>
T	max ( T a, T b)
{
	if ( a > b)
		return (a);
	return (b);
}

#endif