/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchihab <mchihab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 02:24:33 by mchihab           #+#    #+#             */
/*   Updated: 2024/03/04 12:38:50 by mchihab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
#define PIPEX_H
#include <stdio.h>
#include <unistd.h>
#include "./libft/libft.h"
#include<sys/wait.h>

char *get_path(char *env[] );
char *check_cmd(char **splited , char *av);
void exec(char *av , char **env);
void ft_free(char **str);
void ft_close(int *fds);

#endif