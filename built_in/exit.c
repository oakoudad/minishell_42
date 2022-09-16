/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakoudad <oakoudad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 03:00:08 by oakoudad          #+#    #+#             */
/*   Updated: 2022/09/16 04:08:33 by oakoudad         ###   ########.fr       */
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
	free(g_info.names);
	free_cmd_line(g_info.cmds);
}

void	exit_check_args(char **args)
{
	int	i;

	i = 0;
	if (args && args[0] && args[0][i] == '-')
		i++;
	while (args && args[0] && args[0][i])
	{
		if (!is_numeric(args[0][i]))
		{
			write(2, "MiniShell: exit: ", 18);
			write(2, args[0], ft_strlen(args[0]));
			write(2, ": numeric argument required\n", 29);
			exit(255);
		}
		i++;
	}
}

void	built_in_exit(char **args)
{
	unsigned char	i;

	ft_putstr_fd(1, "exit\n");
	exit_check_args(args);
	create_list("?", "1");
	if (args && args[0] && args[1])
		return (ft_putstr_fd(2, "MiniShell: exit: too many arguments\n"));
	i = 0;
	if (args && args[0])
		i = ft_atoi(args[0]);
	free_allenv();
	exit(i);
}
