/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelmoham <eelmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 01:21:09 by eelmoham          #+#    #+#             */
/*   Updated: 2022/09/16 04:32:00 by eelmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_pwd(void)
{
	char	cwd[1000];

	if (getcwd(cwd, 1000))
		return (ft_strdup(cwd));
	else if (get_env_var("PWD"))
		return (ft_strdup(get_env_var("PWD")));
	return (NULL);
}

int	built_in_pwd(void)
{
	char	cwd[1000];

	if (getcwd(cwd, 1000))
	{
		printf("%s\n", cwd);
		return (1);
	}
	else if (get_env_var("PWD"))
	{
		printf("%s\n", get_env_var("PWD"));
		return (1);
	}
	else
		return (0);
}
