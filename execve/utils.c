/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakoudad <oakoudad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 21:16:14 by oakoudad          #+#    #+#             */
/*   Updated: 2022/09/09 21:28:25 by oakoudad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
