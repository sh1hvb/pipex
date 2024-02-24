/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchihab <mchihab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 02:24:36 by mchihab           #+#    #+#             */
/*   Updated: 2024/02/24 15:30:23 by mchihab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include "./libft/libft.h"
#include "pipex.h"

void execute_cmd(char *path ,char *cmd , int fd ,int fd2)
{
	dup2(fd , 0);
	dup2(fd2 , 1);
	execve(env , cmd , env)
}
int main(int ac, char *av[], char *env[])
{

	char *path = get_path(env);
	int fdp[2];
	char **p = ft_split(path, ':');
	char **sp = ft_split(av[2] , ' ');
	char **sp2 = ft_split(av[3] , ' ');
	char *cmd = check_cmd(p, sp[0]);
	char *cmd2 = check_cmd(p, sp[0]);	
	char buf = malloc(20);
	int fd = open(av[2], O_CREAT | O_RDWR | O_TRUNC, 0666);
	int fd2 = open(av[4], O_RDONLY);
	pipe(fdp);


	pid1 = fork();
	
	if (pid1 == -1)
		perror("err");
	if (pid1 == 0)
		execute_cmd(env, cmd1, fd, fdp[1]);
	if (pid2 == 0)
		execute_cmd(env, cmd2, fdp[0], fd2);

	waitpid(0, NULL, 0);
}
char *check_cmd(char **splited , char *av)
{
	int i = 0;
	while(splited[i])
	{
		splited[i] = ft_strjoin(splited[i] , "/");// ./run_program check
		splited[i] = ft_strjoin(splited[i] , av);
		int a = access(splited[i], X_OK);
		if(a == 0)
			return splited[i];
		i++;
	}
	return NULL;
}

char *get_path(char *env[] )
{
	int i = 0 ;
	char *path = NULL;
	while(env[i])
	{
		path = ft_strnstr(env[i],"PATH", 4);
		if(path)
			break;
		i++;
	}
	return path;
}