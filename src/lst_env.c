#include "../minishell.h"

int	init(char *name, char *value, char *env)
{
	int	y;
	int	x;
	int	status;

	y = 0;
	status = 0;
	x = 0;
	while (env[y])
	{
		if (env[y] == '=')
		{
			name[y] = 0;
			status = 1;
			y++;
		}
		if (status == 0)
			name[y] = env[y];
		else
			value[x++] = env[y];
		y++;
	}
	value[x] = '\0';
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

void	ft_envadd_back(t_list_env *new)
{
	t_list_env	*t;
	
	t = info.env_lst;
	if (!t)
	{
		info.env_lst = new;
		return ;
	}
	while (t->next)
	{
		t = t->next;
	}
	t->next = new;
}

int	create_list(char *name, char *value, int i)
{
	t_list_env	*new;
	t_list_env	*tmp;

	tmp = info.env_lst;
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
	new->index = i;
	if (!new)
		return (0);
	ft_envadd_back(new);
	return (1);
}

void	sort_list()
{
	int	i;
	t_list_env	*lst;
	char	**names;

	lst = info.env_lst;
	names = malloc(sizeof(char *) * 100);
	i = 0;
	while (lst)
	{
		names[i] = lst->key;
		lst = lst->next;
		i++;
	}
	names[i] = NULL;
	i = 0;
	int j;
	char *tmp;
	while (names[i + 1])
	{
		j = i + 1;
		while (names[j])
		{
			if(strcmp(names[i], names[j]) > 0){
				tmp = names[j];
				names[j] = names[i];
				names[i] = tmp;
			}
			j++;
		}
		i++;
	}
	info.names = names;
}

void	split_equal(char **env)
{
	int			i;
	char		*name;
	char		*value;

	i = 0;
	while (env[i])
	{
		name = malloc(sizeof(char) * len_key(env[i]));
		value = malloc(sizeof(char) * (strlen(env[i]) - len_key(env[i])));
		init(name, value, env[i]);
		create_list(name, value, i);
		i++;
	}
	sort_list();
}