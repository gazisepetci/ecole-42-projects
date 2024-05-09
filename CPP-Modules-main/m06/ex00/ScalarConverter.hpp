/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uercan <uercan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 17:55:10 by uercan            #+#    #+#             */
/*   Updated: 2023/06/11 17:22:29 by uercan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCALARCONVERTER_HPP
# define SCALARCONVERTER_HPP

#include <iostream>
#include <string>
#include <math.h>
#include <cctype>
#include <limits>

#define _NONE 0
#define _CHAR 1
#define _INT 2
#define _FLOAT 3
#define _DOUBLE 4
#define _LITERALS 5

class ScalarConverter{
	private:
		static std::string	_string;
		static int			_type;
		static bool			_isPossible;
		static int			_index;
		static int			_sign;
		static char			_char;
		static int			_int;
		static float		_float;
		static double		_double;

	public:
			static int	getInt( void );
			static int	getType( void );

			static bool	isChar();
			static bool	isInt();
			static bool	isFloat();
			static bool	isDouble();
			static bool	isLiterals();

			static void	findType( void );
			static void	printChar();
			static void	printInt();
			static void	printFloat();
			static void	printDouble();

			static char	getChar( void );
			static float	getFloat( void );
			static double	getDouble( void );
			static std::string	getValue ( int i );
			static std::string	getString( void );

			static void			ScalarConvertingString( std::string argv );

		class InvalidType : public std::exception{
			public:
				virtual const char *what(void) const throw(){
					return ( "Input is of invalid type!" );
				}
		};
};

#endif