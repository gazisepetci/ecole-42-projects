/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_Data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsepetci <gsepetci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 00:15:58 by gsepetci          #+#    #+#             */
/*   Updated: 2022/10/01 15:09:44 by gsepetci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ft_find_max(t_list *list)
{
	/* int		i;
	t_list	*temp;

	temp = list;
	i = list -> data;
	while (temp)
	{
		if (temp -> data >= i)
			i = temp -> data;
		temp = temp -> next;
	}
	return (i); */
	int i;
	t_list *stk = list;
	int	max;
	if (stk)
		max = stk->data;
	else
		max = 0;
	stk = stk->next;
	while (stk)
	{
		if (max <= stk->data)
			max = stk->data;
		stk = stk->next;
	}
	return (max);
}

int	ft_find_min(t_list *a)
{
	int		i;
	t_list	*temp;

	temp = a;
	i = a -> data;
	while (temp)
	{
		if (temp -> data <= i)
			i = temp -> data;
		temp = temp -> next;
	}
	return (i);
}

int	ft_atoi(char *arr)
{
	int	i;
	int	p;
	int	num;

	i = 0;
	p = 1;
	num = 0;
	while (arr[i] <= ' ')
		i++;
	if (arr[0] == '-' || arr[0] == '+')
	{
		if (arr[0] == '-')
			p = -1;
		i++;
	}
	while (arr[i] >= '0' && arr[i] <= '9')
	{
		num = num * 10 + (arr[i] - 48);
		i++;
	}
	return (num * p);
}
