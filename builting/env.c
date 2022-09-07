/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakoudad <oakoudad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 17:04:16 by oakoudad          #+#    #+#             */
/*   Updated: 2022/09/07 17:12:24 by oakoudad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_env(void)
{
	t_list_env	*lst;

	lst = g_info.env_lst;
	while (lst)
	{
		if (lst->status == 1)
			printf("%s=%s\n", lst->key, lst->value);
		lst = lst->next;
	}
}

void	ft_env(int x)
{
	t_list_env	*lst;
	int			i;

	lst = g_info.env_lst;
	if (lst && x)
		print_env();
	i = -1;
	while (g_info.names[++i] && x == 0)
	{
		if (!(g_info.names[i][0] == '?' && g_info.names[i][1] == '\0'))
			printf(" declare -x %s=", g_info.names[i]);
		lst = g_info.env_lst;
		while (!(g_info.names[i][0] == '?' && g_info.names[i][1] == 0) && lst)
		{
			if (ft_strcmp(lst->key, g_info.names[i]) == 0)
			{
				printf("%s\n", lst->value);
				break ;
			}
			lst = lst->next;
		}
	}
}
