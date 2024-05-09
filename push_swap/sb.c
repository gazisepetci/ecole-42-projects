/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sb.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsepetci <gsepetci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 07:13:35 by gsepetci          #+#    #+#             */
/*   Updated: 2022/10/01 16:01:39 by gsepetci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sb(t_list *list)
{
	int	i;
	int	j;

	i = list -> data;
	j = list -> next -> data;
	list -> data = j;
	list -> next -> data = i;
	write(1, "sb\n", 3);
}
