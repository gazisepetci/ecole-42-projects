/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sa.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsepetci <gsepetci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 07:05:29 by gsepetci          #+#    #+#             */
/*   Updated: 2022/10/01 16:01:31 by gsepetci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sa(t_list *list)
{
	int	i;
	int	j;

	i = list -> data;
	j = list -> next -> data;
	list -> data = j;
	list -> next -> data = i;
	write(1, "sa\n", 3);
}
