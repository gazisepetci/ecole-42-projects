/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uercan <uercan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 20:31:46 by uercan            #+#    #+#             */
/*   Updated: 2023/05/08 16:37:17 by uercan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phonebook.hpp"

int	main(void)
{
	PhoneBook pbook;
	std::string	input;
	int	status;

	status = 0;
	pbook.contact_count = 0;
	while (status == 0)
	{
		pbook.open_book();
		std::cout << ">>===> ";
		std::getline(std::cin, input);
		for (int i = 0; input[i]; i++)
				input[i] = (char)std::tolower(input[i]);
		if (std::cin.eof() || input == "exit")
			status = 1;
		else if (input == ("add"))
			pbook.add_command();
		else if (input == "search")
			pbook.search_command();
		else if (!input.empty())
			std::cout << "Invalid Command: '" << input << "'" << std::endl;
	}
	std::cout << "Exit" << std::endl;
	return (0);
}