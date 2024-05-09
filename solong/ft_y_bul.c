/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_y_bul.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsepetci <gsepetci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 11:39:08 by gsepetci          #+#    #+#             */
/*   Updated: 2022/08/25 15:29:57 by gsepetci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_y_bul(t_list *depo, char *harita)
{
	int		fd;
	int		deger;
	char	*s;
	int		r;

	deger = 0;
	s = (char *)malloc(2);
	fd = open(harita, 0);
	s[1] = '\0';
	while (read(fd, s, 1))
	{
		if (s[0] == '\n')
			deger++;
		if (s[0] == 'C')
			depo->altın += 1;
	}
	close(fd);
	free(s);
	return (deger);
}
