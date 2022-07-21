#include "../minishell.h"

void routes()
{
	t_list *head;

	head = g_info.cmds;
	while (head)
	{
		if (ft_strcmp(head->cmd, "echo") == 0)
			ft_echo(++(head->args), head->fd);
		else if (ft_strcmp(head->cmd, "export") == 0)
			ft_export(++(head->args));
		else if (ft_strcmp(head->cmd, "env") == 0)
			ft_env(1);
		else if (ft_strcmp(head->cmd, "cd") == 0)
		{
			if (head->args && head->args[0] && head->args[1])
				ft_cd(head->args[1]);
			else
				ft_cd("");
		}
		else if (ft_strcmp(head->cmd, "unset") == 0)
			ft_unset(++(head->args));
		else if (ft_strcmp(head->cmd, "pwd") == 0)
			ft_pwd();
		else if (ft_strcmp(head->cmd, "exit") == 0)
			ft_exit(++(head->args));
		else
			exec_cmd(head->args);
		head = head->next;
	}
}