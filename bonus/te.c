/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   te.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchihab <mchihab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 20:35:54 by mchihab           #+#    #+#             */
/*   Updated: 2024/03/05 16:53:23 by mchihab          ###   ########.fr       */
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
void here_doc_puts(char **av, int *fdp){
    int i;
    char *line;
    char *delimiter; 

    delimiter = malloc(strlen(av[2]) + 2);
    if (delimiter == NULL) {
        perror("malloc");
        exit(1);  
    }
    strcpy(delimiter, av[2]);
    strcat(delimiter, "\n");
    while ((line = get_next_line(0)) != NULL) {  
        if (strncmp(line, delimiter, strlen(delimiter)) == 0) {
            free(delimiter);
            delimiter = NULL;
            free(line);
            line = NULL;
            break ;
        }
        ft_putstr_fd(line , fdp[1]);
        free(line); 
    }
    free(delimiter);
}

// void herdoc(char **av)
// {
//     int fds[2];
//     int pid;
//     pid = fork();
//     if(pid == -1)
//     {
//         perror("fork");
//         exit(1);
//     }
//     if(!pid)
//     {
//         here_doc_puts(av, fds);
//     }
//     else
//     {
//         close(fds[1]);
//         dup2(fds[0], 0);
//         wait(NULL);
//     } 
// }
       
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
    ft_putstr_fd(cmd1, 2);
    ft_putstr_fd("\n", 2);
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
    int pid;
    int n ;
	int fds[2];

	pipe(fds);
    pid = fork();
    if(pid == -1)
        perror("fork");
    if(!pid)
    {
        close(fds[0]);
        dup2(fds[1], 1);
        exec(p,env);
    }
    dup2(fds[0], 0);
    close(fds[1]);
    close(fds[0]);
}

int main(int ac, char *av[], char *env[]) 
{
    int fd_out;
    int fd_in;
    int i;
    int fdp[2];

    pipe(fdp);
    i = 0;
    if (ac < 5)
        exit(0);
    if(ft_strcmp(av[1] , "here_doc" ) == 0)
    {
        if(ac < 6)
            exit(0);
        i = 3;
        fd_out = open(av[ac - 1] , O_CREAT | O_RDWR | O_APPEND, 0777);
        here_doc_puts(av, fdp);
    }
    else
    {
        i = 2;
        fd_in = open(av[2] , O_RDONLY);
        fd_out = open(av[ac -1] , O_CREAT | O_RDWR | O_TRUNC, 0777);
        dup2(fd_out, 0);
        
    }
    dup2(fdp[0], 0);
    while(i < ac - 2)
    {
        add_pipe(av[i],env);
        close(fdp[1]);
        close(fdp[0]);
        i++;
    }
	dup2(fd_out, 1);
    exec(av[ac - 2], env);
    close(fd_in);
    close(fd_out);
    close(fdp[1]);
    close(fdp[0]);
}