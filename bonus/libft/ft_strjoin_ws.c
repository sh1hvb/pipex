/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_ws.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchihab <mchihab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 12:46:00 by mchihab           #+#    #+#             */
/*   Updated: 2024/03/04 20:42:35 by mchihab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
char	*ft_strjoin_ws(char const *s1, char const *s2)
{
	char	*p;
	int		i;
	int		j;
	size_t	lens1;
	size_t	lens2;

	if (!s1 || !s2)
		return (0);
	lens1 = ft_strlen((char *)s2);
	lens2 = ft_strlen((char *)s1);
	p = (char *)malloc(sizeof(char) * lens1 + lens2 + 1);
	if (!p)
		return (0);
	i = 0;
	while (s1[i]){
		p[i] = s1[i];
		i++;
	}
	p[i++] ='/';
	j = -1;
	while (s2[++j])
		p[i++] = s2[j];
	p[i] = '\0';
	return (p);
}
// int main()
// {
// 	char *k = "holly shit";
// 	char *p = "ok";
// 	printf("%s\n", ft_strjoin_ws(k , p));
// }