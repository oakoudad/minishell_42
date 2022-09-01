/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakoudad <oakoudad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 03:14:13 by oakoudad          #+#    #+#             */
/*   Updated: 2022/09/01 18:54:22 by oakoudad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_cmd(char *s, int *d, int withextra)
{
	int		end;
	char	*cmd;

	end = end_of_cmd(s);
	cmd = malloc(sizeof(char) * len_of_cmd(s, end) + 1);
	if (!cmd)
		return (NULL);
	create_cmd(s, cmd, end, withextra);
	*d = end + 1;
	return (cmd);
}

char	*ignore_directions_and_get_cmd(char *s)
{
	char	*token;
	int		d;

	d = 0;
	while (1)
	{
		while (is_space(s[0]))
			s++;
		token = get_cmd(s, &d, 1);
		if (ft_strcmp(token, ">") == 0 || ft_strcmp(token, ">>") == 0
			|| ft_strcmp(token, "<") == 0 || ft_strcmp(token, "<<") == 0)
		{
			free(token);
			s += d;
			while (is_space(s[0]))
				s++;
			token = get_cmd(s, &d, 1);
			s += d;
			free(token);
		}
		else
			break ;
	}
	return (token);
}

void	count_args(char *s, t_list **l)
{
	int	i;

	i = 0;
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
}

char	**get_args(char *s, t_list **l)
{
	int		i;
	int		d;
	char	**args;
	int		status;

	(*l)->words = 1;
	count_args(s, l);
	args = malloc(sizeof(char *) * (*l)->words + 1);
	i = 0;
	d = 0;
	status = 1;
	while (i < (*l)->words)
	{
		while (is_space(s[0]))
			s++;
		args[i] = get_cmd(s, &d, status);
		status = 1;
		index_token(args[i][0], i, l, &status);
		s = s + d;
		i++;
	}
	if (args[i - 1][0] == '\0')
		args[i - 1] = NULL;
	args[i] = NULL;
	return (args);
}

void	parsing(char	**pips)
{
	t_list	*node;
	t_list	*head;
	t_list	*tmp;
	int		i;

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
		init_node(&node, pips[i]);
		tmp = node;
		i++;
	}
	tmp->next = NULL;
	g_info.cmds = head;
	if (head->cmd != NULL && head->cmd[0] != '\0')
		exec_pipe(-1, head);
}
