/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchihab <mchihab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 20:36:00 by mchihab           #+#    #+#             */
/*   Updated: 2024/03/05 23:33:18 by mchihab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "pipex_bonus.h"

void ft_free(char **str)

{
    int i;
    i = 0;
    while(str[i])
        free(str[i++]);
    free(str);
    *str =NULL;
}

void ft_close(int *fds)
{
	close(fds[0]);
	close(fds[1]);
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