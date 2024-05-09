#include <iostream>
#include "Array.hpp"

#define MAX_VAL 750

/*
Develop a class template Array that contains elements of type T and that implements
the following behavior and functions:
• Construction with no parameter: Creates an empty array.
• Construction with an unsigned int n as a parameter: Creates an array of n elements
initialized by default.
Tip: Try to compile int * a = new int(); then display *a.
• Construction by copy and assignment operator. In both cases, modifying either the original array or its copy after copying musn’t affect the other array.
• You MUST use the operator new[] to allocate memory. Preventive allocation (allocating memory in advance) is forbidden. Your program must never access nonallocated memory.
• Elements can be accessed through the subscript operator: [ ].
• When accessing an element with the [ ] operator, if its index is out of bounds, an std::exception is thrown.
• A member function size() that returns the number of elements in the array. This member function takes no parameter and musn’t modify the current instance.
As usual, ensure everything works as expected and turn in a main.cpp file that contains your tests.
*/

/*
T türündeki öğeleri içeren ve uygulayan bir sınıf şablonu Dizisi geliştirin
aşağıdaki davranış ve işlevler:
• Parametresiz oluşturma: Boş bir dizi oluşturur.
• Parametre olarak işaretsiz bir int n ile oluşturma: n öğelik bir dizi oluşturur
varsayılan olarak başlatıldı.
İpucu: int * a = new int();'i derlemeye çalışın. ardından *a'yı görüntüleyin.
• Kopyalama ve atama operatörü tarafından yapılanma. Her iki durumda da,
kopyalamadan sonra orijinal dizinin veya onun kopyasının değiştirilmesi diğer diziyi etkilememelidir.
• Belleği ayırmak için new[] operatörünü KULLANMALISINIZ. Önleyici ayırma (önceden bellek ayırma) yasaktır.
Programınız asla ayrılmamış belleğe erişmemelidir.
• Öğelere alt simge operatörü aracılığıyla erişilebilir: [ ].
• [ ] operatörüyle bir elemana erişirken, indeksi sınırların dışındaysa, bir std::exception atılır.
• Dizideki öğelerin sayısını döndüren bir üye işlev size(). 
Bu üye işlev hiçbir parametre almaz ve geçerli örneği değiştirmemelidir.
Her zamanki gibi, her şeyin beklendiği gibi çalıştığından emin olun ve testlerinizi içeren bir main.cpp dosyası açın.
*/


int main(int, char**)
{
    Array<int> numbers(MAX_VAL);
    int* mirror = new int[MAX_VAL];
    srand(time(NULL));
    for (int i = 0; i < MAX_VAL; i++)
    {
        const int value = rand();
        numbers[i] = value;
        mirror[i] = value;
    }
    //SCOPE
    {
        Array<int> tmp = numbers;
        Array<int> test(tmp);
    }

    for (int i = 0; i < MAX_VAL; i++)
    {
        if (mirror[i] != numbers[i])
        {
            std::cerr << "didn't save the same value!!" << std::endl;
            return 1;
        }
    }
    try
    {
        numbers[-2] = 0;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    try
    {
        numbers[MAX_VAL] = 0;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    for (int i = 0; i < MAX_VAL; i++)
    {
        numbers[i] = rand();
    }
    delete [] mirror;
    return 0;
}
