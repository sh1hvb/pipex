#include <stdio.h>
#include <unistd.h>
#include "./libft/libft.h"
#include "pipex.h"
char *get_pathi(char *env[] );char *check_cmd(char **splited , char *av);
int main(int ac, char *av[], char *env[])
{

	char *path = get_path(env);
	int fdp[2];
	char **p = ft_split(path, ':');
	char **sp = ft_split(av[1] , ' ');
	char *cmd = check_cmd(p, sp[0]);
	int fd = open(av[2], O_CREAT | O_RDWR | O_TRUNC, 0666);
	int fd2 = open(av[4], O_RDONLY);
	dup2(fdp[0], 0);
	dup2(fdp[1], 1);
	int pid;
	pid = fork();
	if (pid == -1)
		perror("err");
	if (pid == 0)
	{
		if (execve(cmd , sp , env) == -1)
	 		perror("okay");
	}
}
char *check_cmd(char **splited , char *av)
{
	int i = 0;
	while(splited[i])
	{
		splited[i] = ft_strjoin(splited[i] , "/");
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