/*
Implement a function template iter that takes 3 parameters and returns nothing.
• The first parameter is the address of an array.
• The second one is the length of the array.
• The third one is a function that will be call on every element of the array.
Turn in a main.cpp file that contains your tests. Provide enough code to generate a test executable.
Your iter function template must work with any type of array.
The third parametercan be an instantiated function template.
*/
/*
3 parametre alan ve hiçbir şey döndürmeyen bir function template iter uygulayın.

• İlk parametre bir dizinin adresidir.
• İkincisi, dizinin uzunluğudur.
• Üçüncüsü, dizinin her elemanında çağrılacak bir fonksiyondur.

Testlerinizi içeren bir main.cpp dosyası açın. Yürütülebilir bir test oluşturmak için yeterli kodu sağlayın.
Yineleme işlevi şablonunuz herhangi bir dizi türüyle çalışmalıdır.
Üçüncü parametre, somutlaştırılmış bir işlev şablonu olabilir.
*/

#include "iter.hpp"
#include "whatever.hpp"

int main(){

	int a[] = {1, 2, 3, 4, 5};
	//double b[] = {1.23, 4.567, 7.89};
	//char c[] = {'a', 'b', 'c', 'd', 'e'};

	iter (a, 5, print_temp);

	return (0);
}