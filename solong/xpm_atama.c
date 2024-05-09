/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpm_atama.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsepetci <gsepetci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 19:09:36 by gsepetci          #+#    #+#             */
/*   Updated: 2022/08/23 13:09:45 by gsepetci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_xpm_atama(t_list *depo)
{
	depo->z = 0;
	depo->p = mlx_xpm_file_to_image(depo->mlx, "p.xpm", &depo->z, &depo->z);
	depo->d = mlx_xpm_file_to_image(depo->mlx, "d.xpm", &depo->z, &depo->z);
	depo->b = mlx_xpm_file_to_image(depo->mlx, "b.xpm", &depo->z, &depo->z);
	depo->e = mlx_xpm_file_to_image(depo->mlx, "e.xpm", &depo->z, &depo->z);
	depo->c = mlx_xpm_file_to_image(depo->mlx, "c.xpm", &depo->z, &depo->z);
}
