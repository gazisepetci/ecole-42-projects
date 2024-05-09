/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_kontrol.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsepetci <gsepetci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 16:50:42 by gsepetci          #+#    #+#             */
/*   Updated: 2022/08/25 15:30:41 by gsepetci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_altın_kontrol(t_list *depo)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (depo -> map[y][x] != '\0')
	{
		x = 0;
		while (depo -> map[y][x] != '\n')
		{
			if (depo -> map[y][x] == 'C')
				return (0);
			x++;
		}
		y++;
	}
	return (1);
}

int	ft_duvar_kontrol(t_list *depo)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < depo -> m_y != '\0')
	{
		x = 0;
		while (x < depo -> m_x - 1)
		{
			if (depo -> map[0][x] != '1')
				return (1);
			if (depo -> map[y][0] != '1')
				return (1);
			if (depo -> map[depo -> m_y - 1][x] != '1')
				return (1);
			x++;
		}
		y++;
	}
	return (0);
}

int	ft_duvar_sayi_kontrol(t_list *depo)
{
	int	x;
	int	y;

	x = 0;
	y = 0;

	while (depo -> map[y])
	{
		x = 0;
		while (depo -> map[y][x])
			x++;
		if (depo -> m_x != x)
			return (1);
		y++;
	}
	return (0);
}

int	ft_map_kontrol(t_list *depo)
{
	int	a;
	int	d;
	int	v;

	a = ft_altın_kontrol(depo);
	d = ft_duvar_kontrol(depo);	
	v = ft_duvar_sayi_kontrol(depo);
	if (a == 1 || d == 1 || v == 1)
	{
		return (1);
	}
	return (0);
}
