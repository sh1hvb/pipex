/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchihab <mchihab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 20:35:57 by mchihab           #+#    #+#             */
/*   Updated: 2024/03/10 14:47:41 by mchihab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H
# include "../libft/libft.h"
# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

void	add_pipe(char *p, char *env[]);
void	handle_error(char *msg, int ex);
void	exec(char *av, char **env);
char	*get_path(char *env[]);
char	*check_cmd(char **splited, char *av);
void	exec(char *av, char **env);
void	ft_free(char **str);
void	herdoc(char **av);
void	here_doc_puts(char **av, int *fdp);
void	ft_close(int *fds);
void	handle_error(char *msg, int ex);

#endif