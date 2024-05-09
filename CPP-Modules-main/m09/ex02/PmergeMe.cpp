#include "PmergeMe.hpp"

bool	PmergeMe::checkArg( int argc, char **argv )
{
	if (argc < 1)
		return (false);
	for (int i = 1; argv[i]; i++)
	{
		if(!is_digits(argv[i]) || atoi(argv[i]) < 0)
			return (false);
	}
	return (true);
}

double	PmergeMe::elapsedTime(clock_t start, clock_t end)
{
	double duration = static_cast<double>(end - start) / CLOCKS_PER_SEC;
	double microseconds = duration * 1000000;
	return microseconds;
}

void	PmergeMe::insertSorting_vector( std::vector<int>& vector, int left, int right )
{
	for (int i = left + 1; i <= right; i++)
	{
		int key = vector[i];
		int j = i - 1;

		while (j >= left && vector[j] > key)
		{
			vector[j + 1] = vector[j];
			j--;
		}
		vector[j + 1] = key;
	}
}

void	PmergeMe::mergeSorting_vector( std::vector<int>& vector, int left, int middle, int right )
{
	int n1 = middle - left + 1;
	int n2 = right - middle;

	std::vector<int> L(n1);
	std::vector<int> R(n2);

	for (int i = 0; i < n1; i++)
		L[i] = vector[left + i];
	for (int j = 0; j < n2; j++)
		R[j] = vector[middle + 1 + j];

	int i = 0;
	int j = 0;
	int k = left;

	while (i < n1 && j < n2) {
		if (L[i] <= R[j]) {
			vector[k] = L[i];
			i++;
		} else {
			vector[k] = R[j];
			j++;
		}
		k++;
	}

	while (i < n1) {
		vector[k] = L[i];
		i++;
		k++;
	}

	while (j < n2) {
		vector[k] = R[j];
		j++;
		k++;
	}
}

void	PmergeMe::mergeSorting_list(std::list<int>& list, std::list<int>& left, std::list<int>& right )
{
	std::list<int>::iterator leftIt = left.begin();
	std::list<int>::iterator rightIt = right.begin();

	while (leftIt != left.end() && rightIt != right.end()) {
		if (*leftIt <= *rightIt) {
			list.push_back(*leftIt);
			++leftIt;
		} else {
			list.push_back(*rightIt);
			++rightIt;
		}
	}

	while (leftIt != left.end()) {
		list.push_back(*leftIt);
		++leftIt;
	}

	while (rightIt != right.end()) {
		list.push_back(*rightIt);
		++rightIt;
	}
}

void	PmergeMe::insertSorting_list( std::list<int>::iterator begin, std::list<int>::iterator end )
{
	std::list<int>::value_type temp;
	std::list<int>::iterator it2;

	for (std::list<int>::iterator it1 = begin; it1 != end; ++it1)
	{	
		temp = *it1;
		it2 = it1;
		while (it2 != begin && *std::prev(it2)  > temp)
		{
			*it2 = *std::prev(it2);
			--it2;
		}
		*it2 = temp;
	}
}

void	PmergeMe::MergeInsertionSort_list( std::list<int>& list )
{
	if ((int)list.size() <= 100)
		insertSorting_list(list.begin(), list.end());
	else
	{
		std::list<int> left, right;
		int mid = list.size() / 2;
		std::list<int>::iterator it = list.begin();
		for (int i = 0; i < mid; i++)
		{
			left.push_back(*it);
			++it;
		}
		while (it != list.end())
		{
			right.push_back(*it);
			++it;
		}

		MergeInsertionSort_list(left);
		MergeInsertionSort_list(right);

		list.clear();
		mergeSorting_list(list, left, right);
	}
}

void	PmergeMe::MergeInsertionSort_vector( std::vector<int>& vector, int left, int right )
{
	if (right - left <= 100)
		insertSorting_vector(vector, left, right);
	else
	{
		int middle = left + (right - left) / 2;

		MergeInsertionSort_vector(vector, left, middle);
		MergeInsertionSort_vector(vector, middle + 1, right);

		mergeSorting_vector(vector, left, middle, right);
	}
}

void	PmergeMe::sortList( void )
{
	std::cout << "Before: ";
	std::list<int>::iterator il = _list.begin();
	for (int i = 0; i < 4; i++)
	{
		std::cout << " " << *il;
		il++;
	}
	if (_list.size() > 4)
		std::cout << " [...]";
	clock_t start = clock();
	MergeInsertionSort_list(_list);
	clock_t end = clock();
	il = _list.begin();
	std::cout << "\nAfter: ";
	for (int i = 0; i < 4; i++)
	{
		std::cout << " " << *il;
		il++;
	}
	if (_list.size() > 4)
		std::cout << " [...]\n";
	
	std::cout << "\nTime to process a range of " << _vector.size()
	<< " elements with std::list : " << elapsedTime(start, end) << " us\n";
}

void	PmergeMe::sortVector( void )
{
	std::cout << "Before: ";
	std::vector<int>::iterator il = _vector.begin();
	for (int i = 0; i < 4; i++)
	{
		std::cout << " " << *il;
		il++;
	}
	if (_vector.size() > 4)
		std::cout << " [...]";
	clock_t start = clock();
	MergeInsertionSort_vector(_vector, 0, _vector.size() - 1);
	clock_t end = clock();
	il = _vector.begin();
	std::cout << "\nAfter: ";
	for (int i = 0; i < 4; i++)
	{
		std::cout << " " << *il;
		il++;
	}
	if (_vector.size() > 4)
		std::cout << " [...]\n";
	
	std::cout << "\nTime to process a range of " << _vector.size()
	<< " elements with std::vector : " << elapsedTime(start, end) << " us\n";
}

void	PmergeMe::setInputs(int argc, char **inp)
{
	if (!checkArg(argc, inp))
	{
		std::cerr << "Error!\n";
		return;
	}
	for (int i = 1; inp[i]; i++)
	{
		_list.push_back(atoi(inp[i]));
		_vector.push_back(atoi(inp[i]));
	}
	sortList();
	sortVector();
	std::cout << "\nList -->> " << std::is_sorted(_list.begin(), _list.end()) << std::endl;
	std::cout << "\nVector -->> " << std::is_sorted(_vector.begin(), _vector.end()) << std::endl;
}
