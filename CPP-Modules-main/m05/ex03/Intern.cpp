/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uercan <uercan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 00:39:52 by gsever            #+#    #+#             */
/*   Updated: 2023/06/09 20:15:46 by uercan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Intern.hpp"

Intern::Intern( void ){}

Intern::~Intern( void ){}

AForm	*Intern::makeForm( std::string name, std::string target )
{
	AForm *form;
	std::string form_name_list[] = {"robotomy request", "presidential pardon", "shrubbery creation"};
	int index = 0;

	while (index < (int)form_name_list->length() && (form_name_list[index].empty() == false) && (form_name_list[index]).compare(name))
		index++;
	switch (index)
	{
		case 0:
			form = new RobotomyRequestForm(target);
			break;
		case 1:
			form = new PresidentialPardonForm(target);
			break;
		case 2:
			form = new ShrubberyCreationForm(target);
			break;
		default:
			throw ( Intern::InternCantCreatedForm() );
	}
	std::cout <<  "Intern creates " << form->getName()  << std::endl;
	return (form);
}

const char *Intern::InternCantCreatedForm::what() const throw(){
	return ("Intern can't created form");
}