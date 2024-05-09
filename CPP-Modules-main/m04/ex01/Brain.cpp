/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Brain.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uercan <uercan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 22:11:06 by uercan            #+#    #+#             */
/*   Updated: 2023/06/02 22:56:59 by uercan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Brain.hpp"

Brain::Brain ( void )
{
	std::cout << "Brain constructor called\n";
}

Brain::Brain ( const Brain &src )
{
	std::cout << "Brain copy constructor called\n";
	for (int i = 0; i < 100; i++)
		this->_ideas[i] = src._ideas[i];
}

Brain::~Brain ( void )
{
	std::cout << "Brain destructor called\n";
}

void	Brain::setBrain( int index, std::string idea)
{
	this->_ideas[index] = idea;
}

std::string	Brain::getBrain( int index )
{
	return ( this->_ideas[index] );
}

Brain &Brain::operator=( const Brain &src )
{
	std::cout << "Brain assigment operator called\n";
	for (int i = 0; i < 100; i++)
		this->_ideas[i] = src._ideas[i];
	return (*this);
}
