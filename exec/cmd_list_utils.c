/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amontant <amontant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 14:42:02 by amontant          #+#    #+#             */
/*   Updated: 2022/04/18 14:49:57 by amontant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmd_list_size(t_command *lst)
{
	t_command	*current;
	int			count;

	current = lst;
	count = 0;
	while (current)
	{
		current = current->next;
		count += 1;
	}
	return (count);
}

int	cmd_lst_pos(t_command *lst, t_command *current)
{
	int			count;
	t_command	*temp;

	count = 1;
	temp = lst;
	while (temp && (temp != current))
	{
		temp = temp->next;
		count += 1;
	}
	if (temp == current)
		return (count);
	return (0);
}
