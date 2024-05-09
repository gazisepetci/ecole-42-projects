/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_build.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsepetci <gsepetci@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 22:58:14 by gsepetci          #+#    #+#             */
/*   Updated: 2023/02/10 14:58:46 by gsepetci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(char **input, char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strcmp(env[i], "..") == 0)
			printf("%s\n", env[i]);
		i++;
	}
	exit(1);
}

void	ft_export(char **input, char **env)
{
	int		i;
	char	*temp;

	temp = "";
	if (ft_export_upgrade(input, env) == -1)
	{
		while (env[i])
			i++;
		temp = ft_strjoin(temp, input[1]);
		env[i] = temp;
		env[++i] = NULL;
	}
	else
	{
		i = ft_export_upgrade(input, env);
		temp = ft_strjoin(temp, input[1]);
		env[i] = temp;
	}
	free(temp);
	exit(1);
}

void	ft_unset(char **input, char **env)
{
	int		i;
	char	**temp;

	i = 1;
	while (env[i])
	{
		temp = ft_split(env[i], '=');
		if (ft_strcmp(temp[0], input[1]))
		{
			env[i] = "..";
			break ;
		}
		i++;
	}
	ft_free_2(temp);
	exit(1);
}

void	ft_echo(char **input, char **env)
{
	int	i;

	if (ft_strcmp(input[1], "-n") == 0)
	{
		i = 1;
		while (input[i])
			printf("%s", input[i++]);
		printf("\n");
	}
	else
	{
		i = 2;
		while (input[i])
			printf("%s", input[i++]);
	}
	exit(1);
}

void	ft_pwd(char **input, char **env)
{
	char	**temp;

	temp = ft_env_searc(env, "PWD");
	printf("%s\n", temp[1]);
	ft_free_2(temp);
	exit(1);
}
