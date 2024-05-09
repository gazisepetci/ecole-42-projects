/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uercan <uercan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 12:25:55 by uercan            #+#    #+#             */
/*   Updated: 2023/05/08 17:59:49 by uercan           ###   ########.fr       */
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

		static Fixed		&min( Fixed &a, Fixed &b );
		static const Fixed	&min( const Fixed &a, const Fixed &b);
		static Fixed		&max( Fixed &a, Fixed &b );
		static const Fixed	&max( const Fixed &a, const Fixed &b);

		float	toFloat( void ) const;
		int	toInt( void ) const;
		
		Fixed &operator=( const Fixed &src );

		bool operator>( const Fixed &src ) const;
		bool operator<( const Fixed &src ) const;
		bool operator>=( const Fixed &src ) const;
		bool operator<=( const Fixed &src ) const;
		bool operator==( const Fixed &src ) const;
		bool operator!=( const Fixed &src ) const;

		Fixed operator+( const Fixed &src ) const;
		Fixed operator-( const Fixed &src ) const;
		Fixed operator*( const Fixed &src ) const;
		Fixed operator/( const Fixed &src ) const;

		Fixed	operator++( void );
		Fixed	operator++( int );
		Fixed	operator--( void );
		Fixed	operator--( int );
};
//	>	<	>=	<=	==	!=
//	+	-	*	/

std::ostream	&operator<<( std::ostream &a, Fixed const &b );

#endif