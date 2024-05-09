#ifndef ARRAY_HPP
# define ARRAY_HPP

#include <iostream>


template <typename T>
class	Array
{
	private:
		T*				_array;
		unsigned int	size;
	public:
		Array ( void );
		Array ( unsigned int n );
		Array ( const Array &src );
		~Array ( void );

		Array &operator=( const Array &src );
		T &operator[] ( unsigned int i ) const;

		unsigned int	getSize ( void );

		class OutOfBoundsException : public std::exception
		{
			public:
				virtual const char *what() const throw();
		};
};

template <typename T>
std::ostream &operator<< ( std::ostream &os, Array<T> &src);

#include "Array.tpp"

#endif
