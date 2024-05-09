/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uercan <uercan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 17:45:22 by uercan            #+#    #+#             */
/*   Updated: 2023/06/10 18:51:33 by uercan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Forbidden functions : std::typeinfo

Implement a Base class that has a public virtual destructor only. Create three empty
classes A, B and C, that publicly inherit from Base.
These four classes don’t have to be designed in the Orthodox
Canonical Form.
Implement the following functions:
Base * generate(void);
It randomly instanciates A, B or C and returns the instance as a Base pointer. Feel free
to use anything you like for the random choice implementation.
void identify(Base* p);
It prints the actual type of the object pointed to by p: "A", "B" or "C".
void identify(Base& p);
It prints the actual type of the object pointed to by p: "A", "B" or "C". Using a pointer
inside this function is forbidden.
Including the typeinfo header is forbidden.
Write a program to test that everything works as expected.
*/

/*
Forbidden functions : std::typeinfo

Yalnızca genel bir sanal yok ediciye sahip bir Base sınıf uygulayın.
Base'den herkese açık olarak miras alan üç boş A, B ve C sınıfı oluşturun.

Aşağıdaki işlevleri uygulayın:

Base * generate(void);
Rastgele A, B veya C örneklerini oluşturur ve örneği bir Temel işaretçi olarak döndürür.
Rastgele seçim uygulaması için istediğiniz herhangi bir şeyi kullanmaktan çekinmeyin.

void identify(Base* p); 
p ile işaret edilen nesnenin gerçek tipini yazdırır: "A", "B" veya "C".

void identify(Base& p);
p ile işaret edilen nesnenin gerçek tipini yazdırır: "A", "B" veya "C". Bu işlev içinde bir işaretçi kullanmak yasaktır.
typeinfo başlığının dahil edilmesi yasaktır.
Her şeyin beklendiği gibi çalıştığını test etmek için bir program yazın.
*/

#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"
#include <cstdlib>

Base * generate(void)
{
	srand(time(NULL));
	int number = rand() % 3;
	if (number == 0)
	{
		std::cout << "Generated A" << std::endl;
		return (new A);
	}
	else if (number == 1)
	{
		std::cout << "Generated B" << std::endl;
		return (new B);
	}
	std::cout << "Generated C" << std::endl;
	return (new C);
}

void	identify( Base *p )
{
	if (dynamic_cast<A*>(p))
		std::cout << "A" << std::endl;
	else if (dynamic_cast<B*>(p))
		std::cout << "B" << std::endl;
	else if (dynamic_cast<C*>(p))
		std::cout << "C" << std::endl;
	else
		std::cout << "unknown type: *" << std::endl;
}

void	identify( Base &p )
{
	try
	{
		A	&a = dynamic_cast<A&>(p);
		std::cout << "A&" << std::endl;
		(void)a;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
	try
	{
		B	&b = dynamic_cast<B&>(p);
		std::cout << "B&" << std::endl;
		(void)b;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
	try
	{
		C	&c = dynamic_cast<C&>(p);
		std::cout << "C&" << std::endl;
		(void)c;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
}

int main( void )
{
	Base *ptr;

	ptr = generate();
	identify(ptr);
	identify(*ptr);

	delete ptr;
}