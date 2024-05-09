/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysensoy <ysensoy@student.42kocaeli.com.tr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 12:07:19 by ysensoy           #+#    #+#             */
/*   Updated: 2022/02/09 19:33:35 by ysensoy          ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*my;

	my = (t_list *)malloc(sizeof(t_list));
	if (!my)
		return (NULL);
	my -> content = content;
	my -> next = NULL;
	return (my);
}
