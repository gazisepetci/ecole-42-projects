/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DiamondTrap.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uercan <uercan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 14:46:29 by uercan            #+#    #+#             */
/*   Updated: 2023/05/27 16:57:41 by uercan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DiamondTrap.hpp"

DiamondTrap::~DiamondTrap( void )
{
	std::cout << "DiamondTrap ended" << std::endl;
}

DiamondTrap::DiamondTrap( void ) : ClapTrap(), FragTrap(), ScavTrap()
{
	this->_name = ClapTrap::_name;
	ClapTrap::_name += "_clap_name";
	this->_health = FragTrap::_health;
	this->_energy = ScavTrap::_energy;
	this->_attack_damage = FragTrap::_attack_damage;
	std::cout << "DiamondTrap " << this->_name << " named " << std::endl;
}

DiamondTrap::DiamondTrap( std::string name ) : ClapTrap(name), FragTrap(name), ScavTrap(name), _name(name)
{
	ClapTrap::_name += "_clap_name";
	this->_health = FragTrap::_health;
	this->_energy = ScavTrap::_energy;
	this->_attack_damage = FragTrap::_attack_damage;
	std::cout << "DiamondTrap " << this->_name << " named " << std::endl;
}

DiamondTrap::DiamondTrap( const DiamondTrap &src ) : ClapTrap(src), FragTrap(src), ScavTrap(src), _name(src._name)
{
	std::cout << "DiamondTrap Copy Constructor called: " << this->_name << std::endl;
}

void	DiamondTrap::attack(const std::string& target)
{
	ScavTrap::attack(target);
}

void DiamondTrap::whoAmI ( void )
{
	std::cout << "DiamondTrap name: " << this->_name << std::endl;
	std::cout << "ClapTrap name: " << ClapTrap::_name << std::endl;
}

DiamondTrap &DiamondTrap::operator=( const DiamondTrap &src)
{
	ClapTrap::operator=(src);
	return (*this);
}
