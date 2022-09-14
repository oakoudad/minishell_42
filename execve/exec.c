/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakoudad <oakoudad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 20:50:10 by oakoudad          #+#    #+#             */
/*   Updated: 2022/09/14 21:13:04 by oakoudad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	wait_and_error(int fd, t_list	*head)
{
	int	z;
	int	status;

	z = 0;
	close(fd);
	while (z < g_info.count_pipes && g_info.count_pipes)
	{
		wait(&status);
		if (WIFEXITED(status) && !isbuilting(head) && z == 0)
		{
			g_info.errorstatus = WEXITSTATUS(status);
			if (head->error == 0)
				change_status(g_info.errorstatus);
		}
		if (WIFSIGNALED(status) && !isbuilting(head) && z == 0)
		{
			g_info.errorstatus = WTERMSIG(status) + 128;
			if (g_info.errorstatus == 131)
				write(2, "Quit: 3\n", 8);
			change_status(g_info.errorstatus);
		}
		z++;
	}
	g_info.sig = 1;
	return (1);
}

void	exec_cmd(t_list *lst, t_list *head, t_var var, int intfd)
{
	if (!isbuilting(head))
	{
		g_info.sig = 0;
		var.pid = fork();
		if (var.pid == -1)
			exit(0);
	}
	if (var.pid == 0)
	{
		dup_fd(intfd, var.fd, lst, head);
		if (isbuilting(head) == 0)
		{
			closefd(var.fd[0], var.io_fd[1], var.io_fd[0], -1);
			signal(SIGQUIT, exit);
			execve(var.cmd, lst->args, var.env);
		}
		else
		{
			exc_builtins(head);
			restoreio(var.io_fd);
		}
	}
}

void	exec_pipe(int intfd, t_list *lst, t_list *head, char **env)
{
	t_var	var;

	var.env = NULL;
	if (ft_strcmp("cat", lst->cmd) != 0)
		var.env = env;
	var.pid = 0;
	if (head == NULL)
		return ;
	saveio(var.fd, var.io_fd);
	if (lst->next)
		pipe(var.fd);
	if (!isbuilting(head))
		var.cmd = get_cmd_from_path(head->cmd);
	if (!isbuilting(head) && var.cmd == NULL)
		return (cmd_not_found(var.fd, lst, env));
	g_info.sig = 1;
	exec_cmd(lst, head, var, intfd);
	if (!isbuilting(head))
		free(var.cmd);
	closefd(var.fd[1], var.io_fd[1], var.io_fd[0], intfd);
	if (!lst->next && wait_and_error(var.fd[0], head))
		return ;
	exec_pipe(var.fd[0], lst->next, lst->next, env);
}

void	exec(int intfd, t_list *lst)
{
	char	**env;
	int		i;

	if (g_info.count_pipes == 1 && isbuilting(lst))
		env = NULL;
	else
		env = prepare_env();
	exec_pipe(intfd, lst, lst, env);
	i = 0;
	if (env)
	{
		while (env[i])
		{
			free(env[i]);
			i++;
		}
		free(env);
	}
}

void	cmd_not_found(int fd[], t_list *lst, char **env)
{
	close(fd[1]);
	g_info.sig = 1;
	if (lst->next)
		exec_pipe(fd[0], lst->next, lst->next, env);
}
