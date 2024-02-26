#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "./libft/libft.h"

char *get_pathi(char *env[]);
char *check_cmd(char **splited, char *av);

int main(int ac, char *av[], char *env[])
{
    int pid;
    int fdp[2];
    int fd_in;
    int fd_out;
    char *path = get_pathi(env);
    char **path_split = ft_split(path, ':');
    char *cmd1 = check_cmd(path_split, av[2]);
    char *cmd2 = check_cmd(path_split, av[3]);
    char buf[50];
    
    fd_in = open(av[1], O_RDONLY);
    fd_out = open(av[4], O_CREAT | O_WRONLY | O_TRUNC, 0666);

    dup2(fd_in, 0);
    dup2(fd_out, 1);

    pipe(fdp);
    pid = fork();

    if (pid == 0)
    {
        close(fdp[0]);
        dup2(fdp[1], STDOUT_FILENO);
        char **cmd1split = ft_split(av[2], ' ');
        execve(cmd1, cmd1split, env);
    }
    else
    {
        close(fdp[1]);
        dup2(fdp[0], STDIN_FILENO);
        char **cmd2split = ft_split(av[3], ' ');
        execve(cmd2, cmd2split, env);
        read(fdp[0], buf, sizeof(buf));
        buf[sizeof(buf) - 1] = '\0';
        printf("%s\n\n\n", buf);
    }

    close(fd_in);
    close(fd_out);

    return 0;
}

char *check_cmd(char **splited, char *av)
{
    int i = 0;
    while (splited[i])
    {
        splited[i] = ft_strjoin(splited[i], "/");
        splited[i] = ft_strjoin(splited[i], av);
        int a = access(splited[i], X_OK);
        if (a == 0)
            return splited[i];
        i++;
    }
    return NULL;
}

char *get_pathi(char *env[])
{
    int i = 0;
    char *path = NULL;
    while (env[i])
    {
        path = ft_strnstr(env[i], "PATH", 4);
        if (path)
            break;
        i++;
    }
    return path;
}
