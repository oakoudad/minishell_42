#include "../minishell.h"

char	*get_path(char *key)
{
	t_list_env	*tmp;

	tmp = g_info.env_lst;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

int ft_pwd(void)
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
	create_list("?", "0");
	if (path[0] == '\0')
	{
		if (chdir(get_path("HOME")) == -1)
		{
			printf("Minishell: cd: HOME not set\n");
			create_list("?", "1");
		}
	}	
	else if (ft_strcmp(path, "-") == 0)
	{
		if (chdir(get_path("OLDPWD")) == -1)
		{
			printf("Minishell: cd: OLDPWD not set\n");
			create_list("?", "1");
		}
		else
			ft_pwd();
	}
	else if (ft_strcmp(path, "~") == 0)
	{
		if (chdir(get_path("HOME")) == -1)
		{
			printf("minishell: %s: No such a file or directory\n", get_path("HOME"));
			create_list("?", "1");
		}
	}
	else
	{
		if (chdir(path) == -1)
		{
			printf("minishell: %s: No such a file or directory\n", path);
			create_list("?", "1");
		}
	}
}
