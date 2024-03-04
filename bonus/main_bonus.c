/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchihab <mchihab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 20:35:54 by mchihab           #+#    #+#             */
/*   Updated: 2024/03/04 12:22:50 by mchihab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "pipex_bonus.h"

// void ft_close(int *fds)
// {
//     int status;
// 	close(fds[0]);
// 	close(fds[1]);
// 	while (waitpid(-1, &status, 0) != -1)
// 		{
// 			if (WEXITSTATUS(status) == 2 || WEXITSTATUS(status) == 1)
// 				exit(WEXITSTATUS(status));
// 		}
// }
void here_doc_puts(char **av , int *fds)
{
    int i;
    char *line;
    char *cmp;

    cmp = ft_strjoin(av[2], "\n");
    printf("%s",ft_strjoin(av[2], "\n"));
    while (1)
    {
        line = get_next_line(0);
        printf("%d\n", ft_strncmp(line , cmp , ft_strlen(cmp)));
        if(!ft_strncmp(line , cmp , ft_strlen(line)))
        {
            free(cmp);
            free(line);
            exit(0);
        }
        ft_putstr_fd(line , fds[1]);
        close(fds[1]);
    }
}

void herdoc(char **av)
{
    int fds[2];
    int pid;
    int n;
    
    if(pipe(fds) == -1)
        perror("pipe:");
    pid = fork();
    if(pid == -1)
        perror("fork");
    if(!pid)
        here_doc_puts(av, fds);
    else
    {
        n = fork();
        if(!n)
            dup2(fds[0], 0);
        else
        {
            close(fds[1]);
            wait(NULL);
        }
    }
        
}
void exec(char *av, char **env) {
    if (!av || !env) 
    {
        perror("not valid!");
        exit(1);
    }
    char *path = get_path(env);
    char **splited = ft_split(path, ':');
    char **cmd = ft_split(av, ' ');
    char *cmd1 = check_cmd(splited, cmd[0]);
    if (cmd1)
    {
        if (execve(cmd1, cmd, env) == -1)
        {
            free(path); 
            ft_free(splited); 
            ft_free(cmd);
            perror("execve");
            exit(3);
        }
    }
}


void add_pipe(char *p, char *env[])
{
    int fds[2];
    int pid;
    int n ;
    if(pipe(fds) == -1)
        perror("pipe:");
    pid = fork();
    if(pid == -1)
        perror("fork");
    if(!pid)
    {
        close(fds[0]);
        dup2(fds[1], 1);
        exec(p,env);
    }
    else
    {
        close(fds[1]);
        dup2(fds[0], 0);
        wait(NULL);
    }  
}

int main(int ac, char *av[], char *env[]) 
{
    int fd_out;
    int fd_in;
    int i;
    
    i = 0;
    if (ac < 5)
        exit(0);
    printf("%d\n", ft_strcmp(av[1] , "here_doc" ));
    if(ft_strcmp(av[1] , "here_doc" ) == 0)
    {
        if(ac < 6)
            exit(0);
        i = 3;
        fd_out = open(av[ac -1] , O_CREAT , O_RDWR , O_APPEND, 0777);
        dup2(fd_out,1);
        herdoc(av);
    }
    else
    {
        i = 2;
        fd_in = open(av[2] , O_RDONLY);
        fd_out = open(av[ac -1] , O_CREAT , O_RDWR , O_TRUNC, 0777);
    }
    while(i < ac -2)
        add_pipe(av[i++],env);
    dup2(fd_out, 1);
    // close(fd_in);
    // close(fd_out);
}