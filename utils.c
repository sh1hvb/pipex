/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchihab <mchihab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 20:36:00 by mchihab           #+#    #+#             */
/*   Updated: 2024/03/04 12:39:20 by mchihab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "pipex.h"

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
    int status;
	close(fds[0]);
	close(fds[1]);
	while (waitpid(-1, &status, 0) != -1)
		{
			if (WEXITSTATUS(status) == 2 || WEXITSTATUS(status) == 1)
				exit(WEXITSTATUS(status));
		}
}
char *check_cmd(char **splited, char *av) {
    int i;
    char *cmd_path;

    i = 0;
    if (access(av, X_OK) == 0)
            return av;
    while (splited[i])
    {
        cmd_path = ft_strjoin(splited[i], av);
            printf("%s\n", cmd_path);
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