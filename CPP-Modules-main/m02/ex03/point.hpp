/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uercan <uercan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 12:29:32 by uercan            #+#    #+#             */
/*   Updated: 2023/05/12 14:53:32 by uercan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef POINT_HPP
# define POINT_HPP

#include <iostream>
#include "fixed.hpp"

class Point
{
	private:
		const Fixed _x;
		const Fixed _y;
	public:
		Point( void );
		Point( const Point &cpy );
		Point ( const float x, const float y );
		~Point ( void );

		Fixed get_x( void ) const;
		Fixed get_y( void ) const;

		Point &operator=( const Point &src );
};

Fixed	calculate_area(Point const a, Point const b, Point const c);
bool	bsp (Point const a, Point const b, Point const c, Point const point);

#endif