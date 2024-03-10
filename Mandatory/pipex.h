/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchihab <mchihab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 02:24:33 by mchihab           #+#    #+#             */
/*   Updated: 2024/03/10 09:23:04 by mchihab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "../libft/libft.h"
# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

void	handle_error(char *msg, int ex)
{
	perror(msg);
	exit(ex);
};
void	ft_close(int *fds);
void	add_pipe(char *p, char *env[]);
void	exec(char *av, char **env);
char	*get_path(char *env[]);
char	*check_cmd(char **splited, char *av);
void	exec(char *av, char **env);
void	ft_free(char **str);
#endif