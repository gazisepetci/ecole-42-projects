/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_min_push.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsepetci <gsepetci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 14:15:04 by gsepetci          #+#    #+#             */
/*   Updated: 2022/10/01 17:10:53 by gsepetci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_min_push(t_list **a, t_list **b)
{
	int	min;
	int	i;

	while ((*a))
	{
		min = ft_find_min(*a);
		i = ft_find_index(*a, min);
		if (i == 1)
		{
			pb(a, b);
		}
		else if (i > ft_lstsize(*a) / 2)
		{
			rra(a);
		}
		else
		{
			ra(a);
		}
	}
}
