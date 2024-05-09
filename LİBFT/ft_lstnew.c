/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsepetci <gsepetci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 00:20:53 by gsepetci          #+#    #+#             */
/*   Updated: 2022/02/20 15:57:44 by gsepetci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*elt;

	elt = (t_list *)malloc(sizeof(t_list));
	if (!(elt))
		return (NULL);
	elt->content = content;
	elt->next = NULL;
	return (elt);
}
// int	main(void)
// {
// 	char	*s59;
// 	t_list	*list1;

// 	s59 = "42";
// 	list1 = ft_lstnew(s59);
// 	printf("%s\n", list1->content);
// }
