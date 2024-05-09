/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uercan <uercan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 17:45:22 by uercan            #+#    #+#             */
/*   Updated: 2023/07/04 11:39:28 by uercan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Implement a static class Serialization with the following methods:
uintptr_t serialize(Data* ptr);
It takes a pointer and converts it to the unsigned integer type uintptr_t.
Data* deserialize(uintptr_t raw);
It takes an unsigned integer parameter and converts it to a pointer to Data.
Write a program to test that your class works as expected.
You must create a non-empty (it means it has data members) Data structure.
Use serialize() on the address of the Data object and pass its return value to
deserialize(). Then, ensure the return value of deserialize() compares equal to the
original pointer.
Do not forget to turn in the files of your Data structure.
*/
/*
Aşağıdaki yöntemlerle bir statik sınıf Serileştirici uygulayın:

uintptr_t serialize(Data* ptr);
Bir işaretçi alır ve onu uintptr_t işaretsiz tamsayı türüne dönüştürür.

Data* deserialize(uintptr_t raw);
İşaretsiz bir tamsayı parametresi alır ve onu Data işaretçisine dönüştürür.

Sınıfınızın beklendiği gibi çalıştığını test etmek için bir program yazın.
Boş olmayan (veri üyeleri olduğu anlamına gelir) bir Veri yapısı (Data structure) oluşturmalısınız.

Data nesnesinin adresinde serialize() işlevini kullanın ve dönüş değerini deserialize() işlevine iletin.

Ardından, deserialize() dönüş değerinin orijinal işaretçiye eşit olduğundan emin olun.

Veri yapınızın dosyalarını teslim etmeyi unutmayın.
*/

/*

"Reflection "bir sürecin kendi yapısını ve davranışını inceleme,
iç gözlem yapma ve değiştirme yeteneği" olarak tanımlanır.

reinterpret_cast; dönüştürmeden önceki ve sonraki veri türleri farklı olsa bile,
bazı veri türündeki bir işaretçiyi başka bir veri türündeki işaretçiye dönüştürmek için kullanılır.

reinterpret_cast kullanmanın amacı 
 

reinterpret_cast, çok özel ve tehlikeli bir döküm operatörü türüdür. Ve uygun veri tipini kullanarak kullanılması önerilir, yani (işaretçi veri tipi, orijinal veri tipi ile aynı olmalıdır).
Herhangi bir işaretçiyi başka herhangi bir veri türüne yazabilir.
Bitlerle çalışmak istediğimizde kullanılır.
Bu tür bir döküm kullanırsak, taşınabilir olmayan bir ürün haline gelir. Bu nedenle zorunlu olmadıkça bu kavramın kullanılmaması önerilmektedir.
Yalnızca herhangi bir işaretçiyi orijinal türüne göre tiplendirmek için kullanılır.
Boole değeri tamsayı değerine dönüştürülecektir, yani yanlış için 0 ve doğru için 1.
*/


#include "Serialization.hpp"

int	main ( void )
{
	Data *data = new Data();
	data->a = 42;
	data->b = 42.12f;

	unsigned long ptrVal = reinterpret_cast<unsigned long>(data);
	std::cout << "Different Use: " << ptrVal << std::endl;

	Data *pointer = reinterpret_cast<Data*>(ptrVal);
	std::cout << "Different Use: " << pointer->a << ", " << pointer->b << std::endl;

	uintptr_t raw = Serialization::serialize( data );
	std::cout << "Serialized Value: " << raw << std::endl;

	Data *ptr = Serialization::deserialize( raw );
	std::cout << "Deserialize Value: " << ptr->a << ", " << ptr->b << std::endl;

	delete data;

	return (0);
}