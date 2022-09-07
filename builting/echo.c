/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakoudad <oakoudad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 15:51:42 by oakoudad          #+#    #+#             */
/*   Updated: 2022/09/07 15:59:33 by oakoudad         ###   ########.fr       */
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
	while (check_args(var[i]) == 1)
		i++;
	return (i);
}

void	ft_echo(char **var)
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
			ft_putstr(var[i]);
			if (var[i + 1] != NULL)
				ft_putstr(" ");
		}
		if (n_option == 0)
			ft_putstr("\n");
	}
	else
		ft_putstr("\n");
}
