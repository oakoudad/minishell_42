/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pips_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakoudad <oakoudad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 01:46:50 by oakoudad          #+#    #+#             */
/*   Updated: 2022/09/16 01:47:29 by oakoudad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	if_no_cmd(t_list *head, char **env, t_var	var)
{
	if (head->cmd == NULL || head->cmd[0] == '\0')
	{
		close(head->in_fd);
		close(head->out_fd);
		if (head->next)
		{
			pipe(var.fd);
			close(var.fd[1]);
			exec_pipe(var.fd[0], head->next, head->next, env);
			close(var.fd[1]);
		}
		return (1);
	}
	return (0);
}
