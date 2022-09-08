/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakoudad <oakoudad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 17:44:42 by oakoudad          #+#    #+#             */
/*   Updated: 2022/09/08 21:37:36 by oakoudad         ###   ########.fr       */
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
	{
		printf("Invalid syntax\n");
	}
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
			splited[j] = malloc(sizeof(char) * (strlen(str) + 2));
		if (str[i] == '"' || str[i] == '\'')
			skip_quotes_init(str, &i, &k, splited[j]);
		else if (str[i] == ' ' && str[i + 1])
		{
			splited[j][k] = '\0';
			j++;
			k = 0;
			splited[j] = malloc(sizeof(char) * (strlen(str) + 1));
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
	int		i;
	int		j;
	int		k;
	char	**splited;

	i = 0;
	j = 0;
	k = 0;
	splited = malloc(sizeof(char *) * (strlen(str) + 2));
	if (!splited)
		return (NULL);
	splited = copy_var1(str, j, k, splited);
	return (splited);
}

void	check_key(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
	{
		if ((str[i] >= 'a' && str[i] <= 'z')
			|| (str[i] >= 'A' && str[i] <= 'Z')
			|| (str[i] == '_'))
			i++;
		else if ((str[i] >= '0' && str[i] <= '9') && i != 0)
			i++;
		else
		{
			printf("minishell: export: `%s': not a valid identifier\n", str);
			return ;
		}
	}
}

int	ft_export(char **var)
{
	int	i;

	i = -1;
	if (!var || !var[0])
		ft_env(0);
	else
	{
		while (var[++i])
			check_key(var[i]);
		split_equal(var, 0);
	}
	return (0);
}
