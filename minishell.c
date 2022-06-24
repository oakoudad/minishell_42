#include "minishell.h"

void sighandler(int sig)
{
	if (sig == 2){
		rl_on_new_line();
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

int		main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	(void)env;
	char *buff;

	signal(SIGINT, sighandler);
	signal(SIGQUIT, SIG_IGN);
	while(1)
	{
		buff = readline("\033[32;1mMinishell ➜\033[0m ");
		if (buff == NULL)
			return (write(1, "exit", 4), 0);
		if (buff[0] == '\0')
			continue;
		add_history(buff);
		if(check_syntax(buff) == -1)
			return (0);
		free(buff);
	}
	return (0);
}