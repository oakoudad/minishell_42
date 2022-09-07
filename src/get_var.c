/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakoudad <oakoudad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 18:14:09 by oakoudad          #+#    #+#             */
/*   Updated: 2022/09/07 18:15:08 by oakoudad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_isalnum(int c)
{
	if ((c >= 48 && c <= 57) || (c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return (1);
	return (0);
}

void	get_var(char *s, int *d, int fd)
{
	char	*dup;
	char	*var;
	int		i;

	dup = ft_strdup(s);
	i = 1;
	while (dup[i] != '\0')
	{
		if (!ft_isalnum(dup[i]))
		{
			dup[i] = 0;
			break ;
		}
		i++;
	}
	var = get_env_var(dup + 1);
	write(fd, var, ft_strlen(var));
	if (var == NULL)
		free(var);
	if (dup == NULL)
		free(dup);
	*d += (i - 1);
}
