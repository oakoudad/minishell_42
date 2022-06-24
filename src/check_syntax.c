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

char	**get_args(char *s)
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
	args = malloc(sizeof(char*) * word + 1);
	i = 0;
	d = 0;
	while (i < word)
	{
		while (s[0] == ' ')
			s++;
		args[i] = get_cmd(s, &d);
		printf("arg = %s\n", args[i]);
		s = s + d;
		i++;
	}
	args[i] = NULL;
	return args;
}

void parsing(char	**pips)
{
	t_list	*l;
	int		i;
	int		j;

	i = 0;
	while (pips[i])
	{
		printf("%s\n", *pips);
		l = malloc(sizeof(t_list));
		j = 0;
		l->cmd = get_cmd(pips[i], &j);
		l->args = get_args(pips[i] + j);
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
