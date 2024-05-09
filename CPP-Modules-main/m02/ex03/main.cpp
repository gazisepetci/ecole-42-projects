/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uercan <uercan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 14:40:38 by uercan            #+#    #+#             */
/*   Updated: 2023/05/24 13:08:02 by uercan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "point.hpp"

/*
area =	1/2 * |x1 (y2 - y3) + x2 (y3 - y1) + x3 (y1 - y2)|
m = (y1 - y2) / (x1 - x2)
https://www.omnicalculator.com/math/area-triangle-coordinates
https://embeddedartistry.com/blog/2018/07/12/simple-fixed-point-conversion-in-c/
*/

int	main()
{
	Point	a;
	Point	b(3.0, 0.0);
	Point	c(0.0, 3.0);
	Point	p(1, 1);

	if (bsp(a, b, c, p))
		std::cout << "True" << std::endl;
	else
		std::cout << "False" << std::endl;
	return (0);
}