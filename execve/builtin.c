/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakoudad <oakoudad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 20:49:26 by oakoudad          #+#    #+#             */
/*   Updated: 2022/09/09 20:49:51 by oakoudad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	routes(t_list *lst)
{
	if (ft_strcmp(lst->cmd, "echo") == 0)
		return (1);
	else if (ft_strcmp(lst->cmd, "export") == 0)
		return (1);
	else if (ft_strcmp(lst->cmd, "env") == 0)
		return (1);
	else if (ft_strcmp(lst->cmd, "cd") == 0)
		return (1);
	else if (ft_strcmp(lst->cmd, "unset") == 0)
		return (1);
	else if (ft_strcmp(lst->cmd, "pwd") == 0)
		return (1);
	else if (ft_strcmp(lst->cmd, "exit") == 0)
		return (1);
	else
		return (0);
}

void	exc_builtins(t_list *lst)
{
	if (ft_strcmp(lst->cmd, "echo") == 0)
		ft_echo(++(lst->args));
	else if (ft_strcmp(lst->cmd, "export") == 0)
		ft_export(++(lst->args));
	else if (ft_strcmp(lst->cmd, "env") == 0)
		ft_env(1);
	else if (ft_strcmp(lst->cmd, "cd") == 0)
	{
		if (lst->args && lst->args[0] && lst->args[1])
			ft_cd(lst->args[1]);
		else
			ft_cd("");
	}
	else if (ft_strcmp(lst->cmd, "unset") == 0)
		ft_unset(++(lst->args));
	else if (ft_strcmp(lst->cmd, "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(lst->cmd, "exit") == 0)
		ft_exit(++(lst->args));
}
