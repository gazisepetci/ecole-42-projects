/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_x_bul.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsepetci <gsepetci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 11:07:21 by gsepetci          #+#    #+#             */
/*   Updated: 2022/08/24 17:49:15 by gsepetci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_x_bul(t_list *depo, char *harita)
{
	int		fd;
	int		deger;
	char	*s;
	int		r;

	deger = 0;
	s = (char *)malloc(2);
	fd = open(harita, 0);
	while (s[0] != '\n')
	{
		r = read(fd, s, 1);
		s[1] = '\0';
		deger++;
	}
	close(fd);
	free(s);
	return (deger);
}
