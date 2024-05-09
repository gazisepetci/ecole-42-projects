/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DiamondTrap.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:x+         +:+     */
/*   By: uercan <uercan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 14:46:26 by uercan            #+#    #+#             */
/*   Updated: 2023/05/25 15:10:20 by uercan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DIAMONDTRAP_HPP
#define DIAMONDTRAP_HPP

#include <iostream>
# include "ScavTrap.hpp"
# include "FragTrap.hpp"

class DiamondTrap : public FragTrap, public ScavTrap
{
	private:
		std::string	_name;
	public:
		DiamondTrap ( void );
		DiamondTrap ( std::string name );
		DiamondTrap( const DiamondTrap &src );
		~DiamondTrap ( void );

		DiamondTrap &operator=(const DiamondTrap &src);
		void	attack(const std::string& target);
		void	whoAmI( void );
};

#endif