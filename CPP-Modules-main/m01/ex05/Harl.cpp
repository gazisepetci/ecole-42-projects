/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Harl.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uercan <uercan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 15:28:27 by uercan            #+#    #+#             */
/*   Updated: 2023/04/17 13:38:25 by uercan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Harl.hpp"

void	Harl::debug ( void )
{
	std::cout << "I love having extra bacon for my 7XL-double-cheese-triple-pickle-specialketchup burger. I really do!" << std::endl;
}

void	Harl::info ( void )
{
	std::cout << "I cannot believe adding extra bacon costs more money. You didn’t put enough bacon in my burger! If you did, I wouldn’t be asking for more!" << std::endl;
}

void	Harl::warning ( void )
{
	std::cout << "I think I deserve to have some extra bacon for free. I’ve been coming for years whereas you started working here since last month." << std::endl;
}

void	Harl::error ( void )
{
	std::cout << "This is unacceptable! I want to speak to the manager now." << std::endl;
}

bool	Harl::complain(std::string level)
{
	t_level	level_func[] = {&Harl::debug, &Harl::info, &Harl::warning, &Harl::error};
	std::string level_name[] = {"debug", "info", "warning", "error"};
	for (int i = 0; i < 4; i++)
	{
		if (level == level_name[i])
		{
			(this->*level_func[i])();
			return (true);
		}
	}
	return (false);
}
