/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_player_xy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsepetci <gsepetci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 13:26:53 by gsepetci          #+#    #+#             */
/*   Updated: 2022/08/24 13:10:04 by gsepetci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_player_xy(t_list *depo)
{
	int	x;
	int	y;

	y = 0;
	while (y < depo -> m_y)
	{
		x = 0;
		while (x < depo -> m_x)
		{
			if (depo -> map[y][x] == 'P')
			{
				depo -> p_x = x;
				depo -> p_y = y;
				break ;
			}
			x++;
		}
		y++;
	}
}
