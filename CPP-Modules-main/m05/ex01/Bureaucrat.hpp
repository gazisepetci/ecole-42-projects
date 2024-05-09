/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uercan <uercan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 11:53:11 by uercan            #+#    #+#             */
/*   Updated: 2023/06/10 15:02:02 by uercan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUREAUCRAT_HPP
# define BUREAUCRAT_HPP

#include <iostream>
#include "Form.hpp"

class Form;

class Bureaucrat
{
	private:
		const std::string	_name;
		int					_grade;

	public:
		Bureaucrat ( void );
		~Bureaucrat ( void );
		Bureaucrat ( const Bureaucrat &src );
		Bureaucrat ( std::string name , int grade);

		Bureaucrat	&operator=(const Bureaucrat &src);

		void	signForm ( Form &form );
		void	upGrade ( void );
		void	downGrade ( void );
		int	getGrade( void ) const;
		const std::string	getName( void ) const;

		class GradeTooHighException : public std::exception
		{
			public:
				const char*	what() const throw();
		};
		class GradeTooLowException : public std::exception
		{
			public:
				const char*	what() const throw();
		};

};

std::ostream	&operator<<(std::ostream &os, Bureaucrat const &src);

#endif