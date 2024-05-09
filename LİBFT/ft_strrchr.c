/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsepetci <gsepetci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 10:15:59 by gsepetci          #+#    #+#             */
/*   Updated: 2022/02/17 01:33:29 by gsepetci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int	s;

	s = ft_strlen(str);
	while (s >= 0)
	{
		if (str[s] == (char)c)
			return ((char *)(str + s));
		s--;
	}
	return (0);
}
