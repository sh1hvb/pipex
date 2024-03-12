/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchihab <mchihab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 20:35:54 by mchihab           #+#    #+#             */
/*   Updated: 2024/03/12 21:00:46 by mchihab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
		path = NULL;
		free(cmd1);
		cmd1 = NULL;

		ft_free(splited);
		ft_free(cmd);
		handle_error("cmd not found", 127);
	}
}

void	child_process(int *fds, char *av[], char *env[])
{
	int	fd;

	if (!fds)
		handle_error("Error : file can't open ", 1);
	close(fds[0]);
	if (dup2(fds[1], 1) == -1)
	{
		close(fds[0]);
		handle_error("Error : dup2", 1);
	}
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
	{
		close(fds[0]);
		handle_error("Error : file not found\n", 127);
	}
	if (dup2(fd, 0) == -1)
	{
		close(fd);
		handle_error("Error : file can't open ", 1);
	}
	exec(av[2], env);
}

void	tnd_child_process(int *fds, char *av[], char *env[])
{
	int	fd;

	if (!fds)
		handle_error("Error : file can't open ", 1);
	fd = open(av[4], O_CREAT | O_WRONLY | O_TRUNC, 0666);
	close(fds[1]);
	if (fd == -1)
	{
		close(fds[1]);
		handle_error("Error : file can't open ", 1);
	}
	if (dup2(fd, 1) == -1)
	{
		close(fds[1]);
		handle_error("Error : dup2 ", 1);
	}
	if (dup2(fds[0], 0) == -1)
	{
		close(fd);
		handle_error("Error : dup2 ", 1);
	}
	exec(av[3], env);
}

int	main(int ac, char *av[], char *env[])
{
	int	fds[2];
	int	pid;
	int	id;

	if (ac != 5)
		handle_error("invalid input!?", 1);
	if (pipe(fds) == -1)
		handle_error("pipe", 1);
	pid = fork();
	if (pid < 0)
		handle_error("fork", 1);
	if (!pid)
		child_process(fds, av, env);
	else
	{
		id = fork();
		if (id < 0)
			handle_error("fork", 1);
		if (id == 0)
			tnd_child_process(fds, av, env);
		else
			ft_close(fds);
	}
}
