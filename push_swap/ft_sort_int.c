/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_int.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsepetci <gsepetci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 20:40:56 by gsepetci          #+#    #+#             */
/*   Updated: 2022/09/28 20:52:40 by gsepetci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_sort(t_list **a, t_list **b)
{
	int		i;

	while ((*a))
	{
		i = ft_find_max(*a);
		if ((*a) -> data != i)
			ra(a);
		else if ((*a) -> data == i)
			pb(a, b);
	}
}
