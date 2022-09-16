/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelmoham <eelmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 01:21:09 by eelmoham          #+#    #+#             */
/*   Updated: 2022/09/16 04:31:53 by eelmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_node_vars(t_list_env *node)
{
	free(node->key);
	free(node->value);
	free(node);
}

int	del_node(t_list_env *node)
{
	t_list_env	*tmp;
	t_list_env	*prev;

	if (g_info.env_lst == node)
	{
		g_info.env_lst = node->next;
		free_node_vars(node);
		return (1);
	}
	tmp = g_info.env_lst;
	while (tmp)
	{
		if (tmp == node)
		{
			prev->next = tmp->next;
			free_node_vars(tmp);
			return (1);
		}
		prev = tmp;
		tmp = tmp->next;
	}
	return (0);
}

void	built_in_unset(char **str)
{
	int			i;
	t_list_env	*tmp;
	t_list_env	*tmp2;

	i = 0;
	tmp = g_info.env_lst;
	while (str[i])
	{
		tmp = g_info.env_lst;
		while (tmp)
		{
			if (ft_strcmp(tmp->key, str[i]) == 0)
			{
				tmp2 = tmp;
				tmp = tmp->next;
				del_node(tmp2);
			}
			else
				tmp = tmp->next;
		}
		i++;
	}
	sort_list();
}
