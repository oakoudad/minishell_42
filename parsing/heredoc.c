/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakoudad <oakoudad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 00:37:38 by oakoudad          #+#    #+#             */
/*   Updated: 2022/09/17 04:11:05 by oakoudad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	heredoc_promes(t_list **l, char *buff, char *file)
{
	int	i;

	rl_catch_signals = 1;
	buff = readline("> ");
	if (buff == NULL || ft_strcmp(buff, file) == 0)
	{
		g_info.heredoc_fd = 0;
		return ;
	}
	i = 0;
	while (buff[i])
	{
		if (buff[i] == '$' && isvarformat(buff[i + 1]))
			get_var(&buff[i], &i, (*l)->in_fd);
		else
			write((*l)->in_fd, &buff[i], 1);
		i++;
	}
	if (buff[i] == '\0')
		write((*l)->in_fd, "\n", 1);
	free(buff);
}

void	init_heredoc(int a, int b)
{
	g_info.sig = a;
	g_info.heredoc = b;
}

void	heredoc_wait(int pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		change_status(WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		change_status(WTERMSIG(status));
}

void	heredoc(t_list **l, char *file)
{
	pid_t	pid;
	char	*buff;

	buff = NULL;
	if ((*l)->heredoc_file != NULL)
	{
		free((*l)->heredoc_file);
		(*l)->heredoc_file = NULL;
	}
	(*l)->heredoc_file = generate_name();
	init_heredoc(0, 0);
	pid = fork();
	if (pid == 0)
	{
		(*l)->in_fd = open((*l)->heredoc_file, O_CREAT | O_RDWR, 0666);
		g_info.heredoc = 1;
		g_info.heredoc_fd = (*l)->in_fd;
		while (g_info.heredoc_fd)
			heredoc_promes(l, buff, file);
		close((*l)->in_fd);
		exit(0);
	}
	heredoc_wait(pid);
	init_heredoc(1, 0);
}
