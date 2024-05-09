/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phonebook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uercan <uercan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 15:18:54 by uercan            #+#    #+#             */
/*   Updated: 2023/03/21 12:39:06 by uercan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phonebook.hpp"

void	PhoneBook::add_command( void )
{
	static int	i;

	this->_contacts[i].add_contact();
	i++;
	if (i == 8)
		i = 0;
	if (this->contact_count < 8)
		this->contact_count++;
}

bool	ft_check_digit(std::string s)
{
	for (int j = 0; s[j]; j++)
		if (!std::isdigit(s[j]))
			return (false);
	return (true);
}
void	PhoneBook::search_command(void)
{
	std::string	ins;
	int			i;
	int			index;

	index = -1;
	if (this->contact_count == 0)
		std::cout<< std::endl << "-No contacts to show-" << std::endl << std::endl;
	else
	{
		while (++index < this->contact_count)
			this->_contacts[index].show_contacts(index);
		std::cout << "Select your contact's index: ";
		std::getline(std::cin, ins);
		i =  atoi(ins.c_str());
		while (!ft_check_digit(ins) || i < 0 || i >= this->contact_count)
		{
			std::cout << "Please enter a digit index [0 - " << this->contact_count - 1 << "]" << std::endl;
			std::cout << "Select your contact's index: ";
			std::getline(std::cin, ins);
			i =  atoi(ins.c_str());
		}
		this->_contacts[i].show_contact_info();
	}
}