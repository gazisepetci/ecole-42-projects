#ifndef EASYFIND_HPP
#define EASYFIND_HPP

# include <iostream>
# include <algorithm>
# include <vector>
# include <list>

// template <typename T>
// void	easyfind( T &vec, int i)
// {
// 	for (int j = 0; j < (int)vec.size(); j++)
// 	{
// 		if (vec.operator[](j) == i)
// 		{
// 			std::cout << i << " is found!\n";
// 			return ;
// 		}
// 	}
// 	std::cout << i << " is not found!\n";
// }

template <typename T>
void	easyfind( T &vec, int i)
{
	if (std::find(vec.begin(), vec.end(), i) != vec.end())
		std::cout << i << " is found!\n";
	else
		std::cerr << i << " is not found!\n";
}

#endif
