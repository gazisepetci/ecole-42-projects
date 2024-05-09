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

int	main(int argc, char **argv)
{
	std::string	input;
	Harl		harl;

	if (argc != 2)
		std::cout << "Invalid level!" << std::endl;
	else
		harl.complain(argv[1]);
	return (0);
}