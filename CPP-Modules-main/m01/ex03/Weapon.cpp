/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Weapon.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uercan <uercan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 14:31:03 by uercan            #+#    #+#             */
/*   Updated: 2023/04/13 14:49:26 by uercan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Weapon.hpp"

Weapon::Weapon( std::string type)
{
	this->_type = type;
}

const std::string	&Weapon::getType( void )
{
	return (this->_type);
}

void	Weapon::setType( std::string type)
{
	this->_type = type;
}