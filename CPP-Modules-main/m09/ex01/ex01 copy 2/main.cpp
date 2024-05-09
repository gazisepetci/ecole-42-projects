#include "RPN.hpp"

/*
Bu kısıtlamalara sahip bir program oluşturmalısınız:
• Programın adı RPN'dir.
• Programınız, ters çevrilmiş bir Lehçe matematiksel ifadeyi bağımsız değişken olarak almalıdır.
• Bu işlemde kullanılan ve argüman olarak iletilen sayılar her zaman 10'dan küçük olacaktır.
Hesaplamanın kendisi ve sonuç da bu kuralı dikkate almaz.
• Programınız bu ifadeyi işlemeli ve standart çıktıda doğru sonucu vermelidir.
• Programın yürütülmesi sırasında bir hata oluşursa, standart çıktıda bir hata mesajı görüntülenmelidir.
• Programınız şu belirteçlerle işlemleri gerçekleştirebilmelidir: "+ - / *".

Bu alıştırmayı doğrulamak için kodunuzda en az bir kapsayıcı kullanmalısınız.
Parantezleri veya ondalık sayıları yönetmenize gerek yoktur.
İşte standart kullanıma bir örnek:
$> ./RPN "8 9 * 9 - 9 - 9 - 4 - 1 +"
42
$> ./RPN "7 7 * 7 -"
42
$> ./RPN "1 2 * 2 / 2 * 2 4 - +"
0
$> ./RPN "(1 + 1)"
Error

Uyarı: Bir önceki alıştırmada kullandığınız kap(lar) burada yasaklanmıştır.
Bu alıştırmayı doğrulamak için kullandığınız kap(lar) bu modülün geri kalanında kullanılamayacaktır.
*/

int	main ( int argc, char ** argv)
{
	if (argc < 2)
		std::cerr << "Error: Invalid argument!\n";
	else
		setArgument(argv[1]);
	return (0);
}