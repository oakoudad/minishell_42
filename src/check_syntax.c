/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakoudad <oakoudad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 21:10:26 by oakoudad          #+#    #+#             */
/*   Updated: 2022/05/28 22:39:19 by oakoudad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int len_var(char *s, t_list_env **env)
{
	t_list_env *temp;
	int i;
	int len;
	int res;
	char *var;

	i = -1;
	len = 0;
	res = 0;
	temp = *env;
	while ((s[len] >= 'a' && s[len] <= 'z') || (s[len] >= 'A' && s[len] <= 'Z') || s[len] == '_')
		len++;
	var = malloc(sizeof(char) * len);
	while (++i < len)
		var[i] = s[i];
	var[i] = 0;
	while (temp)
	{
		if (ft_strcmp(temp->key, var) == 0)
			res = ft_strlen(temp->value);
		temp = temp->next;
	}
	free(var);
	var = NULL;
	return (res);
}

char	*ft_strdup(char *s1)
{
	int		i;
	int		len;
	char	*str;

	i = 0;
	len = ft_strlen(s1);
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_charjoin(char *s1, char c)
{
	char	*str;
	size_t	i;

	if (!s1)
		s1 = ft_strdup("");
	if (!c || !s1)
		return (NULL);
	str = malloc(sizeof(char) * ft_strlen(s1) + 2);
	if (!str)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	str[i++] = c;
	str[i] = 0;
	free(s1);
	return (str);
}

int	skep_quotes(char *s, int *d)
{
	char	c;
	int		i;

	c = s[*d];
	i = *d + 1;
	while (s[i] && s[i] != c)
		i++;
	if (s[i] == 0)
	{
		ft_putstr("Minishell: syntax error quotes not closed\n");
		return (0);
	}
	*d = i;
	return (1);
}

int	skep_quotes2(char *s, int *d, t_list_env **env)
{
	char	c;
	int		i;
	int 	res;

	c = s[*d];
	i = *d + 1;
	res = 0;
	while (s[i] && s[i] != c)
	{
		if (s[i] == '$')
			res = len_var(s + i + 1, env);
		i++;
	}
	if (s[i] == 0)
	{
		ft_putstr("Minishell: syntax error quotes not closed\n");
		return (0);
	}
	*d = i;
	return (res);
}

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

int end_of_cmd(char *s)
{
	int end;

	end = 0;
	while (s[end])
	{
		if (s[end] == '"' || s[end] == '\'')
			skep_quotes(s, &end);
		if (s[end] == ' ')
			break;
		end++;
	}
	return (end-1);
}



int len_of_cmd(char *s, int to, t_list_env **env)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < to)
	{
		if(s[i] == '$')
			j += len_var(s + i + 1, env);
		if (s[i] == '"' || s[i] == '\'')
		{
			j -= 2;
			j += skep_quotes2(s, &i, env);
		}
		if (s[i] == ' ')
			break;
		i++;
	}
	return (j);
}

int copy_var(char *s, char *dest,t_list_env **env, int *d)
{
	t_list_env *temp;
	int len;
	int i;
	int j;
	char *var;

	i = -1;
	len = 0;
	temp = *env;
	while ((s[len] >= 'a' && s[len] <= 'z') || (s[len] >= 'A' && s[len] <= 'Z') || s[len] == '_')
		len++;
	var = malloc(sizeof(char) * len);
	while (i < len)
	{
		var[i] = s[i];
		i++;
	}
	var[i] = '\0';
	i = (*d);
	j = -1;
	while (temp)
	{
		if (ft_strcmp(temp->key, var) == 0)
		{
			while (temp->value[++j])
				dest[i++] = temp->value[j];
		}
		temp = temp->next;
	}
	dest[i] = '\0';
	*d = i;
	free(var);
	return (len);
}

void	copyto(char *s, char *cmd, char c, int *d, t_list_env **env)
{
	int		i;
	int		j;

	j = 0;
	i = *d;
	while (s[j] != c)
	{
		if (s[j] == '$' && s[j + 1] != '"' && s[j + 1] != '\'' && s[j + 1] != '\0')
			j += copy_var(s + j + 1, cmd, env, &i);
		else
			cmd[i++] = s[j];
		j++;
	}
	*d = i;
}

char	*get_cmd(char *s, int *d, t_list_env **env)
{
	int		end;
	int	 	j;
	int	 	i;
	char 	*cmd;

	j = 0;
	end = end_of_cmd(s);
	//printf("len = %d\n", len_of_cmd(s, end, env));
	cmd = malloc(sizeof(char) * len_of_cmd(s, end, env) + 1);
	if (!cmd)
		return (NULL);
	i = 0;
	while (j <= end)
	{
		if (s[j] != '"' && s[j] != '\'')
		{
			if (s[j] == '$' && s[j + 1] != '"' && s[j + 1] != '\'' && s[j + 1] != '\0')
				j += copy_var(s + j + 1, cmd, env, &i);
			else
				cmd[i++] = s[j];
		}
		else
		{
			copyto(s + j + 1, cmd, s[j], &i, env);
			skep_quotes(s, &j);
		}
		j++;
	}
	cmd[i] = '\0';
	*d = end + 1;
	return (cmd);
}
int		*intjoin(t_list **l, int d)
{
	t_list	*elm;
	int		i;
	int		*r;

	elm = *l;
	r = malloc(sizeof(int) * elm->count_token + 1);
	i= 0;
	while (i < elm->count_token)
	{
		r[i] = elm->index_token[i];
		i++;
	}
	r[i] = d;
	elm->count_token++;
	free(elm->index_token);
	return (r);
}

char	**get_args(char *s, t_list **l, t_list_env **env)
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
		else if (s[i] == ' ')
			word++;
		i++;
	}
	(*l)->words = word;
	if (word == 0)
	{
		return NULL;
	}
	args = malloc(sizeof(char*) * word + 1);
	i = 0;
	d = 0;
	while (i < word)
	{
		while (s[0] == ' ')
			s++;
		args[i] = get_cmd(s, &d, env);
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

int		iftoken(int index, t_list **l)
{
	int i;
	t_list *elm;

	elm = *l;
	i = 0;
	while (i < elm->count_token)
	{
		if (index == elm->index_token[i])
			return (1);
		i++;
	}
	return (0);
}

void	fileopen(t_list	**l, char *filename, char *token)
{
	t_list	*elm;
	int 	int_token;

	elm = *l;
	if (token[0] == '>' && token[1] == '>')
		int_token = 2;
	else
		int_token = 1;
	if (elm->fd == -5)
	{
		if (int_token == 1)
			elm->fd = open(filename, O_CREAT | O_RDWR, 0666);
		else
			open(filename, O_RDWR | O_APPEND);
	}
	else
	{
		close(elm->fd);
		if (int_token == 1)
			elm->fd = open(filename, O_CREAT | O_RDWR, 0666);
		else
			open(filename, O_RDWR | O_APPEND);
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
	printf("fd : %d\n", elm->fd);
	printf("token : %s\n", elm->token);
	printf("filename : %s\n", elm->filename);
	free(elm->args);
	return (args);
}

// void free_parsing()
// {
// 	int k;

// 	k = 0;
// 	while (l->args && l->args[k])
// 		free(l->args[k++]);
// }

void parsing(char	**pips, t_list_env **env)
{
	t_list	*node;
	t_list	*head;
	t_list	*tmp;
	int		i;
	int		j;

	i = 0;
	head = NULL;
	while (pips[i])
	{
		node = malloc(sizeof(t_list));
		if (head == NULL)
			head = node;
		else
			tmp->next = node;
		j = 0;
		node->cmd = get_cmd(pips[i], &j, env);
		node->fd = -5;
		node->filename = NULL;
		node->token = NULL;
		node->index_token = NULL;
		node->count_token = 0;
		node->args = get_args(pips[i] + j, &node, env);
		if (node->args != NULL)
			node->args = args_filter(&node);
		tmp = node;
		i++;
	}
	while(head)
	{
		printf("CMD = %s\n", head->cmd);
		int k = 0;
		while(head->args && head->args[k] != NULL)
		{
			printf(" Arg %d = %s\n", k + 1, head->args[k]);
			k++;
		}
		head = head->next;
	}
}

int	check_syntax(char *s, t_list_env **env)
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
	parsing(pips, env);
	return (1);
}
