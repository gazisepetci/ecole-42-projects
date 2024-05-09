#include "Array.hpp"

template< typename T >
Array<T>::Array( void )
{
	this->_array = NULL;
	this->size = 0;
}

template< typename T >
Array<T>::Array( unsigned int n )
{
	this->_array = new T[n];
	this->size = n;
}

template< typename T >
Array<T>::Array( const Array &src )
{
	this->_array = new T[src.size];
	this->size = src.size;
	for (unsigned int i = 0; i < this->size; i++)
	{
		this->_array[i] = src._array[i];
	}
}

template< typename T >
Array<T>::~Array(){}

template< typename T >
unsigned int	Array<T>::getSize ( void )
{
	retunr ( this->size );
}

template< typename T >
const char	*Array<T>::OutOfBoundsException::what() const throw()
{
	return ( "Out Of Bounds !" );
}

template< typename T >
T &Array<T>::operator[]( unsigned int i) const
{
	if (i >= this->size)
		throw ( OutOfBoundsException() );
	return ( this->_array[i] );
}

template< typename T >
std::ostream &operator<< ( std::ostream &os, Array<T> &src)
{
	os << "[ ";
	for (unsigned int i = 0; i < src.getSize(); i++)
	{
		os << src[i] << " ";
	}
	os << " ]\n";
	return (os);
}

template< typename T >
Array<T> &Array<T>::operator=( const Array &src )
{
	if ( this != src)
	{
		delete[] this->_array;
		this->_array = new T[src.size];
		this->size = src.size;
		for (unsigned int i = 0; i < this->size; i++)
			this->_array[i] = src._array[i];
	}
	return (*this);
}

