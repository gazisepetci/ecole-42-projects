/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uercan <uercan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 14:37:11 by uercan            #+#    #+#             */
/*   Updated: 2023/05/29 12:52:16 by uercan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
In this exercise, you will create a monster: a ClapTrap that’s half FragTrap, half
ScavTrap. It will be named DiamondTrap, and it will inherit from both the FragTrap
AND the ScavTrap. This is so risky!
The DiamondTrap class will have a name private attribute. Give to this attribute
exactly the same variable’s name (not talking about the robot’s name here) than the one
in the ClapTrap base class.
To be more clear, here are two examples.
If ClapTrap’s variable is name, give the name name to the one of the DiamondTrap.
If ClapTrap’s variable is _name, give the name _name to the one of the DiamondTrap.
Its attributes and member functions will be picked from either one of its parent classes:
• Name, which is passed as parameter to a constructor
• ClapTrap::name (parameter of the constructor + "_clap_name" suffix)
• Hit points (FragTrap)
• Energy points (ScavTrap)
• Attack damage (FragTrap)
• attack() (Scavtrap)
In addition to the special functions of both its parent classes, DiamondTrap will have
its own special capacity:
void whoAmI();
This member function will display both its name and its ClapTrap name.
Of course, the ClapTrap subobject of the DiamondTrap will be created once, and only
once. Yes, there’s a trick.
Again, add more tests to your program.
Do you know the -Wshadow and -Wno-shadow compiler flags?

Bu alıştırmada, bir canavar yaratacaksınız: yarı FragTrap, yarı ScavTrap olan bir ClapTrap.
DiamondTrap olarak adlandırılacak ve hem FragTrap'ten hem de ScavTrap'ten miras alacaktır.
DiamondTrap sınıfının özel bir adı özniteliği olacaktır. Bu özniteliğe, 
ClapTrap temel sınıfındakiyle tam olarak aynı değişken adını verin (burada robotun adından bahsetmiyoruz).
Daha açık olmak gerekirse, işte iki örnek:
-ClapTrap'in değişkeni "name" ise, DiamondTrap'in değişkenine "name" adını verin.
-ClapTrap'in değişkeni "_name" ise, DiamondTrap değişkenlerinden birine "_name" adını verin.
Nitelikleri ve üye işlevleri, üst sınıflarından birinden seçilecektir:
• constructor'a parametre olarak iletilen ad
• ClapTrap::name (kurucunun parametresi + "_clap_name" sonuna eklemek)
• Hit points (FragTrap)
• Energy points (ScavTrap)
• Attack damage (FragTrap)
• attack() (Kazma tuzağı)
DiamondTrap, her iki ebeveyn sınıfının özel işlevlerine ek olarak, kendi özel kapasitesi:
-void whoAmI();
Bu üye işlev, hem adını hem de ClapTrap adını görüntüler.
Elbette, DiamondTrap'in ClapTrap alt nesnesi bir kez ve yalnızca bir kez oluşturulacaktır.
Evet, bir aldatmaca var.

-Wshadow ve -Wno-shadow derleyici bayraklarını biliyor musunuz?
*/

#include "DiamondTrap.hpp"
#include "FragTrap.hpp"
#include "ScavTrap.hpp"
#include "ClapTrap.hpp"

int	main ( void )
{
	DiamondTrap	d1;
	DiamondTrap	d2("diamond2");
	DiamondTrap	d3("diamond3");

	d1.whoAmI();
	d2.whoAmI();
	d3.whoAmI();
	std::cout << std::endl;
	d1.attack("diamond2");
	std::cout << std::endl;
	d3.highFivesGuys();
	d2.gatekeeper();
	std::cout << std::endl;
	d1.attack("diamond2");
	d2.attack("diamond3");
	d2.gatekeeper();
	d2.beRepaired(250);
	std::cout << std::endl;
	return (0);
}