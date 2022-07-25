/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakoudad <oakoudad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 21:11:56 by oakoudad          #+#    #+#             */
/*   Updated: 2022/07/25 16:08:39 by oakoudad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sighandler(int sig)
{
	if (sig == 2 && g_info.sig)
	{
		rl_on_new_line();
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	config_pwd1()
{
	char cwd[256];
	char *pwd;
	
	getcwd(cwd, sizeof(cwd));
	pwd = ft_strdup(cwd);
	create_list("PWD", pwd);
	create_list("OLDPWD", "");
	create_list("_", "/usr/bin/env");
	create_list("SHLVL", "1");
}


int	main(int ac, char **av, char **env)
{
	char	*buff;
	(void)ac;
	(void)av;
	
	g_info.sig = 1;
	config_pwd1();
	if(split_equal(env, 1) == 0)
		return (0);
	signal(SIGINT, sighandler);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		buff = readline("\033[32;1mMinishell ➜ \033[0m");
		if (buff == NULL)
			return (putstr_fd(1, "exit\n"), 0);
		if (buff[0] == '\0')
			continue ;
		add_history(buff);
		if (check_syntax(buff) == -1)
			return (0);
		free(buff);
	}
	return (0);
}
