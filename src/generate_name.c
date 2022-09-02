#include "../minishell.h"

char	*generate_name(void)
{
	char		*start;
	long long	n;
	int			i;

	start = malloc(sizeof(char) * 40);
	start = ft_strdup("/tmp/0xminishell00000000000000.heredoc");
	while(access(start, F_OK) == 0)
	{
		i = 0;
		n = 0;
		while(i < 14)
		{
			n = n * 10 + (start[16 + i] - '0');
			i++;
		}
		n++;
		while(--i >= 0)
		{
			start[16 + i] = (char)((n % 10) + '0');
			n = n / 10;
		}
	}
	return start;
}