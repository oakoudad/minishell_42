/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakoudad <oakoudad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 03:14:13 by oakoudad          #+#    #+#             */
/*   Updated: 2022/07/07 03:31:31 by oakoudad         ###   ########.fr       */
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

char	**get_args(char *s, t_list **l)
{
	int i;
	int d;
	int word;
	char **args;

	i = 0;
	word = 0;
	while (s[i])
	{
		if (s[i] == '"' || s[i] == '\'')
			skep_quotes(s, &i);
		else if (is_space(s[i]))
		{
			while (is_space(s[i]) && is_space(s[i + 1]))
				i++;
			word++;
		}
		i++;
	}
	(*l)->words = word;
	if (word == 0)
		return (NULL);
	args = malloc(sizeof(char*) * word + 1);
	i = 0;
	d = 0;
	while (i < word)
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
		s = s + d;
		i++;
	}
	args[i] = NULL;
	return args;
}

void	fileopen(t_list	**l, char *filename, char *token)
{
	t_list	*elm;
	int 	int_token;

	elm = *l;
	if (ft_strcmp(token, ">>") == 0)
		int_token = 2;
	else
		int_token = 1;
	if (elm->fd == -5)
	{
		if (int_token == 1)
			elm->fd = open(filename, O_CREAT | O_RDWR, 0666);
		else
		{
			elm->fd = open(filename, O_RDWR | O_APPEND);
			if (elm->fd == -1)
				elm->fd = open(filename, O_CREAT | O_RDWR);
		}
	}
	else
	{
		close(elm->fd);
		if (int_token == 1)
			elm->fd = open(filename, O_CREAT | O_RDWR, 0666);
		else
		{
			elm->fd = open(filename, O_RDWR | O_APPEND);
			if (elm->fd == -1)
				elm->fd = open(filename, O_CREAT | O_RDWR);
		}
	}
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
			elm->filename = elm->args[i + 1];
			i++;
		}
		else
			args[j++] = elm->args[i];
	}
	args[i] = NULL;
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
		node->cmd = get_cmd(pips[i], &j);
		node->fd = -5;
		node->filename = NULL;
		node->token = NULL;
		node->index_token = NULL;
		node->count_token = 0;
		node->args = get_args(pips[i] + j, &node);
		if (node->args != NULL)
			node->args = args_filter(&node);
		tmp = node;
		i++;
	}
	tmp->next = NULL;
	if (ft_strcmp(head->cmd, "echo") == 0)
		ft_echo(head->args, head->fd);
	if (ft_strcmp(head->cmd, "export") == 0)
		ft_export(head->args);
	if (ft_strcmp(head->cmd, "env") == 0)
		ft_env(1);
	if (ft_strcmp(head->cmd, "cd") == 0)
	{
		if (head->args)
			ft_cd(head->args[0]);
		else
			ft_cd("");
	}
	if (ft_strcmp(head->cmd, "unset") == 0)
		ft_unset(head->args);
	if (ft_strcmp(head->cmd, "pwd") == 0)
		ft_pwd();
	if (ft_strcmp(head->cmd, "exit") == 0)
		ft_exit(head->args);
}