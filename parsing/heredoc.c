/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakoudad <oakoudad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 00:37:38 by oakoudad          #+#    #+#             */
/*   Updated: 2022/09/14 20:26:35 by oakoudad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	heredoc_promes(t_list **l, char *buff, char *file)
{
	int	i;

	buff = readline("> ");
	if (buff == NULL || ft_strcmp(buff, file) == 0)
		g_info.heredoc_fd = 0;
	if (g_info.heredoc_fd == 0)
		return ;
	i = 0;
	while (buff[i])
	{
		if (buff[i] != '$')
			write((*l)->in_fd, &buff[i], 1);
		else
			get_var(&buff[i], &i, (*l)->in_fd);
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
		g_info.heredoc = 0;
		exit(0);
	}
	waitpid(pid, NULL, 0);
	init_heredoc(1, 0);
}
