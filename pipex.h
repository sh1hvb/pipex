/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchihab <mchihab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 02:24:33 by mchihab           #+#    #+#             */
/*   Updated: 2024/03/08 22:20:33 by mchihab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PIPEX_BONUS_H
#define PIPEX_BONUS_H
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include "libft/libft.h"
#include<sys/wait.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>

#define handle_error(msg , ex) { perror(msg); exit(ex); }

void add_pipe(char *p, char *env[]);
void exec(char *av, char **env);
char *get_path(char *env[] );
char *check_cmd(char **splited , char *av);
void exec(char *av , char **env);
void ft_free(char **str);void herdoc(char **av);
void here_doc_puts(char **av, int *fdp);


#endif