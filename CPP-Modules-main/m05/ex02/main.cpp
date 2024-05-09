/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uercan <uercan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 14:08:36 by uercan            #+#    #+#             */
/*   Updated: 2023/06/10 15:11:52 by uercan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Since you now have basic forms, it’s time to make a few more that actually do something.
In all cases, the base class AForm must be an abstract class, and therefore should be
renamed AForm. Keep in mind the form’s attributes need to remain private and that
they are in the base class.
Add the following concrete classes:
• ShrubberyCreationForm: Required grades: sign 145, exec 137
Create a file <target>_shrubbery in the working directory, and writes ASCII trees
inside it.
• RobotomyRequestForm: Required grades: sign 72, exec 45
Makes some drilling noises. Then, informs that <target> has been robotomized
successfully 50% of the time. Otherwise, informs that the robotomy failed.
• PresidentialPardonForm: Required grades: sign 25, exec 5
Informs that <target> has been pardoned by Zaphod Beeblebrox.
All of them take only one parameter in their constructor: the target of the form. For
example, "home" if you want to plant shrubbery at home.

Now, add the execute(Bureaucrat const & executor) const member function to
the base form and implement a function to execute the form’s action of the concrete
classes. You have to check that the form is signed and that the grade of the bureaucrat
attempting to execute the form is high enough. Otherwise, throw an appropriate exception.
Whether you want to check the requirements in every concrete class or in the base
class (then call another function to execute the form) is up to you. However, one way is
prettier than the other one.
Lastly, add the executeForm(AForm const & form) member function to the Bureaucrat. It must attempt to execute the form. If it’s successful, print something like:
<bureaucrat> executed <form>
If not, print an explicit error message.
Implement and turn in some tests to ensure everything works as expected.



Artık temel formlara sahip olduğunuza göre,
gerçekten bir şeyler yapan birkaç tane daha yapmanın zamanı geldi.

Her durumda, AForm temel sınıfı abstract bir sınıf olmalıdır ve
bu nedenle AForm olarak yeniden adlandırılmalıdır.
AForm özniteliklerinin private kalması gerektiğini ve temel sınıfta olduklarını unutmayın.

Aşağıdaki somut sınıfları ekleyin:
Çalı Oluşturma Formu
• ShrubberyCreationForm: Gerekli notlar: sign 145, exec 137 Çalışma dizininde bir <target>_shrubbery dosyası oluşturun ve içine ASCII ağaçları yazar.

Robotomy Talep Formu
• RobotomyRequestForm: Gerekli notlar: imza 72, yürütme 45
Bazı delme sesleri çıkarır. Ardından, <target> öğesinin zamanın %50'sinde başarıyla robotize edildiğini bildirir. Aksi halde,
robotomy'nin başarısız olduğunu bildirir.

Cumhurbaşkanlığı Af Formu
• PresidentialPardonForm: Gerekli notlar: imza 25, yürütme 5 <target> öğesinin Zaphod Beeblebrox tarafından affedildiğini bildirir.
Hepsi yapıcılarında yalnızca bir parametre alır: formun hedefi. Örneğin, evde çalı dikmek istiyorsanız "ev".

Şimdi, executive(Bureaucrat const & executor) const üye işlevini temel forma ekleyin ve formun somut sınıfların eylemini yürütmek için bir işlev uygulayın.
Formun imzalanıp imzalanmadığını ve formu uygulamaya çalışan bürokratın notunun yeterince yüksek olup olmadığını kontrol etmelisiniz.
Aksi takdirde, uygun bir istisna atın.
Her somut sınıftaki veya temel sınıftaki gereksinimleri kontrol etmek isteyip istemediğiniz (daha sonra formu yürütmek için başka bir işlevi çağırın)
size kalmış. Ancak, bir yol diğerinden daha güzel. Son olarak, executiveForm(AForm const & form) üye işlevini Bürokrat'a ekleyin.
Formu yürütmeye çalışmalıdır. Başarılı olursa, şöyle bir şey yazdırın:
<bureaucrat> executed <form>
Değilse, açık bir hata mesajı yazdırın.
Her şeyin beklendiği gibi çalıştığından emin olmak için bazı testler uygulayın ve teslim edin.
*/

#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

int	main ( void )
{
	{
		try
		{
			Bureaucrat b1("b1", 5);
			std::cout << b1 << std::endl << std::endl;

			PresidentialPardonForm P("p");
			RobotomyRequestForm R("r");
			ShrubberyCreationForm S("s");

			std::cout << P << std::endl;
			std::cout << R << std::endl;
			std::cout << S << std::endl;

			b1.signForm (P);
			b1.signForm (R);
			b1.signForm (S);

			std::cout << P << std::endl;
			std::cout << R << std::endl;
			std::cout << S << std::endl;

			b1.executeForm ( P );
			b1.executeForm ( R );
			b1.executeForm ( S );
		}catch(const std::exception &e){
			std::cerr << e.what() << std::endl;
		}catch(const std::string &e){
			std::cerr << e << std::endl;
		}

	}
	std::cout
		<<"\n       _"<< std::endl
		<<"      |)`"<< std::endl
		<<"      | |"<< std::endl
		<<"      | |_____"<< std::endl
		<<"     /    (]__)"<< std::endl
		<<"    /    (]___)"<< std::endl
		<<"   /    (]___)"<< std::endl
		<<"      ___(]_)"<< std::endl
		<<"     /"<< std::endl
		<<"    /"<< std::endl;
	return (0);
}
