/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsepetci <gsepetci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 14:08:44 by gsepetci          #+#    #+#             */
/*   Updated: 2022/02/20 21:08:51 by gsepetci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	int	i;

	if (!dst && !src)
		return (NULL);
	i = (int)len - 1;
	if (src > dst)
	{
		i = 0;
		while (i < (int)len)
		{
			*(char *)(dst + i) = *(char *)(src + i);
			i++;
		}
		return (dst);
	}
	while (i >= 0)
	{
		*(char *)(dst + i) = *(char *)(src + i);
		i--;
	}
	return (dst);
}
// int main()
// {
// 	char a[] = "abcdefghıi";
// 	char b[] = "123";
// 	printf("%s",ft_memmove(b,a,16));
// }
