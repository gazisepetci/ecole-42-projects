/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   contact.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uercan <uercan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 11:36:18 by uercan            #+#    #+#             */
/*   Updated: 2023/03/29 11:36:20 by uercan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTACT_HPP
# define CONTACT_HPP

#include "phonebook.hpp"

class Contact
{
	private:
		std::string	_name;
		std::string	_lastname;
		std::string	_nickname;
		std::string	_phone_no;
		std::string	_secret;
	public:
		void	add_contact();
		void	show_contacts(int i);
		void	show_contact_info(void);
};

#endif