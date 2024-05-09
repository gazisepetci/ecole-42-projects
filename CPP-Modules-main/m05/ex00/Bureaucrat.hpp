/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uercan <uercan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 11:53:11 by uercan            #+#    #+#             */
/*   Updated: 2023/06/10 14:00:09 by uercan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUREAUCRAT_HPP
# define BUREAUCRAT_HPP

#include <iostream>

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

		const std::string	getName( void ) const;
		int					getGrade( void ) const;
		void				downGrade ( void );
		void				upGrade ( void );

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