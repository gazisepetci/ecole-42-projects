/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_aq_tmf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsepetci <gsepetci@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 22:58:14 by gsepetci          #+#    #+#             */
/*   Updated: 2023/02/10 05:11:27 by gsepetci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free(char ***temp)
{
	int	i;
	int	j;

	i = 0;
	j = 0;

	while (temp[j])
	{
		i = 0;
		while (temp[j][i])
		{
			free(temp[j][i]);
			i++;
		}
		j++;
	}
	free(temp[0]);
	free(temp[1]);
	free(temp[2]);
}
