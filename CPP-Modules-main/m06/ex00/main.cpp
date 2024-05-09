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
Allowed functions : Any function to convert from a string to an int, a
float or a double. This will help, but won’t do the whole job.

Write a static class ScalarConverter that will contain a method "convert" takes as
parameter a string representation of a C++ literal in its most common form. This literal
must belong to one of the following a scalar types:
• char
• int
• float
• double
Except for char parameters, only the decimal notation will be used.
Examples of char literals: ’c’, ’a’, ...
To make things simple, please note that non displayable characters shouldn’t be used as
inputs. If a conversion to char is not displayable, prints an informative message.
Examples of int literals: 0, -42, 42...
Examples of float literals: 0.0f, -4.2f, 4.2f...
You have to handle these pseudo literals as well (you know, for science): -inff, +inff
and nanf.

Examples of double literals: 0.0, -4.2, 4.2...
You have to handle these pseudo literals as well (you know, for fun): -inf, +inf and nan.


Write a program to test that your class works as expected.
You have to first detect the type of the literal passed as parameter, convert it from
string to its actual type, then convert it explicitly to the three other data types. Lastly,
display the results as shown below.
If a conversion does not make any sense or overflows, display a message to inform
the user that the type conversion is impossible. Include any header you need in order to
handle numeric limits and special values.
./convert 0
char: Non displayable
int: 0
float: 0.0f
double: 0.0
./convert nan
char: impossible
int: impossible
float: nanf
double: nan
./convert 42.0f
char: '*'
int: 42
float: 42.0f
double: 42.0
*/
/*
İzin verilen işlevler : Bir dizeden int'e, bir kayan nokta veya çifte dönüştürülecek herhangi bir işlev. Bu yardımcı olacaktır, ancak tüm işi yapmayacaktır.

"convert" yöntemini içerecek statik bir sınıf ScalarConverter yazın, en yaygın biçiminde bir C++ hazır bilgisinin dize temsilini parametre olarak alır.
Bu hazır bilgi, aşağıdaki a skaler türlerinden birine ait olmalıdır:
• char
• int
• float
• double
char parametreleri dışında sadece ondalık gösterim kullanılacaktır.

Karakter değişmezlerine örnekler: 'c', 'a', ...
İşleri kolaylaştırmak için lütfen görüntülenemeyen karakterlerin giriş olarak kullanılmaması gerektiğini unutmayın.
Karaktere dönüştürme görüntülenemiyorsa bilgilendirici bir mesaj yazdırır.

int hazır değerlerine örnekler: 0, -42, 42...
float değerlere örnekler: 0.0f, -4.2f, 4.2f...
Bu sözde değişmezleri de halletmelisiniz (biliyorsunuz, bilim için): -inff, +inff ve nanf.

Double değişmez örnekleri: 0.0, -4.2, 4.2...
Bu sözde değişmezleri de halletmelisiniz (bilirsiniz, eğlence için): -inf, +inf ve nan.

Sınıfınızın beklendiği gibi çalıştığını test etmek için bir program yazın.
Önce parametre olarak iletilen hazır bilginin türünü algılamanız, onu dizeden gerçek türüne dönüştürmeniz,
ardından onu açıkça diğer üç veri türüne dönüştürmeniz gerekir. Son olarak, sonuçları aşağıda gösterildiği gibi görüntüleyin.

./convert 0
char: Non displayable
int: 0
float: 0.0f
double: 0.0

./convert nan
char: impossible
int: impossible
float: nanf
double: nan

./convert 42.0f
char: '*'
int: 42
float: 42.0f
double: 42.0
*/

#include "ScalarConverter.hpp"

int	main ( int argc, char **argv)
{
	if (argc != 2)
	{
		std::cout << "Takes two input!" << std::endl;
		return (1);
	}
	try
	{
		ScalarConverter::ScalarConvertingString(argv[1]);
	}
	catch(std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
	return (0);
}