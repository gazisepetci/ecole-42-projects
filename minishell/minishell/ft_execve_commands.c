/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve_commands.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsepetci <gsepetci@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 10:45:50 by gsepetci          #+#    #+#             */
/*   Updated: 2023/02/10 15:53:20 by gsepetci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_redirect_run_commands(char **new_input)
{
	char	*temp;
	char	*res;
	char	**str;
	int		i;

	i = 0;
	res = "";
	while (ft_redirect_comparison_0(new_input[i]) == 0)
	{
		res = ft_strjoin(res, new_input[i]);
		if (ft_redirect_comparison_0(new_input[i + 1]) == 0)
			res = ft_strjoin(res, " ");
		i++;
	}
	temp = ft_acces(*new_input);
	free(res);
	if (execve(temp, new_input, g_envs) == -1)
	{
		perror("");
		exit(1);
	}
	exit(1);
	perror("");
}

static void	ft_pipe_function_run(char ***str, char *input, char **env)
{
	int	**fd;
	int	pid;
	int	p;
	int	i;

	i = 0;
	p = 1;
	fd = ft_pipe_malloc(fd, ft_pipe_control(input));
	pid = fork();
	if (pid == 0)
	{
		if (ft_redirect_comparison(str[0]) == 2)
		{
			ft_redirect_dup(str[i]);
			dup2(fd[0][1], 1);
			ft_run_commands(str[i], 0, env);
		}
		else if (ft_redirect_comparison(str[0]) != 2 && ft_redirect_comparison(str[0]) > 0)
		{
			dup2(fd[0][1], 1);
			ft_redirect_dup(str[i]);
		}
		else if (ft_is_build(str[i], env))
		{
			dup2(fd[0][1], 1);
			ft_build(str[i], env);
		}
		else
		{
			dup2(fd[0][1], 1);
			ft_close_pipe(fd, 0, 0);
			ft_run_commands(str[i], 0, env);
		}
	}
	waitpid(pid, NULL, 0);
	i = 1;
	while (str[i])
	{
		pid = fork();
		if (pid == 0)
		{
			if (i != ft_pipe_control(input) && ft_redirect_comparison(str[i]) == 0)
				dup2(fd[i][1], 1);
			if (ft_redirect_comparison(str[i]) == 2)
			{
				ft_redirect_dup(str[i]);
				dup2(fd[i][1], 1);
				dup2(fd[i - 1][0], 0);
				ft_run_commands(str[i], 0, env);
			}
			else if (ft_is_build(str[i], env))
			{
				//dup2(fd[i - 1][0], 0);
				dup2(fd[i][1], 1);
				ft_build(str[i], env);
			}
			else
			{
				dup2(fd[i - 1][0], 0);
				ft_close_pipe(fd, i, 1);
				ft_run_commands(str[i], 0, env);
			}
		}
		i++;
	}
	ft_close_pipe(fd, ft_pipe_control(input), 1);
	waitpid(pid, NULL, 0);
	free(input);
	ft_free(str);
}

char	*ft_dolar(char *str)
{
	char	*b;
	char	*a;
	char	*c;

	int (i) = 0;
	int (j) = 0;
	int (t) = 0;
	int (y) = 0;
	int (p) = 0;
	y = ft_dolarnumber(str);
	a = malloc(sizeof(char *) * 1000);
	while (str[j])
	{
		if (str[j] == '$')
		{
			c = malloc(sizeof(char *) * 1000);
			j++;
			while (str[j] != ' ' && str[j])
			{
				c[i] = str[j];
				i++;
				j++;
			}
			c[i] = '\0';
			b = getenv(c);
			free(c);
			break ;
		}
		j++;
	}
	j = 0;
	i = 0;
	int (check) = 0;
	while (str[j])
	{
		if (str[j] == '$' && check == 0)
		{
			check = 1;
			while (str[j] != ' ' && str[j])
				j++;
			while (b[t])
			{
				a[i] = b[t];
				t++;
				i++;
			}
		}
		a[i] = str[j];
		i++;
		j++;
	}
	a[i] = '\0';
	return (a);
}

static char	*ft_cd_split(char *input)
{
	int		i;
	char	**temp;
	char	*res;
	char	*re;

	i = 0;
	re = "";
	temp = ft_split(input, '/');
	while (temp[i + 2])
	{
		temp[i] = ft_strjoin(temp[i], "/");
		i++;
	}
	i = 0;
	while (temp[i + 1])
		re = ft_strjoin(re, temp[i++]);
	return (re);
}

int	ft_env_index(char **env, char *res)
{
	int		i;
	char	**temp;

	i = 0;
	while (env[i])
	{
		temp = ft_split(env[i], '=');
		if (ft_strcmp(temp[0], res))
			return (i);
		i++;
	}
	return (-1);
}

char	*ft_cd_path(char *input)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	j = 0;
	while (input[i])
		i++;
	while (input[i--] != '/')
		j++;
	temp = malloc(sizeof(char) * j + 1);
	j = 0;
	while (input[i])
	{
		temp[j] = input[i];
		i++;
		j++;
	}
	temp[j] = '\0';
	return (temp);
}

static void	ft_old_pwd(char **input, char **env)
{
	char	*src;
	char	**res;

	res = ft_env_searc(env, "PWD");
	src = malloc(sizeof(char) * (ft_strlen(res[1]) + 5));
	src = ft_strjoin(src, "OLDPWD=");
	src = ft_strjoin(src, res[1]);
	env[ft_env_index(env, "OLDPWD")] = src;
}

int	ft_cd_run(char **input, char **env)
{
	int		i;
	char	*temp;
	char	*src;
	char	**res;

	if (ft_strlen_2(input) == 1)
	{
		ft_old_pwd(input, env);
		res = ft_env_searc(env, "HOME");
		chdir(res[1]);
		src = malloc(sizeof(char) * (ft_strlen(res[1]) + 5));
		src = ft_strjoin(src, "PWD=");
		src = ft_strjoin(src, res[1]);
		env[ft_env_index(env, "PWD")] = src;
	}
	else
	{
		ft_old_pwd(input, env);
		i = chdir(input[1]);
		if (ft_strcmp(input[1], ".."))
		{
			res = ft_env_searc(env, "PWD");
			src = malloc(sizeof(char) * (ft_strlen(res[1]) + 5));
			src = ft_strjoin(src, "PWD=");
			src = ft_strjoin(src, "/");
			src = ft_strjoin(src, ft_cd_split(res[1]));
			env[ft_env_index(env, "PWD")] = src;
		}
		else
		{
			if (i == 0 && input[1][0] == '/')
			{
				ft_old_pwd(input, env);
				chdir(input[1]);
				src = ft_strjoin("PWD=", input[1]);
				env[ft_env_index(env, "PWD")] = src;
			}
			else if (i == 0)
			{
				res = ft_env_searc(env, "PWD");
				src = ft_strjoin("PWD=", res[1]);
				src = ft_strjoin(src, "/");
				src = ft_strjoin(src, input[1]);
				env[ft_env_index(env, "PWD")] = src;
			}
		}
	}
	return (0);
}

void	ft_execve_commands(char *input, char **env)
{
	char	**new_input;
	int		pipe_len;
	int		i;
	int		j;

	j = 0;
	input = ft_dolar(input);
	pipe_len = ft_pipe_control(input);
	if (pipe_len == 0)
	{
		if (ft_redirect_count(input) > 0)
				input = ft_redirect(input, 0, 0);
		input = ft_strtrim(input, ' ');
		input = ft_echo_control(input);
		new_input = ft_split(input, ' ');
		new_input = ft_echo_reverse(new_input);
		if (ft_exit(new_input[0]) == 0)
			is_exits(new_input);
		else if (ft_strcmp(new_input[0], "cd"))
		{
			ft_cd_run(new_input, env);
			return ;
		}
		i = fork();
		if (ft_redirect_comparison(new_input) && i == 0)
			ft_redirect_dup(new_input);
		else if (i == 0 && ft_is_build(new_input, env) == 0)
			ft_run_commands(new_input, 0, env);
		else if (i == 0 && ft_is_build(new_input, env) == 1)
			ft_build(new_input, env);
		else if (i == 0)
			exit(1);
		waitpid(i, NULL, j);
		ft_free_2(new_input);
		free(input);
	}
	else
		ft_pipe_function_run(ft_pipe_arr(ft_pipe_control(input), input), input, env);
}
