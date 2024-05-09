/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uercan <uercan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 12:28:12 by uercan            #+#    #+#             */
/*   Updated: 2023/05/12 14:23:01 by uercan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fixed.hpp"

Fixed::Fixed ( void )
{
	this->_fixed_point = 0;
}

Fixed::~Fixed ( void )
{
}

Fixed::Fixed (const int nbr )
{
	this->_fixed_point = nbr << this->_fract_bit;
}

Fixed::Fixed( const float nbr )
{
	this->_fixed_point = std::roundf(nbr * ( 1 << this->_fract_bit));
}

Fixed::Fixed ( const Fixed &cpy )
{
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
//--------
int	Fixed::getRawBits( void ) const
{
	return (this->_fixed_point);
}

void	Fixed::setRawBits( int const raw )
{
	this->_fixed_point = raw;
}
//--------

Fixed &Fixed::operator=( const Fixed &src )
{ 
	this->_fixed_point = src.getRawBits();
	return (*this);
}

std::ostream	&operator<<(std::ostream &a, Fixed const &b)
{
	a << b.toFloat();
	return (a);
}

Fixed &Fixed::min( Fixed &a, Fixed &b)
{
	if (a.getRawBits() > b.getRawBits())
		return ( b );
	return ( a );
}

const Fixed &Fixed::min( const Fixed &a, const Fixed &b)
{
	if (a.getRawBits() > b.getRawBits())
		return ( b );
	return ( a );
}

Fixed &Fixed::max( Fixed &a, Fixed &b)
{
	if (a.getRawBits() < b.getRawBits())
		return ( b );
	return ( a );
}

const Fixed &Fixed::max( const Fixed &a, const Fixed &b)
{
	if (a.getRawBits() < b.getRawBits())
		return ( b );
	return ( a );
}

bool Fixed::operator>( const Fixed &src ) const
{
	if (this->getRawBits() > src.getRawBits())
		return (true);
	return (false);
}

bool Fixed::operator<( const Fixed &src ) const
{
	if (this->getRawBits() < src.getRawBits())
		return (true);
	return (false);
}

bool Fixed::operator>=( const Fixed &src ) const
{
	if (this->getRawBits() >= src.getRawBits())
		return (true);
	return (false);
}

bool Fixed::operator<=( const Fixed &src ) const
{
	if (this->getRawBits() <= src.getRawBits())
		return (true);
	return (false);
}

bool Fixed::operator==( const Fixed &src ) const
{
	if (this->getRawBits() == src.getRawBits())
		return (true);
	return (false);
}

bool Fixed::operator!=( const Fixed &src ) const
{
	if (this->getRawBits() != src.getRawBits())
		return (true);
	return (false);
}

Fixed	Fixed::operator+(const Fixed &src) const
{
	// this->toFloat() + rhs.toFloat();
	// return (*this);
	return (Fixed(this->toFloat() + src.toFloat()));
}

Fixed	Fixed::operator-(const Fixed &src) const
{
	return (Fixed(this->toFloat() - src.toFloat()));
}

Fixed	Fixed::operator*(const Fixed &src) const
{
	return (Fixed(this->toFloat() * src.toFloat()));
}
Fixed	Fixed::operator/(const Fixed &src) const
{
	return (Fixed(this->toFloat() / src.toFloat()));
}

Fixed	Fixed::operator++( void )
{
	this->_fixed_point++;
	return (*this);
}

Fixed	Fixed::operator++( int )
{
	Fixed val(*this);
	val._fixed_point = this->_fixed_point++;
	return (val);
}

Fixed	Fixed::operator--( void )
{
	this->_fixed_point--;
	return (*this);
}

Fixed	Fixed::operator--( int )
{
	Fixed val(*this);
	val._fixed_point = this->_fixed_point--;
	return (val);
}