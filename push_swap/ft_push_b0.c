/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_push_b0.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsepetci <gsepetci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 14:20:31 by gsepetci          #+#    #+#             */
/*   Updated: 2022/10/04 04:55:31 by gsepetci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ft_medium(t_list **a)
{
	t_list	*temp;
	int		medium;
	int		size;

	temp = *a;
	medium = 0;
	size = 0;
	while (temp)
	{
		medium = medium + temp -> data;
		size++;
		temp = temp -> next;
	}
	return (medium / size);
}

void	ft_push_b0(t_list **a, t_list **b)
{
	int		med;
	int		i;

	med = ft_medium(a);
	while ((*a) && ft_find_min(*a) < med)
	{
		if ((*a) -> data < med)
		{
			pb(a, b);
		}
		else
			ra(a);
	}
}
