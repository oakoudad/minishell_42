/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelmoham <eelmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 01:21:09 by eelmoham          #+#    #+#             */
/*   Updated: 2022/09/16 04:32:10 by eelmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_env(void)
{
	t_list_env	*lst;

	lst = g_info.env_lst;
	while (lst)
	{
		if (lst->status == 1 && lst->value)
			printf("%s=%s\n", lst->key, lst->value);
		lst = lst->next;
	}
}

void	built_in_env(int x)
{
	t_list_env	*lst;
	int			i;

	lst = g_info.env_lst;
	create_list("?", "0");
	if (lst && x)
		return (print_env());
	i = -1;
	while (g_info.names[++i] && x == 0)
	{
		if (!(g_info.names[i][0] == '?' && g_info.names[i][1] == '\0'))
			printf(" declare -x %s", g_info.names[i]);
		lst = g_info.env_lst;
		while (!(g_info.names[i][0] == '?' && g_info.names[i][1] == 0) && lst)
		{
			if (ft_strcmp(lst->key, g_info.names[i]) == 0)
			{
				if (lst->value != NULL)
					printf("=\"%s\"", lst->value);
				printf("\n");
				break ;
			}
			lst = lst->next;
		}
	}
}
