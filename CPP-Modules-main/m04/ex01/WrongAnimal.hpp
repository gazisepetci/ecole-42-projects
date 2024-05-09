/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongAnimal.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uercan <uercan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 17:40:04 by uercan            #+#    #+#             */
/*   Updated: 2023/05/30 17:40:39 by uercan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WRONGANIMAL_HPP
 #define WRONGANIMAL_HPP

#include "iostream"

class WrongAnimal{

protected:
	std::string	_type;

public:
	WrongAnimal( void );
	WrongAnimal( const WrongAnimal &ref );
	WrongAnimal &operator=( const WrongAnimal &ref );
	~WrongAnimal( void );

	void			makeSound( void ) const;
	std::string		getType( void ) const;
};

#endif
