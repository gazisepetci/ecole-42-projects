#ifndef ITER_HPP
 #define ITER_HPP

#include <iostream>

template <typename T>
void	print_temp ( T a)
{
	std::cout << a << std::endl;
}

template <typename T>
void	set_temp ( T &a)
{
	a = 42;
}

template < typename T>
void	iter ( T *arr, int len, void	(*func)(T const&))
{
	for (int i = 0; i < len; i++)
	{
		func(arr[i]);
	}
}


#endif
