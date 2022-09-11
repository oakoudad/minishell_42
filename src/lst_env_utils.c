/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_env_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakoudad <oakoudad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 23:06:46 by oakoudad          #+#    #+#             */
/*   Updated: 2022/09/11 01:05:39 by oakoudad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	prepare_name(char **names)
{
	int		j;
	int		i;
	char	*tmp;

	i = 0;
	while (names[i + 1])
	{
		j = i + 1;
		while (names[j])
		{
			if (strcmp(names[i], names[j]) > 0)
			{
				tmp = names[j];
				names[j] = names[i];
				names[i] = tmp;
			}
			j++;
		}
		i++;
	}
}

int	len_key(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '=' && str[i])
		i++;
	return (i);
}

void	ft_envadd_back(t_list_env *new)
{
	t_list_env	*t;

	t = g_info.env_lst;
	if (t == NULL)
	{
		g_info.env_lst = new;
		return ;
	}
	while (t->next)
		t = t->next;
	t->next = new;
}

t_list_env	*ft_lstenv(char *key, char *value)
{
	t_list_env	*list;

	list = malloc(sizeof(t_list));
	if (!list)
		return (NULL);
	list->value = ft_strdup(value);
	list->key = ft_strdup(key);
	list->next = NULL;
	return (list);
}