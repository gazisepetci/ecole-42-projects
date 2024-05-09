/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uercan <uercan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 19:15:10 by uercan            #+#    #+#             */
/*   Updated: 2023/05/25 12:37:31 by uercan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"

ClapTrap::~ClapTrap()
{
	std::cout << "ClapTrap ended" << std::endl;
}

ClapTrap::ClapTrap()
{
	this->_health = 10;
	this->_energy = 10;
	this->_attack_damage = 0;
	this->_name = "Default";
	std::cout << "ClapTrap start" << std::endl;
}

ClapTrap::ClapTrap(std::string name)
{
	this->_name = name;
	this->_health = 10;
	this->_energy = 10;
	this->_attack_damage = 0;
	std::cout << "ClapTrap " << this->_name << " named " << std::endl;
}

ClapTrap::ClapTrap( const ClapTrap &src )
{
	this->_health = src._health;
	this->_energy = src._energy;
	this->_attack_damage = src._attack_damage;
	this->_name = src._name;
	std::cout << "Copy constructor called" << std::endl;
}

void	ClapTrap::hit_point(int hp)
{
	if (this->_health > 0 || this->_energy > 0)
		{
			this->_health = hp;
			this->_energy--;
		}
	else
	{
		if (this->_health < 1)
			std::cout << "ClapTrap " << this->_name << " is DIED !" << std::endl;
		else if (this->_energy < 1)
			std::cout << "ClapTrap " << this->_name << " has no energy !" << std::endl;
		else
			std::cout << "ClapTrap " << this->_name << " is can't do that !" << std::endl;
	}
}

void	ClapTrap::attack(const std::string &target)//ClapTrap <name> attacks <target>, causing <damage> points of damage!
{
	if (this->_energy > 0 && this->_health > 0)
	{
		std::cout << "ClapTrap " << this->_name << " attacks " << target << ", causing " << this->_attack_damage << " points of damage!" << std::endl;
		this->_energy--;
	}
	else
	{
		std::cout << "ClapTrap " << this->_name;
		if (this->_health < 1)
			std::cout << " is DIED !" << std::endl;
		else if (this->_energy < 1)
			std::cout << " has no ENERGY !" << std::endl;
		else
			std::cout << "ClapTrap " << this->_name << " is can't do that !" << std::endl;
	}
}

void	ClapTrap::takeDamage(unsigned int amount)
{
	if (this->_health <= 0)
		std::cout << "ClapTrap " << this->_name << " is DIED !";
	else
	{
		this->_health -= amount;
		std::cout << "ClapTrap " << this->_name << " takeDamage " << amount;
		if (this->_health <= 0)
		{
			std::cout << " and DIED";
			this->_health = 0;
		}
	}
	std::cout << std::endl;
}
void	ClapTrap::energy_points(unsigned int amount)
{
	this->_energy += amount;
	std::cout << "ClapTrap " << this->_name << " added energy points " << amount << std::endl;
}

void	ClapTrap::beRepaired(unsigned int amount)
{
	if (this->_energy > 0 && this->_health > 0)
	{
		this->_health += amount;
		std::cout << "ClapTrap " << this->_name << " beRepaired " << amount << std::endl;
		this->_energy--;
	}
	else
	{
		std::cout << "ClapTrap " << this->_name;
		if (this->_health < 1)
			std::cout << " is DIED !" << std::endl;
		else if (this->_energy < 1)
			std::cout << " has no ENERGY !" << std::endl;
		else
			std::cout << "ClapTrap " << this->_name << " is can't do that !" << std::endl;
	}
	
}

void	ClapTrap::set_name( std::string name )
{
	this->_name = name;
}

void	ClapTrap::set_health( int hp )
{
	this->_health = hp;
}

void	ClapTrap::set_energy( int energy )
{
	this->_energy = energy;
}

void	ClapTrap::set_attack_damage( int AD )
{
	this->_attack_damage = AD;
}

std::string	ClapTrap::get_name( void ) const
{
	return ( _name );
}

int	ClapTrap::get_health( void ) const
{
	return ( _health );
}

int	ClapTrap::get_energy( void ) const
{
	return ( _energy );
}

int	ClapTrap::get_attack_damage( void ) const
{
	return ( _attack_damage );
}

ClapTrap	&ClapTrap::operator=( const ClapTrap &src )
{
	this->_name = src._name;
	this->_health = src._health;
	this->_energy = src._energy;
	this->_attack_damage = src._attack_damage;
	return (*this);
}
