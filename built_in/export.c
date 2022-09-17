/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakoudad <oakoudad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 01:21:09 by eelmoham          #+#    #+#             */
/*   Updated: 2022/09/17 23:03:44 by oakoudad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	skip_quotes_init(char *str, int *d, int *c, char *var)
{
	int	i;
	int	y;

	i = *d + 1;
	y = *c;
	while (str[i] && str[i] != '\'' && str[i] != '\"')
	{
		var[y] = str[i];
		i++;
		y++;
	}
	if (str[i] == 0)
		printf("Invalid syntax\n");
	*d = i;
	*c = y;
}

char	**copy_var1(char *str, int j, int k, char **splited)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (i == 0)
			splited[j] = ft_calloc(sizeof(char) * (ft_strlen(str) + 2));
		if (str[i] == '"' || str[i] == '\'')
			skip_quotes_init(str, &i, &k, splited[j]);
		else if (str[i] == ' ' && str[i + 1])
		{
			splited[j][k] = '\0';
			j++;
			k = 0;
			splited[j] = ft_calloc(sizeof(char) * (ft_strlen(str) + 1));
		}
		else
		{
			splited[j][k] = str[i];
			k++;
		}
	}
	splited[j][k] = '\0';
	splited[j + 1] = NULL;
	return (splited);
}

char	**split(char *str)
{
	int		j;
	int		k;
	char	**splited;

	j = 0;
	k = 0;
	splited = ft_calloc(sizeof(char *) * (ft_strlen(str) + 2));
	if (!splited)
		return (NULL);
	splited = copy_var1(str, j, k, splited);
	return (splited);
}

int	check_key(char *str)
{
	int	i;

	i = 0;
	if (str && (str[0] == '=' || str[0] == '\0'))
		return (export_error(str));
	while (str[i] && str[i] != '=' && str[i] != '+')
	{
		if ((str[i] >= 'a' && str[i] <= 'z')
			|| (str[i] >= 'A' && str[i] <= 'Z')
			|| (str[i] == '_')
			|| (str[i] >= '0' && str[i] <= '9' && i > 0))
			i++;
		else if ((str[i] >= '0' && str[i] <= '9') && i != 0)
			i++;
		else
			return (export_error(str));
	}
	if (str[i] == '+' && (str[i + 1] != '=' || i == 0))
		return (export_error(str));
	return (1);
}

int	built_in_export(char **var)
{
	int		i;
	char	**t;

	i = -1;
	create_list("?", "0");
	if (!var || !var[0])
		built_in_env(0);
	else
	{
		while (var[++i])
		{
			if (check_key(var[i]))
			{
				t = ft_calloc(sizeof(char *) * 2);
				t[0] = var[i];
				t[1] = NULL;
				split_equal(t, 0);
				free(t);
			}
		}
	}
	return (0);
}
