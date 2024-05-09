/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_build_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsepetci <gsepetci@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 22:58:14 by gsepetci          #+#    #+#             */
/*   Updated: 2023/02/10 15:08:00 by gsepetci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_build(char **input, char **env)
{
	if (ft_strcmp(input[0], "export"))
		ft_export(input, env);
	else if (ft_strcmp(input[0], "env"))
		ft_env(input, env);
	else if (ft_strcmp(input[0], "unset"))
		ft_unset(input, env);
	else if (ft_strcmp(input[0], "echo"))
		ft_echo(input, env);
	else if (ft_strcmp(input[0], "pwd"))
		ft_pwd(input, env);
}

int	ft_is_build(char **input, char **env)
{
	if (ft_strcmp(input[0], "export"))
		return (1);
	else if (ft_strcmp(input[0], "env"))
		return (1);
	else if (ft_strcmp(input[0], "unset"))
		return (1);
	else if (ft_strcmp(input[0], "echo"))
		return (1);
	else if (ft_strcmp(input[0], "pwd"))
		return (1);
	return (0);
}

void	sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
		//rl_replace_line("", 0);
	}
}

int	ft_export_upgrade(char **input, char **env)
{
	int		i;
	char	**temp;
	char	**res;

	i = 0;
	res = ft_split(input[1], '=');
	while (env[i])
	{
		temp = ft_split(env[i], '=');
		if (ft_strcmp(res[0], temp[0]))
			return (i);
		free(temp);
		i++;
	}
	ft_free_2(temp);
	ft_free_2(res);
	return (-1);
}
