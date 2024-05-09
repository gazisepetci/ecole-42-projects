/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RobotomyRequestForm.hpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uercan <uercan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 12:58:11 by uercan            #+#    #+#             */
/*   Updated: 2023/06/09 16:48:14 by uercan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ROBOTOMYREQUESTFORM_HPP
# define ROBOTOMYREQUESTFORM_HPP

#include "AForm.hpp"

class RobotomyRequestForm : public AForm
{
	private:
		const std::string	_target;
	public:
		RobotomyRequestForm( void );
		RobotomyRequestForm( const std::string target);
		RobotomyRequestForm( const RobotomyRequestForm &rhs );
		~RobotomyRequestForm( void );

		void	execute( const Bureaucrat &executor ) const;

		RobotomyRequestForm &operator=( const RobotomyRequestForm &src );
};

#endif
