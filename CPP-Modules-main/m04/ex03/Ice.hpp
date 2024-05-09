/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ice.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uercan <uercan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 08:21:34 by uercan            #+#    #+#             */
/*   Updated: 2023/06/03 08:25:36 by uercan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ICE_HPP
# define ICE_HPP

# include "AMateria.hpp"

class Ice : public AMateria
{
	public:
		Ice( void );
		Ice( Ice const &rhs );
		~Ice( void );

		Ice	&operator=( Ice const &rhs );

		virtual AMateria	*clone( void ) const;
		virtual void		use( ICharacter &target );
};

#endif