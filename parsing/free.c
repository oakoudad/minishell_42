/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakoudad <oakoudad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 21:46:49 by oakoudad          #+#    #+#             */
/*   Updated: 2022/09/11 22:48:11 by oakoudad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../minishell.h"

void	free_cmd_line(t_list	*head)
{
	int i;

	while (head)
	{
		free(head->index_token);
		free(head->cmd);
		i = 0;
		if (head->heredoc_file != NULL)
			free(head->heredoc_file);
		while (head->allargs && head->allargs[i])
		{
			free(head->allargs[i]);
			head->allargs[i] = NULL;
			i++;
		}
		if (head->allargs != NULL)
		{
			free(head->allargs);
			head->allargs = NULL;
		}
		if (head->args != NULL)
			free(head->args);
		free(head);
		head = head->next;
	}
}