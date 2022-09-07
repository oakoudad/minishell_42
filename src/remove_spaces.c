/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_spaces.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakoudad <oakoudad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 18:19:25 by oakoudad          #+#    #+#             */
/*   Updated: 2022/09/07 18:19:26 by oakoudad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	skep_and_full(char *s, char *p, int *d, int *j)
{
	char	c;
	int		i;
	int		z;

	c = s[*d];
	p[*j] = s[*d];
	i = *d + 1;
	z = *j + 1;
	while (s[i] && s[i] != c)
	{
		p[z] = s[i];
		z++;
		i++;
	}
	if (s[i] == c)
		p[z++] = s[i++];
	*d = i;
	*j = z;
}

// char	*refull(char *s, int len)
// {
// 	int		i;
// 	int		j;
// 	int		status;
// 	char	*p;

// 	p = malloc(len + 1);
// 	init_index(&i, &status, &j);
// 	while(s[i])
// 	{
// 		if (s[i] == '"' || s[i] == '\'')
// 		{
// 			if (status == 1)
// 			{
// 				status = 0;
// 				p[j++] = ' ';
// 			}
// 			skep_and_full(s, p, &i, &j);
// 		}
// 		printf("%d, %d\n", i ,j);
// 		if (s[i] == ' ')
// 		{
// 			status = 1;
// 			i++;
// 			continue;
// 		}
// 		else if (s[i] != ' ' && status == 1)
// 		{
// 			p[j] = ' ';
// 			j++;
// 			status = 0;
// 		}
// 		p[j++] = s[i++];
// 	}
// 	p[len] = 0;
// 	printf("--->%s;", p);
// 	return (s);
// }

// char	*remove_spaces(char *p)
// {
// 	int		i;
// 	int		j;
// 	int		status;

// 	init_index(&i, &status, &j);
// 	while(p[i])
// 	{
// 		if (p[i] == '"' || p[i] == '\'')
// 		{
// 			j = j - i;
// 			skep_quotes(p, &i);
// 			j = j + i;
// 		}
// 		if (p[i] == ' ')
// 		{
// 			status = 1;
// 			i++;
// 			continue;
// 		}
// 		else if (p[i] != ' ' && status == 1)
// 		{
// 			j++;
// 			status = 0;
// 		}
// 		j++;
// 		i++;
// 	}
// 	return (refull(p, j));
// }