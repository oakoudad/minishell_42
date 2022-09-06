#include "../minishell.h"

void saveio(int fd[])
{
	fd[0] = dup(STDIN_FILENO);
	fd[1] = dup(STDOUT_FILENO);
}

void restoreio(int fd[])
{
	dup2(fd[0], 0);
	dup2(fd[1], 1);
	close(fd[0]);
	close(fd[1]);
}

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
	{	
		write (fd, "-2147483648", 11);
		return ;
	}
	else if (n < 0)
	{
		ft_putchar_fd('-', fd);
		n *= -1;
	}
	if (n >= 0 && n < 10)
		ft_putchar_fd(n + '0', fd);
	else
	{
		ft_putnbr_fd(n / 10, fd);
		ft_putchar_fd((n % 10) + '0', fd);
	}
}

void exec_pipe(int intfd, t_list *lst)
{
	t_list *head;
	int fd[2];
	int io_fd[2];
	char *cmd;
	char	**env;

	head = lst;
	if(head == NULL)
		return;
	saveio(io_fd);
	if(lst->next)
		pipe(fd);
	if (!routes(head))
		cmd = get_cmd_from_path(head->cmd);
	if (!routes(head) && cmd == NULL){
		write(2, "minishell: ", 12);
		write(2, head->cmd, ft_strlen(head->cmd));
		write(2, ": command not found\n", 21);
		close(fd[1]);
		if (lst->next)
			exec_pipe(fd[0], lst->next);
		return;
	}
	env = prepare_env();
	pid_t pid = 0;
	if (routes(head))
		g_info.sig = 1;
	else
	{
		g_info.sig = 0;
		pid = fork();
	}
	if(pid == 0)
	{
		if(intfd != -1)
		{
			write(1, "\n00\n", 4);
			dup2(intfd, 0);
			close(intfd);
		}
		if (head->in_fd > 0)
		{
			write(1, "\n01\n", 4);
			dup2(head->in_fd, 0);
			close(head->in_fd);
		}
		if (head->out_fd > 0)
		{
			write(1, "\n02\n", 4);
			dup2(head->out_fd, 1);
			close(head->out_fd);
		}
		else if(lst->next)
		{
			write(1, "\n03\n", 4);
			dup2(fd[1], 1);
			close(fd[1]);
		}
		if(routes(head) == 0)
			execve(cmd, lst->args, env);
		else
		{
			exc_builtins(head);
			restoreio(io_fd);
		}
	}
	if (!lst->next)	
	{
		close(intfd);
		close(fd[1]);
		close(fd[0]);
		waitpid(pid, NULL, 0);
		g_info.sig = 1;
		return;
	}
	close(fd[1]);
	//g_info.sig = 1;
	exec_pipe(fd[0], lst->next);
}