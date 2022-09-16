/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakoudad <oakoudad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 18:18:32 by oakoudad          #+#    #+#             */
/*   Updated: 2022/09/15 22:52:36 by oakoudad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	create_cmd(char *s, char *cmd, int end, int withextra)
{
	int		j;
	int		i;

	i = 0;
	j = 0;
	while (j <= end)
	{
		if (s[j] != '"' && s[j] != '\'')
		{
			if (withextra && s[j] == '$' && isvarformat(s[j + 1]))
				j += copy_var(s + j + 1, cmd, &i);
			else
				cmd[i++] = s[j];
		}
		else
		{
			copyto(s + j + 1, cmd, &i, withextra);
			skip_quotes(s, &j, 1);
		}
		j++;
	}
	cmd[i] = '\0';
}

void	set_token(t_list	**l, t_list	*elm, int i)
{
	fileopen(l, elm->allargs[i + 1], elm->allargs[i]);
	elm->token = elm->allargs[i];
	elm->outfile = elm->allargs[i + 1];
}

void	index_token(char token, int i, t_list **l, int *status)
{
	if (token == '>')
	{
		if ((*l)->count_token == 0)
		{
			(*l)->index_token = ft_calloc(sizeof(int) * 1);
			(*l)->index_token[0] = i;
			(*l)->count_token = 1;
		}
		else
			(*l)->index_token = intjoin(l, i);
	}
	if (token == '<')
	{
		if ((*l)->count_token == 0)
		{
			(*l)->index_token = ft_calloc(sizeof(int) * 1);
			(*l)->index_token[0] = i;
			(*l)->count_token = 1;
		}
		else
			(*l)->index_token = intjoin(l, i);
		if (token == '<')
			*status = 0;
	}
}

void	init_node(t_list	**node, char *pip)
{
	(*node)->cmd = ignore_directions_and_get_cmd(pip);
	(*node)->out_fd = -5;
	(*node)->in_fd = -5;
	(*node)->error = 0;
	(*node)->outfile = NULL;
	(*node)->heredoc_file = NULL;
	(*node)->token = NULL;
	(*node)->index_token = NULL;
	(*node)->count_token = 0;
	(*node)->args = NULL;
	(*node)->allargs = get_args(pip, node);
	if ((*node)->allargs != NULL)
		(*node)->args = args_filter(node);
}

char	**args_filter(t_list	**l)
{
	t_list	*elm;
	int		i;
	int		j;
	char	**args;

	elm = *l;
	i = elm->words;
	if (elm->count_token != 0)
		i -= 2 * elm->count_token;
	args = ft_calloc(sizeof(char *) * i + 1);
	i = -1;
	j = 0;
	while (elm->allargs[++i])
	{
		if (iftoken(i, l))
		{
			set_token(l, elm, i);
			i++;
		}
		else
			args[j++] = elm->allargs[i];
	}
	args[j] = NULL;
	return (args);
}
