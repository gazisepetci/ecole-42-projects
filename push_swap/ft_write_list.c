/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsepetci <gsepetci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 21:32:57 by gsepetci          #+#    #+#             */
/*   Updated: 2022/10/03 21:35:08 by gsepetci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

char	*ft_itoa(int num)
{
	int		i;
	char	*str;
	int		temp;

	temp = num;
	i = 0;
	while (temp)
	{
		i++;
		temp = temp / 10;
	}
	str = malloc((i + 1));
	str[i] = '\0';
	i--;
	while (i >= 0)
	{
		str[i] = (num % 10) + 48;
		num = num / 10;
		i--;
	}
	return (str);
}

void	ft_putstr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
	write(1, " ", 1);
}

void	ft_write_list(t_list *list)
{
	t_list	*temp;
	char	*str;

	temp = list;
	while (temp)
	{
		str = ft_itoa(temp -> data);
		ft_putstr(str);
		free(str);
		temp = temp -> next;
	}
	write(1, "\n", 1);
	temp = list;
}
