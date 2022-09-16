/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oakoudad <oakoudad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 04:01:44 by oakoudad          #+#    #+#             */
/*   Updated: 2022/09/16 04:02:35 by oakoudad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	export_error(char *str)
{
	write(2, "minishell: export: `", 21);
	write(2, str, ft_strlen(str));
	write(2, "': not a valid identifier\n", 27);
	create_list("?", "1");
	return (0);
}
