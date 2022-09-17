/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakoudad <oakoudad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 20:49:26 by oakoudad          #+#    #+#             */
/*   Updated: 2022/09/17 23:14:47 by oakoudad         ###   ########.fr       */
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

void	check_export_exec(t_list *lst)
{
	if (lst->next && lst->args + 1 == NULL)
		built_in_export(lst->args + 1);
	else if (lst->next && lst->args + 1 != NULL)
		return ;
	else
		built_in_export(lst->args + 1);
}

void	check_unset_exec(t_list *lst)
{
	if (lst->next && lst->args + 1 == NULL)
		built_in_unset(lst->args + 1);
	else if (lst->next && lst->args + 1 != NULL)
		return ;
	else
		built_in_unset(lst->args + 1);
}

void	check_exit_exec(t_list *lst)
{
	if (lst->next)
		return ;
	else
		built_in_exit(lst->args + 1);
}

void	exc_built_ins(t_list *lst)
{
	if (ft_strcmp(lst->cmd, "echo") == 0)
		built_in_echo(lst->args + 1);
	else if (ft_strcmp(lst->cmd, "export") == 0)
		check_export_exec(lst);
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
		check_unset_exec(lst);
	else if (ft_strcmp(lst->cmd, "pwd") == 0)
		built_in_pwd();
	else if (ft_strcmp(lst->cmd, "exit") == 0)
		check_exit_exec(lst);
}
