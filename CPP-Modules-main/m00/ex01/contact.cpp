/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   contact.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uercan <uercan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 12:17:04 by uercan            #+#    #+#             */
/*   Updated: 2023/03/17 12:02:57 by uercan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phonebook.hpp"

std::string	get_input(std::string msg, bool digit)
{
	std::string	input;

	if (digit)
	{
		std::cout << std::endl << msg;
		std::getline(std::cin, input);
		while (input.empty() || !ft_check_digit(input))
		{
			std::cout << "Please enter a phone number with numbers" << std::endl;
			std::cout << std::endl << msg;
			std::getline(std::cin, input);
		}
	}
	while (input.empty())
	{
		std::cout << std::endl << msg;
		std::getline(std::cin, input);
	}
	return (input);
}

void	Contact::add_contact()
{
	std::string	input;

	this->_name = get_input("New contact's name: ", false);
	this->_lastname = get_input("New contact's lastname: ", false);
	this->_nickname = get_input("New contact's nickname: ", false);
	this->_secret = get_input("Darkest secret: ", false);
	this->_phone_no = get_input("New contact's phone no: ", true);
}

void	Contact::show_contact_info(void)
{
	std::cout << "Name:           " << this->_name << std::endl;
	std::cout << "LastName:       " << this->_lastname << std::endl;
	std::cout << "Nickname:       " << this->_nickname << std::endl;
	std::cout << "Darkest secret: " << this->_secret << std::endl;
	std::cout << "Phone Number:   " << this->_phone_no << std::endl;
}

void	print_info_to_search(std::string inf)
{
	if (inf.length() > 10)
		std::cout << inf.substr(0, 9) << ".";
	else
		std::cout << std::setfill(' ') << std::setw(10) << inf << "|";
}

void	Contact::show_contacts(int i)
{
	if (i == 0)
	{
		std::cout << std::setfill(' ') << std::setw(11) << "Index|" <<
		std::setfill(' ') << std::setw(11) << "Name|" <<
		std::setfill(' ') << std::setw(11) << "Lastname|" <<
		std::setfill(' ') << std::setw(11) << "Nickname|" <<
		std::endl;
	}
	std::cout << std::setfill(' ') << std::setw(10) << i << "|";
	print_info_to_search(this->_name);
	print_info_to_search(this->_lastname);
	print_info_to_search(this->_nickname);
	std::cout << std::endl;
}
