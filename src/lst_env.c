/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakoudad <oakoudad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 18:15:44 by oakoudad          #+#    #+#             */
/*   Updated: 2022/09/10 21:58:17 by oakoudad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	init(char *name, char *value, char *env)
{
	int	i;
	int	x;
	int	status;

	i = -1;
	status = 0;
	x = 0;
	while (env[++i])
	{
		if (env[i] == '=' && status == 0)
		{
			name[i] = '\0';
			status = 1;
			i++;
		}
		if (status == 0)
			name[i] = env[i];
		if (status == 1 && value != NULL)
			value[x++] = env[i];
	}
	if (value != NULL)
		value[x] = '\0';
	if (!status)
		name[i] = '\0';
	return (status);
}

int	create_list(char *name, char *value)
{
	t_list_env	*tmp;

	tmp = g_info.env_lst;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, name) == 0)
		{
			tmp->value = value;
			return (1);
		}
		tmp = tmp->next;
	}
	tmp = ft_lstenv(name, value);
	if (!tmp)
		return (0);
	if (name[0] == '?' && name[1] == '\0')
		tmp->status = 0;
	else
		tmp->status = 1;
	if (!tmp)
		return (0);
	ft_envadd_back(tmp);
	return (1);
}

int	sort_list(void)
{
	int			i;
	t_list_env	*lst;
	char		**names;

	lst = g_info.env_lst;
	names = malloc(sizeof(char *) * 100);
	if (!names)
		return (0);
	i = 0;
	while (lst)
	{
		names[i] = lst->key;
		lst = lst->next;
		i++;
	}
	names[i] = NULL;
	prepare_name(names);
	g_info.names = names;
	return (1);
}

int	set_status(char *name, char *value, int type)
{
	int alocatname;
	int alocatvalue;

	alocatname = 0;
	alocatvalue = 0;
	if (type == 1)
		name = "?";
	if (type == 1 && !name)
		return (0);
	if (type == 1)
		value = "0";
	if (type == 1 && !value)
		return (0);
	if (type == 1 && create_list(name, value) == 0)
		return (0);
	if (sort_list() == 0)
		return (0);
	return (1);
}

int	split_equal(char **env, int type)
{
	int			i;
	char		*name;
	char		*value;

	i = -1;
	while (env[++i])
	{
		name = malloc(sizeof(char) * len_key(env[i]));
		if (!name)
			return (0);
		if (strlen(env[i]) - len_key(env[i]) == 0)
			value = NULL;
		else
		{
			value = malloc(sizeof(char) * (strlen(env[i]) - len_key(env[i])));
			if (value == NULL)
				return (0);
		}
		init(name, value, env[i]);
		if (create_list(name, value) == 0)
			return (0);
	}
	return (set_status(name, value, type));
}
