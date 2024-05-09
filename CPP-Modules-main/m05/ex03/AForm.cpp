/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AForm.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uercan <uercan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 13:06:10 by uercan            #+#    #+#             */
/*   Updated: 2023/06/08 14:05:44 by uercan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AForm.hpp"
#include "Bureaucrat.hpp"

int			AForm::signGrade ( void ) const{return (this->_signGrade);}
int			AForm::executeGrade ( void ) const{return (this->_executeGrade);}
std::string	AForm::getName ( void ) const{return (this->_name);}
bool		AForm::getSign ( void ) const{return (this->_isSigned);}
void		AForm::setSign ( bool s ) {this->_isSigned = s;}
AForm::~AForm ( void ){}

AForm::AForm ( void ): _name("Default_form"), _isSigned(false), _signGrade(75), _executeGrade(75)
{}

AForm::AForm( const std::string name, int signGrade, int executeGrade): _name(name), _signGrade(signGrade), _executeGrade(executeGrade){
	this->_isSigned = false;
	if (this->_signGrade < 1 || this->_executeGrade < 1)
		throw( AForm::GradeTooHighException() );
	else if (this->_signGrade > 150 || this->_executeGrade > 150)
		throw( AForm::GradeTooLowException() );
}

void	AForm::beSigned( const Bureaucrat &bro )
{
	if (this->getSign())
		throw (FormAllreadySigned());
	else if (bro.getGrade() > this->signGrade())
		throw (GradeTooLowException());
	else
		this->_isSigned = true;
}

const char	*AForm::GradeTooHighException::what() const throw()
{
	return ("Grade too 'HIGH'.");
}

const char	*AForm::GradeTooLowException::what() const throw()
{
	return ("Grade too 'LOW'.");
}
const char	*AForm::FormAllreadySigned::what() const throw()
{
	return ("Form is allready signed.");
}

const char	*AForm::FormIsNotSigned::what() const throw()
{
	return ("Form is not signed.");
}

std::ostream	&operator<<(std::ostream &os, const AForm &src)
{
	os << src.getName()<< "\nsign: "<< src.getSign() << "\nsign grade: " << src.signGrade() << "\nexecute grade: " << src.executeGrade() << std::endl;
	return (os);
}
