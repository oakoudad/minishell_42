/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_error.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakoudad <oakoudad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 18:21:04 by oakoudad          #+#    #+#             */
/*   Updated: 2022/09/15 22:52:36 by oakoudad         ###   ########.fr       */
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
	write(2, "syntax error near unexpected token '", 37);
	write(2, &token, 1);
	write(2, &token2, 1);
	write(2, "'\n", 2);
	create_list("?", "258");
	return (0);
}

void	init_var(int *j, int *status)
{
	*j = -1;
	*status = 0;
}

void	calc_redirections(char **p, int *status, int i, int j)
{
	if (p[i][j] == '"' || p[i][j] == '\'')
		skip_quotes(p[i], &j, 0);
	if (chech_red(p[i][j]))
		*status += 1;
}

int	redirections_error(char **p, int count)
{
	int	i;
	int	j;
	int	status;

	i = -1;
	while (p[++i])
	{
		init_var(&j, &status);
		while (p[i][++j])
		{
			calc_redirections(p, &status, i, j);
			if (status == 2 && chech_red(p[i][j]) && !chech_red(p[i][j - 1]))
				return (unexpected(p[i][j], 0));
			if (status == 3)
				return (unexpected(p[i][j], 0));
			if (p[i][j] != '>' && p[i][j] != '<' && !is_space(p[i][j]))
				status = 0;
		}
		if (status > 0 && count > i)
			return (unexpected('|', 0));
		if (status > 0 && count == i)
			return (unexpected('\\', 'n'));
	}
	return (1);
}
