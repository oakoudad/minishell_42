#include "../minishell.h"

char	*get_path(char *key)
{
	t_list_env	*tmp;

	tmp = info.env_lst;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

int ft_pwd()
{

	char	cwd[1000];

	if (getcwd(cwd, 1000))
	{
		printf("%s\n", cwd);
		return (1);
	}
	else
		return (0);
}

void	ft_cd(char *path)
{
	if (path[0] == '\0')
	{
		if (chdir(get_path("HOME")) == -1)
			printf("no such a file\n");
	}	
	else if (ft_strcmp(path, "-") == 0)
	{
		if (chdir(get_path("OLDPWD")) == -1)
			printf("no such a file\n");
	}
	else if (ft_strcmp(path, "~") == 0)
	{
		if (chdir(get_path("HOME")) == -1)
			printf("no such a file\n");
	}
	else
	{
		if (chdir(path) == -1)
			printf("no such a file\n");
	}
}
