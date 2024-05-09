/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uercan <uercan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 15:30:52 by uercan            #+#    #+#             */
/*   Updated: 2023/07/20 12:40:44 by uercan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
A first easy exercise is the way to start off on the right foot.
Write a function template easyfind that accepts a type T. It takes two parameters.
The first one has type T and the second one is an integer.
Assuming T is a container of integers, this function has to find the first occurrence
of the second parameter in the first parameter.
If no occurrence is found, you can either throw an exception or return an error value
of your choice. If you need some inspiration, analyze how standard containers behave.
Of course, implement and turn in your own tests to ensure everything works as expected.
You don’t have to handle associative containers.
*/

/*

"Container" (konteyner), C++ Standard Kütüphanesi'nde bulunan bir terimdir.
Verileri depolamak, yönetmek ve erişmek için kullanılan bir yapı veya sınıfı ifade eder. 
C++'ta çeşitli konteyner sınıfları mevcuttur ve farklı amaçlar için farklı özelliklere sahiptirler.
( vector, list, deque,map, set, multimap, multiset,stack, queue, priority_queue)

-at() = Parametre olarak belirtilen index değerine karşılık gelen elemanı döndürür. örn: vect_int_item.at(0); ilk elemanı döndürür.
-front() = Vectorün en başında yer alan elemanı döndürür.
-back() = Vectorün en sonunda yer alan elemanı döndürür.
-swap() = Vectorler arasında elemanları değiş tokuş eder.
Örnek kullanım:
vector<int> vect1(10,44);
vector<int> vect2(15); //15 elemanlı.
vect1.swap(vect2);
Bu kullanım sonucunda vect1 içeriği eleman olarak 0(sıfır) değerleri,vect2 içeriği elemanları ise 44 değerler yer alacaktır.
Ayrıca swap sonucunda vectorlere ait eski boyutlar da yeni elemanlara göre değişecektir. Yani vect2 boyutu 10 olarak değişmiştir.
-push_back() = Vectorün sonuna eleman ekler.
-pop_back() = Vectorden son elemanı çıkarır/siler.
-empty() = Vectorün boş olup olmadığını belirleyen bir bool durum döndürür.
-insert() = Belirtilen bir pozisyona yeni eleman ekler.
-erase() = Belirtilen bir elemanı vectorden siler.
-resize() = Vectorün boyutunu değiştirir.
-clear() = Vectordeki tüm elemanları siler.
-size() = Vectordeki eleman sayısını belirtilen bir değer döndürür.
-capacity() = Vectorün mevcut kapasitesini belirten bir değer döndürür.
-assign() = Vecktore yeni değerler atamak için kullanılır. En temel haliyle iki adet parametre alır. İlk parametre eleman sayısı,ikinci parametrede atanacak değer belirlenir.
Örnek kullanım:
vect.assign(10,”A”); //10 adet A değeri atanmıştır.

*/
/*
İlk kolay egzersiz, sağ ayakla başlamanın yoludur.
T tipini kabul eden bir fonksiyon şablonu easyfind yazın. İki parametre alır.
	İlki T tipine sahiptir ve ikincisi bir tamsayıdır.
T'nin bir tamsayı container olduğunu varsayarsak, bu fonksiyon ikinci parametrenin ilk geçtiği yeri birinci parametrede bulmalıdır.

Herhangi bir oluşum bulunamazsa, bir istisna atabilir veya seçtiğiniz bir hata değeri döndürebilirsiniz.
İlhama ihtiyacınız varsa, standart container nasıl davrandığını analiz edin.

Elbette, her şeyin beklendiği gibi çalıştığından emin olmak için kendi testlerinizi uygulayın ve teslim edin.

İlişkisel container ile  uğraşmak zorunda değilsiniz.
*/

#include "easyfind.hpp"

int	main ( void )
{
	std::vector<int> vec(5, 42);
	easyfind (vec, 4);
	std::list<int> lst;
	lst.push_back(123);
	lst.push_back(456);
	lst.push_back(7);
	lst.push_back(8);
	easyfind (lst, 8);
	return (0);
}
