/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ice.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uercan <uercan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 08:21:54 by uercan            #+#    #+#             */
/*   Updated: 2023/06/03 08:23:07 by uercan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Ice.hpp"

Ice::Ice( void ) : AMateria("ice")
{
}

Ice::Ice( Ice const &rhs ) : AMateria("ice")
{
	*this = rhs;
}

Ice::~Ice( void )
{
}

Ice	&Ice::operator=( Ice const &rhs )
{
	if (this != &rhs)
		this->type = rhs.getType();
	return (*this);
}

AMateria	*Ice::clone( void ) const
{
	return (new Ice(*this));
}

void	Ice::use( ICharacter &target )
{
	std::cout << "* shoots an ice bolt at " << target.getName() << " *" << std::endl;
}