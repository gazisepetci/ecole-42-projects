/*
Now that you have bureaucrats, let’s give them something to do. What better activity
could there be than the one of filling out a stack of forms?
Then, let’s make a Form class. It has:
• A constant name.
• A boolean indicating whether it is signed (at construction, it’s not).
• A constant grade required to sign it.
• And a constant grade required to execute it.
All these attributes are private, not protected.
The grades of the Form follow the same rules that apply to the Bureaucrat. Thus,
the following exceptions will be thrown if a form grade is out of bounds:
Form::GradeTooHighException and Form::GradeTooLowException.
Same as before, write getters for all attributes and an overload of the insertion («)
operator that prints all the form’s informations.

Add also a beSigned() member function to the Form that takes a Bureaucrat as
parameter. It changes the form status to signed if the bureaucrat’s grade is high enough
(higher or egal to the required one). Remember, grade 1 is higher than grade 2.
If the grade is too low, throw a Form::GradeTooLowException.
Lastly, add a signForm() member function to the Bureaucrat. If the form got signed,
it will print something like:
<bureaucrat> signed <form>
Otherwise, it will print something like:
<bureaucrat> couldn’t sign <form> because <reason>.
Implement and turn in some tests to ensure everything works as expected.

*/

/*
Artık bürokratlarınız olduğuna göre, onlara yapacak bir şeyler verelim. Bir yığın form doldurmaktan daha iyi bir aktivite olabilir mi?
Ardından bir Form sınıfı oluşturalım. Şunlara sahiptir:
• Sabit bir ad.
• İmzalanıp imzalanmadığını gösteren bir boole (yapım aşamasında değil).
• İmzalamak için gereken sabit bir not.
• Ve bunu gerçekleştirmek için gereken sabit not.
Tüm bu özellikler özeldir, korunmaz.
Formun notları, Bürokrat için geçerli olan aynı kuralları izler. Böylece,
Bir form notu sınırların dışındaysa aşağıdaki istisnalar atılır:
Form::GradeTooHighException ve Form::GradeTooLowException.
Daha önce olduğu gibi, tüm öznitelikler için alıcılar yazın ve
tüm formun bilgilerini basan ekleme («) operatörünün aşırı yüklenmesi.

Parametre olarak Bürokrat alan Forma ayrıca bir beSigned() üye işlevi ekleyin.
Bürokratın notu yeterince yüksekse (gerekli olandan daha yüksek veya eşit) form durumunu imzalı olarak değiştirir.
Unutmayın, 1. derece 2. dereceden daha yüksektir.
Not çok düşükse bir Form::GradeTooLowException atın. Son olarak, Bureaucrat'a bir signForm() üye işlevi ekleyin. Form imzalandıysa,
şöyle bir şey yazdıracak:
<bureaucrat> signed <form>
Aksi takdirde, şöyle bir şey yazdıracaktır:
<bureaucrat> couldn’t sign <form> because <reason>.
Her şeyin beklendiği gibi çalıştığından emin olmak için bazı testler uygulayın ve teslim edin.
*/

#include "Bureaucrat.hpp"
#include "Form.hpp"

int	main ( void )
{
	try{
		Bureaucrat	A;
		Bureaucrat	B("B_B", 15);
		Bureaucrat	C("C_C", 75);
		Form	form1;
		Form	form2 ("form2", 15, 100);
		std::cout << A << std::endl;
		std::cout << B << std::endl;
		std::cout << form1 << std::endl;
		std::cout << form2 << std::endl;

		B.signForm (form2);
		std::cout << form1 << std::endl;
		std::cout << form2 << std::endl;

	}catch ( const Bureaucrat::GradeTooHighException& e ){
		std::cout << e.what() << std::endl;
	}catch ( const Bureaucrat::GradeTooLowException& e ){
		std::cout << e.what() << std::endl;
	}catch ( const Form::GradeTooHighException& e ){
		std::cout << e.what() << std::endl;
	}catch ( const Form::GradeTooLowException& e ){
		std::cout << e.what() << std::endl;
	}
	
	return (0);
}
