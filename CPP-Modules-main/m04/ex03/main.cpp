/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uercan <uercan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 04:34:49 by uercan            #+#    #+#             */
/*   Updated: 2023/06/03 08:34:57 by uercan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Interfaces C++98'de yoktur (C++20'de bile yoktur).
Bununla birlikte, saf soyut sınıflara genellikle arayüzler denir.
Bu nedenle, bu son alıştırmada, bu modülü aldığınızdan emin olmak için arayüzleri uygulamaya çalışalım.

Aşağıdaki AMeria sınıfının tanımını tamamlayın ve gerekli üye işlevleri uygulayın.
	class AMateria
	{
	protected:
	[...]
	public:
	AMateria(std::string const & type);
	[...]
	std::string const & getType() const; //Returns the materia type
	virtual AMateria* clone() const = 0;
	virtual void use(ICharacter& target);
	};

Materias somut sınıfları Ice and Cure'u uygulayın.
Türlerini ayarlamak için adlarını küçük harflerle
(Buz için "ice", Tedavi için "cure") kullanın.
Elbette, üye işlevleri clone() aynı türden yeni bir örnek döndürür
(yani, bir Ice Materia'yı klonlarsanız, yeni bir Ice Materia alırsınız).

use (ICarakter&) üye işlevi şunları gösterecektir:
• Ice: "* shoots an ice bolt at <name> *"
• Cure: "* heals <name>’s wounds *"
<name>, parametre olarak iletilen Karakterin adıdır. Köşeli parantezleri (< ve >) yazdırmayın.

Bir Materia'yı diğerine atarken, yazı tipini kopyalamak mantıklı değil.

Aşağıdaki arabirimi uygulayacak olan somut karakter sınıfını yazın:
	class ICharacter
	{
	public:
	virtual ~ICharacter() {}
	virtual std::string const & getName() const = 0;
	virtual void equip(AMateria* m) = 0;
	virtual void unequip(int idx) = 0;
	virtual void use(int idx, ICharacter& target) = 0;
	};

Karakter 4 yuvalık bir envantere sahiptir, bu da en fazla 4 Materia anlamına gelir.
Envanter yapım aşamasında boştur. Materiaları buldukları ilk boş yuvaya yerleştirirler.
Bu şu anlama gelir: 0. yuvadan 3. yuvaya. Dolu bir envantere bir Materia eklemeye çalışırlarsa veya
var olmayan bir Materia'yı kullanırlarsa/donatmazlarsa,
hiçbir şey yapmayın (ancak yine de hatalar yasaktır). unequip() üye işlevi Materia'yı SİLMEMELİDİR!

Karakterinizin yerde bıraktığı Materia'ları istediğiniz gibi kullanın.
unequip() veya başka bir şeyi çağırmadan önce adresleri kaydedin, ancak
bellek sızıntılarından kaçınmanız gerektiğini unutmayın.

use(int, ICharacter&) üye işlevinin yuva[idx]'te Materia'yı kullanması ve
hedef parametreyi AMeria::use işlevine iletmesi gerekir.

Karakterinizin envanteri her türlü AMeria'yı destekleyebilecek.

Karakterinizin adını parametre olarak alan bir oluşturucusu olmalıdır.
Bir Karakterin herhangi bir kopyası (kopya oluşturucu veya kopya atama işleci kullanılarak)
derin olmalıdır. Kopyalama sırasında, bir Karakterin Materyalleri envantere yenileri eklenmeden önce silinmelidir.
Elbette, bir Karakter yok edildiğinde Materyaller silinmelidir.

Aşağıdaki arabirimi uygulayacak somut sınıf MateriaSource'u yazın:
	class
	{
	public:
	virtual ~IMateriaSource() {}
	virtual void learnMateria(AMateria*) = 0;
	virtual AMateria* createMateria(std::string const & type) = 0;
	};

• learnMateria(AMateria*)
	Geçirilen Materia'yı parametre olarak kopyalar ve daha sonra klonlanabilmesi için bellekte saklar.
	Karakter gibi, MateriaSource da en fazla 4 Materia bilebilir. Benzersiz olmaları gerekmez.
• createMateria(std::string const &)
	Yeni bir Materia döndürür.
	Sonuncusu, türü parametre olarak iletilen olana eşit olan
	MateriaSource tarafından daha önce öğrenilen Materia'nın bir kopyasıdır. Tür bilinmiyorsa 0 döndürür.

Özetle, MateriaSource'unuz gerektiğinde bunları oluşturmak için Materias "şablonlarını" öğrenebilmelidir.
Ardından, yalnızca türünü tanımlayan bir dizi kullanarak yeni bir Materia oluşturabileceksiniz.

Bu kodu çalıştırmak:

	int main()
	{
		IMateriaSource* src = new MateriaSource();
		src->learnMateria(new Ice());
		src->learnMateria(new Cure());
		ICharacter* me = new Character("me");
		AMateria* tmp;
		tmp = src->createMateria("ice");
		me->equip(tmp);
		tmp = src->createMateria("cure");
		me->equip(tmp);
		ICharacter* bob = new Character("bob");
		me->use(0, *bob);
		me->use(1, *bob);
		delete bob;
		delete me;
		delete src;
		return 0;
	}

Çıkmalı
	$> clang++ -W -Wall -Werror *.cpp
	$> ./a.out | cat -e
	* shoots an ice bolt at bob *$
	* heals bob's wounds *$

Her zamanki gibi, yukarıda verilenlerden daha fazla test uygulayın ve teslim edin.
Bu modülü egzersiz yapmadan geçebilirsiniz 03
*/

#include "IMateriaSource.hpp"
#include "MateriaSource.hpp"
#include "ICharacter.hpp"
#include "AMateria.hpp"
#include "Character.hpp"
#include "Cure.hpp"
#include "Ice.hpp"

int main()
{
	IMateriaSource* src = new MateriaSource();
	src->learnMateria(new Ice());
	src->learnMateria(new Cure());
	ICharacter* me = new Character("me");
	AMateria* tmp;
	tmp = src->createMateria("ice");
	me->equip(tmp);
	tmp = src->createMateria("cure");
	me->equip(tmp);
	ICharacter* bob = new Character("bob");
	me->use(0, *bob);
	me->use(1, *bob);
	delete bob;
	delete me;
	delete src;
	return 0;
}
