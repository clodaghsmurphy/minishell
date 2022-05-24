/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shiloub <shiloub@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 15:05:26 by clmurphy          #+#    #+#             */
/*   Updated: 2022/05/24 16:35:27 by shiloub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*command_lstnew(char **commands)
{
	t_command	*new;

	new = ft_calloc(sizeof(t_command), 1);
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

void	print_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab[i])
		return ;
	while (tab[i] != NULL)
	{
		printf("tab[%d] is [%s]\n", i, tab[i]);
		i++;
	}
}

void	print_command(t_command *command)
{
	t_command	*temp;
	int			i;

	i = 0;
	temp = command;
	while (temp != NULL)
	{
		i++;
		printf("<--------CHAR ** DANS COMMAND NO %d ----------->\n", i);
		print_tab(temp->value);
		temp = temp->next;
	}
}

int	command_size(t_command*command)
{
	t_command	*temp;
	int			i;

	i = 0;
	temp = command;
	while (temp != NULL)
	{
		temp = temp->next;
		i++;
	}
	return (i);
}
