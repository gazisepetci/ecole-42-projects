/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uercan <uercan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 11:53:11 by uercan            #+#    #+#             */
/*   Updated: 2023/06/09 20:09:11 by uercan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERN_HPP
# define INTERN_HPP

#include <iostream>
#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

class AForm;

class Intern
{
	private:
	public:
		Intern	( void );
		~Intern	( void );
		Intern	( std::string name , std::string target);

		AForm	*makeForm( std::string name, std::string );

		Intern &operator=( const Intern &src );

		class InternCantCreatedForm : public std::exception
		{
			public:
				virtual const char *what(void) const throw();
		};
};

#endif