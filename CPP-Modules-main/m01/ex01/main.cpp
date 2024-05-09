/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uercan <uercan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 12:31:09 by uercan            #+#    #+#             */
/*   Updated: 2023/04/17 13:02:57 by uercan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "zombie.hpp"

Zombie* Zombie::zombieHorde( int i, std::string name )
{
	Zombie *zombies = new Zombie [i];
	for(int j = 0; j < i; j++)
	{
		zombies[j].setName(name);
		zombies[j].announce();
	}
	return (zombies);
}

int	main ()
{

	Zombie *zombies;

	zombies = Zombie::zombieHorde(5, "Zombie");

	delete [] zombies;
	return (0);
}
