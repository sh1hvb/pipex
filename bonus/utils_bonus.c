/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchihab <mchihab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 20:36:00 by mchihab           #+#    #+#             */
/*   Updated: 2024/03/10 14:55:51 by mchihab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_free(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
	*str = NULL;
}

char	*check_cmd(char **splited, char *av)
{
	int		i;
	char	*cmd_path;

	i = 0;
	cmd_path = NULL;
	if (access(av, X_OK) == 0)
		return (av);
	while (splited[i])
	{
		cmd_path = ft_strjoin_ws(splited[i], av);
		if (access(cmd_path, X_OK) == 0)
			return (cmd_path);
		free(cmd_path);
		i++;
	}
	return (NULL);
}

char	*get_path(char *env[])
{
	int		i;
	char	*path_string;

	i = 0;
	path_string = NULL;
	while (env[i])
	{
		if (ft_strnstr(env[i], "PATH=", 5))
		{
			path_string = ft_substr(env[i], 5, ft_strlen(env[i]) - 5);
			break ;
		}
		i++;
	}
	return (path_string);
}

void	add_pipe(char *p, char *env[])
{
	int	fds[2];
	int	pid;

	if (pipe(fds) == -1)
		perror("pipe:");
	pid = fork();
	if (pid == -1)
		perror("fork");
	if (!pid)
	{
		close(fds[0]);
		dup2(fds[1], 1);
		exec(p, env);
	}
	close(fds[1]);
	dup2(fds[0], 0);
}

void	exec(char *av, char **env)
{
	char	**splited;
	char	**cmd;
	char	*path;
	char	*cmd1;

	path = get_path(env);
	splited = ft_split(path, ':');
	cmd = ft_split(av, ' ');
	cmd1 = check_cmd(splited, cmd[0]);
	if (execve(cmd1, cmd, env) < 0)
	{
		free(path);
		free(cmd1);
		ft_free(splited);
		ft_free(cmd);
		perror("cmd not found");
		exit(EXIT_FAILURE);
	}
}
