/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uercan <uercan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 12:25:55 by uercan            #+#    #+#             */
/*   Updated: 2023/05/18 16:26:02 by uercan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_HPP
# define FIXED_HPP

#include <iostream>
#include <cmath>

class Fixed
{
	private:
		int	_fixed_point;
		static const int _fract_bit = 8;
	public:
		Fixed ( void );
		Fixed ( const int fixed_point );
		Fixed ( const float nbr );
		Fixed ( const Fixed &cpy );
		~Fixed ( void );
		int		getRawBits( void ) const;
		void	setRawBits( int const raw );
		float	toFloat( void ) const;
		int		toInt( void ) const;
		Fixed &operator=( const Fixed &src );
};

std::ostream	&operator<<( std::ostream &a, Fixed const &b );

#endif