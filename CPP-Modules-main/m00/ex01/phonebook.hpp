/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phonebook.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uercan <uercan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 11:50:49 by uercan            #+#    #+#             */
/*   Updated: 2023/05/08 16:31:19 by uercan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHONEBOOK_HPP
# define PHONEBOOK_HPP

#include <iostream>
#include <iomanip>
#include <locale>
#include "contact.hpp"

class PhoneBook : Contact
{
	private:
		Contact _contacts[8];
	public:
		int	contact_count;
		void	open_book()
		{
			std::cout << " / ---------*--------- \\" << std::endl;
			std::cout << "| PhoneBook - Commands: |" << std::endl;
			std::cout << "| --------------------- |" << std::endl;
			std::cout << "| ADD || SEARCH || EXIT |" << std::endl;
			std::cout << " \\ --------*---------- /" << std::endl;
		}
		void	search_command(void);
		void	add_command(void);
};

bool		ft_check_digit(std::string s);
void		print_info_to_search(std::string inf);
std::string	get_input(std::string msg, bool digit);

#endif