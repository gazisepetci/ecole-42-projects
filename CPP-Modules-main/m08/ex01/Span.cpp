/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uercan <uercan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 14:34:18 by uercan            #+#    #+#             */
/*   Updated: 2023/07/20 13:03:48 by uercan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Span.hpp"

Span::Span( void ): _numberCount(0)
{}
Span::~Span( void )
{}

Span::Span( unsigned int i )
{
	this->_numberCount = i;
}

Span::Span(const Span &src)
{
	*this = src;
}

void	Span::addNumber( int i)
{
	try
	{
		if ((unsigned int)this->_num.size() < this->_numberCount)
			this->_num.push_back(i);
		else
			throw (Span::AlreadyNElementsStored());
	}catch ( std::exception &e){
		std::cerr << e.what() << std::endl;
	}
}


int	Span::shortestSpan( void )
{
	int	min = longestSpan();
	try
	{
		if (this->_num.size() < 2)
			throw (Span::ThereIsOnlyOneElement());
		else
		{
			std::list<int>::iterator it1 = this->_num.begin();
			std::list<int>::iterator it2 = this->_num.end();
			while (it1 != this->_num.end())
			{
				it2 = this->_num.begin();
				while (it2 != this->_num.end())
				{
					if (it1 != it2)
					{
						if (std::abs(*it1 - *it2) < min)
						{
							min = std::abs(*it1 - *it2);
						}
					}
					it2++;
				}
				it1++;
			}
		}
	}catch ( std::exception &e){
	std::cerr << e.what() << std::endl;
	}
	return (min);
}
int	Span::longestSpan( void )
{
	int	max = 0;
	try
	{
		if (this->_num.size() < 2)
			throw (Span::ThereIsOnlyOneElement());
		else
		{
			std::list<int>::iterator it1 = this->_num.begin();
			std::list<int>::iterator it2 = this->_num.end();
			while (it1 != this->_num.end())
			{
				it2 = this->_num.begin();
				while (it2 != this->_num.end())
				{
					if (it1 != it2)
					{
						if (std::abs(*it1 - *it2) > max)
						{
							max = std::abs(*it1 - *it2);
						}
					}
					it2++;
				}
				it1++;
			}
		}
	}catch ( std::exception &e){
	std::cerr << e.what() << std::endl;
	}
	return (max);
}

std::list<int>	Span::getNumber ( void ) const
{
	return (this->_num);
}
unsigned int	Span::getNumberMax ( void ) const
{
	return (this->_numberCount);
}

Span &Span::operator=( const Span &src)
{
	this->_num.clear();
	this->_num = src.getNumber();
	this->_numberCount = src.getNumberMax();
	return (*this);
}

const char	*Span::AlreadyNElementsStored::what() const throw()
{
	return ("Already N elements stored!");
}

const char	*Span::ThereIsOnlyOneElement::what() const throw()
{
	return ("There is only one elements!");
}
