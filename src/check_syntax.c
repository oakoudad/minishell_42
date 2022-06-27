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

int len_of_cmd(char *s, int to)
{
	int i;
	int j;

	i = 0;
	j = to + 1;
	while (i < to)
	{
		if (s[i] == '"' || s[i] == '\'')
		{
			j -= 2;
			skep_quotes(s, &i);
		}
		if (s[i] == ' ')
			break;
		i++;
	}
	return (j);
}

void	copyto(char *src, char *dst, char c, int *d)
{
	int		i;
	int		j;

	i = 0;
	j = *d;
	while (src[i] != c)
		dst[j++] = src[i++];
	dst[j] = '\0';
	*d = j;
}

char	*get_cmd(char *s, int *d)
{
	int		end;
	int	 	j;
	int	 	i;
	char 	*cmd;

	j = 0;
	end = end_of_cmd(s);
	cmd = malloc(sizeof(char) * len_of_cmd(s, end) + 1);
	printf("len = %d", len_of_cmd(s, end));
	if (!cmd)
		return (NULL);
	i = 0;
	while (j <= end)
	{
		if (s[j] != '"' && s[j] != '\'')
			cmd[i++] = s[j];
		else
		{
			copyto(s + j + 1, cmd, s[j], &i);
			skep_quotes(s, &j);
		}
		j++;
	}
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
		else if (s[i] == ' ')
			word++;
		i++;
	}
	(*l)->words = word;
	if (word == 0)
		return NULL;
	args = malloc(sizeof(char*) * word + 1);
	i = 0;
	d = 0;
	while (i < word)
	{
		while (s[0] == ' ')
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

void parsing(char	**pips)
{
	t_list	*l;
	int		i;
	int		j;
	int		k;

	i = 0;
	while (pips[i])
	{
		l = malloc(sizeof(t_list));
		j = 0;
		l->cmd = get_cmd(pips[i], &j);
		l->fd = -5;
		l->index_token = NULL;
		l->count_token = 0;
		l->args = get_args(pips[i] + j, &l);
		l->args = args_filter(&l);
		k = 0;
		while (l->args[k])
			printf("%s\n", l->args[k++]);
		i++;
	}
	
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
