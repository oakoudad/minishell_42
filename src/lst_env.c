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
	
	t = g_info.env_lst;
	if (!t)
	{
		g_info.env_lst = new;
		return ;
	}
	while (t->next)
	{
		t = t->next;
	}
	t->next = new;
}

int		create_list(char *name, char *value)
{
	t_list_env	*new;
	t_list_env	*tmp;

	tmp = g_info.env_lst;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, name) == 0)
		{
			tmp->value = value;
			return (1);
		}
		tmp = tmp->next;
	}
	new = ft_lstenv(name, value);
	if (!new)
		return (0);
	if (name[0] == '?' && name[1] == '\0')
		new->status = 0;
	else
		new->status = 1;
	if (!new)
		return (0);
	ft_envadd_back(new);
	return (1);
}

int	sort_list(void)
{
	int	i;
	t_list_env	*lst;
	char	**names;

	lst = g_info.env_lst;
	names = malloc(sizeof(char *) * 100);
	if (!names)
		return (0);
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
	g_info.names = names;
	return (1);
}

int	split_equal(char **env, int type)
{
	int			i;
	char		*name;
	char		*value;

	i = 0;
	while (env[i])
	{
		name = malloc(sizeof(char) * len_key(env[i]));
		if (!name)
			return (0);
		value = malloc(sizeof(char) * (strlen(env[i]) - len_key(env[i])));
		if (!value)
			return (0);
		init(name, value, env[i]);
		if (create_list(name, value) == 0)
			return (0);
		i++;
	}
	if (type == 1)
		name = ft_strdup("?");
	if (type == 1 && !name)
		return (0);
	if (type == 1)
		value = ft_strdup("0");
	if (type == 1 && !value)
		return (0);
	if (type == 1 && create_list(name, value) == 0)
	{
		while(1);
		return (0);
	}
	if (sort_list() == 0)
		return (0);
	return (1);
}