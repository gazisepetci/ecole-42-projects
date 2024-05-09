/*
Please note that exception classes don’t have to be designed in
Orthodox Canonical Form. But every other class has to.
Let’s design an artificial nightmare of offices, corridors, forms, and waiting queues.
Sounds fun? No? Too bad.
First, start by the smallest cog in this vast bureaucratic machine: the Bureaucrat.
A Bureaucrat must have:
• A constant name.
• And a grade that ranges from 1 (highest possible grade) to 150 (lowest possible
grade).
Any attempt to instantiate a Bureaucrat using an invalid grade must throw an exception:
either a Bureaucrat::GradeTooHighException or a Bureaucrat::GradeTooLowException.
You will provide getters for both these attributes: getName() and getGrade(). Implement also two member functions to increment or decrement the bureaucrat grade. If
the grade is out of range, both of them will throw the same exceptions as the constructor.
Remember. Since grade 1 is the highest one and 150 the lowest,
incrementing a grade 3 should give a grade 2 to the bureaucrat.
The thrown exceptions must be catchable using try and catch blocks:
try
{
//do some stuff with bureaucrats
}
catch (std::exception & e)
{
//handle exception
}
You will implement an overload of the insertion («) operator to print something like
(without the angle brackets):
<name>, bureaucrat grade <grade>.
As usual, turn in some tests to prove everything works as expected
*/

/*
İstisna sınıflarının Ortodoks Kanonik Biçimde tasarlanması gerekmediğini lütfen unutmayın. Ama diğer tüm sınıflar yapmak zorunda.

Ofisler, koridorlar, formlar ve bekleme kuyruklarından oluşan yapay bir kabus tasarlayalım.
Kulağa eğlenceli mi geliyor? HAYIR? Çok kötü.
İlk olarak, bu geniş bürokratik makinedeki en küçük dişli ile başlayın: Bürokrat.
Bir Bürokrat şunlara sahip olmalıdır:
• Sabit bir ad.
• Ve 1 (mümkün olan en yüksek not) ile 150 (mümkün olan en düşük not) arasında değişen bir not
seviye).
Geçersiz bir not kullanarak bir Bürokrat örneğini oluşturmaya yönelik herhangi bir girişim bir istisna atmalıdır:
ya bir Bureaucrat::GradeTooHighException
ya da bir Bureaucrat::GradeTooLowException.

Bu özniteliklerin her ikisi için de alıcılar sağlayacaksınız: getName() ve getGrade().
Bürokrat notunu artırmak veya azaltmak için iki üye işlevi de uygulayın.
Derece aralığın dışındaysa, her ikisi de oluşturucuyla aynı istisnaları atar.

Hatırlamak. 1. sınıf en yüksek ve 150 en düşük olduğu için,
3. dereceyi artırmak bürokrata 2. not vermelidir.

Fırlatılan istisnalar, try ve catch blokları kullanılarak yakalanabilir olmalıdır:
	try
	{
	//bürokratlarla bir şeyler yapalım
	}
	catch (std::exception & e)
	{
	//stisnayı ele al
	}

Gibi bir şey yazdırmak için ekleme («) operatörünün aşırı yüklenmesini uygulayacaksınız.
(açılı ayraçlar olmadan):
<name>, bureaucrat grade <grade>.
Her zamanki gibi, her şeyin beklendiği gibi çalıştığını kanıtlamak için bazı testler yapın.
*/

#include "Bureaucrat.hpp"

int	main ( void )
{
	try{
		Bureaucrat	A;
		Bureaucrat	B("BBBBB", 50);
		Bureaucrat	C("CCCCC", 50);
		std::cout << A << std::endl;
		std::cout << B << std::endl;
	}catch ( const Bureaucrat::GradeTooHighException &e ){
		std::cout << e.what() << std::endl;
	}catch ( const Bureaucrat::GradeTooLowException &e ){
		std::cout << e.what() << std::endl;
	}
	return (0);
}
