/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cure.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uercan <uercan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 08:19:27 by uercan            #+#    #+#             */
/*   Updated: 2023/06/03 08:21:00 by uercan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cure.hpp"

Cure::Cure( void ) : AMateria("cure")
{
}

Cure::Cure( Cure const &rhs ) : AMateria("cure")
{
	*this = rhs;
}

Cure::~Cure( void )
{
}

Cure	&Cure::operator=( Cure const &rhs )
{
	if (this != &rhs)
		this->type = rhs.getType();
	return (*this);
}

AMateria	*Cure::clone( void ) const
{
	return (new Cure(*this));
}

void	Cure::use( ICharacter &target )
{
	std::cout << "* heals " << target.getName() << "'s wounds *" << std::endl;
}