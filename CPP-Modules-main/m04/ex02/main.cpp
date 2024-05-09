/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uercan <uercan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 17:23:15 by uercan            #+#    #+#             */
/*   Updated: 2023/06/03 03:12:48 by uercan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Creating Animal objects doesn’t make sense after all. It’s true, they make no sound!
To avoid any possible mistakes, the default Animal class should not be instantiable.
Fix the Animal class so nobody can instantiate it. Everything should work as before.
If you want to, you can update the class name by adding a A prefix to Animal
*/

/*
Animal nesneleri yaratmak sonuçta bir anlam ifade etmiyor.
Doğru, ses çıkarmıyorlar! Olası hatalardan kaçınmak için, varsayılan Animal sınıfı örneklenebilir olmamalıdır.
Animal sınıfını kimsenin somutlaştıramayacağı şekilde düzeltin.
Her şey eskisi gibi çalışmalı. İsterseniz Animal'a bir A öneki ekleyerek sınıf adını güncelleyebilirsiniz.
*/

#include "Dog.hpp"
#include "Cat.hpp"
#include "Animal.hpp"

int	main()
{
		const Animal *j = new Dog();
		const Animal *i = new Cat();

		delete j;
		delete i;
	return (0);
}
