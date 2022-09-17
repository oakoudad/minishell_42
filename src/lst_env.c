/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakoudad <oakoudad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 18:15:44 by oakoudad          #+#    #+#             */
/*   Updated: 2022/09/17 22:45:32 by oakoudad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	end_name(char *env, char *name, int *i, int *status)
{
	int	join;

	join = 0;
	if (env[*i] == '+')
	{
		(*i) = (*i) + 1;
		join = 1;
	}
	name[*i] = '\0';
	*status = 1;
	(*i) = (*i) + 1;
	return (join);
}

int	init(char *name, char *value, char *env, int *join)
{
	int	i;
	int	x;
	int	status;

	i = -1;
	status = 0;
	x = 0;
	while (env[++i])
	{
		if ((env[i] == '=' || env[i] == '+') && status == 0)
			*join = end_name(env, name, &i, &status);
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
			if (value == NULL)
				return (1);
			myfree(tmp->value);
			tmp->value = ft_strdup(value);
			return (1);
		}
		tmp = tmp->next;
	}
	tmp = ft_lstenv(name, value);
	if (!tmp)
		return (0);
	if (tmp->key[0] == '?' && tmp->key[1] == '\0')
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
	if (g_info.names != NULL)
		free(g_info.names);
	names = ft_calloc(sizeof(char *) * 1000);
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

int	split_equal(char **env, int type)
{
	int			i;
	char		*name;
	char		*value;
	int			join;

	i = -1;
	while (env[++i])
	{
		name = ft_calloc(sizeof(char) * len_key(env[i]) + 2);
		if (ft_strlen(env[i]) - len_key(env[i]) == 0)
			value = NULL;
		else
			value = ft_calloc(2 + (ft_strlen(env[i]) - len_key(env[i])));
		join = 0;
		init(name, value, env[i], &join);
		if (join == 1)
			value = join_env_value(value, name);
		if (create_list(name, value) == 0)
			return (0);
		free(name);
		free(value);
	}
	return (set_status(type));
}
