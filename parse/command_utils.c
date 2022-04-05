/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clmurphy <clmurphy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 15:05:26 by clmurphy          #+#    #+#             */
/*   Updated: 2022/04/05 15:49:44 by clmurphy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*command_lstnew(char **commands)
{
	t_command	*new;

	new = malloc(sizeof(t_command));
	if (!new)
		return (NULL);
	new->value = commands;
	new->next = NULL;
	return (new);
}

void	command_lstadd_back(t_command **alst, t_command *new)
{
	t_command	*current;

	if (!alst || *alst == NULL)
	{
		*alst = new;
		return ;
	}
	current = *alst;
	if (!new)
		return ;
	while (current->next != NULL)
	{
		current = current->next;
	}
	current->next = new;
}
