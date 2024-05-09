/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uercan <uercan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 17:04:45 by uercan            #+#    #+#             */
/*   Updated: 2023/04/17 13:38:25 by uercan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Harl.hpp"

int	main( void )
{
	std::string	input;
	Harl		harl;
	while (1)
	{
		std::cin >> input;
		if (!harl.complain(input))
			std::cout << "Invalid level!" << std::endl;
	}
	return (0);
}