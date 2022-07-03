#include "../minishell.h"

void	ft_echo(char **var)
{
	int		i;
	int		n_option;

	i = -1;
	n_option = 0;
	if (var && var[0])
	{
		if (strcmp(var[0], "-n") == 0)
		{
			n_option = 1;
			i++;
		}
		while (var[++i])
		{
			if (i != 0)
				printf(" ");
			printf("%s", var[i]);
		}
		if (n_option == 0)
			printf("\n");
	}
	else
		printf("\n");
}
