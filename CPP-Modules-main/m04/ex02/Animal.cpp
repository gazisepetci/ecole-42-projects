/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uercan <uercan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 12:36:08 by uercan            #+#    #+#             */
/*   Updated: 2023/06/03 03:46:29 by uercan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Animal.hpp"

Animal::Animal ( void )
{
	std::cout << "Animal constructor called\n";
}

Animal::Animal ( const Animal &src )
{
	std::cout << "Animal copy constructor called\n";
	this->_type = src._type;
}

Animal::~Animal ( void )
{
	std::cout << "Animal destructor called\n";
}

Animal &Animal::operator=( const Animal &src )
{
	std::cout << "Animal assigment operator called\n";
	this->_type = src._type;
	return (*this);
}

std::string	Animal::getType ( void ) const
{
	return ( this->_type );
}
