/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchihab <mchihab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 02:24:33 by mchihab           #+#    #+#             */
/*   Updated: 2024/02/22 23:36:42 by mchihab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PIPEX_H
#define PIPEX_H

typedef struct s_env{
    char **PATH;
    char **ENV;  
} t_env;

typedef struct s_cmd{
    char*path;
    char*args;  
} t_cmd;

char *get_path(char *env[] );
char *check_cmd(char **splited , char *av);

#endif