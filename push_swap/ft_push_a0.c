/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_push_a0.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsepetci <gsepetci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 04:52:14 by gsepetci          #+#    #+#             */
/*   Updated: 2022/10/04 04:56:13 by gsepetci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_push_a0(t_list **a, t_list **b)
{
	int		med;
	int		i;

	med = ft_medium(a);
	while ((*a) && ft_find_max(*a) > med)
	{
		if ((*a) -> data > med)
		{
			pb(a, b);
		}
		else
			ra(a);
	}
}
