/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_push_inş_A.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsepetci <gsepetci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 23:10:02 by gsepetci          #+#    #+#             */
/*   Updated: 2022/10/04 04:02:09 by gsepetci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_push_max_a(t_list **a, t_list **b)
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
