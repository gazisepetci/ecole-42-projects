/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsepetci <gsepetci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 19:57:44 by gsepetci          #+#    #+#             */
/*   Updated: 2022/02/12 14:09:22 by gsepetci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*a;
	int		i;

	i = 0;
	a = (char *)malloc(ft_strlen(s1) + 1);
	if (!a)
		return (0);
	while (s1[i] != '\0')
	{
		a[i] = s1[i];
		i++;
	}
	a[i] = 0;
	return (a);
}
