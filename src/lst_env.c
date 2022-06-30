#include "../minishell.h"

int	init(char *name, char *value, char *env)
{
	int	y;
	int	x;
	int	status;

	y = 0;
	status = 0;
	x = 0;
	while (env[y] != '\0')
	{
		if (env[y] == '=')
		{
			status = 1;
			y++;
		}
		if (status == 0)
			name[y] = env[y];
		else
			value[x++] = env[y];
		y++;
	}
	return (status);
}

int	len_key(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '=')
		i++;
	return (i);
}

t_list_env	*ft_lstenv(char *key, char *value)
{
	t_list_env	*list;

	list = malloc(sizeof(t_list));
	if (!list)
		return (NULL);
	list->value = value;
	list->key = key;
	list->next = NULL;
	return (list);
}

void	ft_envadd_back(t_list_env **lst, t_list_env *new)
{
	t_list_env	*t;
	
	t = *lst;
	if (!t)
	{
		*lst = new;
		return ;
	}
	while (t->next)
	{
		t = t->next;
	}
	t->next = new;
}

int	create_list(t_list_env **lst, char *name, char *value)
{
	t_list_env	*new;
	t_list_env	*tmp;

	tmp = *lst;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, name) == 0)
		{
			tmp->value = value;
			return (0);
		}
		tmp = tmp->next;
	}
	new = ft_lstenv(name, value);
	if (!new)
		return (0);
	ft_envadd_back(lst, new);
	return (1);
}

void	split_equal(t_list_env **lst, char **env)
{
	int		i;
	char	*name;
	char	*value;

	i = 0;
	while (env[i])
	{
		name = malloc(sizeof(char) * len_key(env[i]));
		value = malloc(sizeof(char) * (strlen(env[i]) - len_key(env[i])));
		init(name, value, env[i]);
		create_list(lst, name, value);
		i++;
	}
}