/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsepetci <gsepetci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 16:47:32 by gsepetci          #+#    #+#             */
/*   Updated: 2022/08/27 19:35:19 by gsepetci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

#define KEY_A 0
#define KEY_D 2
#define KEY_W 13
#define KEY_S 1

int test_exit(int err)
{
	err = 0;
	exit(0);
	return (0);
}

void	ft_exit(int key, t_list *depo)
{
	printf("%d\n",depo->altın);
	if (key == 53)
		exit(0);
	if (key == KEY_W)
	{
		if (depo -> map[depo->p_y - 1][depo->p_x] == 'E' && depo -> altın == 0)
			exit(0);
	}
	if (key == KEY_S)
	{
		if (depo -> map[depo->p_y + 1][depo->p_x] == 'E' && depo -> altın == 0)
			exit(0);
	}
	if (key == KEY_A)
	{
		if (depo -> map[depo->p_y][depo->p_x - 1] == 'E' && depo -> altın == 0)
			exit(0);
	}
	if (key == KEY_D)
	{
		if (depo -> map[depo->p_y][depo->p_x + 1] == 'E' && depo -> altın == 0)
			exit(0);
	}
}

void	ft_dikey(int key, t_list *depo)
{
	if (key == KEY_W)
	{
		if (depo -> map[depo->p_y - 1][depo->p_x] != '1' && depo -> map[depo->p_y - 1][depo->p_x] != 'E')
		{
			if (depo -> map[depo->p_y - 1][depo->p_x] == 'C')
				depo -> altın -= 1;
			depo -> p_y -= 1;
			depo ->map[depo -> p_y][depo->p_x] = 'P';
			depo ->map[depo -> p_y + 1][depo->p_x] = '0';
			depo->hareket += 1;
			ft_xpm_bas(depo, 0, 0);
			mlx_string_put(depo->mlx, depo->win, 16, 16, 0xfffffff, ft_itoa(depo -> hareket));
		}
	}
	else if (key == KEY_S)
	{
		if (depo -> map[depo->p_y + 1][depo->p_x] != '1' && depo -> map[depo->p_y + 1][depo->p_x] != 'E')
		{
			if (depo -> map[depo->p_y + 1][depo->p_x] == 'C')
				depo -> altın -= 1;
			depo -> p_y += 1;
			depo ->map[depo -> p_y][depo->p_x] = 'P';
			depo ->map[depo -> p_y - 1][depo->p_x] = '0';
			depo->hareket += 1;
			ft_xpm_bas(depo, 0, 0);
			mlx_string_put(depo->mlx, depo->win, 16, 16, 0xfffffff, ft_itoa(depo -> hareket));
		}
	}
}

int	ft_mlx_key_hook(int key, t_list *depo)
{
	ft_exit(key, depo);
	if (key == KEY_D)
	{
		if (depo -> map[depo->p_y][depo->p_x + 1] != '1' && depo -> map[depo->p_y][depo->p_x + 1] != 'E')
		{
			if (depo -> map[depo->p_y][depo->p_x + 1] == 'C')
				depo -> altın -= 1;
			depo -> p_x += 1;
			depo ->map[depo -> p_y][depo->p_x] = 'P';
			depo ->map[depo -> p_y][depo->p_x - 1] = '0';
			depo->hareket += 1;
			ft_xpm_bas(depo, 0, 0);
			mlx_string_put(depo->mlx, depo->win, 16, 16, 0xfffffff, ft_itoa(depo -> hareket));
		}
	}
	else if (key == KEY_A)
	{
		if (depo -> map[depo->p_y][depo->p_x - 1] != '1' && depo -> map[depo->p_y][depo->p_x - 1] != 'E')
		{
			if (depo -> map[depo->p_y][depo->p_x - 1] == 'C')
				depo -> altın -= 1;
			depo -> p_x -= 1;
			depo ->map[depo -> p_y][depo->p_x] = 'P';
			depo ->map[depo -> p_y][depo->p_x + 1] = '0';
			depo->hareket += 1;
			ft_xpm_bas(depo, 0, 0);
			mlx_string_put(depo->mlx, depo->win, 16, 16, 0xfffffff, ft_itoa(depo -> hareket));
		}
	}
	ft_dikey(key, depo);
	return (0);
}

int	main(int argc, char **argv)
{
	t_list	depo;
	int		c;

	depo.hareket = 0;
	depo.altın = 0;
	ft_map_oku(&depo, argv[1], 0);
	if (ft_map_kontrol(&depo) == 1)
		exit(0);
	depo.mlx = mlx_init();
	depo.win = mlx_new_window(depo.mlx, (depo.m_x -1) * 32, depo.m_y * 32, "0");
	ft_xpm_atama(&depo);
	ft_xpm_bas(&depo, 0, 0);
	ft_player_xy(&depo);
	mlx_string_put(depo.mlx, depo.win, 16, 16, 0xffffff, ft_itoa(depo.hareket));
	mlx_key_hook(depo.win, ft_mlx_key_hook, &depo);
	mlx_hook(depo.win, 17, (0L), test_exit, &depo);
	mlx_loop(depo.mlx);
}
