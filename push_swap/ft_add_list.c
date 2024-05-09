/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsepetci <gsepetci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 16:29:51 by gsepetci          #+#    #+#             */
/*   Updated: 2022/09/28 20:40:09 by gsepetci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_add_list(t_list *list, int num)
{
	t_list	*temp;

	temp = malloc(sizeof(t_list));
	while (list -> next)
		list = list -> next;
	list -> next = temp;
	list -> data = num;
	list = temp;
}

void	ft_add_arg(char **argv, t_list *a)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		ft_add_list(a, ft_atoi(argv[i]));
		i++;
	}
}
