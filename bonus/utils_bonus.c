/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchihab <mchihab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 20:36:00 by mchihab           #+#    #+#             */
/*   Updated: 2024/03/09 00:04:17 by mchihab          ###   ########.fr       */
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
void ft_free(char **str)

{
    int i;
    i = 0;
    while(str[i])
        free(str[i++]);
    free(str);
    *str =NULL;
}

char *check_cmd(char **splited, char *av) {
    int i;
    char *cmd_path;

    i = 0;
    cmd_path = NULL;
    if (access(av, X_OK) == 0)
            return av;
    while (splited[i])
    {
        cmd_path = ft_strjoin_ws(splited[i], av);
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
    while (env[i]) {
        if (ft_strnstr(env[i], "PATH=", 5)) {
            path_string = ft_substr(env[i], 5, ft_strlen(env[i]) - 5);
            break;
        }
        i++;
    }

    return path_string;
}
void add_pipe(char *p, char *env[])
{
    int fds[2];
    int pid;
    
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
    close(fds[1]);
    dup2(fds[0], 0);
}
void exec(char *av, char **env) 
{

    if (!av || !env) 
    {
        perror("not valid!");
        exit(1);
    }
    char *path = get_path(env); 
    char **splited = ft_split(path, ':');
    char **cmd = ft_split(av, ' ');
    char *cmd1 = check_cmd(splited, cmd[0]);
    if (access(cmd1, X_OK) != 0)
    {
        free(path); 
        ft_free(splited); 
        ft_free(cmd);
        perror("CMD Not found");
        exit(127);

    }
    if (execve(cmd1, cmd, env) == -1)
    {
        free(path); 
        ft_free(splited); 
        ft_free(cmd);
        perror("execve");
        exit(1);
    }
}