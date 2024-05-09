/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Serialization.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uercan <uercan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 17:55:10 by uercan            #+#    #+#             */
/*   Updated: 2023/06/11 17:22:29 by uercan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERIALIZATION_HPP
# define SERIALIZATION_HPP

#include <iostream>
#include <string>

struct Data{
	int		a;
	float	b;
};

class Serialization{
	public:
		static uintptr_t serialize( Data* ptr );
		static Data* deserialize( uintptr_t raw );

};

#endif