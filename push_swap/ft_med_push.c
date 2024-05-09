/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_med_push.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsepetci <gsepetci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 16:49:26 by gsepetci          #+#    #+#             */
/*   Updated: 2022/10/04 04:01:35 by gsepetci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_med_push(t_list **a, t_list **b, int med)
{
	int	max;
	int	i;

	while ((*a) && max > med)
	{
		max = ft_find_max(*a);
		i = ft_find_index(*a, max);
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
