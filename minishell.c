/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakoudad <oakoudad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 21:11:56 by oakoudad          #+#    #+#             */
/*   Updated: 2022/09/09 22:59:25 by oakoudad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sighandler(int sig)
{
	int	tmp;

	if (sig == 2 && g_info.sig)
	{
		rl_on_new_line();
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_redisplay();
	}
	tmp = g_info.sig;
	if (g_info.heredoc == 1)
		g_info.sig = 1;
	if (sig == 2 && g_info.heredoc == 1 && tmp == 0)
	{
		close(g_info.heredoc_fd);
		g_info.heredoc_fd = open(g_info.heredoc_file,
				O_RDONLY | O_WRONLY | O_TRUNC);
		close(g_info.heredoc_fd);
		exit(0);
	}
}

void	config(char **e)
{
	int		i;
	int		shlvl;
	int		status;
	char	*new_shlvl;

	i = -1;
	status = 1;
	while (e[++i])
	{
		if (e[i][0] == 'S' && e[i][1] == 'H' && e[i][2] == 'L'
			&& e[i][3] == 'V' && e[i][4] == 'L' && e[i][5] == '=')
		{
			status = 0;
			shlvl = ft_atoi(&e[i][6]) + 1;
			new_shlvl = ft_itoa(shlvl);
			e[i] = ft_strjoin(ft_strdup("SHLVL="), new_shlvl);
			free(new_shlvl);
		}
	}
	if (status)
		create_list("SHLVL", "1");
	create_list("PATH", "/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.");
}

int	main(int ac, char **av, char **env)
{
	char	*buff;

	(void)ac;
	(void)av;
	config(env);
	g_info.sig = 1;
	if (split_equal(env, 1) == 0)
		return (0);
	signal(SIGINT, sighandler);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		buff = readline("\033[32;1mMinishell ➜ \033[0m");
		if (buff == NULL)
			return (ft_putstr("exit\n"), 0);
		if (buff[0] == '\0')
			continue ;
		add_history(buff);
		if (check_syntax(buff) == -1)
			return (0);
		free(buff);
	}
	return (0);
}
