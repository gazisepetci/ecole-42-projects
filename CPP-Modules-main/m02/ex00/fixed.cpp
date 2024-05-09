/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uercan <uercan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 12:28:12 by uercan            #+#    #+#             */
/*   Updated: 2023/05/20 17:19:49 by uercan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fixed.hpp"

Fixed::Fixed ( void )
{
	std::cout << "Default constructor called" << std::endl;
	this->_fixed_point = 0;
}

Fixed::Fixed ( const Fixed &cpy )
{
	std::cout << "Copy constructor called" << std::endl;
	this->_fixed_point = cpy.getRawBits();
}

Fixed &Fixed::operator=( const Fixed &src )
{
	std::cout << "Copy assignment operator called" << std::endl;
	this->_fixed_point = src.getRawBits();
	return (*this);
}

Fixed::~Fixed ( void )
{
	std::cout << "Destructor called" << std::endl;
}

int	Fixed::getRawBits( void ) const
{
	std::cout << "getRawBits member function called" << std::endl;
	return (this->_fixed_point);
}

void	Fixed::setRawBits( int const raw )
{
	std::cout << "setRawBits member function called" << std::endl;
	this->_fixed_point = raw;
}