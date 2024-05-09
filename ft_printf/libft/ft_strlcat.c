/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysensoy <ysensoy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 10:17:03 by ysensoy           #+#    #+#             */
/*   Updated: 2022/02/17 10:19:21 by ysensoy          ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	a;
	size_t	de;
	size_t	sr;

	de = ft_strlen(dst);
	sr = ft_strlen((char *)src);
	a = 0;
	if (dstsize <= de)
		return (dstsize + sr);
	while (src[a] != '\0' && de + a + 1 < dstsize)
	{
		dst[de + a] = src[a];
		a++;
	}
	dst[de + a] = '\0';
	return (de + sr);
}
/*
int main(void)
{
	char yasintemp[55] = "yasintemp";
	char metetemp[50] = "mete";
	printf("%lu\n", ft_strlcat(yasintemp, metetemp, 5));
}*/
