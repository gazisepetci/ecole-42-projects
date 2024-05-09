/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysensoy <ysensoy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 10:14:36 by ysensoy           #+#    #+#             */
/*   Updated: 2022/02/17 11:39:11 by ysensoy          ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	long long	s;
	int			d;

	s = 0;
	d = 1;
	while ((*str < 14 && *str > 8) || *str == 32)
		str++;
	if (*str == '-')
	{
		d *= -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		s = (s * 10) + (*str - 48);
		str++;
		if (s > 2147483647 && d == 1)
			return (-1);
		else if (s > 2147483648 && d == -1)
			return (0);
	}
	return ((int)(s * d));
}
/*
int	main()
{
	char	yasin[] = " -21474836555111111111111";
	printf("%d\n",ft_atoi(yasin));
	printf("%d",atoi(yasin));
}*/
