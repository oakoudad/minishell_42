/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakoudad <oakoudad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 03:24:23 by oakoudad          #+#    #+#             */
/*   Updated: 2022/07/07 03:46:48 by oakoudad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		iftoken(int index, t_list **l)
{
	int i;
	t_list *elm;

	elm = *l;
	i = 0;
	while (i < elm->count_token)
	{
		if (index == elm->index_token[i])
			return (1);
		i++;
	}
	return (0);
}

int len_var(char *s)
{
	t_list_env *temp;
	int i;
	int len;
	int res;
	char *var;

	i = -1;
	len = 0;
	res = 0;
	temp = g_info.env_lst;
	while ((s[len] >= 'a' && s[len] <= 'z') || (s[len] >= 'A' && s[len] <= 'Z') || s[len] == '_')
		len++;
	var = malloc(sizeof(char) * len);
	while (++i < len)
		var[i] = s[i];
	var[i] = 0;
	while (temp)
	{
		if (ft_strcmp(temp->key, var) == 0)
			res = ft_strlen(temp->value);
		temp = temp->next;
	}
	res -= strlen(var) + 1;
	free(var);
	var = NULL;
	return (res);
}

int	skep_quotes(char *s, int *d)
{
	char	c;
	int		i;

	c = s[*d];
	i = *d + 1;
	while (s[i] && s[i] != c)
		i++;
	if (s[i] == 0)
	{
		ft_putstr("Minishell: syntax error quotes not closed\n");
		return (0);
	}
	*d = i;
	return (1);
}

int	skep_quotes2(char *s, int *d)
{
	char	c;
	int		i;
	int 	res;

	c = s[*d];
	i = *d + 1;
	res = 0;
	while (s[i] && s[i] != c)
	{
		if (s[i] == '$')
			res += len_var(s + i + 1);
		i++;
	}
	if (s[i] == 0)
	{
		ft_putstr("Minishell: syntax error quotes not closed\n");
		return (0);
	}
	*d = i;
	return (res);
}

int len_of_cmd(char *s, int to)
{
	int i;
	int j;

	i = 0;
	j = to + 1;
	while (i < to)
	{
		if(s[i] == '$'){
			j += len_var(s + i + 1);
		}
		if (s[i] == '"' || s[i] == '\'')
		{
			j -= 2;
			j += skep_quotes2(s, &i);
		}
		if (is_space(s[i]))
			break;
		i++;
	}
	return (j);
}