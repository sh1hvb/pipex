/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchihab <mchihab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 17:51:41 by mchihab           #+#    #+#             */
/*   Updated: 2024/03/06 20:29:20 by mchihab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_next(char *s1, char *s2)
{
	char	*str;
	int		len;

	if (!s1 && !s2)
		return (NULL);
	else if (!s1)
		return (ft_strdup(s2));
	else if (!s2)
		return (ft_strdup(s1));
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	str = malloc(len * sizeof(char));
	if (!str)
		return (str);
	str[0] = '\0';
	ft_strlcat(str, s1, ft_strlen(s1) + 1);
	ft_strlcat(str, s2, len);
	free(s1);
	return (str);
}

char	*ft_sstrchr(const char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s && *s != (char) c)
		s++;
	if (*s == (char) c)
		return ((char *) s);
	return (NULL);
}

char	*read_all(int fd, char *last)
{
	char	*buf;
	int		size;

	buf = malloc(((size_t)BUFFER_SIZE + 1) * sizeof(char));
	if (!buf)
		return (free(last), NULL);
	size = 1;
	while (!ft_sstrchr(last, '\n') && size)
	{
		size = read(fd, buf, BUFFER_SIZE);
		if (size < 0)
		{
			free(buf);
			free(last);
			return (NULL);
		}
		buf[size] = '\0';
		last = ft_strjoin_next(last, buf);
	}
	free(buf);
	return (last);
}

static char	*read_line(char *src)
{
	char	*dst;
	int		i;

	i = 0;
	if (!src || src[i] == '\0')
		return (NULL);
	while (src[i] && src[i] != '\n')
		i++;
	if (src[i] && src[i] == '\n')
		i++;
	dst = malloc((i + 1) * sizeof(char));
	if (!dst)
		return (NULL);
	ft_strlcpy(dst, src, i + 1);
	return (dst);
}

static char	*move_last(char *src)
{
	char	*left;
	int		i;
	int		len;

	i = 0;
	if (!src || !src[i])
		return (NULL);
	while (src[i] && src[i] != '\n')
		i++;
	if (!src[i])
		return (NULL);
	len = ((ft_strlen(src) - i) + 1);
	left = malloc(len * sizeof(char));
	if (!left)
		return (NULL);
	else
		ft_strlcpy(left, src + i + 1, len);
	return (left);
}

char	*get_next_line(int fd)
{
	static char	*last;
	char		*return_line;
	char		*tmp_all;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	tmp_all = read_all(fd, last);
	return_line = read_line(tmp_all);
	last = move_last(tmp_all);
	free(tmp_all);
	return (return_line);
}