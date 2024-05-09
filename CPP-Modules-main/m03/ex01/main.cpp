/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uercan <uercan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 19:08:22 by uercan            #+#    #+#             */
/*   Updated: 2023/05/25 13:58:22 by uercan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Because you can never have enough ClapTraps, you will now create a derived robot.
It will be named ScavTrap and will inherit the constructors and destructor from ClapTrap. However, its constructors, destructor and attack() will print different messages.
After all, ClapTraps are aware of their individuality.

Note that proper construction/destruction chaining must be shown in your tests.
When a ScavTrap is created, the program starts by building a ClapTrap. Destruction is
in reverse order. Why?

ScavTrap will use the attributes of ClapTrap (update ClapTrap in consequence) and
must initialize them to:
• Name, which is passed as parameter to a constructor
• Hit points (100), represent the health of the ClapTrap
• Energy points (50)
• Attack damage (20)

ScavTrap will also have its own special capacity:
void guardGate();
This member function will display a message informing that ScavTrap is now in Gate keeper mode.
Don’t forget to add more tests to your program
*/

/*
Hiçbir zaman yeterince ClapTrap'e sahip olamayacağınız için artık türetilmiş bir robot yaratacaksınız.
ScavTrap olarak adlandırılacak ve yapıcıları ve yıkıcıları ClapTrap'ten devralacak. Ancak yapıcıları, yıkıcısı ve attack() farklı mesajlar basacaktır.
Ne de olsa, ClapTraps bireyselliklerinin farkındadır.

Testlerinizde uygun yapım/yıkım zincirinin gösterilmesi gerektiğini unutmayın.
Bir ScavTrap oluşturulduğunda, program bir ClapTrap oluşturarak başlar. İmha
ters sırada. Neden?

ScavTrap, ClapTrap'in özniteliklerini kullanır (bunun sonucunda ClapTrap'i günceller) ve
onları şu şekilde başlatmalı:
• Name, Yapıcıya parametre olarak iletilen ad
• Hit points (100), ClapTrap'in sağlığını temsil eder
• Energy points (50)
• Attack damage (20)

ScavTrap ayrıca kendi özel kapasitesine sahip olacaktır:
void guardGate();
Bu üye işlevi, ScavTrap'in artık Kapı bekçisi modunda olduğunu bildiren bir mesaj görüntüler.
Programınıza daha fazla test eklemeyi unutmayın
*/


#include "ScavTrap.hpp"

int	main()
{
	ScavTrap p1;
	ScavTrap p2;

	p2 = p1;
	p1.gatekeeper();
	p1.attack ("Hmmmmmmm");
	p1.gatekeeper();
	p1.attack ("Hmmmmmmm");
	p1.takeDamage(100);
	p1.takeDamage(100);
	p2.takeDamage(10);
	p2.beRepaired (100);
	return (0);
}