/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakoudad <oakoudad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 17:44:42 by oakoudad          #+#    #+#             */
/*   Updated: 2022/09/14 02:23:00 by oakoudad         ###   ########.fr       */
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
			splited[j] = malloc(sizeof(char) * (ft_strlen(str) + 2));
		if (str[i] == '"' || str[i] == '\'')
			skip_quotes_init(str, &i, &k, splited[j]);
		else if (str[i] == ' ' && str[i + 1])
		{
			splited[j][k] = '\0';
			j++;
			k = 0;
			splited[j] = malloc(sizeof(char) * (ft_strlen(str) + 1));
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
	splited = malloc(sizeof(char *) * (ft_strlen(str) + 2));
	if (!splited)
		return (NULL);
	splited = copy_var1(str, j, k, splited);
	return (splited);
}

int	check_key(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
	{
		if ((str[i] >= 'a' && str[i] <= 'z')
			|| (str[i] >= 'A' && str[i] <= 'Z')
			|| (str[i] == '_')
			|| (str[i] >= '0' && str[i] <= '9' && i > 0))
			i++;
		else if ((str[i] >= '0' && str[i] <= '9') && i != 0)
			i++;
		else
		{
			write(2, "minishell: export: `", 21);
			write(2, str, ft_strlen(str));
			write(2, "': not a valid identifier\n", 27);
			create_list("?", "1");
			return (0);
		}
	}
	return (1);
}

int	ft_export(char **var)
{
	int		i;
	char	**t;

	i = -1;
	create_list("?", "0");
	if (!var || !var[0])
		ft_env(0);
	else
	{
		while (var[++i])
		{
			if (check_key(var[i]))
			{
				t = malloc(sizeof(char *) * 2);
				t[0] = var[i];
				t[1] = NULL;
				split_equal(t, 0);
				free(t);
			}
		}
	}
	return (0);
}
//cat << "echo" >