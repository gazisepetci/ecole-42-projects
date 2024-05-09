/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_push_a.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsepetci <gsepetci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 13:15:35 by gsepetci          #+#    #+#             */
/*   Updated: 2022/10/01 14:33:19 by gsepetci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_push_a(t_list **a, t_list **b)
{
	int	med;

	med = ft_medium(b);
	while ((*b) && ft_find_min(*b) < med && !ft_sortmu(b))
	{
		if ((*b) -> data < med)
		{
			pa(a, b);
		}
		else
			rb(b);
	}

}
