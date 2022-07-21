#include "../minishell.h"

int check_args(char *str)
{
	int y;
	int n_option;

	y = 1;
	n_option = 0;
	while (str[0] == '-' && str[y] != '\0')
	{
		if(str[y] != 'n')
		{
			n_option = 0;
			break;
		}
		else
			n_option = 1;
		y++;
	}
	return (n_option);
}

void	ft_echo(char **var, int fd)
{
	int		i;
	int		n_option;

	i = -1;
	n_option = 0;
	if (fd == -5)
		fd = 1;
	if (var && var[0])
	{
		n_option = check_args(var[0]);
		if (n_option == 1)
			i = 0;
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
