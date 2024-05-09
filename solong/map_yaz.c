/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_yaz.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsepetci <gsepetci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 19:45:40 by gsepetci          #+#    #+#             */
/*   Updated: 2022/08/25 15:39:09 by gsepetci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_xpm_bas(t_list *depo, int a, int b)
{
	while (b < depo -> m_y)
	{
		a = 0;
		while (a < depo -> m_x - 1)
		{
			if (depo -> map[b][a] == '1')
				mlx_put_image_to_window(depo->mlx, depo->win,
					depo->d, a * 32, b * 32);
			else if (depo -> map[b][a] == '0')
				mlx_put_image_to_window(depo->mlx, depo->win,
					depo->b, a * 32, b * 32);
			else if (depo -> map[b][a] == 'P')
				mlx_put_image_to_window(depo->mlx, depo->win,
					depo->p, a * 32, b * 32);
			else if (depo -> map[b][a] == 'E')
				mlx_put_image_to_window(depo->mlx, depo->win,
					depo->e, a * 32, b * 32);
			else if (depo -> map[b][a] == 'C')
				mlx_put_image_to_window(depo->mlx, depo->win,
					depo->c, a * 32, b * 32);
			a++;
		}
		b++;
	}
}
