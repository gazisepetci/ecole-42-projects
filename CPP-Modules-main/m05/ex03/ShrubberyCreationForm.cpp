/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShrubberyCreationForm.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uercan <uercan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 15:45:26 by uercan            #+#    #+#             */
/*   Updated: 2023/06/09 17:46:13 by uercan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ShrubberyCreationForm.hpp"

ShrubberyCreationForm::ShrubberyCreationForm ( void ) : AForm("ShrubberyCreationForm", 145, 137), _target("Default"){}
ShrubberyCreationForm::ShrubberyCreationForm ( const std::string target ) : AForm("ShrubberyCreationForm", 145, 137), _target(target){}
ShrubberyCreationForm::ShrubberyCreationForm ( const ShrubberyCreationForm &src) : AForm("ShrubberyCreationForm", 145, 137), _target(src._target){}
ShrubberyCreationForm::~ShrubberyCreationForm ( void ){}

ShrubberyCreationForm &ShrubberyCreationForm::operator=( const ShrubberyCreationForm &src )
{
	this->setSign( src.getSign() );
	return (*this);
}

void	ShrubberyCreationForm::execute ( const Bureaucrat &bro) const
{
	// if (bro.getGrade() > this->signGrade())
	// {
	// 	std::cout << bro.getName() << "'s grade is too low for execute\n";
	// 	throw (AForm::GradeTooLowException());
	// }
	// else if (bro.getGrade() < this->signGrade())
	// {
	// 	std::cout << bro.getName() << "'s grade is too High for execute\n";
	// 	throw (AForm::GradeTooHighException());
	// }
	if (!this->getSign())
		throw (AForm::FormIsNotSigned());
	else if (bro.getGrade() > this->signGrade())
	{
		std::cout << bro.getName() << "'s grade is too low for execute\n";
		throw (AForm::GradeTooLowException());
	}
	std::ofstream	file(_target + "_shrubbery");
	file << "            # #### ####         " << std::endl;
	file << "          ### \\/#|### |/####    " << std::endl;
	file << "         ##\\/#/ \\||/##/_/##/_#  " << std::endl;
	file << "       ###  \\/###|/ \\/ # ###    " << std::endl;
	file << "     ##_\\_#\\_\\## | #/###_/_#### " << std::endl;
	file << "    ## #### # \\ #| /  #### ##/##" << std::endl;
	file << "     __#_--###`  |{,###---###-~ " << std::endl;
	file << "               \\ }{             " << std::endl;
	file << "                }}{             " << std::endl;
	file << "                }}{             " << std::endl;
	file << "                {{}             " << std::endl;
	file << "          , -=-~{ .-^- _        " << std::endl;
	file << "                `}              " << std::endl;
	file << "                 {              " << std::endl;
	file.close();
}
