/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uercan <uercan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 12:28:12 by uercan            #+#    #+#             */
/*   Updated: 2023/05/24 13:00:49 by uercan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fixed.hpp"

Fixed::Fixed ( void )
{
	std::cout << "Default constructor called" << std::endl;
	this->_fixed_point = 0;
}

Fixed::~Fixed ( void )
{
	std::cout << "Destructor called" << std::endl;
}

Fixed::Fixed (const int nbr )
{
	std::cout << "Int constructor called" << std::endl;
	this->_fixed_point = nbr << this->_fract_bit;
}

Fixed::Fixed( const float nbr )
{
	std::cout << "Float constructor called" << std::endl;
	this->_fixed_point = std::roundf(nbr * ( 1 << this->_fract_bit));
}

Fixed::Fixed ( const Fixed &cpy )
{
	std::cout << "Copy constructor called" << std::endl;
	*this = cpy;
}

float	Fixed::toFloat( void ) const
{
	return (static_cast<float>(this->getRawBits()) / (1 << this->_fract_bit));
}

int	Fixed::toInt( void ) const
{
	return (this->getRawBits() >> this->_fract_bit);
}

int	Fixed::getRawBits( void ) const
{
	return (this->_fixed_point);
}

void	Fixed::setRawBits( int const raw )
{
	std::cout << "setRawBits member function called" << std::endl;
	this->_fixed_point = raw;
}

Fixed &Fixed::operator=( const Fixed &src )
{
	std::cout << "Copy assignment operator called" << std::endl;
	this->_fixed_point = src.getRawBits();
	return (*this);
}

std::ostream	&operator<<(std::ostream &a, Fixed const &b)
{
	a << b.toFloat();
	return (a);
}