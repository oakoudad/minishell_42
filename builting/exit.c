/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakoudad <oakoudad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 03:00:08 by oakoudad          #+#    #+#             */
/*   Updated: 2022/09/11 00:10:54 by oakoudad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_numeric(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

void	free_allenv(void)
{
	t_list_env	*env;

	env = g_info.env_lst;
	while (env)
	{
		free(env->key);
		free(env->value);
		free(env);
		env = env->next;
	}
}

void	ft_exit(char **args)
{
	int	i;

	i = -1;
	ft_putstr("exit\n");
	while (args && args[0] && args[0][++i])
	{
		if (!is_numeric(args[0][i]))
		{
			ft_putstr("MiniShell: exit: ");
			ft_putstr(args[0]);
			ft_putstr(": numeric argument required\n");
			exit(255);
		}
	}
	create_list("?", "1");
	if (args && args[0] && args[1])
		return (ft_putstr("MiniShell: exit: too many arguments\n"));
	free_allenv();
	if (args && args[0])
		exit(ft_atoi(args[0]));
	else
		exit(0);
}
