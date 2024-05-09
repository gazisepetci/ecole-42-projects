#ifndef WRONGCAT_HPP
 #define WRONGCAT_HPP

#include "WrongAnimal.hpp"

class	WrongCat : public WrongAnimal
{

public:
	WrongCat( void );
	WrongCat( const WrongCat &ref );
	WrongCat &operator=( const WrongCat &ref );
	~WrongCat( void );
	
	void	makeSound( void ) const;
};

#endif
