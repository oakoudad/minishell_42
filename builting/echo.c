#include "../minishell.h"

void	ft_echo(char **var, int fd)
{
	int		i;
	int		y;
	int		n_option;

	i = -1;
	n_option = 0;
	if (fd == -5)
		fd = 1;
	if (var && var[0])
	{
		y = 0;
		while (var[0][0] == '-' && var[0][y] != '\0')
		{
			if(var[0][y] != 'n')
			{
				n_option = 1;
				break;
			}
			else
				n_option = 0;
			y++;
		}
		if (n_option == 1)
			i = 0;
		while (var[++i])
		{
			if (i != 0)
				write(fd, " ", 1);
			write(fd, var[i], ft_strlen(var[i]));
		}
		if (n_option == 0)
			write(fd, "\n", 1);
	}
	else
		write(fd, "\n", 1);
}
