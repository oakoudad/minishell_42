/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakoudad <oakoudad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 03:24:23 by oakoudad          #+#    #+#             */
/*   Updated: 2022/09/15 22:52:36 by oakoudad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	iftoken(int index, t_list **l)
{
	int		i;
	t_list	*elm;

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

int	len_var(char *s)
{
	t_list_env	*temp;
	int			i;
	int			j;
	char		*var;

	i = -1;
	j = 0;
	temp = g_info.env_lst;
	while ((s[j] >= 'a' && s[j] <= 'z') || (s[j] >= 'A' && s[j] <= 'Z')
		|| s[j] == '_'
		|| (s[j] >= '0' && s[j] <= '9'))
		j++;
	var = ft_calloc(sizeof(char) * j);
	while (++i < j)
		var[i] = s[i];
	var[i] = '\0';
	j = -(ft_strlen(var) + 1);
	while (temp)
	{
		if (ft_strcmp(temp->key, var) == 0)
			j += ft_strlen(temp->value);
		temp = temp->next;
	}
	free(var);
	return ((var = NULL), j);
}

int	skip_quotes(char *s, int *d, int status)
{
	char	c;
	int		i;

	c = s[*d];
	i = *d + 1;
	while (s[i] && s[i] != c)
		i++;
	if (s[i] == 0 && status)
	{
		ft_putstr_fd(2, "Minishell: syntax error quotes not closed\n");
		create_list("?", "1");
		return (0);
	}
	*d = i;
	return (1);
}

int	skip_quotes2(char *s, int *d)
{
	char	c;
	int		i;
	int		res;

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
		ft_putstr_fd(2, "Minishell: syntax error quotes not closed\n");
		create_list("?", "1");
		return (0);
	}
	*d = i;
	return (res);
}

int	len_of_cmd(char *s, int to)
{
	int	i;
	int	j;

	i = 0;
	j = to + 1;
	while (i < to)
	{
		if (s[i] == '$')
		{
			j += len_var(s + i + 1);
		}
		if (s[i] == '"' || s[i] == '\'')
		{
			j -= 2;
			j += skip_quotes2(s, &i);
		}
		if (is_space(s[i]))
			break ;
		i++;
	}
	return (j);
}
