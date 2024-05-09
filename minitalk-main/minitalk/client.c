/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uercan <uercan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 13:46:09 by uercan            #+#    #+#             */
/*   Updated: 2022/07/03 15:02:36 by uercan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>

int	ft_atoi(const char *str);

void	ft_bitsend(int j, char **argv, int i)
{
	if (argv[2][i] & (1 << j))
	{
		kill(ft_atoi(argv[1]), SIGUSR2);
		usleep(50);
	}
	else
	{
		kill(ft_atoi(argv[1]), SIGUSR1);
		usleep(50);
	}
}

int	main(int argc, char **argv)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (argc == 3)
	{
		while (argv[2][i])
		{
			j = 0;
			while (j < 8)
			{
				ft_bitsend(j, argv, i);
				j++;
			}
			i++;
		}
	}
	return (0);
}
