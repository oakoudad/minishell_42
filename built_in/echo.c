/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelmoham <eelmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 01:21:09 by eelmoham          #+#    #+#             */
/*   Updated: 2022/09/16 04:32:13 by eelmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_args(char *str)
{
	int	y;
	int	n_option;

	y = 1;
	n_option = 0;
	if (str[0] == '-')
	{
		while (str[y])
		{
			if (str[y] != 'n')
			{
				n_option = 0;
				return (n_option);
			}
			else
			{
				n_option = 1;
			}
			y++;
		}
	}
	return (n_option);
}

int	pass_n(char **var)
{
	int	i;

	i = 0;
	while (var[i] && check_args(var[i]) == 1)
		i++;
	return (i);
}

void	built_in_echo(char **var)
{
	int	i;
	int	y;
	int	n_option;

	i = -1;
	y = -1;
	n_option = 0;
	if (var && var[0])
	{
		while (var[++y])
			n_option = check_args(var[0]);
		if (n_option == 1)
			i = pass_n(var) - 1;
		while (var[++i])
		{
			ft_putstr_fd(1, var[i]);
			if (var[i + 1] != NULL)
				ft_putstr_fd(1, " ");
		}
		if (n_option == 0)
			ft_putstr_fd(1, "\n");
	}
	else
		ft_putstr_fd(1, "\n");
	create_list("?", "0");
}
