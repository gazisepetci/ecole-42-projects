      /* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uercan <uercan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 19:08:22 by uercan            #+#    #+#             */
/*   Updated: 2023/04/02 15:29:47 by uercan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
First, you have to implement a class! How original!
It will be called ClapTrap and will have the following private attributes initialized
to the values specified in brackets:
• Name, which is passed as parameter to a constructor
• Hit points (10), represent the health of the ClapTrap
• Energy points (10)
• Attack damage (0)
Add the following public member functions so the ClapTrap looks more realistic:
• void attack(const std::string& target);
• void takeDamage(unsigned int amount);
• void beRepaired(unsigned int amount);
When ClapTrack attacks, it causes its target to lose <attack damage> hit points.
When ClapTrap repairs itself, it gets <amount> hit points back. Attacking and repairing
cost 1 energy point each. Of course, ClapTrap can’t do anything if it has no hit points
or energy points left.


In all of these member functions, you have to print a message to describe what happens. For example, the attack() function may display something like (of course, without
the angle brackets):
ClapTrap <name> attacks <target>, causing <damage> points of damage!
The constructors and destructor must also display a message, so your peer-evaluators
can easily see they have been called.
Implement and turn in your own tests to ensure your code works as expected.
*/

/*
İlk olarak, bir sınıf uygulamanız gerekir! Ne kadar orijinal!
ClapTrap olarak adlandırılacak ve aşağıdaki özel nitelikler başlatılacak
parantez içinde belirtilen değerlere:
• Yapıcıya parametre olarak iletilen ad
• Hit points (10), ClapTrap'in sağlığını temsil eder
• Energy points (10)
•Attack damage (0)
ClapTrap'in daha gerçekçi görünmesi için aşağıdaki ortak üye işlevlerini ekleyin:
• void attack(const std::string& target);
• void takeDamage(unsigned int amount);
• void beRepaired(unsigned int amount);;
ClapTrack saldırdığında, hedefinin <saldırı gücü> can puanı kaybetmesine neden olur.
ClapTrap kendini onardığında <amount> can puanı geri alır. Saldırı ve onarım
her biri 1 enerji puanına mal olur. Elbette, ClapTrap can puanı yoksa hiçbir şey yapamaz.
veya kalan enerji noktaları.


Tüm bu üye işlevlerde, ne olduğunu açıklamak için bir mesaj yazdırmanız gerekir. 
Örneğin, attack() işlevi (elbette, olmadan) gibi bir şey görüntüleyebilir.
açılı ayraçlar):
ClapTrap <isim>, <hedef>e saldırarak <hasar> hasar puanına neden olur!
Oluşturucular ve yıkıcılar da bir mesaj göstermelidir, böylece akran değerlendiricileriniz
çağrıldıklarını kolayca görebilirler.
Kodunuzun beklendiği gibi çalıştığından emin olmak için kendi testlerinizi uygulayın ve teslim edin.
*/

//ClapTrap <name> attacks <target>, causing <damage> points of damage!

#include "ClapTrap.hpp"

// int	main( void )
// {
// 	ClapTrap	a("AA");

// 	a.hit_point(100);
// 	a.attack("bb");
// 	a.takeDamage(10);
// 	a.beRepaired(5);
// 	return (0);
// }

int	main()
{
	ClapTrap	p1;
	ClapTrap	p2("player2");
	ClapTrap	p3("player3");
	ClapTrap	p4(p2);
	ClapTrap	p5 = p3;

	p4 = p5;
	p1.attack("player2");
	p2.attack("player1");
	p2.takeDamage(5);
	std::cout << std::endl;
	p1.beRepaired(10);
	std::cout << std::endl;
	p2.beRepaired(10);
	std::cout << std::endl;
	return (0);
}