/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MateriaSource.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uercan <uercan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 08:31:09 by uercan            #+#    #+#             */
/*   Updated: 2023/06/03 08:31:48 by uercan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MateriaSource.hpp"

MateriaSource::MateriaSource( void )
{
	for (int i = 0; i < 4; i++)
		this->_materias[i] = NULL;
}

MateriaSource::MateriaSource( MateriaSource const &rhs )
{
	*this = rhs;
}

MateriaSource::~MateriaSource( void )
{
}

MateriaSource	&MateriaSource::operator=( MateriaSource const &rhs )
{
	if (this != &rhs)
		for (int i = 0; i < 4; i++)
			this->_materias[i] = rhs._materias[i];
	return (*this);
}

void	MateriaSource::learnMateria( AMateria* materia)
{
	for (int i = 0; i < 4; i++)
	{
		if (this->_materias[i] == NULL)
		{
			this->_materias[i] = materia;
			return ;
		}
	}
}

AMateria	*MateriaSource::createMateria( std::string const &type )
{
	for (int i = 0; i < 4; i++)
		if (this->_materias[i] && this->_materias[i]->getType() == type)
			return (this->_materias[i]->clone());
	return (NULL);
}

AMateria	*MateriaSource::getMateria( std::string const &type )
{
	for (int i = 0; i < 4; i++)
		if (this->_materias[i] && this->_materias[i]->getType() == type)
			return (this->_materias[i]);
	return (NULL);
}
