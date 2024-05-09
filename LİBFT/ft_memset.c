/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsepetci <sepetcigazi3@hotmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 10:08:26 by gsepetci          #+#    #+#             */
/*   Updated: 2022/02/02 13:36:48 by gsepetci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *dest, int c, size_t n)
{
	char	*a;
	size_t	i;

	i = 0;
	a = (char *)dest;
	while (i < n)
	{
		a[i] = c;
		i++;
	}
	return (a);
}
