/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakoudad <oakoudad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 19:08:45 by oakoudad          #+#    #+#             */
/*   Updated: 2022/09/13 23:28:41 by oakoudad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	isvarformat(char c)
{
	if (c == '_' || c == '?' || (c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}

void	copyto(char *s, char *cmd, int *d, int w)
{
	int		i;
	int		j;
	char	c;

	j = 0;
	i = *d;
	c = *(s - 1);
	while (s[j] != c)
	{
		if (c == '"' && w && s[j] == '$' && s[j + 1] != '"'
			&& s[j + 1] != '\'' && s[j + 1] != '\0')
			j += copy_var(s + j + 1, cmd, &i);
		else
			cmd[i++] = s[j];
		j++;
	}
	*d = i;
}

char	*create_var(char *s, int len)
{
	int		i;
	char	*var;

	i = -1;
	var = malloc(sizeof(char) * len);
	while (++i < len)
		var[i] = s[i];
	var[i] = '\0';
	return (var);
}

int	already(char *s, int to)
{
	int	i;

	i = 0;
	if (s[0])
		while (is_space(s[i]))
			i++;
	if (i < to && s[i] != '>' && s[i] != '<')
		return (i);
	return (0);
}

int	end_of_cmd(char *s)
{
	int	end;

	end = 0;
	while (s[end])
	{
		if (s[end] == '"' || s[end] == '\'')
			skep_quotes(s, &end, 1);
		if ((s[end] == '>' || s[end] == '<') && end == 0)
		{
			while (s[end] == '>' || s[end] == '<')
				end++;
			return (end - 1);
		}
		if (is_space(s[end]) || s[end] == '>' || s[end] == '<')
			break ;
		end++;
	}
	return (end - 1);
}
