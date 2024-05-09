/*
You have to create a program which outputs the value of a certain amount of bitcoin
on a certain date.
This program must use a database in csv format which will represent bitcoin price
over time. This database is provided with this subject.
The program will take as input a second database, storing the different prices/dates
to evaluate.
Your program must respect these rules:
• The program name is btc.
• Your program must take a file as argument.
• Each line in this file must use the following format: "date | value".
• A valid date will always be in the following format: Year-Month-Day.
• A valid value must be either a float or a positive integer between 0 and 1000.
You must use at least one container in your code to validate this
exercise. You should handle possible errors with an appropriate
error message.
Here is an example of an input.txt file:
$> head input.txt
date | value
2011-01-03 | 3
2011-01-03 | 2
2011-01-03 | 1
2011-01-03 | 1.2
2011-01-09 | 1
2012-01-11 | -1
2001-42-42
2012-01-11 | 1
2012-01-11 | 2147483648
$>
Your program will use the value in your input file.
Your program should display on the standard output the result of the value multiplied
by the exchange rate according to the date indicated in your database.
If the date used in the input does not exist in your DB then you
must use the closest date contained in your DB. Be careful to use the
lower date and not the upper one.
The following is an example of the program’s use.
$> ./btc
Error: could not open file.
$> ./btc input.txt
2011-01-03 => 3 = 0.9
2011-01-03 => 2 = 0.6
2011-01-03 => 1 = 0.3
2011-01-03 => 1.2 = 0.36
2011-01-09 => 1 = 0.32
Error: not a positive number.
Error: bad input => 2001-42-42
2012-01-11 => 1 = 7.1
Error: too large a number.
$>
Warning: The container(s) you use to validate this exercise will no
longer be usable for the rest of this module.
*/

/*
Belirli bir tarihte belirli miktarda bitcoin değerini veren bir program oluşturmalısınız.
Bu program, zaman içinde bitcoin fiyatını temsil edecek csv formatında bir veritabanı kullanmalıdır. Bu veri tabanı bu konu ile birlikte sağlanmaktadır.
Program, değerlendirmek üzere farklı fiyatları/tarihleri saklayan ikinci bir veri tabanını girdi olarak alacaktır.
Programınız şu kurallara uymalıdır:
• Programın adı btc'dir.
• Programınız argüman olarak bir dosya almalıdır.
• Bu dosyadaki her satır şu biçimi kullanmalıdır: "tarih | değer"     "date | value".
• Geçerli bir tarih her zaman şu formatta olacaktır: Yıl-Ay-Gün     Year-Month-Day..
• Geçerli bir değer, kayan nokta veya 0 ile 1000 arasında pozitif bir tam sayı olmalıdır.

Bunu doğrulamak için kodunuzda en az bir kapsayıcı kullanmalısınız.
egzersiz yapmak. Olası hataları uygun bir hata mesajı ile ele almalısınız.

İşte bir input.txt dosyası örneği:
$> head input.txt
date | value
2011-01-03 | 3
2011-01-03 | 2
2011-01-03 | 1
2011-01-03 | 1.2
2011-01-09 | 1
2012-01-11 | -1
2001-42-42
2012-01-11 | 1
2012-01-11 | 2147483648
$>

Programınız giriş dosyanızdaki değeri kullanacaktır.
Programınız, veri tabanınızda belirtilen tarihe göre değerin döviz kuru ile çarpımı sonucunu standart çıktıda göstermelidir.
Girdide kullanılan tarih DB'nizde yoksa, DB'nizde bulunan en yakın tarihi kullanmalısınız. Üst tarihi değil alt tarihi kullanmaya dikkat edin.
Aşağıda programın kullanımına bir örnek verilmiştir.
$> ./btc
Error: could not open file.
$> ./btc input.txt
2011-01-03 => 3 = 0.9
2011-01-03 => 2 = 0.6
2011-01-03 => 1 = 0.3
2011-01-03 => 1.2 = 0.36
2011-01-09 => 1 = 0.32
Error: not a positive number.
Error: bad input => 2001-42-42
2012-01-11 => 1 = 7.1
Error: too large a number.
$>
Uyarı: Bu alıştırmayı doğrulamak için kullandığınız kap(lar) artık bu modülün geri kalanında kullanılamayacaktır.
*/

#include "BitcoinExchange.hpp"

int	main (int argc, char **argv)
{
	try
	{
		std::cout << "------------------------------\n";
		btc	Btc;
		Btc.setDataBase(argc);
		Btc.setInput(argv[1]);
		std::cout << "------------------------------\n";
	}catch(const std::exception& e){
		std::cerr << e.what() << std::endl;
	}
	return (0);
}