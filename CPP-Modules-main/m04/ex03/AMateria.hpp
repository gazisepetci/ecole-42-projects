/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AMateria.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uercan <uercan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 04:36:52 by uercan            #+#    #+#             */
/*   Updated: 2023/06/03 08:38:34 by uercan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AMETERIA_HPP
# define AMETERIA_HPP

#include "ICharacter.hpp"
#include <iostream>

class ICharacter;

class AMateria
{
	protected:
		std::string	type;
	public:
		AMateria( void );
		AMateria( std::string const &type );
		AMateria( AMateria const &rhs );
		virtual	~AMateria( void );

		std::string const	&getType() const; // Returns the materia type

		virtual AMateria	*clone() const = 0;
		virtual void		use( ICharacter &target );
};

#endif