/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsepetci <gsepetci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 16:49:09 by gsepetci          #+#    #+#             */
/*   Updated: 2022/08/24 16:51:55 by gsepetci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# include "get_next_line/get_next_line.h"
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include "mlx/mlx.h"

typedef struct a_list
{
	void	*mlx;
	void	*win;
	char	**map;
	int		m_x;
	int		m_y;
	int		p_x;
	int		p_y;
	int		z;
	void	*p;
	void	*d;
	void	*b;
	void	*e;
	void	*c;
	int		altın;
	int		hareket;
}t_list;

void	ft_map_oku(t_list *depo, char *harita, int i);
void	ft_xpm_atama(t_list *depo);
void	ft_xpm_bas(t_list *depo, int a, int b);
int		ft_x_bul(t_list *depo, char *harita);
int		ft_y_bul(t_list *depo, char *harita);
void	ft_player_xy(t_list *depo);
char	*ft_itoa(int n);
int		ft_map_kontrol(t_list *depo);
#endif