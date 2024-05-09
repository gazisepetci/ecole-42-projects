/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysensoy <ysensoy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 10:17:41 by ysensoy           #+#    #+#             */
/*   Updated: 2022/02/17 13:08:09 by ysensoy          ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	char	*samanlik;
	char	*igne;
	size_t	i;
	size_t	a;

	i = 0;
	a = 0;
	samanlik = (char *)haystack;
	igne = (char *)needle;
	if (igne[a] == '\0')
		return (samanlik);
	while (samanlik[i] != '\0' && i < len)
	{
		while (samanlik[i] == igne[a] && i + 1 <= len)
		{
			if (igne[a + 1] == '\0')
				return (&samanlik[i - a]);
			i++;
			a++;
		}
		i = i - a;
		a = 0;
		i++;
	}
	return (0);
}
/*
#include <string.h>
int	main()
{
	char	yasin[] = "taha haksal";
	char	yasin2[] =  "ha ha";
	printf("%s\n", ft_strnstr(yasin,yasin2,8));
	printf("%s", strnstr(yasin,yasin2,8));
}*/
