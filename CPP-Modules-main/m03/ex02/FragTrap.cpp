/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FragTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uercan <uercan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 14:25:28 by uercan            #+#    #+#             */
/*   Updated: 2023/05/25 14:36:14 by uercan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FragTrap.hpp"

FragTrap &FragTrap::operator=( const FragTrap &src )
{
	this->set_name ( src.get_name());
	this->set_energy ( src.get_energy());
	this->set_health ( src.get_health());
	this->set_attack_damage ( src.get_attack_damage());
	return (*this);
}

FragTrap::~FragTrap()
{
	std::cout << "FragTrap ended" << std::endl;
}

FragTrap::FragTrap()
{
	this->set_health (100);
	this->set_attack_damage (30);
	this->set_energy (100);
	this->set_name ("Default FragTrap");
	std::cout << "FragTrap start" << std::endl;
}

FragTrap::FragTrap( std::string name )
{
	this->set_health (100);
	this->set_attack_damage (30);
	this->set_energy (100);
	this->set_name (name);
	std::cout << "FragTrap " << this->get_name() << " named " << std::endl;
}

FragTrap::FragTrap( const FragTrap &src )
{
	this->set_name ( src.get_name());
	this->set_energy ( src.get_energy());
	this->set_health ( src.get_health());
	this->set_attack_damage ( src.get_attack_damage());
	std::cout << "FragTrap copy constructor called" << std::endl;
}

void FragTrap::highFivesGuys ( void )
{
	std::cout << this->get_name() << "a positive high fives !" << std::endl;
	this->beRepaired(10);
	this->set_energy (get_energy() + 10);

}
