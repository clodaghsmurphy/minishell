/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clmurphy <clmurphy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 15:05:26 by clmurphy          #+#    #+#             */
/*   Updated: 2022/04/12 18:57:14 by clmurphy         ###   ########.fr       */
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

void	print_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab[i])
		return ;
	while (tab[i] != NULL)
	{
		printf("tab[%d] is %s\n", i, tab[i]);
		i++;
	}
}

void	freetab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		free(tab[i]);
	free(tab);
}

void	print_command(t_mshell *mshell)
{
	t_command	*temp;
	int			i;

	i = 0;
	temp = mshell->command;
	while (temp->next != NULL)
	{
		i++;
		print_tab(temp->value);
		temp = temp->next;
	}
}
