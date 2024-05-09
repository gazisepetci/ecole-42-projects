/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MateriaSource.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uercan <uercan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 08:30:53 by uercan            #+#    #+#             */
/*   Updated: 2023/06/03 08:30:57 by uercan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATERIASOURCE_HPP
# define MATERIASOURCE_HPP

#include "AMateria.hpp"
#include "IMateriaSource.hpp"

class MateriaSource : public IMateriaSource
{
	private:
		AMateria	*_materias[4];
	public:
		MateriaSource( void );
		MateriaSource( MateriaSource const &rhs );
		~MateriaSource( void );

		MateriaSource	&operator=( MateriaSource const &rhs );

		void		learnMateria( AMateria* );
		AMateria	*createMateria( std::string const &type );
		AMateria	*getMateria( std::string const &type );
};

#endif