/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_home.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakoudad <oakoudad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 19:11:12 by oakoudad          #+#    #+#             */
/*   Updated: 2022/09/09 19:11:32 by oakoudad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_home(void)
{
	char	*home;
	char	*tmp;

	home = get_path("HOME");
	if (home == NULL || *home == 0)
		return ("");
	tmp = ft_strdup(home);
	return (tmp);
}