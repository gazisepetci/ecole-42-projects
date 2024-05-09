/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_max_push.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsepetci <gsepetci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 16:04:19 by gsepetci          #+#    #+#             */
/*   Updated: 2022/10/01 17:11:01 by gsepetci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_max_push(t_list **a, t_list **b)
{
	int	max;
	int	i;

	while ((*a))
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
