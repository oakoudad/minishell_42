/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakoudad <oakoudad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 20:50:10 by oakoudad          #+#    #+#             */
/*   Updated: 2022/09/09 21:47:55 by oakoudad         ###   ########.fr       */
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
		if (WIFEXITED(status) && !routes(head))
		{
			g_info.errorstatus = WEXITSTATUS(status);
			create_list("?", ft_itoa(g_info.errorstatus));
		}
		if (WIFSIGNALED(status) && !routes(head))
		{
			g_info.errorstatus = WTERMSIG(status) + 128;
			if (g_info.errorstatus == 131)
				write(2, "Quit: 3\n", 8);
			create_list("?", ft_itoa(g_info.errorstatus));
		}
		z++;
	}
	g_info.sig = 1;
	return (1);
}

void	dup_fd(int intfd, int fd[], t_list *lst, t_list *head)
{
	if (intfd != -1)
	{
		dup2(intfd, 0);
		close(intfd);
	}
	if (head->in_fd > 0)
	{
		dup2(head->in_fd, 0);
		close(head->in_fd);
	}
	if (head->out_fd > 0)
	{
		dup2(head->out_fd, 1);
		close(head->out_fd);
	}
	else if (lst->next)
	{
		dup2(fd[1], 1);
		close(fd[1]);
	}
}

void	exec_pipe(int intfd, t_list *lst, t_list *head, char	**env)
{
	int		fd[2];
	int		io_fd[2];
	char	*cmd;
	pid_t	pid;

	pid = 0;
	if (head == NULL)
		return ;
	saveio(fd, io_fd);
	if (lst->next)
		pipe(fd);
	if (!routes(head))
		cmd = get_cmd_from_path(head->cmd);
	if (!routes(head) && cmd == NULL)
	{
		cmd_not_found(fd, lst, env);
		return ;
	}
	g_info.sig = 1;
	if (!routes(head))
	{
		g_info.sig = 0;
		pid = fork();
	}
	if (pid == 0)
	{
		dup_fd(intfd, fd, lst, head);
		if (routes(head) == 0)
		{
			closefd(fd[0], io_fd[1], io_fd[0], -1);
			signal(SIGQUIT, exit);
			execve(cmd, lst->args, env);
		}
		else
		{
			exc_builtins(head);
			restoreio(io_fd);
		}
	}
	closefd(fd[1], io_fd[1], io_fd[0], intfd);
	if (!lst->next && wait_and_error(fd[0], head))
		return ;
	exec_pipe(fd[0], lst->next, lst->next, env);
}

void	exec(int intfd, t_list *lst)
{
	char	**env;
	int		i;

	env = prepare_env();
	exec_pipe(intfd, lst, lst, env);
	i = 0;
	while (env && env[i])
	{
		free(env[i]);
		i++;
	}
}

void	cmd_not_found(int fd[], t_list *lst, char **env)
{
	close(fd[1]);
	if (lst->next)
		exec_pipe(fd[0], lst->next, lst->next, env);
}
