/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsepetci <gsepetci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 12:50:56 by gsepetci          #+#    #+#             */
/*   Updated: 2022/10/01 16:01:24 by gsepetci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	rb(t_list **list)
{
	if ((*list) && (*list)->next)
	{
	t_list	*temp;
	t_list	*new;

	new = *list;
	temp = (*list)-> next;
	*list = (*list)-> next;

	while ((*list)-> next)
	{
		*list = (*list)-> next;
	}
	(*list)-> next = new;
	new -> next = NULL;
	*list = temp;
	}
	write(1, "rb\n", 3);
}
