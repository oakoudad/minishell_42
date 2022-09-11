/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakoudad <oakoudad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 18:15:44 by oakoudad          #+#    #+#             */
/*   Updated: 2022/09/12 00:30:40 by oakoudad         ###   ########.fr       */
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
			if (tmp->value != NULL)
				free(tmp->value);
			if (value)
				tmp->value = ft_strdup(value);
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
	ft_envadd_back(tmp);
	return (1);
}

int	sort_list(void)
{
	int			i;
	t_list_env	*lst;
	char		**names;

	lst = g_info.env_lst;
	if (g_info.names !=	NULL){
		free(g_info.names);}
	names = malloc(sizeof(char *) * 1000);
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

int	set_status(int type)
{
	create_list("?", "0");
	if (sort_list() == 0)
		return (0);
	return (type);
}

int	split_equal(char **env, int type)
{
	int			i;
	char		*name;
	char		*value;

	i = -1;
	while (env[++i])
	{
		name = malloc(sizeof(char) * len_key(env[i]) + 1);
		if (!name)
			return (0);
		if (strlen(env[i]) - len_key(env[i]) == 0)
			value = NULL;
		else
		{
			value = malloc(1 + (strlen(env[i]) - len_key(env[i])));
			if (value == NULL)
				return (0);
		}
		init(name, value, env[i]);
		if (create_list(name, value) == 0)
			return (0);
		free(name);
		free(value);
	}
	return (set_status(type));
}
