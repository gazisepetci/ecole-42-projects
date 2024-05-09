/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PresidentialPardonForm.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uercan <uercan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 12:58:11 by uercan            #+#    #+#             */
/*   Updated: 2023/06/09 16:48:22 by uercan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRESIDENTIALPARDONFORM_HPP
# define PRESIDENTIALPARDONFORM_HPP

#include "AForm.hpp"

class PresidentialPardonForm : public AForm
{
	private:
		const std::string	_target;
	public:
		PresidentialPardonForm( void );
		PresidentialPardonForm( const std::string target);
		PresidentialPardonForm( const PresidentialPardonForm &rhs );
		~PresidentialPardonForm( void );

		void	execute( const Bureaucrat &bro ) const;

		PresidentialPardonForm &operator=( const PresidentialPardonForm &src );
};

#endif
