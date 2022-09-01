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

void	copyto(char *s, char *cmd, int *d, int w)
{
	int		i;
	int		j;
	char	c;

	j = 0;
	i = *d;
	c = *(s - 1);
	while (s[j] != c)
	{
		if (c == '"' && w && s[j] == '$' && s[j + 1] != '"'
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

int already(char *s, int to)
{
	int i;

	i = 0;
	if (s[0])
	while (is_space(s[i]))
		i++;
	if (i < to && s[i] != '>' && s[i] != '<')
		return (i);
	return (0);
}

int	end_of_cmd(char *s)
{
	int	end;

	end = 0;
	while (s[end])
	{
		if (s[end] == '"' || s[end] == '\'')
			skep_quotes(s, &end);
		if ((s[end] == '>' || s[end] == '<') && end == 0)
		{
			while (s[end] == '>' || s[end] == '<')
				end++;
			return (end - 1);
		}
		if (is_space(s[end]) || s[end] == '>' || s[end] == '<')
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
	
	if (ft_strcmp(token, "<") == 0)
	{
		if ((*l)->in_fd != -5)
			close((*l)->in_fd);
		(*l)->in_fd = open(file, O_RDONLY);
		if ((*l)->in_fd == -1)
			printf("minishell: %s: No such file or directory\n", file);
	}
	if (ft_strcmp(token, "<<") == 0)
	{
		if ((*l)->in_fd != -5)
		{
			close((*l)->in_fd);
			if ((*l)->heredog_file != NULL)
				free((*l)->heredog_file);
			(*l)->heredog_file = NULL;
		}
		(*l)->heredog_file = generate_name();
		pid_t pid;
		g_info.sig = 0;
		g_info.heredog = 0;
		{
			pid = fork();
			if (pid == 0)
			{
				(*l)->in_fd = open((*l)->heredog_file, O_CREAT | O_RDWR, 0666);
				g_info.heredog = 1;
				while (1)
				{
					char *buff = readline("> ");
					if (buff == NULL)
						break ;
					if (ft_strcmp(buff, file) == 0)
						break ;
					int i = 0;
					while(buff[i])
					{
						if (buff[i] != '$')
							write((*l)->in_fd, &buff[i], 1);
						else
							get_var(&buff[i], &i, (*l)->in_fd);
						i++;
					}
					if (buff[i] == '\0')
						write((*l)->in_fd, "\n", 1);
					free(buff);
				}
				close((*l)->in_fd);
				exit(0);
			}
		}
		waitpid(pid, NULL, 0);
		g_info.heredog = 0;
		g_info.sig = 1;
		(*l)->in_fd = open((*l)->heredog_file, O_RDONLY, 0666);
		unlink((*l)->heredog_file);
	}
}
