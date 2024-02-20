#include <stdio.h>
#include <unistd.h>
#include "./libft/libft.h"

int main(int ac, char *av[], char *env[])
{
	char *path;
	int i = 0 ;
	while(env[i])
	{
		path = ft_strnstr(env[i],"PATH", 4);
		if(path){
			// printf("%s\n", path);
			break;
		}
		i++;
	}
	// printf("%s\n", path);
	char **p = ft_split(path, ':');
	// printf("%s\n", p[0]);
	i = 0;
	while(p[i])
	{
		p[i] = ft_strjoin(p[i],"/");
		// printf("%s\n",p[i]);
		p[i] = ft_strjoin(p[i], av[1]);
		int a = access(p[i] , F_OK);
		if(a == 0)
		{
			// printf("135452");
				printf("%s\n" , p[i]);
				break;
		}
		i++;
	}
	
}
