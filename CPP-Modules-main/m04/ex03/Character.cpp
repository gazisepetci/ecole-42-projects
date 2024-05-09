#include "Character.hpp"

Character::Character( std::string const &name ) : _name(name)
{
	for (int i = 0; i < 4; i++)
		this->_inventory[i] = NULL;
}

Character::Character( Character const &rhs ) : _name(rhs._name)
{
	*this = rhs;
}

Character::~Character( void )
{
	for (int i = 0; i < 4; i++)
		delete this->_inventory[i];
}

Character	&Character::operator=( Character const &rhs )
{
	if (this != &rhs)
	{
		this->_name = rhs._name;
		for (int i = 0; i < 4; i++)
			this->_inventory[i] = rhs._inventory[i];
	}
	return (*this);
}

std::string const	&Character::getName( void ) const
{
	return (this->_name);
}

void	Character::equip( AMateria *m)
{
	for (int i = 0; i < 4; i++)
		if (this->_inventory[i] == NULL)
		{
			this->_inventory[i] = m;
			return ;
		}
}

void	Character::unequip( int idx )
{
	if (this->_inventory[idx])
	{
		this->_inventory[idx] = NULL;
	}
}

void	Character::use( int idx, ICharacter &target )
{
	if (this->_inventory[idx])
	{
		this->_inventory[idx]->use(target);
	}
}