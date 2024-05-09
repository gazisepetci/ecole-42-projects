/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rra.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsepetci <gsepetci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 12:50:40 by gsepetci          #+#    #+#             */
/*   Updated: 2022/10/04 05:05:21 by gsepetci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	rra(t_list **lsta)
{
	t_list	*end_lst;
	t_list	*temp;
	int		i;

	temp = *lsta;
	//write(1, "rra\n", 4);
	i = ft_lstlast(*lsta)->data;
	while (temp->next->next)
		temp = temp->next;
	free(ft_lstlast(*lsta));
	temp->next = NULL;
	end_lst = malloc(sizeof(t_list));
	end_lst->data = i;
	end_lst->next = *lsta;
	*lsta = end_lst;
}
