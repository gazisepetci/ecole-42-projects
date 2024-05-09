/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uercan <uercan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 16:42:12 by uercan            #+#    #+#             */
/*   Updated: 2023/05/30 17:08:21 by uercan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef DOG_HPP
# define DOG_HPP

#include <iostream>
#include "Animal.hpp"

class Dog : public Animal
{
	private:
	public:
		Dog( void );
		~Dog( void );
		Dog( const Dog &src );
		Dog &operator=( const Dog &src );

		void	makeSound ( void ) const;
};

#endif
