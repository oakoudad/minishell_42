/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakoudad <oakoudad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 03:26:50 by oakoudad          #+#    #+#             */
/*   Updated: 2022/09/14 21:28:48 by oakoudad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strdup2(char *s1)
{
	int		i;
	int		len;
	char	*str;

	i = 0;
	len = ft_strlen(s1);
	str = ft_calloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	if (len == 0)
	{
		str[0] = '\0';
		return (str);
	}
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_strdup(char *s1)
{
	int		i;
	int		len;
	char	*str;

	i = 0;
	len = ft_strlen(s1);
	if (len == 0)
	{
		str = ft_calloc(sizeof(char) * 1);
		str[0] = 0;
		return (str);
	}
	str = ft_calloc(sizeof(char) * (len + 1));
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
	str = ft_calloc(sizeof(char) * ft_strlen(s1) + 2);
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

int	*intjoin(t_list **l, int d)
{
	t_list	*elm;
	int		i;
	int		*r;

	elm = *l;
	r = ft_calloc(sizeof(int) * elm->count_token + 1);
	i = 0;
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

int	is_valid_key(char c)
{
	if ((c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z') || c == '_'
		|| (c >= '0' && c <= '9'))
		return (1);
	return (0);
}
