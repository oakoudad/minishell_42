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

void	fileopen(t_list	**l, char *file, char *token)
{
	if ((*l)->out_fd == -5)
	{
		if (ft_strcmp(token, ">") == 0)
			(*l)->out_fd = open(file, O_CREAT | O_RDWR, 0666);
		else if(ft_strcmp(token, ">>") == 0)
		{
			(*l)->out_fd = open(file, O_RDWR | O_APPEND);
			if ((*l)->out_fd == -1)
				(*l)->out_fd = open(file, O_CREAT | O_RDWR);
		}
	}
	else
	{
		close((*l)->out_fd);
		if (ft_strcmp(token, ">") == 0)
			(*l)->out_fd = open(file, O_CREAT | O_RDWR, 0666);
		else if(ft_strcmp(token, ">>") == 0)
		{
			(*l)->out_fd = open(file, O_RDWR | O_APPEND);
			if ((*l)->out_fd == -1)
				(*l)->out_fd = open(file, O_CREAT | O_RDWR);
		}
	}
		printf("im here! 1\n");
	if ((*l)->in_fd == -5)
	{
		if (ft_strcmp(token, "<") == 0)
		{
			printf("im here!\n");
			(*l)->in_fd = open(file, O_RDONLY);
			if ((*l)->in_fd == -1)
				printf("minishell: %s: No such file or directory\n", file);
		}
	}
	else
	{
		
	}
}
