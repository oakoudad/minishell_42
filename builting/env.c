#include "../minishell.h"

int ft_env(int x)
{
	t_list_env *lst;
	int i;

	lst = g_info.env_lst;
	while (lst && x)
	{
		if (lst->status == 1)
			printf("%s=%s\n", lst->key, lst->value);
		lst = lst->next;
	}
	i = 0;
	while (g_info.names[i] && x == 0)
	{
		if (!(g_info.names[i][0] == '?' && g_info.names[i][1] == '\0'))
			printf(" declare -x %s=", g_info.names[i]);
		lst = g_info.env_lst;
		while (!(g_info.names[i][0] == '?' && g_info.names[i][1] == '\0') && lst)
		{
			if (ft_strcmp(lst->key, g_info.names[i]) == 0)
			{
				printf("%s\n", lst->value);
				break;
			}
			lst = lst->next;
		}
		i++;
	}
	return (0);
}