/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsp.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uercan <uercan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 12:43:07 by uercan            #+#    #+#             */
/*   Updated: 2023/05/13 15:08:53 by uercan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fixed.hpp"
#include "point.hpp"

static Fixed	abs(Fixed num)
{
	if (num < 0)
		return (num * -1);
	return (num);
}

Fixed	calculate_area(Point const a, Point const b, Point const c)
{
	Fixed	area;

	area = (abs((a.get_x() * (b.get_y() - c.get_y())
		+ (b.get_x() * (c.get_y() - a.get_y()))
		+ (c.get_x() * (a.get_y() - b.get_y()))) / 2));
	return (area);
}

Fixed	calculate_slope(Point const a, Point const b)
{
	Fixed	slope;

	if (a.get_x() - b.get_x() == 0)
		return(false);
	slope = (a.get_y() - b.get_y()) / (a.get_x() - b.get_x());
	return (slope);
}

bool	bsp (Point const a, Point const b, Point const c, Point const point)
{
	Fixed	area = calculate_area(a, b, c);

	std::cout << "A(" << a.get_x() << " , " << a.get_y() << ") ";
	std::cout << "B(" << b.get_x() << " , " << b.get_y() << ") ";
	std::cout << "C(" << c.get_x() << " , " << c.get_y() << ") ";
	std::cout << "P(" << point.get_x() << " , " << point.get_y() << ")" << std::endl;
	std::cout << "Main area: " << calculate_area(a, b, c) << std::endl;
	std::cout << "Point area: "<< (calculate_area(a, b, point) + calculate_area(a, point, c) + calculate_area(point, b, c)) << std::endl;
	std::cout << "a-b-p area: "<< calculate_area(a, b, point) << std::endl;
	std::cout << "a-p-c area: "<< calculate_area(a, point, c) << std::endl;
	std::cout << "p-b-c area: "<< calculate_area(point, b, c) << std::endl;
	std::cout << "m(b,p): "<< calculate_slope(b, point) << std::endl;
	std::cout << "m(a,p): "<< calculate_slope(a, point) << std::endl;
	std::cout << "m(c,p): "<< calculate_slope(c, point) << std::endl << std::endl;

	if (area == (calculate_area(a, b, point) 
		+ calculate_area(a, point, c) 
		+ calculate_area(point, b, c)))
	{
		if (calculate_slope(b, point) != calculate_slope(a, point) 
			&& calculate_slope(b, point) != calculate_slope(c, point)
			&& calculate_slope(a, point) != calculate_slope(c, point))
		{
			return (true);
		}
	}
	return (false);
}
