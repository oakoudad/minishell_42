
# include "../minishell.h"

char	*get_env_var(char *key)
{
	t_list_env *lst;

	lst = g_info.env_lst;
	while (lst)
	{
		if (strcmp(lst->key, key) == 0)
		{
			return (lst->value);
		}
		lst = lst->next;
	}
	return (NULL);
}

char	*get_cmd_from_path(char *cmd)
{
	char	*path;
	char	*checkpath;
	char	**vals;
	int		i;

	i = -1;
	path = get_env_var("PATH");
	vals = ft_split(path, ':');
	while (vals[++i]){
		checkpath = ft_strjoin(vals[i], "/");
		checkpath = ft_strjoin(checkpath, cmd);
		if(access(checkpath, X_OK) == 0)
			return (checkpath);
		free(checkpath);
	}
	return (NULL);
}

char **prepare_env()
{
	int i;
	int y;
	int len;
	t_list_env *lst;
	char **newenv;

	lst = g_info.env_lst;
	i = 0;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	newenv = malloc(sizeof(char *) * i + 1);
	if (!newenv)
		return (NULL);
	lst = g_info.env_lst;
	i = 0;
	while (lst)
	{
		y = 0;
		len = ft_strlen(lst->key) + ft_strlen(lst->key) + 2;
		newenv[i] = ft_strjoin("", lst->key);
		newenv[i] = ft_strjoin(newenv[i], "=");
		newenv[i] = ft_strjoin(newenv[i], lst->value);
		i++;
		lst = lst->next;
	}
	newenv[i] = NULL;
	return (newenv);
}

int		exec_cmd(char **args)
{
	char	*cmd;
	char	**env;
	int		status;
	pid_t	pid;
	int 	s;

	if ((args[0][0] == '.' && args[0][1] == '/') || args[0][0] == '/')
		cmd = args[0];
	else
		cmd = get_cmd_from_path(args[0]);
	if (cmd == NULL)
	{
		create_list("?", ft_itoa(127));
		return (printf("bash: %s: command not found\n", args[0]), 0);
	}
	env = prepare_env();
	g_info.sig = 0;
	{
		pid = fork();
		if (pid == 0)
		{
			create_list("?", ft_itoa(0));
			status = execve(cmd, args, env);
			if (status == -1)
			{
				write(1, "minishell: ", 12);
				write(1, cmd, ft_strlen(cmd));
				write(1, ": ", 2);
				perror("");
				if (errno == EPERM)
					exit(126);
				else
					exit(127);
			}
		}
	}
	waitpid(pid, &s, 0);
	g_info.sig = 1;
	create_list("?", ft_itoa(WEXITSTATUS(s)));
	return (0);
}