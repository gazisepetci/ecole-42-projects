/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysensoy <ysensoy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 10:15:39 by ysensoy           #+#    #+#             */
/*   Updated: 2022/02/17 13:08:31 by ysensoy          ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	int				k;
	unsigned char	*str;

	i = 0;
	k = 0;
	str = (unsigned char *)s;
	if (n == i)
		return (NULL);
	while (i < n)
	{
		if (str[i] == (unsigned char)c)
			return (&str[i]);
		else
			k = 1;
		i++;
	}
	if (k == 1)
		return (0);
	else
		return (&str[i]);
}
/*
int	main()
{
	char cp[] = "bilgisayar";
	char cd = 'g';
	printf("%c karakterin bellek adresi %p\n", cd, ft_memchr(cp, cd, 2));
	printf("%c karakterin bellek adresi %p\n", cd, memchr(cp, cd, 2));
	return 0;
}*/
