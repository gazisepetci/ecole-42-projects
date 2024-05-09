/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uercan <uercan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 18:09:11 by uercan            #+#    #+#             */
/*   Updated: 2023/06/11 17:22:15 by uercan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Serialization.hpp"

uintptr_t Serialization::serialize( Data* ptr ){
	return ( reinterpret_cast<uintptr_t>(ptr) );
}

Data* Serialization::deserialize( uintptr_t raw ){
	return ( reinterpret_cast<Data*>(raw) );
}
