/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_zero.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsepetci <gsepetci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 19:19:41 by gsepetci          #+#    #+#             */
/*   Updated: 2022/09/28 18:04:14 by gsepetci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_remove_zero(t_list *a)
{
	while (a -> next -> next)
		a = a -> next;
	free(a->next);
	a -> next = NULL;
}
