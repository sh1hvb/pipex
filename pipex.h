/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchihab <mchihab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 20:35:57 by mchihab           #+#    #+#             */
/*   Updated: 2024/02/27 20:35:58 by mchihab          ###   ########.fr       */
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
void exec(char *av , char **env , int fd);
void ft_free(char **str);

#endif