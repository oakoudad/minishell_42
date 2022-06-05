#include "../minishell.h"

int is_space(char c)
{
	if (c == ' ')
		return (1);
	return 0;
}

int ft_strlen(char *s)
{
	int i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	ft_putstr(char *s)
{
	write(1, s, ft_strlen(s));
}