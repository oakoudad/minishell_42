/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakoudad <oakoudad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 03:30:46 by oakoudad          #+#    #+#             */
/*   Updated: 2022/07/07 03:31:34 by oakoudad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	copyto(char *s, char *cmd, char c, int *d)
{
	int		i;
	int		j;

	j = 0;
	i = *d;
	while (s[j] != c)
	{
		if (s[j] == '$' && s[j + 1] != '"' && s[j + 1] != '\'' && s[j + 1] != '\0')
			j += copy_var(s + j + 1, cmd, &i);
		else
			cmd[i++] = s[j];
		j++;
	}
	*d = i;
}

int copy_var(char *s, char *dest, int *d)
{
	t_list_env *temp;
	int len;
	int i;
	int j;
	char *var;

	i = -1;
	len = 0;
	temp = g_info.env_lst;
	while ((s[len] >= 'a' && s[len] <= 'z') || (s[len] >= 'A' && s[len] <= 'Z') || s[len] == '_')
		len++;
	var = malloc(sizeof(char) * len);
	while (i < len)
	{
		var[i] = s[i];
		i++;
	}
	var[i] = '\0';
	i = (*d);
	j = -1;
	while (temp)
	{
		if (ft_strcmp(temp->key, var) == 0)
		{
			while (temp->value[++j])
				dest[i++] = temp->value[j];
		}
		temp = temp->next;
	}
	dest[i] = '\0';
	*d = i;
	free(var);
	return (len);
}

int end_of_cmd(char *s)
{
	int end;

	end = 0;
	while (s[end])
	{
		if (s[end] == '"' || s[end] == '\'')
			skep_quotes(s, &end);
		if (is_space(s[end]))
			break;
		end++;
	}
	return (end-1);
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
			printf("%d\n", len_var(s + i + 1));
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