/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uercan <uercan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 12:59:23 by uercan            #+#    #+#             */
/*   Updated: 2023/06/02 23:52:58 by uercan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Dog.hpp"

Dog::Dog ( void )
{
	this->brain = new Brain();
	std::cout << "Dog constructor called\n";
	this->_type = "Dog";
}

Dog::Dog ( const Dog &src )
{
	std::cout << "Dog copy constructor called\n";
	this->_type = src._type;
	this->brain = src.brain;
}

Dog::~Dog ( void )
{
	delete this->brain;
	std::cout << "Dog destructor called\n";
}

Dog &Dog::operator=( const Dog &src )
{
	std::cout << "Dog assigment operator called\n";
	this->_type = src._type;
	this->brain = new Brain;
	return (*this);
}

void Dog::makeSound ( void ) const
{
	std::cout << "Hawv" << std::endl;
}

Brain *Dog::getBrain( void ) const
{
	return ( this->brain );
}