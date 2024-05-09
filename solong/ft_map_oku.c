/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_oku.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsepetci <gsepetci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 17:29:36 by gsepetci          #+#    #+#             */
/*   Updated: 2022/08/27 19:35:03 by gsepetci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_map_oku(t_list *depo, char *harita, int i)
{
	int		fd;
	int		x;
	int		y;

	i = 0;
	x = 0;
	y = 0;
	depo -> m_x = ft_x_bul(depo, harita);
	depo -> m_y = ft_y_bul(depo, harita);
	fd = open(harita, O_RDONLY);
	depo -> map = (char **)malloc(sizeof(char *) * (depo->m_y + 1));
	while (i < depo->m_y)
	{
		depo -> map[i] = get_next_line(fd);
		i++;
	}
	depo->map[i] = NULL;
	close(fd);
}
