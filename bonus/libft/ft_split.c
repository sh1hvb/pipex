/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchihab <mchihab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 12:32:04 by mchihab           #+#    #+#             */
/*   Updated: 2024/02/11 21:31:50 by mchihab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <stdlib.h>

int	word_count(char const *s, char c)
{
    int i;
    int count;

    i = 0;
    count = 0;
    while (s[i])
    {
        if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
            count++;
        i++;
    }
    return (count);
}

int	word_length(char const *s, char c)
{
    int i;
    int len;

    i = 0;
    len = 0;
    while (s[i] != c && s[i] != '\0')
    {
        i++;
        len++;
    }
    return (len);
}

char	**f(char const *s, char c, char **result, int words_count)
{
    int i;
    int j;
    int w_len;

    while (*s == c)
        s++;
    i = -1;
    while (++i < words_count)
    {
        while (*s == c)
            s++;
        j = 0;
        w_len = word_length(s, c);
        result[i] = (char *)malloc(sizeof(char) * (w_len + 1));
        if (!(result[i]))
        {
            // Free memory in case of allocation failure
            while (--i >= 0)
                free(result[i]);
            free(result);
            return (NULL);
        }
        while (j < w_len)
        {
            result[i][j] = *s;
            s++;
            j++;
        }
        result[i][j] = '\0';
    }
    return (result);
}

char	**ft_split(char const *s, char c)
{
    char	**result;
    int		wcount;

    if (!s)
        return (NULL);
    wcount = word_count(s, c);
    result = (char **)malloc(sizeof(char *) * (wcount + 1));
    if (!(result))
        return (NULL);
    result = f(s, c, result, wcount);
    if (!result)
        return (NULL); // Allocation failure handled in the helper function
    result[wcount] = NULL;
    return (result);
}

// Add a function to free the memory allocated by ft_split
void	free_split_result(char **result)
{
    int i = 0;
    while (result[i])
    {
        free(result[i]);
        i++;
    }
    free(result);
}

// int main() {
//     char *a="chihab , habibi , come , to , 1337";
//     char c =',';
//     char **arr= ft_split(a,c);
//     size_t i = 0;
//     while( i <= 4)
//     {
//        printf("%s\n",arr[i++]);
//     }

//     return (0);
// }