/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_status.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakoudad <oakoudad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 22:45:22 by oakoudad          #+#    #+#             */
/*   Updated: 2022/09/17 22:46:06 by oakoudad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	set_status(int type)
{
	char	**oldpwd;

	if (type == 1)
	{
		oldpwd = ft_calloc(sizeof(char *) * 2);
		oldpwd[0] = ft_strdup("OLDPWD");
		oldpwd[1] = NULL;
		built_in_unset(oldpwd);
		free(oldpwd[0]);
		free(oldpwd);
	}
	create_list("?", "0");
	if (sort_list() == 0)
		return (0);
	return (type);
}
