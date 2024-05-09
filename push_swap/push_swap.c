/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsepetci <gsepetci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 15:55:04 by gsepetci          #+#    #+#             */
/*   Updated: 2022/10/04 05:05:01 by gsepetci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ft_sortmu(t_list **list)
{
	t_list	*temp;
	int		i;

	temp = (*list);
	i = temp -> data;
	while (temp->next)
	{
		i = temp -> next -> data;
		if (temp -> data > i && temp -> next)
			return (0);
		temp = temp -> next;
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_list	*a;
	t_list	*b;
	char	*i;
	int		med;

	a = malloc(sizeof(t_list));
	ft_add_arg(argv, a);
	ft_remove_zero(a);

	i = ft_itoa(ft_medium(&a));
	// ft_putstr(i);
	free(i);

	ft_push_b0(&a, &b);
	ft_write_list(a);
	ft_write_list(b);
	write(1,"-----\n",6);
	ft_min_push(&a, &b);
	ft_write_list(a);
	ft_write_list(b);
	write(1,"-----\n",6);
	med = ft_medium(&b);
	ft_med_push(&b, &a, med);
	ft_write_list(a);
	ft_write_list(b);
	write(1,"-----\n",6);
	ft_push_a0(&b, &a);
	ft_write_list(a);
	ft_write_list(b);
	// write(1,"-----\n",6);
	// ft_max_push(&b, &a);
	// ft_write_list(a);
	// ft_write_list(b);
	// return (0);
}
