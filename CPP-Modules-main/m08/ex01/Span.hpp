/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uercan <uercan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 14:29:55 by uercan            #+#    #+#             */
/*   Updated: 2023/07/20 13:02:20 by uercan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPAN_HPP
# define SPAN_HPP

#include <iostream>
#include <vector>
#include <list>

class Span
{
	private:
	unsigned int	_numberCount;
		std::list<int> _num;
	public:
		Span( void );
		Span( unsigned int i );
		Span(const Span &src);
		~Span( void );

		std::list<int>	getNumber ( void ) const;
		unsigned int	getNumberMax ( void ) const;
		void			addNumber( int i);

		int	shortestSpan( void );
		int	longestSpan( void );

		class AlreadyNElementsStored : public std::exception
		{
			public:
				const char*	what() const throw();
		};
		class ThereIsOnlyOneElement : public std::exception
		{
			public:
				const char*	what() const throw();
		};

		Span &operator=( const Span &src);
};

#endif