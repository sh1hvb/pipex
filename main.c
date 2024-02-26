#include <stdio.h>
#include <unistd.h>
#include "./libft/libft.h"
char *get_pathi(char *env[] );char *check_cmd(char **splited , char *av);void exec(char **av , char **env);

void child_process(int fds , char *av[] , char *env[])
{
	int fd ;

	if(!fd || !(*av) || !(*env))
		perror("not valid !");
	if(dup2(fds , 0) == -1){
		perror("dup2");
		close(fds);
	}
	fd = open(av[1] , O_RDONLY );
	if(dup2(fd , 1) == -1){
		perror("dup2");
		close(fd);
	}
	close(fd);
	close(fds);
	exec(av , env);
}
void parent_process(int fds , char *av[] , char *env[])
{
	int fd ;

	if(!fd || !(*av) || !(*env))
		perror("not valid !");
	if(dup2(fds , 1) == -1){
		perror("dup2");
		close(fds);
	}
	fd = open(av[4] , O_RDONLY , O_CREAT , O_TRUNC , 0777);
	if(dup2(fd , 0) == -1){
		perror("dup2");
		close(fd);
	}
	close(fd);
	close(fds);
	exec(av , env);
}
void exec(char **av , char **env)
{
	if(!(*av) || !(*env))
		perror("not valid!");
	char *path =ft_substr( get_pathi(env), 5 , 50);
	char **splited = ft_split(path , ':');
	char **cmd = ft_split(av[1] , ' ');
	char *check;
	char *cmd1;
	if((cmd1 = check_cmd(splited , av[1])))
		if(execve(cmd1 , cmd , env) == -1)
			perror("execve");

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
	if(!pid)
		child_process(fds[0] ,av, env);
	else
		parent_process(fds[1] , av , env);
		wait(NULL);
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
	return env[i];
}