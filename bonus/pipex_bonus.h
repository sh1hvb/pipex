/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchihab <mchihab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 20:35:57 by mchihab           #+#    #+#             */
/*   Updated: 2024/03/06 20:17:23 by mchihab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
#define PIPEX_BONUS_H
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include "libft/libft.h"
#include<sys/wait.h>

#ifndef here_doc
#define her_doc 
#endif
typedef struct s_env
{
	char **env;
	char *path_dplited[];
}t_env;
char *get_path(char *env[] );
char *check_cmd(char **splited , char *av);
void exec(char *av , char **env);
void ft_close(int *fds);
void ft_free(char **str);void herdoc(char **av);
void here_doc_puts(char **av, int *fdp);


#endif