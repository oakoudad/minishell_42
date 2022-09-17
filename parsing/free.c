/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakoudad <oakoudad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 21:46:49 by oakoudad          #+#    #+#             */
/*   Updated: 2022/09/17 23:06:48 by oakoudad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	myfree(void *p)
{
	if (p)
		free(p);
}

void	free_cmd_line(t_list	*head)
{
	int	i;

	while (head)
	{
		myfree(head->index_token);
		head->index_token = NULL;
		myfree(head->cmd);
		head->cmd = NULL;
		if (head->heredoc_file)
			myfree(head->heredoc_file);
		head->heredoc_file = NULL;
		i = 0;
		while (head->allargs && head->allargs[i])
		{
			free(head->allargs[i]);
			head->allargs[i] = NULL;
			i++;
		}
		myfree(head->allargs);
		myfree(head->args);
		free(head);
		head = head->next;
	}
}
