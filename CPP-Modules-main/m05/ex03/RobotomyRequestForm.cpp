/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RobotomyRequestForm.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uercan <uercan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 15:45:26 by uercan            #+#    #+#             */
/*   Updated: 2023/06/09 18:00:30 by uercan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RobotomyRequestForm.hpp"
#include <cstdlib>

RobotomyRequestForm::RobotomyRequestForm ( void ) : AForm("RobotomyRequestForm", 72, 45), _target("Default"){}
RobotomyRequestForm::RobotomyRequestForm ( const std::string target ) : AForm("RobotomyRequestForm", 72, 45), _target(target){}
RobotomyRequestForm::RobotomyRequestForm ( const RobotomyRequestForm &src) : AForm("RobotomyRequestForm", 72, 45), _target(src._target){}
RobotomyRequestForm::~RobotomyRequestForm ( void ){}

RobotomyRequestForm &RobotomyRequestForm::operator=( const RobotomyRequestForm &src )
{
	this->setSign( src.getSign() );
	return (*this);
}

void	RobotomyRequestForm::execute ( const Bureaucrat &bro) const
{
	if (!this->getSign())
		throw (AForm::FormIsNotSigned());
	else if (bro.getGrade() > this->signGrade())
	{
		std::cout << bro.getName() << "'s grade is too low for execute\n";
		throw (AForm::GradeTooLowException());
	}
	std::cout << "zzzzz\nzghhtthg\ndarDarrRdarAdR\n";
	srand((unsigned) time(NULL));
	int random = rand() % 2;
	if (random == 0)
		std::cout << "->" << this->_target << "<- has been robotomized!\n";
	else
		std::cout << "* ERROR! *\n->" << this->_target << "<- has not been robotomized!\n";
}
