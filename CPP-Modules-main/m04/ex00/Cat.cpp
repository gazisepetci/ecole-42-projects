/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cat.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uercan <uercan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 13:08:18 by uercan            #+#    #+#             */
/*   Updated: 2023/05/30 17:02:51 by uercan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cat.hpp"

Cat::Cat ( void )
{
	std::cout << "Cat constructor called\n";
	this->_type = "Cat";
}

Cat::Cat ( const Cat &src )
{
	std::cout << "Cat copy constructor called\n";
	this->_type = src._type;
}

Cat::~Cat ( void )
{
	std::cout << "Cat destructor called\n";
}

Cat	&Cat::operator=( const Cat &src )
{
	std::cout << "Cat assigment operator called\n";
	this->_type = src._type;
	return (*this);
}

void	Cat::makeSound ( void ) const
{
	std::cout << "Miyvwv" << std::endl;
}
