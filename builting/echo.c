#include "../minishell.h"

int check_args(char *str)
{
	int y;
	int n_option;

	y = 1;
	n_option = 0;
	if (str[0] == '-')
	{
		while (str[y])
		{
			if(str[y] != 'n')
			{
				n_option = 0;
				return (n_option);
			}
			else
			{
				n_option = 1;
			}
			y++;
		}
	}
	return (n_option);
}

int pass_n(char **var)
{
	int i;

	i = 0;
	while (check_args(var[i]) == 1)
		i++;
	return (i);
}

void	ft_echo(char **var, int fd)
{
	int		i;
	int 	y;
	int		n_option;

	i = -1;
	y = -1;
	n_option = 0;
	if (fd == -5)
		fd = 1;
	if (var && var[0])
	{
		while (var[++y])
			n_option = check_args(var[0]);
		if (n_option == 1)
			i = pass_n(var) - 1;
		while (var[++i])
		{
			putstr_fd(fd, var[i]);
			if (var[i + 1] != NULL)
				putstr_fd(fd, " ");
		}
		if (n_option == 0)
			putstr_fd(fd, "\n");
	}
	else
		putstr_fd(fd, "\n");
}
