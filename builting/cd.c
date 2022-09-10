/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakoudad <oakoudad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 16:44:42 by oakoudad          #+#    #+#             */
/*   Updated: 2022/09/10 21:57:00 by oakoudad         ###   ########.fr       */
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

int	ft_pwd(void)
{
	char	cwd[1000];

	if (getcwd(cwd, 1000))
	{
		printf("%s\n", cwd);
		return (1);
	}
	else
		return (0);
}

void	ft_cd_puterror(char *path)
{
	if (ft_strcmp(path, "-") == 0 || ft_strcmp(path, "HOME") == 0
		|| ft_strcmp(path, "OLDPWD") == 0 || ft_strcmp(path, "~") == 0)
		printf("Minishell: cd: %s not set\n", path);
	else
		printf("minishell: %s: No such a file or directory\n", path);
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

void	ft_cd(char *path)
{
	(void)path;
	create_list("?", "0");
	if (path[0] == '\0')
	{
		if (chdir(get_path("HOME")) == -1)
			ft_cd_puterror("HOME");
		return ;
	}
	if (ft_strcmp(path, "-") == 0)
	{
		if (chdir(get_path("OLDPWD")) == -1)
			ft_cd_puterror("OLDPWD");
		else
			ft_pwd();
		return ;
	}
	if (path_error(path))
		if (chdir(path) == -1)
			ft_cd_puterror(path);
}
