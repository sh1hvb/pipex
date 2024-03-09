/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchihab <mchihab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 20:35:54 by mchihab           #+#    #+#             */
/*   Updated: 2024/03/09 17:22:55 by mchihab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "pipex_bonus.h"

void setup_input_output(int ac, char *av[], int *fd_in, int *fd_out) 
{
    if (ft_strcmp(av[1], "here_doc") == 0) 
    {
        if (ac < 6)
            handle_error("./a.out fd_in cmd1 cmd2 fd_out\n");
        *fd_out = open(av[ac - 1], O_CREAT | O_RDWR | O_TRUNC, 0777);
        if (*fd_out < 0)
            handle_error("can't open file");
        herdoc(av);
    } 
    else 
    {
        *fd_in = open(av[1], O_RDONLY);
        *fd_out = open(av[ac - 1], O_CREAT | O_WRONLY | O_TRUNC, 0777);
        if (*fd_out < 0 || *fd_in < 0)
            handle_error("error open out_file | in_file");
        dup2(*fd_in, 0);
    }
}

void create_pipes_and_execute(int ac, char *av[], char *env[], int fd_out)
{
    int (i) , (pid) ;
    if(ft_strcmp(av[1], "here_doc") == 0)
        i = 3;
    else 
        i = 2;
    while (i < ac - 2) {
        add_pipe(av[i], env);
        i++;
    }
    pid = fork();
    if (!pid)
    {
        dup2(fd_out, 1);
        exec(av[ac - 2], env);
    }
    wait(NULL);
 }

void here_doc_puts(char **av, int *fdp){
    char (*line) , (*delimiter); 

    delimiter = ft_strjoin(av[2], "\n");
    while (1) 
    {  
        write(1, "heredoc> ", 9);
        line = get_next_line(0);
        if (!line || strcmp(line, delimiter) == 0) {
            free(delimiter);
            delimiter = NULL;
            free(line);
            line = NULL;
            exit(1) ;
        }
        ft_putstr_fd(line , fdp[1]);
        free(line); 
    }
    close(fdp[1]);
    free(delimiter);  
}

void herdoc(char **av)
{
    int fds[2];
    int pid;

    if(pipe(fds) == -1)
        handle_error("pipe");
    pid = fork();
    if(pid == -1)
        handle_error("fork");
    if(!pid)
        here_doc_puts(av , fds);
    close(fds[1]);
    if(dup2(fds[0],0) == -1)
        handle_error("dup2");
}
       
int main(int ac, char *av[], char *env[]) 
{
    int fd_out;
    int fd_in;

    if (ac < 5 || !(*av))
        handle_error("invalid input! ?");
    if(!(env))
        handle_error("cannot find the envirenments");
    setup_input_output(ac, av, &fd_in, &fd_out);
    create_pipes_and_execute(ac, av, env, fd_out);
}



