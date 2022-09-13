/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakoudad <oakoudad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 16:44:42 by oakoudad          #+#    #+#             */
/*   Updated: 2022/09/13 23:20:28 by oakoudad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_path(char *key)
{
	t_list_env	*tmp;

	tmp = g_info.env_lst;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

void	ft_cd_puterror(char *path)
{
	if (ft_strcmp(path, "-") == 0 || ft_strcmp(path, "HOME") == 0
		|| ft_strcmp(path, "OLDPWD") == 0 || ft_strcmp(path, "~") == 0)
	{
		write(2, "Minishell: cd: ", 16);
		write(2, path, ft_strlen(path));
		write(2, " not set\n", 10);
	}
	else
	{
		write(2, "Minishell: ", 12);
		write(2, path, ft_strlen(path));
		write(2, ": No such a file or directory\n", 31);
	}
	create_list("?", "1");
}

int	path_error(char *path)
{
	if (is_file(path))
	{
		printf_error(path, ": Not a directory\n", "1");
		return (0);
	}
	if (!is_file(path) && access(path, F_OK) == 0
		&& access(path, X_OK) != 0)
	{
		printf_error(path, ": Permission denied\n", "1");
		return (0);
	}
	return (1);
}

int	mychdir(char *path)
{
	int		r;
	char	*curr_pwd;
	char	*old_pwd;

	old_pwd = NULL;
	curr_pwd = NULL;
	old_pwd = get_pwd();
	r = chdir(path);
	if (r != -1)
		create_list("OLDPWD", old_pwd);
	curr_pwd = get_pwd();
	if (curr_pwd)
	{
		create_list("PWD", curr_pwd);
		free(curr_pwd);
	}
	if (old_pwd)
		free(old_pwd);
	return (r);
}

void	ft_cd(char *path)
{
	create_list("?", "0");
	if (path && path[0] == '\0')
		return ;
	if (path == NULL)
	{
		if (mychdir(get_path("HOME")) == -1)
			ft_cd_puterror("HOME");
		return ;
	}
	if (ft_strcmp(path, "-") == 0)
	{
		if (mychdir(get_path("OLDPWD")) == -1)
			ft_cd_puterror("OLDPWD");
		else
			ft_pwd();
		return ;
	}
	if (path_error(path))
		if (mychdir(path) == -1)
			ft_cd_puterror(path);
}
