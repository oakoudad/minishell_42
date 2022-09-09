/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_spaces.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakoudad <oakoudad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 18:19:25 by oakoudad          #+#    #+#             */
/*   Updated: 2022/09/09 23:26:25 by oakoudad         ###   ########.fr       */
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
