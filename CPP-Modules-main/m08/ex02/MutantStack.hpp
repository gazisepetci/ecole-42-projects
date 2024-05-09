/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*    MutantStack.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uercan <uercan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 12:55:28 by uercan            #+#    #+#             */
/*   Updated: 2023/07/20 13:08:05 by uercan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MUTANTSTACK_HPP
# define MUTANTSTACK_HPP

#include <stack>
#include <vector>
#include <iostream>
#include <deque>

//template <class Type, class Container = deque<Type> > class stack;
template <typename T>
class MutantStack: public std::stack<T>
{
	public:
		MutantStack( void ) : std::stack<T>() {}
		MutantStack( const MutantStack &src ) : std::stack<T>( src ){*this = src;}
		~MutantStack( void ){}

		MutantStack &operator=( const MutantStack &src ){
			std::stack<T>::operator=(src);
			return (*this);
		}
		typedef typename std::stack<T>::container_type::iterator iterator;
		iterator begin ( void ){ return (this->c.begin());}
		iterator end ( void ){ return (this->c.end()); }
};

#endif
