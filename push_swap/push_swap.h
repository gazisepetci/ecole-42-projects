/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsepetci <gsepetci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 15:55:12 by gsepetci          #+#    #+#             */
/*   Updated: 2022/10/04 04:52:51 by gsepetci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct t_list
{
	int				data;
	struct t_list	*next;
}				t_list;
//kurallar
void	sa(t_list *list);
void	sb(t_list *list);
void	ss(t_list *a, t_list *b);
void	pa(t_list **a, t_list **b);
void	pb(t_list **a, t_list **b);
void	ra(t_list **list);
void	rb(t_list **list);
void	rr(t_list *a, t_list *b);
void	rra(t_list **lsta);
//yan fonksiyonlar
void	ft_add_arg(char **argv, t_list *a);
void	ft_add_list(t_list *list, int num);
int		ft_find_min(t_list *a);
int		ft_medium(t_list **a);
void	ft_remove_zero(t_list *a);
void	ft_min_first_data(t_list **list, t_list **b);
int		ft_lstsize(t_list *list);
int		ft_find_max(t_list *list);
int		ft_sortmu(t_list **list);
int		ft_find_index(t_list *list, int num);
t_list	*ft_lstlast(t_list *lst);
//pushlama fonksiyonları
void	ft_push_a(t_list **a, t_list **b);
void	ft_push(t_list **a, t_list **b);
void	ft_sort(t_list **a, t_list **b);
void	ft_push_b0(t_list **a, t_list **b);
void	ft_max_push(t_list **a, t_list **b);
void	ft_min_push(t_list **a, t_list **b);
void	ft_med_push(t_list **a, t_list **b, int med);
void	ft_push_a0(t_list **a, t_list **b);
//ekrana basma
int		ft_atoi(char *arr);
char	*ft_itoa(int num);
void	ft_putstr(char *str);
void	ft_write_list(t_list *list);
#endif
