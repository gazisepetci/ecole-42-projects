/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uercan <uercan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 14:37:11 by uercan            #+#    #+#             */
/*   Updated: 2023/05/25 15:58:23 by uercan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Making ClapTraps is probably starting to get on your nerves.
Now, implement a FragTrap class that inherits from ClapTrap. It is very similar to
ScavTrap. However, its construction and destruction messages must be different. Proper
construction/destruction chaining must be shown in your tests. When a FragTrap is
created, the program starts by building a ClapTrap. Destruction is in reverse order.
Same things for the attributes, but with different values this time:
• Name, which is passed as parameter to a constructor
• Hit points (100), represent the health of the ClapTrap
• Energy points (100)
• Attack damage (30)
FragTrap has a special capacity too:
void highFivesGuys(void);
This member function displays a positive high fives request on the standard output.
Again, add more tests to your program.



ClapTraps yapmak muhtemelen sinirlerinizi bozmaya başlıyor.
Şimdi, ClapTrap'ten miras alan bir FragTrap sınıfı uygulayın.
ScavTrap'e çok benzer. Ancak yapım ve yıkım mesajları farklı olmalıdır.
Testlerinizde uygun yapım/yıkım zinciri gösterilmelidir.
Bir FragTrap oluşturulduğunda, program bir ClapTrap oluşturarak başlar. İmha ters sıradadır.
Nitelikler için aynı şeyler, ancak bu sefer farklı değerlerle:
Yapıcıya parametre olarak iletilen Name
• Hit points (100), ClapTrap'in sağlığını temsil eder
• Energy points (100)
• Attack damage (30)
FragTrap'in de özel bir kapasitesi vardır:
	void highFivesGuys(void);
Bu üye işlevi, standart çıktıda olumlu bir beşlik çakma isteği görüntüler.
Yine, programınıza daha fazla test ekleyin.
*/

#include "FragTrap.hpp"
#include "ScavTrap.hpp"
#include "ClapTrap.hpp"

int	main ( void )
{
	FragTrap	p1;
	ScavTrap	p2;
	ClapTrap	p3;

	p1.attack("target of p1");
	p2.attack("target of p2");
	p2.takeDamage(50);
	p1.takeDamage(50);
	p2.beRepaired (100);
	p1.highFivesGuys();
	p2.gatekeeper();
	p2.attack("target of p2");

	return (0);
}