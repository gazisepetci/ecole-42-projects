/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uercan <uercan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 16:23:41 by uercan            #+#    #+#             */
/*   Updated: 2023/07/18 12:54:24 by uercan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANIMAL_HPP
# define ANIMAL_HPP

#include <iostream>

class Animal
{
	protected:
		std::string _type;
	public:
		Animal( void );
		virtual ~Animal( void );
		Animal( const Animal &src );
		
		Animal &operator=( const Animal &src );

		std::string		getType( void ) const;
		virtual void	makeSound ( void ) const;
};

#endif