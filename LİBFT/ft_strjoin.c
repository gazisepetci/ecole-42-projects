/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsepetci <gsepetci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 15:35:09 by gsepetci          #+#    #+#             */
/*   Updated: 2022/02/20 17:13:32 by gsepetci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ptr_str;
	int		i;
	int		j;

	if (!s1)
		return (0);
	if (!s2)
		return (0);
	ptr_str = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!ptr_str)
		return (0);
	i = 0;
	while (s1[i] != '\0')
	{
		ptr_str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\0')
		ptr_str[i++] = s2[j++];
	ptr_str[i] = '\0';
	return (ptr_str);
}
