/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uercan <uercan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 13:38:44 by uercan            #+#    #+#             */
/*   Updated: 2022/07/03 13:56:45 by uercan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

static void	my_putchar(char c)
{
	write(1, &c, 1);
}

static void	my_putstr(char const *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		write(1, &s[i], 1);
		i++;
	}
}

void	ft_putnbr(int n)
{
	if (n == -2147483648)
		my_putstr("-2147483648");
	else
	{
		if (n < 0)
		{
			n *= -1;
			my_putchar('-');
		}
		if (n > 9)
			ft_putnbr(n / 10);
		my_putchar(n % 10 + '0');
	}
}
