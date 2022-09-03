/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_var.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakoudad <oakoudad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 18:19:19 by oakoudad          #+#    #+#             */
/*   Updated: 2022/09/02 18:23:28 by oakoudad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	copy_var_2(int *d, char *var, char *dest)
{
	t_list_env	*temp;
	int			i;
	int			j;

	temp = g_info.env_lst;
	i = (*d);
	j = -1;
	while (temp)
	{
		if (ft_strcmp(temp->key, var) == 0)
		{
			while (temp->value[++j])
				dest[i++] = temp->value[j];
		}
		temp = temp->next;
	}
	dest[i] = '\0';
	*d = i;
}

int	copy_var(char *s, char *dest, int *d)
{
	t_list_env	*temp;
	int			len;
	char		*var;

	len = 0;
	temp = g_info.env_lst;
	if (s[0] == '?')
		len = 1;
	else
		while (is_valid_key(s[len]))
			len++;
	var = create_var(s, len);
	copy_var_2(d, var, dest);
	return (free(var), len);
}
