/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakoudad <oakoudad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 21:16:14 by oakoudad          #+#    #+#             */
/*   Updated: 2022/09/12 00:40:29 by oakoudad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	change_status(int status)
{
	char	*err;

	err = ft_itoa(status);
	create_list("?", err);
	free(err);
}

void	closefd(int a, int b, int c, int d)
{
	if (a > -1)
		close(a);
	if (b > -1)
		close(b);
	if (c > -1)
		close(b);
	if (d > -1)
		close(d);
}

void	saveio(int fd[], int io_fd[])
{
	fd[0] = -1;
	fd[1] = -1;
	io_fd[0] = dup(STDIN_FILENO);
	io_fd[1] = dup(STDOUT_FILENO);
}

void	restoreio(int io_fd[])
{
	dup2(io_fd[0], 0);
	dup2(io_fd[1], 1);
	close(io_fd[0]);
	close(io_fd[1]);
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
	if (head->out_fd >= 0)
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
