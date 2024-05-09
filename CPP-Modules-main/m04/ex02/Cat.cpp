/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uercan <uercan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 13:08:18 by uercan            #+#    #+#             */
/*   Updated: 2023/06/03 03:40:28 by uercan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cat.hpp"

Cat::Cat ( void )
{
	brain = new Brain;
	std::cout << "Cat constructor called\n";
	this->_type = "Cat";
}

Cat::Cat ( const Cat &src )
{
	std::cout << "Cat copy constructor called\n";
	this->_type = src._type;
	this->brain = new Brain (*src.brain);
}

Cat::~Cat ( void )
{
	delete brain;
	std::cout << "Cat destructor called\n";
}

Cat	&Cat::operator=( const Cat &src )
{
	std::cout << "Cat assigment operator called\n";
	this->_type = src._type;
	this->brain = new Brain(*src.brain);
	return (*this);
}

void	Cat::makeSound ( void ) const
{
	std::cout << "Miyvwv" << std::endl;
}

Brain *Cat::getBrain( void ) const
{
	return ( this->brain );
}