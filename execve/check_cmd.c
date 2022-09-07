
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
	if ((cmd[0] == '.' && cmd[1] == '/') || (cmd[0] == '/'))
		return (cmd);
	path = get_env_var("PATH");
	if (path == NULL)
		return (NULL);
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
		len = ft_strlen(lst->key) + ft_strlen(lst->key) + 2;
		newenv[i] = ft_strdup(lst->key);
		newenv[i] = ft_strjoin(newenv[i], "=");
		newenv[i] = ft_strjoin(newenv[i], lst->value);
		i++;
		lst = lst->next;
	}
	newenv[i] = NULL;
	return (newenv);
}
