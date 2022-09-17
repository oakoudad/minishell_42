/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakoudad <oakoudad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 20:49:26 by oakoudad          #+#    #+#             */
/*   Updated: 2022/09/17 04:08:49 by oakoudad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_built_in(t_list *lst)
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

void	exc_built_ins(t_list *lst)
{
	if (ft_strcmp(lst->cmd, "echo") == 0)
		built_in_echo(lst->args + 1);
	else if (ft_strcmp(lst->cmd, "export") == 0)
		built_in_export(lst->args + 1);
	else if (ft_strcmp(lst->cmd, "env") == 0)
		built_in_env(1);
	else if (ft_strcmp(lst->cmd, "cd") == 0)
	{
		if (lst->next)
			return ;
		else if (lst->args && lst->args[0] && lst->args[1])
			built_in_cd(lst->args[1]);
		else
			built_in_cd(NULL);
	}
	else if (ft_strcmp(lst->cmd, "unset") == 0)
		built_in_unset(lst->args + 1);
	else if (ft_strcmp(lst->cmd, "pwd") == 0)
		built_in_pwd();
	else if (ft_strcmp(lst->cmd, "exit") == 0)
		built_in_exit(lst->args + 1);
}
