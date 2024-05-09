/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AMateria.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uercan <uercan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 08:12:32 by uercan            #+#    #+#             */
/*   Updated: 2023/06/03 08:25:36 by uercan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AMateria.hpp"

AMateria::AMateria( void ) : type("Default")
{
}

AMateria::AMateria( std::string const &type ) : type(type)
{
}

AMateria::AMateria( AMateria const &rhs ) : type(rhs.type)
{
}

AMateria::~AMateria( void )
{
}

std::string const	&AMateria::getType( void ) const
{
	return (this->type);
}

AMateria	*AMateria::clone( void ) const
{
	return ((AMateria*)this);
}

void	AMateria::use( ICharacter &target )
{
	std::cout << "AMateria " << this->type << " used on " << target.getName() << std::endl;
}