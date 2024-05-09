/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShrubberyCreationForm.hpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uercan <uercan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 12:58:11 by uercan            #+#    #+#             */
/*   Updated: 2023/06/09 16:13:12 by uercan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHRUBBERYCREATIONFORM_HPP
# define SHRUBBERYCREATIONFORM_HPP

#include <fstream>
#include "AForm.hpp"

class ShrubberyCreationForm : public AForm
{
	private:
		const std::string	_target;
	public:
		ShrubberyCreationForm( void );
		ShrubberyCreationForm( const std::string target);
		ShrubberyCreationForm( const ShrubberyCreationForm &src );
		~ShrubberyCreationForm( void );

		void	execute( const Bureaucrat &bro ) const;

		ShrubberyCreationForm &operator=( const ShrubberyCreationForm &src );
};

#endif
