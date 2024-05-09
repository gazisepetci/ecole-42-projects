#ifndef FragTrap_HPP
# define FragTrap_HPP

#include <iostream>
#include "ClapTrap.hpp"

class FragTrap : virtual public ClapTrap
{
	private:
	public:
		FragTrap ( void );
		FragTrap ( std::string name );
		FragTrap ( const FragTrap &src );
		~FragTrap ( void );

		void		highFivesGuys( void );
		FragTrap	&operator=( const FragTrap &src );
};

#endif