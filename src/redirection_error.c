/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_error.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakoudad <oakoudad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 18:21:04 by oakoudad          #+#    #+#             */
/*   Updated: 2022/09/07 18:30:09 by oakoudad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	chech_red(char c)
{
	if (c == '>' || c == '<')
		return (1);
	return (0);
}

int	unexpected(char token, char token2)
{
	write(1, "syntax error near unexpected token '", 37);
	write(1, &token, 1);
	write(1, &token2, 1);
	write(1, "'\n", 2);
	return (0);
}

int	redirections_error(char **p, int count)
{
	int	i;
	int	j;
	int	status;

	i = -1;
	while (p[++i])
	{
		init_index(&j, &j, &status);
		while (p[i][j])
		{
			if (p[i][j] == '"' || p[i][j] == '\'')
				skep_quotes(p[i], &j);
			if (chech_red(p[i][j]))
				status++;
			if (status == 2 && chech_red(p[i][j]) && !chech_red(p[i][j - 1]))
				return (unexpected(p[i][j], 0));
			if (status == 3)
				return (unexpected(p[i][j], 0));
			if (p[i][j] != '>' && p[i][j] != '<' && !is_space(p[i][j]))
				status = 0;
			j++;
		}
		if (status > 0 && count > i)
			return (unexpected('|', 0));
		if (status > 0 && count == i)
			return (unexpected('\\', 'n'));
	}
	return (1);
}
