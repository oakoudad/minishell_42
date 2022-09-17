/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakoudad <oakoudad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 21:11:56 by oakoudad          #+#    #+#             */
/*   Updated: 2022/09/17 01:30:11 by oakoudad         ###   ########.fr       */
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
		write(1, "\n", 1);
		close(g_info.heredoc_fd);
		g_info.heredoc_fd = open(g_info.heredoc_file,
				O_RDONLY | O_WRONLY | O_TRUNC);
		close(g_info.heredoc_fd);
		exit(1);
	}
}

void	config(char **e, int ac, char **av)
{
	int		i;
	int		shlvl;
	char	*new_shlvl;

	(void)ac;
	(void)av;
	i = -1;
	g_info.env_lst = NULL;
	g_info.sig = 1;
	while (e[++i])
	{
		if (var_cmp("SHLVL", e[i]))
		{
			shlvl = ft_atoi(&e[i][6]) + 1;
			if (shlvl < 0)
				shlvl = 0;
			new_shlvl = ft_itoa(shlvl);
			e[i] = ft_strjoin(ft_strdup("SHLVL="), new_shlvl);
			free(new_shlvl);
		}
	}
	if (!search_var("SHLVL", e))
		create_list("SHLVL", "1");
	if (!search_var("PATH", e))
		create_list("PATH", "/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.");
}

int	main(int ac, char **av, char **env)
{
	char		*buff;

	config(env, ac, av);
	if (split_equal(env, 1) == 0)
		return (0);
	signal(SIGINT, sighandler);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		rl_catch_signals = 0;
		buff = readline("\033[32;1mMinishell ➜ \033[0m");
		if (buff == NULL)
			return (ft_putstr_fd(1, "exit\n"), 0);
		if (buff[0] == EOF)
		{
			free(buff);
			continue ;
		}
		add_history(buff);
		if (check_syntax(buff) == -1)
			return (0);
		free(buff);
		buff = NULL;
	}
}
