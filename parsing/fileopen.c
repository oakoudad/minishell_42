/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fileopen.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakoudad <oakoudad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 18:10:12 by oakoudad          #+#    #+#             */
/*   Updated: 2022/09/14 20:22:49 by oakoudad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	path_check(char *path, t_list	**l, int status)
{
	char	*name;

	name = generate_name();
	if (!is_file(path))
	{
		printf_error(path, ": is a directory\n", "1");
		if (status)
			(*l)->out_fd = open(name, O_CREAT | O_RDWR, 0666);
		else
			(*l)->in_fd = open(name, O_CREAT | O_RDWR, 0666);
		(*l)->error = 1;
		return (unlink(name), 0);
	}
	if (is_file(path) && access(path, F_OK) == 0 && access(path, X_OK) != 0)
	{
		printf_error(path, ": Permission denied\n", "1");
		if (status)
			(*l)->out_fd = open(name, O_CREAT | O_RDWR, 0666);
		else
			(*l)->in_fd = open(name, O_CREAT | O_RDWR, 0666);
		(*l)->error = 1;
		return (unlink(name), 0);
	}
	return (1);
}

int	out_file(t_list	**l, char *file, char *token)
{
	if (ft_strcmp(token, ">") == 0)
	{
		(*l)->out_fd = open(file, O_CREAT | O_RDWR, 0666);
		if ((*l)->out_fd == -1)
			return (path_check(file, l, 1));
	}
	else if (ft_strcmp(token, ">>") == 0)
	{
		(*l)->out_fd = open(file, O_RDWR | O_APPEND);
		if ((*l)->out_fd == -1)
			(*l)->out_fd = open(file, O_CREAT | O_RDWR);
		if ((*l)->out_fd == -1)
			return (path_check(file, l, 1));
	}
	return (1);
}

void	in_file(t_list	**l, char *file)
{
	if ((*l)->in_fd != -5)
		close((*l)->in_fd);
	(*l)->in_fd = open(file, O_RDONLY);
	if ((*l)->in_fd == -1)
		path_check(file, l, 0);
}

void	fileopen(t_list	**l, char *file, char *token)
{
	if ((*l)->out_fd == -5)
		out_file(l, file, token);
	else
	{
		close((*l)->out_fd);
		out_file(l, file, token);
	}
	if (ft_strcmp(token, "<") == 0)
		in_file(l, file);
	if (ft_strcmp(token, "<<") == 0)
	{
		if ((*l)->in_fd != -5)
		{
			close((*l)->in_fd);
			if ((*l)->heredoc_file != NULL)
				free((*l)->heredoc_file);
			(*l)->heredoc_file = NULL;
		}
		heredoc(l, file);
		(*l)->in_fd = open((*l)->heredoc_file, O_RDONLY);
		unlink((*l)->heredoc_file);
	}
}
