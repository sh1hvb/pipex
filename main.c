/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchihab <mchihab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 20:35:54 by mchihab           #+#    #+#             */
/*   Updated: 2024/02/28 22:32:00 by mchihab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "pipex.h"

void child_process(int *fds, char *av[], char *env[]) {
    int fd;

    if (!fds) {
        perror("not valid!");
        exit(1); 
    }
	close(fds[0]);
    if (dup2(fds[1], 1) == -1) {
        perror("dup2 child");
        close(fds[0]);
        exit(1); 
    }

    fd = open(av[1], O_RDONLY);
    if (fd == -1) {
        perror("open child");
        close(fds[0]);
        exit(1);
    }

    if (dup2(fd, 0) == -1) {
        perror("dup2 child");
        close(fd);
        exit(1);
    }
    exec(av[2], env, fds[0]); 
    perror("execve"); 
    exit(2); 
}
void ft_close(int *fds)
{
    int status;
	close(fds[0]);
	close(fds[1]);
	while (waitpid(-1, &status, 0) != -1)
		{
			if (WEXITSTATUS(status) == 2 || WEXITSTATUS(status) == 1)
				exit(WEXITSTATUS(status));
		}
}
void parent_process(int *fds, char *av[], char *env[]) {
    int fd;

    if (!fds) {
        perror("not valid!");
        exit(1);
    }
    fd = open(av[4], O_CREAT | O_WRONLY | O_TRUNC, 0666);
	close(fds[1]);
    if (fd == -1) {
        perror("open parent");
        close(fds[1]);
        exit(1);
    }
    if (dup2(fd, 1) == -1) {
        perror("dup2 parent 0");
        close(fds[1]);
        exit(1);
    }
    if (dup2(fds[0], 0) == -1) {
        perror("dup2 parent 1");
        close(fd);
        exit(1);
    }
    // system("leaks a.out ");
    exec(av[3], env, fds[0]); 
    perror("execve");
    exit(2);
}

void exec(char *av, char **env, int fd) {
    if (!av || !env) {
        perror("not valid!");
        exit(1);
    }

    char *path = ft_substr(get_path(env), 5, 50);
    char **splited = ft_split(path, ':');
    char **cmd = ft_split(av, ' ');

    char *cmd1 = check_cmd(splited, cmd[0]);
    printf("%s\n", cmd1); printf("jidaj\n");

    if (cmd1){
        if (execve(cmd1, cmd, env) == -1) {

            free(path); 
            ft_free(splited); 
            ft_free(cmd);
            perror("execve");

            exit(2);
        }
     } 
    free(path); 
    ft_free(splited); 
    ft_free(cmd);
}


int main(int ac, char *av[], char *env[]) {
    int fds[2];
    int pid;
	// char **p =ft_split(get_path(env) , ' ');
	// char **k =ft_split(av[2], ' ');
    if (ac != 5) {
        perror("");
        exit(1);
    }

    if (pipe(fds) == -1) {
        perror("pipe:");
        exit(1);
    }

    pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(1);
    }

	if(!pid)
		child_process(fds ,av, env);
	else
	{
		int id =fork();
		if (id == 0)
			parent_process(fds , av , env);
		else 
            ft_close(fds);
    // system("leaks a.out");

	}
}

char *check_cmd(char **splited, char *av) {
    int i = 0;
    if (access(av, X_OK) == 0)
            return av;
    while (splited[i]) {
        char *cmd_path = ft_strjoin(splited[i], av);
            if (access(cmd_path, X_OK) == 0)
            return cmd_path;
        free(cmd_path);
        
        i++;
    }
    return NULL;
}

char *get_path(char *env[]) {
    int i = 0;
    char *path_string = NULL;
    char *path;
    while (env[i]) {
        if (ft_strnstr(env[i], "PATH=", 5)) {
            path_string = ft_substr(env[i], 5, ft_strlen(env[i]) - 5);
            break;
        }
        i++;
    }
    path = path_string;
    free(path_string);
    return path;
}