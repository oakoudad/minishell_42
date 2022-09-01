/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakoudad <oakoudad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 18:18:32 by oakoudad          #+#    #+#             */
/*   Updated: 2022/09/01 19:04:30 by oakoudad         ###   ########.fr       */
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
			if (withextra && s[j] == '$' && s[j + 1] != '"'
				&& s[j + 1] != '\'' && s[j + 1] != '\0')
				j += copy_var(s + j + 1, cmd, &i);
			else
				cmd[i++] = s[j];
		}
		else
		{
			copyto(s + j + 1, cmd, &i, withextra);
			skep_quotes(s, &j);
		}
		j++;
	}
	cmd[i] = '\0';
}

void	set_token(t_list	**l, t_list	*elm, int i)
{
	fileopen(l, elm->args[i + 1], elm->args[i]);
	elm->token = elm->args[i];
	elm->outfile = elm->args[i + 1];
}

void	index_token(char token, int i, t_list **l, int *status)
{
	if (token == '>')
	{
		if ((*l)->count_token == 0)
		{
			(*l)->index_token = malloc(sizeof(int) * 1);
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
			(*l)->index_token = malloc(sizeof(int) * 1);
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
	(*node)->outfile = NULL;
	(*node)->heredog_file = NULL;
	(*node)->token = NULL;
	(*node)->index_token = NULL;
	(*node)->count_token = 0;
	(*node)->args = get_args(pip, node);
	if ((*node)->args != NULL)
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
	args = malloc(sizeof(char *) * i + 1);
	i = -1;
	j = 0;
	while (elm->args[++i])
	{
		if (iftoken(i, l))
		{
			set_token(l, elm, i);
			i++;
		}
		else
			args[j++] = elm->args[i];
	}
	args[j] = NULL;
	free(elm->args);
	return (args);
}
