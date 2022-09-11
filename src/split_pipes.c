/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakoudad <oakoudad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 21:10:26 by oakoudad          #+#    #+#             */
/*   Updated: 2022/09/11 22:03:29 by oakoudad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*mem(char *str, int start, int end)
{
	char	*p;
	int		i;

	i = 0;
	p = NULL;
	while (is_space(str[start]))
		start++;
	while (is_space(str[end - 1]))
		end--;
	p = malloc((end - start + 1));
	if (!p)
		return (NULL);
	while (start < end)
		p[i++] = str[start++];
	p[i] = 0;
	return (p);
}

void	init_index(int *i, int *start, int *end)
{
	*i = 0;
	*start = 0;
	*end = 0;
}

int	split_pipes2(char *s, char **p, int count)
{
	int	i;
	int	start;
	int	end;

	init_index(&i, &start, &end);
	while (i < count)
	{
		while (s[end])
		{
			if (s[end] == '"' || s[end] == '\'')
				skep_quotes(s, &end, 1);
			if (s[end] == '|')
				break ;
			++end;
		}
		p[i] = mem(s, start, end);
		if (!p)
			return (-1);
		if (s[end] == '|')
			end++;
		start = end;
		i++;
	}
	return ((p[i] = 0), 1);
}

char	**split_pipes(char *s)
{
	int		i;
	int		count;
	char	**p;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == '"' || s[i] == '\'')
			skep_quotes(s, &i, 1);
		if (s[i] == '|')
			count++;
		i++;
	}
	g_info.count_pipes = count + 1;
	p = malloc(sizeof(char *) * (count + 2));
	if (!p || !split_pipes2(s, p, count + 1))
		return (NULL);
	p[count + 1] = NULL;
	i = 0;
	if (!redirections_error(p, count))
		return (NULL);
	return (p);
}
