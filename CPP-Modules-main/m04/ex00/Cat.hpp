/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uercan <uercan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 16:41:45 by uercan            #+#    #+#             */
/*   Updated: 2023/05/30 17:08:27 by uercan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAT_HPP
# define CAT_HPP

#include <iostream>
#include "Animal.hpp"

class Cat : public Animal
{
	private:
	public:
		Cat( void );
		~Cat( void );
		Cat( const Cat &src );
		Cat &operator=( const Cat &src );

		void	makeSound ( void ) const;
};

#endif
