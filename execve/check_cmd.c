/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakoudad <oakoudad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 18:47:26 by oakoudad          #+#    #+#             */
/*   Updated: 2022/09/10 21:57:11 by oakoudad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_env_var(char *key)
{
	t_list_env	*lst;

	lst = g_info.env_lst;
	while (lst)
	{
		if (strcmp(lst->key, key) == 0)
		{
			return (lst->value);
		}
		lst = lst->next;
	}
	return (NULL);
}

void	printf_error(char *cmd, char *message, char *status)
{
	write(2, "minishell: ", 12);
	write(2, cmd, ft_strlen(cmd));
	write(2, message, ft_strlen(message));
	create_list("?", status);
}

int	cmd_error(char *cmd)
{
	if (access(cmd, X_OK) != 0)
	{
		if (access(cmd, F_OK) == 0)
			printf_error(cmd, ": Permission denied\n", "126");
		else
			printf_error(cmd, ": Not a directory\n", "126");
		return (0);
	}
	if (access(cmd, F_OK) != 0)
	{
		printf_error(cmd, ": No such file or directory\n", "127");
		return (0);
	}
	return (1);
}

char	*get_cmd_from_path(char *cmd)
{
	char	*path;
	char	*checkpath;
	char	**vals;
	int		i;

	if ((cmd[0] == '.' && cmd[1] == '/') || (cmd[0] == '/'))
	{
		if (cmd_error(cmd))
			return (cmd);
		return (NULL);
	}
	path = get_env_var("PATH");
	if (path == NULL)
		return (printf_error(cmd, ": command not found\n", "127"), NULL);
	vals = ft_split(path, ':');
	i = -1;
	while (vals[++i])
	{
		checkpath = ft_strjoin(vals[i], "/");
		checkpath = ft_strjoin(checkpath, cmd);
		if (access(checkpath, X_OK) == 0)
			return (checkpath);
		free(checkpath);
	}
	return (printf_error(cmd, ": command not found\n", "127"), NULL);
}

char	**prepare_env(void)
{
	int			i;
	t_list_env	*lst;
	char		**newenv;

	lst = g_info.env_lst;
	i = 0;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	newenv = malloc(sizeof(char *) * i + 1);
	if (!newenv)
		return (NULL);
	lst = g_info.env_lst;
	i = -1;
	while (lst)
	{
		newenv[++i] = ft_strdup(lst->key);
		newenv[i] = ft_strjoin(newenv[i], "=");
		newenv[i] = ft_strjoin(newenv[i], lst->value);
		lst = lst->next;
	}
	newenv[i] = NULL;
	return (newenv);
}
