/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_index.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsepetci <gsepetci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 12:43:58 by gsepetci          #+#    #+#             */
/*   Updated: 2022/10/01 15:18:40 by gsepetci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ft_lstsize(t_list *list)
{
	t_list	*temp;
	int		i;

	i = 0;
	temp = list;
	while (temp)
	{
		i++;
		temp = temp -> next;
	}
	return (i);
}

int	ft_find_index(t_list *list, int num)
{
	t_list	*temp;
	int		i;

	temp = list;
	i = 1;
	while (temp)
	{
		if (temp->data == num)
		{
			return (i);
		}
		i++;
		temp = temp -> next;
	}
	return(0);
}
