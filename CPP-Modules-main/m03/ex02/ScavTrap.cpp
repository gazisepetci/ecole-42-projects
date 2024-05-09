/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScavTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uercan <uercan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 19:15:10 by uercan            #+#    #+#             */
/*   Updated: 2023/05/25 14:36:26 by uercan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScavTrap.hpp"

ScavTrap &ScavTrap::operator=( const ScavTrap &src )
{
	this->set_name ( src.get_name());
	this->set_energy ( src.get_energy());
	this->set_health ( src.get_health());
	this->set_attack_damage ( src.get_attack_damage());
	return (*this);
}

ScavTrap::~ScavTrap()
{
	std::cout << "ScavTrap ended" << std::endl;
}

ScavTrap::ScavTrap()
{
	this->_gatekeeper_mode = false;
	this->set_health (100);
	this->set_attack_damage (20);
	this->set_energy (50);
	this->set_name ("Default ScavTrap");
	std::cout << "ScavTrap start" << std::endl;
}

ScavTrap::ScavTrap( std::string name )
{
	this->_gatekeeper_mode = false;
	this->set_health (100);
	this->set_attack_damage (20);
	this->set_energy (50);
	this->set_name (name);
	std::cout << "ScavTrap " << this->get_name() << " named " << std::endl;
}

ScavTrap::ScavTrap( const ScavTrap &src )
{
	this->_gatekeeper_mode = false;
	this->set_name ( src.get_name());
	this->set_energy ( src.get_energy());
	this->set_health ( src.get_health());
	this->set_attack_damage ( src.get_attack_damage());
	std::cout << "ScavTrap copy constructor called" << std::endl;
}

void	ScavTrap::attack(const std::string& target)
{
	if (this->get_health() > 0)
	{
		if (this->_gatekeeper_mode)
			std::cout << "ScavTrap " << this->get_name() << " in Gatekepeer Mode" << std::endl;
		else
		{
			std::cout << "ScavTrap " << this->get_name() << " attacks " << target << ", causing " << this->get_attack_damage() << " points of damage!" << std::endl;
			this->set_energy (get_energy() - 1);
		}
	}
	else if (this->get_energy() < 1)
		std::cout << this->get_name() << " has no energy!" << std::endl;
	else
		std::cout << "ScavTrap " << this->get_name() << " is Died!" << std::endl;
}

void ScavTrap::gatekeeper ( void )
{
	this->_gatekeeper_mode = !this->_gatekeeper_mode;
	std::cout << "Gate Keeper moded" << std::endl;
}