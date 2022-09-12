/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakoudad <oakoudad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 02:02:16 by oakoudad          #+#    #+#             */
/*   Updated: 2022/09/12 02:30:57 by oakoudad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_pwd(void)
{
	char	cwd[1000];

	if (getcwd(cwd, 1000))
		return (ft_strdup(cwd));
	return (NULL);
}

int	ft_pwd(void)
{
	char	cwd[1000];

	if (getcwd(cwd, 1000))
	{
		printf("%s\n", cwd);
		return (1);
	}
	else
		return (0);
}
