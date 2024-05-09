/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uercan <uercan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 12:40:33 by uercan            #+#    #+#             */
/*   Updated: 2023/05/12 14:30:16 by uercan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "point.hpp"

Point::Point ( void ) : _x(0), _y(0)
{
}

Point::Point (const float x, const float y) : _x(x), _y(y)
{
}

Point::Point( const Point &cpy ) : _x(cpy._x), _y(cpy._y)
{
}

Point::~Point ( void )
{
}

Point	&Point::operator=( const Point &src )
{
	if (this != &src)
	{
		(Fixed)this->_x = src.get_x();
		(Fixed)this->_y = src.get_y();
	}
	return (*this);
}

Fixed Point::get_x( void ) const
{
	return (this->_x);
}

Fixed Point::get_y( void ) const
{
	return (this->_y);
}