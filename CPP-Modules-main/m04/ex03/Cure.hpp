/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cure.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uercan <uercan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 08:19:04 by uercan            #+#    #+#             */
/*   Updated: 2023/06/03 08:40:06 by uercan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CURE_HPP
# define CURE_HPP

# include "AMateria.hpp"

class Cure : public AMateria
{
	public:
		Cure( void );
		Cure( Cure const &rhs );
		~Cure( void );

		Cure	&operator=( Cure const &rhs );

		virtual AMateria	*clone( void ) const;
		virtual void		use( ICharacter &target );
};

#endif