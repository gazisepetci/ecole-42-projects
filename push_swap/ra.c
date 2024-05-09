/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ra.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsepetci <gsepetci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 12:50:59 by gsepetci          #+#    #+#             */
/*   Updated: 2022/10/04 05:05:15 by gsepetci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ra(t_list **list)
{
	t_list	*temp;
	t_list	*new;

	new = *list;
	temp = (*list)-> next;
	*list = (*list)-> next;
	while ((*list)-> next)
		*list = (*list)-> next;
	(*list)-> next = new;
	new -> next = NULL;
	*list = temp;
	//write(1, "ra\n", 3);
}
