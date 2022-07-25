/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakoudad <oakoudad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 03:14:13 by oakoudad          #+#    #+#             */
/*   Updated: 2022/07/25 16:48:54 by oakoudad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_cmd(char *s, int *d)
{
	int		end;
	int	 	j;
	int	 	i;
	char 	*cmd;

	end = end_of_cmd(s);
	cmd = malloc(sizeof(char) * len_of_cmd(s, end) + 1);
	if (!cmd)
		return (NULL);
	i = 0;
	j = 0;
	while (j <= end)
	{
		if (s[j] != '"' && s[j] != '\'')
		{
			if (s[j] == '$' && s[j + 1] != '"' && s[j + 1] != '\'' && s[j + 1] != '\0')
				j += copy_var(s + j + 1, cmd, &i);
			else
				cmd[i++] = s[j];
		}
		else
		{
			copyto(s + j + 1, cmd, s[j], &i);
			skep_quotes(s, &j);
		}
		j++;
	}
	cmd[i] = '\0';
	*d = end + 1;
	return (cmd);
}

char	*ignore_directions_and_get_cmd(char *s)
{
	char 	*token;
	int d;

	d = 0;
	while (1)
	{
		while (is_space(s[0]))
			s++;
		token = get_cmd(s, &d); // get	cmd
		if(ft_strcmp(token, ">") == 0 || ft_strcmp(token, ">>") == 0 || ft_strcmp(token, "<") == 0 || ft_strcmp(token, "<<") == 0) // if result is token
		{
			free(token);
			s += d;
			while (is_space(s[0]))
				s++;
			token = get_cmd(s, &d);
			s += d;
			free(token);
		}
		else if(token[0] == '>' || token[0] == '<')
		{
			free(token);
			s += d;
			while (is_space(s[0]))
				s++;
		}
		else
			break ;
	}
	return (token);
}

char	**get_args(char *s, t_list **l)
{
	int i;
	int d;
	char **args;

	i = 0;
	(*l)->words = 0;
	while (s[i])
	{
		if (s[i] == '"' || s[i] == '\'')
			skep_quotes(s, &i);
		else if (is_space(s[i]))
		{
			while (is_space(s[i]) && is_space(s[i + 1]))
				i++;
			(*l)->words += 1;
		}
		else if ((s[i] == '>' || s[i] == '<') && !is_space(s[i - 1]))
		{
			while ((s[i] == '>' || s[i] == '<'))
				i++;
			(*l)->words += 2;
		}
		i++;
	}
	(*l)->words += 1;
	args = malloc(sizeof(char*) * (*l)->words + 1);
	i = 0;
	d = 0;
	while (i < (*l)->words)
	{
		while (is_space(s[0]))
			s++;
		args[i] = get_cmd(s, &d);
		if (args[i][0] == '>')
		{
			if((*l)->count_token == 0)
			{
				(*l)->index_token = malloc(sizeof(int) * 1);
				(*l)->index_token[0] = i;
				(*l)->count_token = 1;
			}
			else
				(*l)->index_token = intjoin(l, i);
		}
		if (args[i][0] == '<')
		{
			if((*l)->count_token == 0)
			{
				(*l)->index_token = malloc(sizeof(int) * 1);
				(*l)->index_token[0] = i;
				(*l)->count_token = 1;
			}
			else
				(*l)->index_token = intjoin(l, i);
		}
		s = s + d;
		i++;
	}
	if (args[i - 1][0] == '\0')
		args[i - 1] = NULL;
	args[i] = NULL;
	return args;
}

char	**args_filter(t_list	**l)
{
	t_list	*elm;
	int		size;
	int		i;
	int		j;
	char	**args;

	elm = *l;
	size = elm->words;
	if (elm->count_token != 0)
		size -= 2 * elm->count_token;
	args = malloc(sizeof(char*) * size + 1);
	i = -1;
	j = 0;
	while (elm->args[++i])
	{
		if (iftoken(i, l)){
			fileopen(l,  elm->args[i + 1],  elm->args[i]);
			elm->token = elm->args[i];
			elm->outfile = elm->args[i + 1];
			i++;
		}
		else
			args[j++] = elm->args[i];
	}
	args[j] = NULL;
	free(elm->args);
	return (args);
}

void	parsing(char	**pips)
{
	t_list	*node;
	t_list	*head;
	t_list	*tmp;
	int		i;
	int		j;
	i = 0;
	head = NULL;
	while (pips[i] != NULL && i < g_info.count_pipes)
	{
		node = malloc(sizeof(t_list));
		node->args = NULL;
		if (head == NULL)
			head = node;
		else
			tmp->next = node;
		j = 0;
		node->cmd = ignore_directions_and_get_cmd(pips[i]);
		node->out_fd = -5;
		node->in_fd = -5;
		node->outfile = NULL;
		node->token = NULL;
		node->index_token = NULL;
		node->count_token = 0;
		node->args = get_args(pips[i], &node);
		if (node->args != NULL)
			node->args = args_filter(&node);
		tmp = node;
		i++;
	}
	tmp->next = NULL;
	g_info.cmds = head;
	routes();
}