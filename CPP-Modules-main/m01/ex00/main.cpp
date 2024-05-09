/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                     +:+ +:+         +:+     */
/*   By: uercan <uercan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 12:31:09 by uercan            #+#    #+#             */
/*   Updated: 2023/03/21 14:59:18 by uercan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "zombie.hpp"

int	main ()
{
	Zombie	*zombieptr;

	zombieptr = newZombie("ZombieZ");
	zombieptr->announce();
	randomChump("zzzzZOmbie");
	delete zombieptr;
	return (0);
}