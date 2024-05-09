/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uercan <uercan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 18:09:11 by uercan            #+#    #+#             */
/*   Updated: 2023/07/04 14:33:27 by uercan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"

std::string	ScalarConverter::_string = "";
int		ScalarConverter::_type = 0;
bool		ScalarConverter::_isPossible = true;
int			ScalarConverter::_index = 0;
int			ScalarConverter::_sign = 1;
char		ScalarConverter::_char = '\0';
int			ScalarConverter::_int = 0;
float		ScalarConverter::_float = 0.0f;
double		ScalarConverter::_double = 0.0;

std::string	ScalarConverter::getString( void ) { return (_string); }
char		ScalarConverter::getChar( void ) { return (_char); }
int			ScalarConverter::getInt( void ) { return (_int); }
float		ScalarConverter::getFloat( void ) { return (_float); }
double		ScalarConverter::getDouble( void ) { return (_double); }
int			ScalarConverter::getType( void ) { return (_type); }

std::string	ScalarConverter::getValue( int i )
{
	std::string ret = "LITERALS";
	switch ( i )
	{
		case _CHAR:
			ret = "CHAR";
			break;
		
		case _NONE:
			ret = "NONE";
			break;
		
		case _INT:
			ret = "INT";
			break;

		case _FLOAT:
			ret = "FLOAT";
			break;

		case _DOUBLE:
			ret = "DOUBLE";
			break;

		default:
			break;
	}
	return ( ret );
}

void		ScalarConverter::findType( void ){
	if (isChar())
		_type = _CHAR;
	else if (isInt())
		_type = _INT;
	else if (isFloat())
		_type = _FLOAT;
	else if (isDouble())
		_type = _DOUBLE;
	else if (isLiterals())
		_type = _LITERALS;
	std::cout << "Type is: " << getValue ( _type ) << std::endl;
}

void		ScalarConverter::ScalarConvertingString( std::string argv ){
	_string = argv;
	findType();
	if (getType() == _NONE)
		throw ( ScalarConverter::InvalidType() );
	switch (getType())
	{
		case _CHAR:
			_char	= _string[0];
			_int	= static_cast<int>(_char);
			_float	= static_cast<float>(_char);
			_double	= static_cast<double>(_char);
			break;
		
		case _INT:
			_int	= atoi(&_string.c_str()[_index]);
			_int	= _int * _sign;
			_char	= static_cast<char>(_int);
			_float	= static_cast<float>(_int);
			_double	= static_cast<double>(_int);
			break;

		case _FLOAT:
			_float	= atof(&_string.c_str()[_index]);
			_float	= _float * _sign;
			_char	= static_cast<char>(_float);
			_int	= static_cast<int>(_float);
			_double	= static_cast<double>(_float);
			break;

		case _DOUBLE:
			_double = atof(&_string.c_str()[_index]);
			_double	= _double * _sign;
			_char	= static_cast<char>(_double);
			_int	= static_cast<int>(_double);
			_float	= static_cast<float>(_double);
			break;
		default:
			break;
	}
	std::cout << "char: "; ScalarConverter::printChar();
	std::cout << "int: "; ScalarConverter::printInt();
	std::cout << "float: "; ScalarConverter::printFloat();
	std::cout << "double: "; ScalarConverter::printDouble();
}

bool	ScalarConverter::isChar( void )
{
	if (_string.length() == 1 && std::isprint(_string[0]))
		return (true);
	return (false);
}

bool		ScalarConverter::isInt( void )
{
	int	i;
	_sign = 1;

	i = 0;
	while (_string[i] == '-' || _string[i] == '+')
	{
		if (_string[i] == '-')
			_sign *= -1;
		i++;
	}
	_index = i;
	while (i < (int)_string.length())
	{
		if (!std::isdigit(_string[i]))
			return (false);
		i++;
	}
	return (true);
}

bool	ScalarConverter::isFloat( void )
{
	int countF = 0;
	int	countDot = 0;
	std::string tmp;
	_sign = 1;

	for (int i = 0; _string[i] != '\0'; i++)
	{
		if (_string[i] == 'f')
			countF++;
		if (_string[i] == '.')
			countDot++;
		if (_string[i] != 'f' && _string[i] != '.' && _string[i] != '-' && _string[i] != '+' && !(_string[i] >= 48 && _string[i] <= 57))
			return (false);
	}
	if (countF != 1 || countDot != 1 || _string.length() < 3 || (_string[_string.length() - 1] != 'f' && countF == 1))
		return (false);
	for (int i = 0; _string[i] == '-' || _string[i] == '+'; i++)
	{
		if (_string[i] == '-')
			_sign *= -1;
		if (_string[i + 1] != '\0' && (_string[i + 1] != '-' || _string[i + 1] != '+'))
		{
			tmp = &_string[i + 1];
			_index = i + 1;
			if ((int)tmp.find('-') != -1 || (int)tmp.find('+') != -1 || tmp.length() < 3)
				return (false);
		}
	}
	return (true);
}

bool	ScalarConverter::isDouble( void )
{
	int countDot = 0;
	std::string tmp;
	_sign = 1;

	for (int i = 0; _string[i] != '\0'; i++)
	{
		if (_string[i] == '.')
			countDot++;
		if (_string[i] != '.' && _string[i] != '-' && _string[i] != '+' && !(_string[i] >= 48 && _string[i] <= 57))
			return (false);
	}
	if (countDot != 1)
		return (false);
	for (int i = 0; _string[i] == '-' || _string[i] == '+'; i++)
	{
		if (_string[i] == '-')
			_sign *= -1;
		if (!_string[i + 1] && (_string[i + 1] != '-' || _string[i + 1] != '+'))
		{
			tmp = &_string[i + 1];
			_index = i + 1;
			if ((int)tmp.find('-') != -1 || (int)tmp.find('+') != -1)
				return (false);
		}
	}
	return (true);
}

bool	ScalarConverter::isLiterals( void )
{
	if (!_isPossible
		|| (_string.compare("nan") == 0)
		|| (_string.compare("nanf") == 0)
		|| (_string.compare("+inff") == 0) // Float
		|| (_string.compare("inff") == 0) // Float
		|| (_string.compare("-inff") == 0) // Float
		|| (_string.compare("+inf") == 0) // Double
		|| (_string.compare("inf") == 0) // Double
		|| (_string.compare("-inf") == 0)) // Double
		return (true);
	return (false);
}

void	ScalarConverter::printChar( void )
{
	if (isLiterals() || !(_int >= 0 && _int < 127))
		std::cout << "impossible" << std::endl;
	else if (!std::isprint(_int))
		std::cout << "Non displayable" << std::endl;
	else
		std::cout << "'" << getChar() << "'" << std::endl;
}

void		ScalarConverter::printInt( void )
{
	if (isLiterals())
		std::cout << "impossible" << std::endl;
	else
		std::cout << getInt() << std::endl;
}

void		ScalarConverter::printFloat( void )
{
	if (_string.compare("nan") == 0 || _string.compare("nanf") == 0)
		std::cout << "nanf" << std::endl;
	else if (_string.compare("+inf") == 0 || _string.compare("+inff") == 0)
		std::cout << "+inff" << std::endl;
	else if (_string.compare("-inf") == 0 || _string.compare("-inff") == 0)
		std::cout << "-inff" << std::endl;
	else
	{
		if (_float - static_cast<int>(_float) == 0)
			std::cout << _float << ".0f" << std::endl;
		else
			std::cout << getFloat() << "f" << std::endl;
	}
}

void		ScalarConverter::printDouble( void )
{
	if (_string.compare("nan") == 0 || _string.compare("nanf") == 0)
		std::cout << "nan" << std::endl;
	else if (_string.compare("+inf") == 0 || _string.compare("+inff") == 0)
		std::cout << "+inf" << std::endl;
	else if (_string.compare("-inf") == 0 || _string.compare("-inff") == 0)
		std::cout << "-inf" << std::endl;
	else
	{
		if (_double - static_cast<int>(_double) == 0)
			std::cout << _double << ".0" << std::endl;
		else
			std::cout << getDouble() << std::endl;
	}
}
