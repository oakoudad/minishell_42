/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakoudad <oakoudad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 21:10:26 by oakoudad          #+#    #+#             */
/*   Updated: 2022/09/15 22:52:36 by oakoudad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_syntax2(char *s)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] == '"' || s[i] == '\'')
			if (!skip_quotes(s, &i, 1))
				return (0);
		if (s[i] == '|')
			j++;
		if (s[i] == ';')
			return (ft_putstr_fd(2, "Minishell: ';' is not supported\n"), 0);
		if (j == 2)
			return (ft_putstr_fd(2, "Minishell: syntax error near `||'\n"), 0);
		if (!is_space(s[i]) && s[i] != '|')
			j = 0;
		i++;
	}
	return (1);
}

int	check_syntax(char *s)
{
	int		i;
	int		j;
	char	**pips;

	i = 0;
	pips = NULL;
	while (*s && is_space(s[i]))
		s++;
	j = ft_strlen(s) - 1;
	while (j >= 0 && is_space(s[j]))
		j--;
	if (s[i] == '|' || s[j] == '|')
		return (unexpected('|', '\0'), 0);
	if (!check_syntax2(s))
		return (0);
	if (ft_strlen(s) > 0)
		pips = split_pipes(s);
	if (!pips)
		return (0);
	i = 0;
	parsing(pips);
	return (1);
}
