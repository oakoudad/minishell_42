
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
