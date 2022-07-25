/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakoudad <oakoudad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 21:10:26 by oakoudad          #+#    #+#             */
/*   Updated: 2022/07/25 16:08:56 by oakoudad         ###   ########.fr       */
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
			if(!skep_quotes(s, &i))
				return (0);
		if (s[i] == '|')
			j++;
		if (s[i] == ';')
			return (ft_putstr("Minishell: ';' is not supported\n"), 0);
		if (j == 2)
			return (ft_putstr("Minishell: syntax error near `||'\n"), 0);
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
	char	**pips = NULL;
	i = 0;
	while (s[i] && is_space(s[i]))
		i++;
	j = ft_strlen(s) - 1;
	while (j >= 0 && is_space(s[j]))
		j--;
	if (s[i] == '|' || s[j] == '|')
		return (ft_putstr("Minishell: parse error near `|'\n"), 0);
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
