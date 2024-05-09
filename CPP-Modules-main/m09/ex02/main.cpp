

/*You must create a program with these constraints:
• The name of the program is PmergeMe.
• Your program must be able to use a positive integer sequence as argument.
• Your program must use the merge-insert sort algorithm to sort the positive integer
sequence.
To clarify, yes, you need to use the Ford-Johnson algorithm.
• If an error occurs during program execution, an error message should be displayed
on the standard output.
You must use at least two different containers in your code to
validate this exercise. Your program must be able to handle at
least 3000 different integers.

It is strongly advised to implement your algorithm for each container
and thus to avoid using a generic function.
Here are some additional guidelines on the information you should display line by line
on the standard output:
• On the first line you must display an explicit text followed by the unsorted positive
integer sequence.
• On the second line you must display an explicit text followed by the sorted positive
integer sequence.
• On the third line you must display an explicit text indicating the time used by
your algorithm by specifying the first container used to sort the positive integer
sequence.
• On the last line you must display an explicit text indicating the time used by
your algorithm by specifying the second container used to sort the positive integer
sequence.
The format for the display of the time used to carry out your sorting
is free but the precision chosen must allow to clearly see the
difference between the two containers used.
Here is an example of a standard use:
$> ./PmergeMe 3 5 9 7 4
Before: 3 5 9 7 4
After: 3 4 5 7 9
Time to process a range of 5 elements with std::[..] : 0.00031 us
Time to process a range of 5 elements with std::[..] : 0.00014 us
$> ./PmergeMe `shuf -i 1-100000 -n 3000 | tr "\n" " "`
Before: 141 79 526 321 [...]
After: 79 141 321 526 [...]
Time to process a range of 3000 elements with std::[..] : 62.14389 us
Time to process a range of 3000 elements with std::[..] : 69.27212 us
$> ./PmergeMe "-1" "2"
Error
$> # For OSX USER:
$> ./PmergeMe `jot -r 3000 1 100000 | tr '\n' ' '`
[...]
$>
The indication of the time is deliberately strange in this example.
Of course you have to indicate the time used to perform all your
operations, both the sorting part and the data management part.

Warning: The container(s) you used in the previous exercises are
forbidden here.
The management of errors related to duplicates is left to your
discretion.
*/

/*
Bu kısıtlamalara sahip bir program oluşturmalısınız:
• Programın adı PmergeMe'dir.
• Programınız pozitif bir tamsayı dizisini bağımsız değişken olarak kullanabilmelidir.
• Programınız, pozitif tamsayı sırasını sıralamak için birleştirme-ekleme sıralama algoritmasını kullanmalıdır.
!Açıklığa kavuşturmak için, evet, Ford-Johnson algoritmasını kullanmanız gerekiyor

• Programın yürütülmesi sırasında bir hata oluşursa, standart çıktıda bir hata mesajı görüntülenmelidir.

!Bu alıştırmayı doğrulamak için kodunuzda en az iki farklı kap kullanmalısınız.
Programınız en az 3000 farklı tamsayı işleyebilmelidir.

Algoritmanızı her kapsayıcı için uygulamanız
ve böylece genel bir işlev kullanmaktan kaçınmanız şiddetle tavsiye edilir.
Standart çıktıda satır satır görüntülemeniz gereken bilgilerle ilgili bazı ek yönergeler şunlardır:
• İlk satırda açık bir metin ve ardından sıralanmamış pozitif tamsayı dizisini görüntülemeniz gerekir.
• İkinci satırda, açık bir metni ve ardından sıralanmış pozitif tamsayı dizisini görüntülemeniz gerekir.
• Üçüncü satırda, pozitif tamsayı dizisini sıralamak için kullanılan ilk kapsayıcıyı belirterek,
algoritmanız tarafından kullanılan zamanı gösteren açık bir metin göstermelisiniz.
• Son satırda, pozitif tamsayı dizisini sıralamak için kullanılan ikinci kapsayıcıyı belirterek,
algoritmanız tarafından kullanılan zamanı gösteren açık bir metin göstermelisiniz.

İşte standart bir kullanım örneği:
$> ./PmergeMe 3 5 9 7 4
Before: 3 5 9 7 4
After: 3 4 5 7 9
Time to process a range of 5 elements with std::[..] : 0.00031 us
Time to process a range of 5 elements with std::[..] : 0.00014 us
$> ./PmergeMe `shuf -i 1-100000 -n 3000 | tr "\n" " "`
Before: 141 79 526 321 [...]
After: 79 141 321 526 [...]
Time to process a range of 3000 elements with std::[..] : 62.14389 us
Time to process a range of 3000 elements with std::[..] : 69.27212 us
$> ./PmergeMe "-1" "2"
Error
$> # For OSX USER:
$> ./PmergeMe `jot -r 3000 1 100000 | tr '\n' ' '`
[...]
$>

Bu örnekte zamanın belirtilmesi kasıtlı olarak gariptir.
Elbette, hem sıralama kısmı hem de veri yönetimi kısmı olmak üzere tüm işlemlerinizi gerçekleştirmek için kullanılan süreyi belirtmeniz gerekir.
Uyarı: Önceki alıştırmalarda kullandığınız kap(lar) burada yasaklanmıştır.

Yinelemelerle ilgili hataların yönetimi sizin takdirinize bırakılmıştır.
*/

#include "PmergeMe.hpp"

int	main ( int argc, char **argv)
{
	PmergeMe pmergeme;
	pmergeme.setInputs(argc, argv);
	return (0);
}