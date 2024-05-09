/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uercan <uercan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 19:30:26 by uercan            #+#    #+#             */
/*   Updated: 2023/04/17 14:28:49 by uercan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "replace.hpp"

std::string	ft_check_replace(std::string full_string, std::string line, std::string old_s, std::string new_s)
{
	int	j;
	std::cout << "test" << std::endl;
	for (int i = 0; line[i]; i++)
	{
		j = 0;
		while (line[i + j] == old_s[j])
			j++;
		if (old_s[j] == '\0')
		{
			full_string += new_s;
			i += j - 1;
		}
		else
			full_string += line[i];
	}
	return (full_string);
}

void	ft_replace(std::string	 file_name, std::string	 old_s, std::string	new_s)
{
	std::ifstream	f_read(file_name);
	std::ofstream	f_write(file_name + ".replace");
	std::string		line;
	std::string		full_string;
	if (f_read.is_open())
	{
		while (getline (f_read,line))
			full_string = ft_check_replace(full_string, line, old_s, new_s);
		f_read.close();
	}
	else
		std::cout << "Unable to open file";
	f_write << full_string;
	f_write.close();
}

int	main(int argc, char **argv)
{
	if (argc != 4)
		std::cout << "Invalid format,use <filename> S1 S2" << std::endl;
	else
		ft_replace(argv[1], argv[2], argv[3]);
	return (0);
}
