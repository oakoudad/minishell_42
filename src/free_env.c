/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakoudad <oakoudad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 20:46:50 by oakoudad          #+#    #+#             */
/*   Updated: 2022/09/11 21:38:19 by oakoudad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	var_cmp(char *var, char *env)
{
	int	i;

	i = 0;
	if (!var || !env)
		return (0);
	while (var[i] && env[i] && var[i] == env[i] && env[i] != '=')
		i++;
	if (var[i] == 0 && (env[i] == '=' || env[i] == 0))
		return (1);
	return (0);
}

int	search_var(char *var, char **env)
{
	int	i;

	i = 0;
	while (env && env[i])
	{
		if (var_cmp(var, env[i]))
			return (1);
		i++;
	}
	return (0);
}

void	free_env(char *var)
{
	t_list_env	*tmp;

	tmp = g_info.env_lst;
	while (tmp)
	{
		if (var_cmp(var, tmp->key))
		{
			free(tmp->value);
			return ;
		}
		tmp = tmp->next;
	}
}

void	free_splited(char **vals, int i)
{
	while (vals[++i])
		free(vals[i]);
	free(vals);
}
