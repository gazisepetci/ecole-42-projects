/*
For every exercise, you have to provide the most complete tests you can.
Constructors and destructors of each class must display specific messages. Don’t use the
same message for all classes.
Start by implementing a simple base class called Animal. It has one protected
attribute:
• std::string type;
Implement a Dog class that inherits from Animal.
Implement a Cat class that inherits from Animal.
These two derived classes must set their type field depending on their name. Then,
the Dog’s type will be initialized to "Dog", and the Cat’s type will be initialized to "Cat".
The type of the Animal class can be left empty or set to the value of your choice.
Every animal must be able to use the member function:
makeSound()
It will print an appropriate sound (cats don’t bark).
Running this code should print the specific sounds of the Dog and Cat classes, not
the Animal’s.

<<<>>>
*/

/*
Her egzersiz için, yapabileceğiniz en eksiksiz testleri sağlamanız gerekir.
Her sınıfın yapıcıları ve yıkıcıları belirli mesajları göstermelidir. Tüm sınıflar için aynı mesajı kullanmayın.

Animal adında basit bir temel sınıf uygulayarak başlayın. Korumalı bir özniteliği vardır:
• std::string type;
Animal'dan miras alan bir Dog sınıfı uygulayın.
Animal'dan miras alan bir Cat sınıfı uygulayın.

Bu iki türetilmiş sınıf, tür alanlarını adlarına göre ayarlamalıdır.
Ardından, Köpeğin türü "Köpek" olarak başlatılacak ve Kedinin türü "Kedi" olarak başlatılacaktır.
Animal sınıfının türü boş bırakılabilir veya istediğiniz değere ayarlanabilir.
Her hayvan üye işlevini kullanabilmelidir:
makeSound()
Uygun bir ses çıkaracaktır (kediler havlamaz).
Bu kodu çalıştırmak, Hayvanın değil, Köpek ve Kedi sınıflarının belirli seslerini yazdırmalıdır.
int main()
{
const Animal* meta = new Animal();
const Animal* j = new Dog();
const Animal* i = new Cat();
std::cout << j->getType() << " " << std::endl;
std::cout << i->getType() << " " << std::endl;
i->makeSound(); //will output the cat sound!
j->makeSound();
meta->makeSound();
...
return 0;

Nasıl çalıştığını anladığınızdan emin olmak için WrongAnimal sınıfından miras alan bir WrongCat sınıfı uygulayın.
Animal ve Cat öğelerini yukarıdaki kodda yanlış olanlarla değiştirirseniz, WrongCat, WrongAnimal sesini çıkarmalıdır.
Yukarıda verilenlerden daha fazla test uygulayın ve teslim edin.
}
*/

#include "Animal.hpp"
#include "Cat.hpp"
#include "Dog.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"

int main()
{
	{
		const Animal* meta = new Animal();
		const Animal* dog = new Dog();
		const Animal* cat = new Cat();

		std::cout << "type: " << dog->getType() << " " << std::endl;
		std::cout << "type: " << cat->getType() << " " << std::endl;

		dog->makeSound();
		cat->makeSound(); //will output the cat sound!
		meta->makeSound();
		delete (meta);
		delete (dog);
		delete (cat);
	}
	{
		std::cout << std::endl;
		std::cout << std::endl;

		const WrongAnimal *meta = new WrongAnimal();
		const WrongAnimal *i = new WrongCat();

		std::cout << "type: " << i->getType() << " " << std::endl;
		std::cout << "type: " << meta->getType() << " " << std::endl;
		std::cout << "Wrong cat sound: "; i->makeSound();
		std::cout << "Wrong Animal sound: "; meta->makeSound();
		delete	i;
		delete	meta;
	}
	return 0;
}
