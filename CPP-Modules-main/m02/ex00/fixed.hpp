/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uercan <uercan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 12:25:55 by uercan            #+#    #+#             */
/*   Updated: 2023/05/18 16:19:40 by uercan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_HPP
# define FIXED_HPP

#include <iostream>

class Fixed
{
	private:
		int	_fixed_point;
		static const int _fract_bit = 8;
	public:
		Fixed ( void );
		Fixed ( const Fixed &cpy );
		~Fixed ();
		Fixed &operator=( const Fixed &src );
		int		getRawBits( void ) const;
		void	setRawBits( int const raw );
};

#endif
