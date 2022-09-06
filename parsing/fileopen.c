/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fileopen.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakoudad <oakoudad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 18:10:12 by oakoudad          #+#    #+#             */
/*   Updated: 2022/09/06 20:10:42 by oakoudad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	fileopen(t_list	**l, char *file, char *token)
{
	pid_t	pid;
	char	*buff;
	int		i;

	if ((*l)->out_fd == -5)
	{
		if (ft_strcmp(token, ">") == 0)
		{
			(*l)->out_fd = open(file, O_CREAT | O_RDWR, 0666);
		}
		else if (ft_strcmp(token, ">>") == 0)
		{
			(*l)->out_fd = open(file, O_RDWR | O_APPEND);
			if ((*l)->out_fd == -1)
				(*l)->out_fd = open(file, O_CREAT | O_RDWR);
		}
	}
	else
	{
		close((*l)->out_fd);
		if (ft_strcmp(token, ">") == 0)
			(*l)->out_fd = open(file, O_CREAT | O_RDWR, 0666);
		else if (ft_strcmp(token, ">>") == 0)
		{
			(*l)->out_fd = open(file, O_RDWR | O_APPEND);
			if ((*l)->out_fd == -1)
				(*l)->out_fd = open(file, O_CREAT | O_RDWR);
		}
	}
	if (ft_strcmp(token, "<") == 0)
	{
		if ((*l)->in_fd != -5)
			close((*l)->in_fd);
		(*l)->in_fd = open(file, O_RDONLY);
		if ((*l)->in_fd == -1)
			printf("minishell: %s: No such file or directory\n", file);
	}
	if (ft_strcmp(token, "<<") == 0)
	{
		if ((*l)->in_fd != -5)
		{
			close((*l)->in_fd);
			if ((*l)->heredoc_file != NULL)
				free((*l)->heredoc_file);
			(*l)->heredoc_file = NULL;
		}
		(*l)->heredoc_file = generate_name();
		g_info.sig = 0;
		g_info.heredoc = 0;
		{
			pid = fork();
			if (pid == 0)
			{
				(*l)->in_fd = open((*l)->heredoc_file, O_CREAT | O_RDWR, 0666);
				g_info.heredoc = 1;
				g_info.heredoc_fd = (*l)->in_fd;
				g_info.heredoc_file = (*l)->heredoc_file;
				while (1)
				{
					buff = readline("> ");
					if (buff == NULL || ft_strcmp(buff, file) == 0)
						break ;
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
				close((*l)->in_fd);
				g_info.heredoc = 0;
				exit(0);
			}
		}
		waitpid(pid, NULL, 0);
		
		g_info.heredoc = 0;
		g_info.sig = 1;
		(*l)->in_fd = open((*l)->heredoc_file, O_RDONLY);
		unlink((*l)->heredoc_file);
	}
}
