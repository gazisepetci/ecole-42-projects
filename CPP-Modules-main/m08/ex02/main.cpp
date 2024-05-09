/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uercan <uercan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 11:57:10 by uercan            #+#    #+#             */
/*   Updated: 2023/07/20 13:29:41 by uercan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Şimdi, daha ciddi şeylere geçme zamanı. Garip bir şey geliştirelim.
std::stack kabı çok güzel. Ne yazık ki, yinelenemeyen tek STL Konteynerlerinden biridir. Bu çok kötü.

Ama bunu neden kabul edelim? Özellikle eksik özellikleri oluşturmak için orijinal yığını kesme özgürlüğüne sahipsek.

Bu adaletsizliği onarmak için std::stack kapsayıcısını yinelenebilir yapmalısınız.

Bir MutantStack sınıfı yazın. Bir std::stack açısından uygulanacaktır.
Tüm üye işlevlerini ve ek bir özelliği sunacak: yineleyiciler.

Elbette, her şeyin beklendiği gibi çalıştığından emin olmak için kendi testlerinizi yazıp teslim edeceksiniz.

int main()
{
MutantStack<int> mstack;
mstack.push(5);
mstack.push(17);
std::cout << mstack.top() << std::endl;
mstack.pop();
std::cout << mstack.size() << std::endl;
mstack.push(3);
mstack.push(5);
mstack.push(737);
//[...]
mstack.push(0);
MutantStack<int>::iterator it = mstack.begin();
MutantStack<int>::iterator ite = mstack.end();
++it;
--it;
while (it != ite)
{
std::cout << *it << std::endl;
++it;
}
std::stack<int> s(mstack);
return 0;
}

İlk kez MutantStack'inizle çalıştırırsanız ve ikinci kez MutantStack'i örneğin bir std::list ile değiştirirseniz, iki çıktı aynı olmalıdır.
Elbette, başka bir kapsayıcıyı test ederken, aşağıdaki kodu karşılık gelen üye işlevlerle güncelleyin (push(), push_back() haline gelebilir).
*/

#include " MutantStack.hpp"

int main()
{
	{
		MutantStack<int> mstack;
		mstack.push(5);
		mstack.push(17);
		std::cout << mstack.top() << std::endl;
		mstack.pop();
		std::cout << mstack.size() << std::endl;
		mstack.push(3);
		mstack.push(5);
		mstack.push(737);
		//[...]
		mstack.push(0);
		MutantStack<int>::iterator it = mstack.begin();
		MutantStack<int>::iterator ite = mstack.end();
		++it;
		--it;
		while (it != ite)
		{
		std::cout << *it << std::endl;
		++it;
		}
		std::stack<int> s(mstack);
	}

	{
		std::cout << "*2*\n";
		MutantStack<std::string> ms;
		ms.push("aaa");
		ms.push("bbb");
		ms.push("ccc");
		ms.push("ddd");
		ms.push("eee");
		MutantStack<std::string>::iterator it = ms.begin();
		MutantStack<std::string>::iterator ite = ms.end();
		while (it != ite)
		{
			std::cout << *it << std::endl;
			++it;
		}
	}
	return 0;
}
