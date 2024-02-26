#include <stdio.h>
#include <unistd.h>
#include "./libft/libft.h"
char *check_cmd(char **splited , char *av);char *get_pathi(char *env[] );
void exec(char **av , char **env)
{
	if(!(*av) || !(*env))
		perror("not valid!");
	char *cmd = get_pathi(env);
	printf("%s\n", cmd);
}
int main(int ac, char *av[], char *env[])
{
	int fds[2];
	int pid;

	if(ac < 5)
		exit(1);
	if(pipe(fds) == -1)
		perror("pipe:");
	pid = fork();
	if(pid < 0)
		perror("fork");
	// if(!pid)
	// 	child_process(fds[0] ,av, env);
	// else
	// 	parent_process(fds[1] , av , env);
	// 	wait(NULL);
}
char *check_cmd(char **splited , char *av)
{
	int i = 0;
	while(splited[i])
	{ splited[i] = ft_strjoin(splited[i] , "/");
		splited[i] = ft_strjoin(splited[i] , av);
		int a = access(splited[i], X_OK);
		if(a == 0)
			return splited[i];
		i++;
	}
	return NULL;
}

char *get_pathi(char *env[] )
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