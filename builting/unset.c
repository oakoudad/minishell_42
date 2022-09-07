/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakoudad <oakoudad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 17:44:31 by oakoudad          #+#    #+#             */
/*   Updated: 2022/09/07 17:45:09 by oakoudad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	del_node(t_list_env *node)
{
	t_list_env	*tmp;
	t_list_env	*prev;

	if (g_info.env_lst == node)
	{
		g_info.env_lst = node->next;
		free(node);
		return (1);
	}
	tmp = g_info.env_lst;
	while (tmp)
	{
		if (tmp == node)
		{
			prev->next = tmp->next;
			free(tmp);
			return (1);
		}
		prev = tmp;
		tmp = tmp->next;
	}
	return (0);
}

void	ft_unset(char **str)
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
