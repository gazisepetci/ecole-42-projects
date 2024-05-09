/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Brain.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uercan <uercan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 16:23:41 by uercan            #+#    #+#             */
/*   Updated: 2023/06/02 22:57:13 by uercan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BRAIN_HPP
# define BRAIN_HPP

#include <iostream>

class Brain
{
	private:
		std::string _ideas[100];
	public:
		Brain( void );
		virtual ~Brain( void );
		Brain( const Brain &src );

		void		setBrain( int index, std::string idea );
		std::string	getBrain( int index );

		Brain &operator=( const Brain &src );
};

#endif