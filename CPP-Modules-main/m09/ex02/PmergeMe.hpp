#ifndef PMERGEME_HPP
# define PMERGEME_HPP

#include <iostream>
#include <list>
#include <vector>
#include <algorithm>

class PmergeMe
{
	private:
		std::vector<int> _vector;
		std::list<int> _list;
	public:
		void	setInputs (int argc, char **inp);
		double	elapsedTime(clock_t start, clock_t end);
		bool	checkArg( int argc, char **argv );
		void	sortList( void );
		void	sortVector( void );

		void	MergeInsertionSort_list( std::list<int>& list );
		void	MergeInsertionSort_vector( std::vector<int>& vector, int left, int right );

		void	mergeSorting_list(std::list<int>& list, std::list<int>& left, std::list<int>& right );
		void	mergeSorting_vector( std::vector<int>& vector, int left, int middle, int right );

		void	insertSorting_vector( std::vector<int>& vector, int left, int right );
		void	insertSorting_list( std::list<int>::iterator begin, std::list<int>::iterator end );
		bool	is_digits(const std::string &str){return str.find_first_not_of("0123456789") == std::string::npos;}
};

#endif
