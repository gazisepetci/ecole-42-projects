/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uercan <uercan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 12:47:47 by uercan            #+#    #+#             */
/*   Updated: 2023/06/10 15:02:02 by uercan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include "AForm.hpp"

Bureaucrat::Bureaucrat ( void ): _name ("Default"), _grade (150){}
Bureaucrat::~Bureaucrat ( void ){}
Bureaucrat::Bureaucrat ( std::string name , int grade): _name (name)
{
	if (grade < 1)
		throw (Bureaucrat::GradeTooHighException());
	if (grade > 150)
		throw (Bureaucrat::GradeTooLowException());
	else
		this->_grade = grade;
}

Bureaucrat::Bureaucrat ( const Bureaucrat &src): _name(src.getName())
{
	if (src.getGrade() < 1)
		throw (Bureaucrat::GradeTooLowException());
	else if (src.getGrade() > 150)
		throw (Bureaucrat::GradeTooHighException());
	else
		this->_grade = src.getGrade();
}

void	Bureaucrat::signForm ( AForm &form )
{
	form.beSigned (*this);
}

const std::string	Bureaucrat::getName( void ) const
{
	return (this->_name);
}

int	Bureaucrat::getGrade( void ) const
{
	return (this->_grade);
}

void	Bureaucrat::downGrade ( void )
{
	if (this->_grade - 1 < 1)
		throw (Bureaucrat::GradeTooHighException());
}

void	Bureaucrat::upGrade ( void )
{
	if (this->_grade + 1 > 150)
		throw (Bureaucrat::GradeTooLowException());
}

void	Bureaucrat::executeForm( AForm const &form )
{
	if (form.executeGrade() < this->getGrade())
		std::cout << this->getName() << " is can't execute " << form.getName() << std::endl;
	else
	{
		form.execute( *this );
		std::cout << this->getName() << " executed " << form.getName() << std::endl;
	}
}

const char	*Bureaucrat::GradeTooHighException::what() const throw()
{
	return ("Bureaucrat: Grade too 'HIGH'.");
}

const char	*Bureaucrat::GradeTooLowException::what() const throw()
{
	return ("Bureaucrat: Grade too 'LOW'.");
}

Bureaucrat &Bureaucrat::operator=(const Bureaucrat &src)
{
	this->_grade = src._grade;
	return (*this);
}

std::ostream	&operator<<(std::ostream &os, Bureaucrat const &src)
{
	//os << src.getGrade();
	os << src.getName() << ", bureaucrat grade " << src.getGrade();
	return (os);
}
