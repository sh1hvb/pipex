/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchihab <mchihab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 20:35:54 by mchihab           #+#    #+#             */
/*   Updated: 2024/03/07 19:56:25 by mchihab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "pipex_bonus.h"

void setup_input_output(int ac, char *av[], int *fd_in, int *fd_out) 
{
    int status;
    if (ft_strcmp(av[1], "here_doc") == 0) 
    {
        if (ac < 6)
            exit(0);
        *fd_out = open(av[ac - 1], O_CREAT | O_RDWR | O_TRUNC, 0777);
        if (fd_out < 0)
        {
            perror("error open out_file");
            exit(1);
        }
        herdoc(av);
    } 
    else 
    {
        *fd_in = open(av[1], O_RDONLY);
        *fd_out = open(av[ac - 1], O_CREAT | O_WRONLY | O_TRUNC, 0777);
        if (*fd_out < 0 || *fd_in < 0)
        {
            perror("error open out_file | in_file");
            exit(1);
        }
        dup2(*fd_in, 0);
    }
}

void create_pipes_and_execute(int ac, char *av[], char *env[], int fd_out)
{
    int (i) , (status) , (pid) ;
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

}

void here_doc_puts(char **av, int *fdp){
    int i;
    char *line;
    char *delimiter; 

    delimiter = ft_strjoin(av[2], "\n");
    close(fdp[0]);
    while (1) {  
        write(1, "heredoc> ", 9);
        line = get_next_line(0);
        if (strcmp(line, delimiter) == 0 || !line) {
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
        wait(NULL);
}
       


int main(int ac, char *av[], char *env[]) 
{
    int fd_out;
    int fd_in;
    int status;
    if (ac < 5 )
        handle_error("invalid input! ?");
    if(!(*env))
        handle_error("cannot find the envirenments");
    setup_input_output(ac, av, &fd_in, &fd_out);
    create_pipes_and_execute(ac, av, env, fd_out);
    while (waitpid(-1, &status, 0) != -1)
	{
	if (WEXITSTATUS(status) == 127 || WEXITSTATUS(status) == 1)
			exit(WEXITSTATUS(status));
	}
    return 0;
}



