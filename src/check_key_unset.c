/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_key_unset.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakoudad <oakoudad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 22:48:17 by oakoudad          #+#    #+#             */
/*   Updated: 2022/09/17 23:05:29 by oakoudad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	unset_error(char *str)
{
	write(2, "minishell: unset: `", 20);
	write(2, str, ft_strlen(str));
	write(2, "': not a valid identifier\n", 27);
	create_list("?", "1");
	return (0);
}

int	check_key_unset(char *str)
{
	int	i;

	i = 0;
	if (str && str[0] == '\0')
		return (unset_error(str));
	while (str[i])
	{
		if ((str[i] >= 'a' && str[i] <= 'z')
			|| (str[i] >= 'A' && str[i] <= 'Z')
			|| (str[i] == '_')
			|| (str[i] >= '0' && str[i] <= '9' && i > 0))
			i++;
		else if ((str[i] >= '0' && str[i] <= '9') && i != 0)
			i++;
		else
			return (unset_error(str));
	}
	if (str[i] == '+' && (str[i + 1] != '=' || i == 0))
		return (unset_error(str));
	return (1);
}
