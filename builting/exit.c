/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakoudad <oakoudad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 03:00:08 by oakoudad          #+#    #+#             */
/*   Updated: 2022/07/21 15:23:42 by oakoudad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_numeric(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

void	ft_exit(char **args)
{
	int		i;

	i = -1;
	putstr_fd(1, "exit\n");
	while (args && args[0] && args[0][++i])
	{
		if (!is_numeric(args[0][i]))
		{
			putstr_fd(1, "MiniShell: exit: ");
			putstr_fd(1, args[0]);
			putstr_fd(1, ": numeric argument required\n");
			exit(255);
		}
	}
	if (args && args[0] && args[1])
		return (putstr_fd(1, "MiniShell: exit: too many arguments\n"));
	if (args && args[0])
		exit(atoi(args[0]));
	else
		exit(0);
}
