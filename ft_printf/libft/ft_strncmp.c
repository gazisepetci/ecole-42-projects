/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysensoy <ysensoy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 10:17:35 by ysensoy           #+#    #+#             */
/*   Updated: 2022/02/17 10:27:40 by ysensoy          ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char	*s1, const char	*s2, size_t n)
{
	unsigned char	*k1;
	unsigned char	*k2;
	size_t			i;

	i = 0;
	k1 = (unsigned char *)s1;
	k2 = (unsigned char *)s2;
	while (k1[i] == k2[i] && (k1[i] != '\0' || k2[i] != '\0'))
		i++;
	if (n <= i)
		return (0);
	else
		return (k1[i] - k2[i]);
}
/*
#include <string.h>
int	main()
{
	printf("%d\n",ft_strncmp("yasin","yasir",5));
	//printf("%d",strncmp("test\200", "test\0", 6));
}*/
