/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   utils2.c										   :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: oakoudad <oakoudad@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2022/07/07 03:30:46 by oakoudad		  #+#	#+#			 */
/*   Updated: 2022/07/07 03:48:39 by oakoudad		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "../minishell.h"

void	copyto(char *s, char *cmd, char c, int *d)
{
	int		i;
	int		j;

	j = 0;
	i = *d;
	while (s[j] != c)
	{
		if (s[j] == '$' && s[j + 1] != '"'
			&& s[j + 1] != '\'' && s[j + 1] != '\0')
			j += copy_var(s + j + 1, cmd, &i);
		else
			cmd[i++] = s[j];
		j++;
	}
	*d = i;
}

char	*create_var(char *s, int len)
{
	int		i;
	char	*var;

	i = -1;
	var = malloc(sizeof(char) * len);
	while (++i < len)
		var[i] = s[i];
	var[i] = '\0';
	return (var);
}

int	copy_var(char *s, char *dest, int *d)
{
	t_list_env	*temp;
	int			len;
	int			i;
	int			j;
	char		*var;

	len = 0;
	temp = g_info.env_lst;
	if (s[0] == '?')
		len = 1;
	else
		while (is_valid_key(s[len]))
			len++;
	var = create_var(s, len);
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
	return (free(var), len);
}

int	end_of_cmd(char *s)
{
	int	end;

	end = 0;
	while (s[end])
	{
		if (s[end] == '"' || s[end] == '\'')
			skep_quotes(s, &end);
		if (is_space(s[end]))
			break ;
		end++;
	}
	return (end - 1);
}

void	fileopen(t_list	**l, char *filename, char *token)
{
	int	int_token;

	int_token = 1;
	if (ft_strcmp(token, ">>") == 0)
		int_token = 2;
	if ((*l)->fd == -5)
	{
		if (int_token == 1)
			(*l)->fd = open(filename, O_CREAT | O_RDWR, 0666);
		else
		{
			(*l)->fd = open(filename, O_RDWR | O_APPEND);
			if ((*l)->fd == -1)
				(*l)->fd = open(filename, O_CREAT | O_RDWR);
		}
	}
	else
	{
		close((*l)->fd);
		if (int_token == 1)
			(*l)->fd = open(filename, O_CREAT | O_RDWR, 0666);
		else
		{
			(*l)->fd = open(filename, O_RDWR | O_APPEND);
			if ((*l)->fd == -1)
				(*l)->fd = open(filename, O_CREAT | O_RDWR);
		}
	}
}
