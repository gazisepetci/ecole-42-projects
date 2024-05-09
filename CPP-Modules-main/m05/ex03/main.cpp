/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uercan <uercan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 14:08:36 by uercan            #+#    #+#             */
/*   Updated: 2023/06/10 15:02:02 by uercan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Because filling out forms is annoying enough, it would be cruel to ask our bureaucrats
to do this all day long. Fortunately, interns exist. In this exercise, you have to implement
the Intern class. The intern has no name, no grade, no unique characteristics. The only
thing the bureaucrats care about is that they do their job.
However, the intern has one important capacity: the makeForm() function. It takes
two strings. The first one is the name of a form and the second one is the target of the
form. It return a pointer to a Form object (whose name is the one passed as parameter)
whose target will be initialized to the second parameter.
It will print something like:
Intern creates <form>
If the form name passed as parameter doesn’t exist, print an explicit error message.

You must avoid unreadable and ugly solutions like using a if/elseif/else forest. This
kind of things won’t be accepted during the evaluation process. You’re not in Piscine
(pool) anymore. As usual, you have to test that everything works as expected.
For example, the code below creates a RobotomyRequestForm targeted on "Bender":
{
Intern someRandomIntern;
Form* rrf;
rrf = someRandomIntern.makeForm("robotomy request", "Bender");
}




Form doldurmak yeterince can sıkıcı olduğu için, bürokratlarımızdan gün boyu bunu yapmasını istemek zalimlik olur.
Neyse ki, stajyerler var.Bu alıştırmada, Intern sınıfını uygulamalısınız.
Stajyerin adı, derecesi, benzersiz özellikleri yoktur. Bürokratların umursadığı tek şey işlerini yapmalarıdır.

Ancak stajyerin önemli bir kapasitesi vardır: makeForm() işlevi. İki dizi alır.
Birincisi bir formun adı, ikincisi ise formun hedefidir.
Hedefi ikinci parametreye başlatılacak olan bir Form nesnesine (adı parametre olarak iletilen olan) bir işaretçi döndürür.

Şunun gibi bir şey yazdıracak:
Intern creates <form>
Parametre olarak iletilen form adı yoksa açık bir hata mesajı yazdırın.

if/elseif/else ormanı kullanmak gibi okunamayan ve çirkin çözümlerden kaçınmalısınız.
Değerlendirme sürecinde bu tür şeyler kabul edilmeyecektir. Artık Piscine'de (pool) değilsiniz.
Her zamanki gibi, her şeyin beklendiği gibi çalıştığını test etmeniz gerekir.

Örneğin, aşağıdaki kod "Bender" üzerinde hedeflenen bir RobotomyRequestForm oluşturur:
{
	Intern someRandomIntern;
	Form* rrf;
	rrf = someRandomIntern.makeForm("robotomy request", "Bender");
}

*/

#include "Bureaucrat.hpp"
#include "Intern.hpp"
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

int	main ( void )
{
	{
		Intern someRandomIntern;
		AForm* f1;
		f1 = someRandomIntern.makeForm("robotomy request", "Bender");
		std::cout << *f1;
	}
	// {
	// 	try
	// 	{
	// 		Bureaucrat b1("b1", 1);
	// 		std::cout << b1 << std::endl << std::endl;

	// 		PresidentialPardonForm P("p");
	// 		RobotomyRequestForm R("r");
	// 		ShrubberyCreationForm S("s");

	// 		std::cout << P << std::endl;
	// 		std::cout << R << std::endl;
	// 		std::cout << S << std::endl;

	// 		b1.signForm (P);
	// 		b1.signForm (R);
	// 		b1.signForm (S);

	// 		std::cout << P << std::endl;
	// 		std::cout << R << std::endl;
	// 		std::cout << S << std::endl;

	// 		b1.executeForm ( P );
	// 		b1.executeForm ( R );
	// 		b1.executeForm ( S );
	// 	}catch(const std::exception &e){
	// 		std::cerr << e.what() << std::endl;
	// 	}catch(const std::string &e){
	// 		std::cerr << e << std::endl;
	// 	}

	// }
	std::cout
		<<"\n       _"<< std::endl
		<<"      |)`"<< std::endl
		<<"      | |"<< std::endl
		<<"      | |_____"<< std::endl
		<<"     /    (]__)"<< std::endl
		<<"    /    (]___)"<< std::endl
		<<"   /    (]___)"<< std::endl
		<<"      ___(]_)"<< std::endl
		<<"     /"<< std::endl
		<<"    /"<< std::endl;
	return (0);
}
