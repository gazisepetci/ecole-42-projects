/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uercan <uercan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 17:16:32 by uercan            #+#    #+#             */
/*   Updated: 2023/06/03 03:29:49 by uercan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Constructors and destructors of each class must display specific messages.
Implement a Brain class. It contains an array of 100 std::string called ideas.
This way, Dog and Cat will have a private Brain* attribute.
Upon construction, Dog and Cat will create their Brain using new Brain();
Upon destruction, Dog and Cat will delete their Brain.
In your main function, create and fill an array of Animal objects. Half of it will
be Dog objects and the other half will be Cat objects. At the  of your program
execution, loop over this array and delete every Animal. You must delete directly dogs
and cats as Animals. The appropriate destructors must be called in the expected order.
Don’t forget to check for memory leaks.
A copy of a Dog or a Cat mustn’t be shallow. Thus, you have to test that your copies
are deep copies!
int main()
{
const Animal* j = new Dog();
const Animal* i = new Cat();
delete j;//should not create a leak
delete i;
...
return 0;
}
*/
/*
Her sınıfın yapıcıları ve yıkıcıları belirli mesajları göstermelidir.
Bir Beyin sınıfı uygulayın. ideas adı verilen 100 std::string dizisi içerir.
Bu şekilde, Dog ve Cat özel bir Brain* özelliğine sahip olacaktır.
Yapım üzerine, Dog ve Cat yeni Brain() kullanarak Beyinlerini oluşturacaklar;
Yok edildiğinde, Köpek ve Kedi Beyinlerini siler.

Ana işlevinizde, bir dizi Hayvan nesnesi oluşturun ve doldurun.
Bunun yarısı Dog nesneleri, diğer yarısı ise Cat nesneleri olacaktır.
Program yürütmenizin sonunda, bu dizinin üzerinden geçin ve her Animal'ı silin.
Hayvanlar olarak doğrudan köpekleri ve kedileri silmelisiniz.
Uygun yıkıcılar beklenen sırayla çağrılmalıdır.

Bellek sızıntılarını kontrol etmeyi unutmayın. Bir Köpek veya Kedinin kopyası sığ olmamalıdır.
Bu nedenle, kopyalarınızın derin kopyalar olduğunu test etmelisiniz!
*/

#include "Animal.hpp"
#include "Cat.hpp"
#include "Dog.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"

int main()
{
	{
		Animal *animals[5];
		for(int i = 0; i < 5; i++)
		{
			if (i % 2 == 0)
				animals[i] = new Dog();
			else
				animals[i] = new Cat();
		}
		for(int i = 0; i < 5; i++)
			delete animals[i];
		std::cout << std::endl << std::endl << std::endl;
	}
	{
		Cat b;
		std::cout << std::endl;
		b.getBrain()->setBrain(0, "one");
		std::cout << std::endl;
		Cat a = b;
		std::cout << std::endl;
		a.getBrain()->setBrain(0, "two");
	}
	return (0);
}