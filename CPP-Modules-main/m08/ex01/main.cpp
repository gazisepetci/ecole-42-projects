/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uercan <uercan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 18:02:14 by uercan            #+#    #+#             */
/*   Updated: 2023/07/20 13:05:08 by uercan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Develop a Span class that can store a maximum of N integers. N is an unsigned int
variable and will be the only parameter passed to the constructor.
This class will have a member function called addNumber() to add a single number
to the Span. It will be used in order to fill it. Any attempt to add a new element if there
are already N elements stored should throw an exception.
Next, implement two member functions: shortestSpan() and longestSpan()
They will respectively find out the shortest span or the longest span (or distance, if
you prefer) between all the numbers stored, and return it. If there are no numbers stored,
or only one, no span can be found. Thus, throw an exception.
Of course, you will write your own tests and they will be way more thorough than the
ones below. Test your Span at least with a minimum of 10 000 numbers. More would be
even better.
*/

/*
En fazla N tamsayı depolayabilen bir Span sınıfı geliştirin.
N, işaretsiz bir int değişkenidir ve yapıcıya iletilen tek parametre olacaktır.

Bu sınıfın, Span'a tek bir sayı eklemek için addNumber() adlı bir üye işlevi olacaktır.
Doldurmak için kullanılacaktır.
Halihazırda depolanan N öğe varsa, yeni bir öğe eklemeye yönelik herhangi bir girişim bir istisna atmalıdır.

Ardından, iki üye işlevi uygulayın: shortestSpan() ve LongSpan()

Depolanan tüm sayılar arasındaki en kısa aralığı veya en uzun aralığı (veya tercih ederseniz mesafeyi)
bulup geri getireceklerdir. Depolanan numara yoksa veya yalnızca bir tane varsa, aralık bulunamaz.
Böylece, bir istisna atın.

Elbette kendi testlerinizi yazacaksınız ve bunlar aşağıdaki testlerden çok daha kapsamlı olacak.
Span'ınızı en az 10 000 sayı ile test edin. Daha fazlası daha da iyi olacaktır.


Running this code:
int main()
{
Span sp = Span(5);
sp.addNumber(6);
sp.addNumber(3);
sp.addNumber(17);
sp.addNumber(9);
sp.addNumber(11);
std::cout << sp.shortestSpan() << std::endl;
std::cout << sp.longestSpan() << std::endl;
return 0;
}
Should output:
$> ./ex01
2
14

Son olarak, Span'ınızı bir dizi yineleyici kullanarak doldurmak harika olurdu.
addNumber()'a binlerce arama yapmak çok sinir bozucu.
Span'ınıza tek bir çağrıda birçok numara eklemek için bir üye işlevi uygulayın.
*/

#include "Span.hpp"

int main()
{
	// Span s1(4);
	// s1.addNumber(1);
	// s1.addNumber(5);
	// s1.addNumber(13);
	// s1.addNumber(42);
	// std::cout << s1.shortestSpan() << std::endl;
	
	Span sp = Span(5);
	sp.addNumber(0);
	sp.addNumber(3);
	sp.addNumber(17);
	sp.addNumber(9);
	sp.addNumber(142);

	sp.addNumber(1234);
	sp.addNumber(131);
	std::cout << "min dis: " << sp.shortestSpan() << std::endl;
	std::cout << "max dis: " << sp.longestSpan() << std::endl;
	return 0;
}
