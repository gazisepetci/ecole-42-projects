/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uercan <uercan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 12:59:23 by uercan            #+#    #+#             */
/*   Updated: 2023/05/30 17:02:54 by uercan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Dog.hpp"

Dog::Dog ( void )
{
	std::cout << "Dog constructor called\n";
	this->_type = "Dog";
}

Dog::Dog ( const Dog &src )
{
	std::cout << "Dog copy constructor called\n";
	this->_type = src._type;
}

Dog::~Dog ( void )
{
	std::cout << "Dog destructor called\n";
}

Dog &Dog::operator=( const Dog &src )
{
	std::cout << "Dog assigment operator called\n";
	this->_type = src._type;
	return (*this);
}

void Dog::makeSound ( void ) const
{
	std::cout << "Hawv" << std::endl;
}
