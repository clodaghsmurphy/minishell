/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clmurphy <clmurphy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 15:05:26 by clmurphy          #+#    #+#             */
/*   Updated: 2022/04/12 12:02:17 by clmurphy         ###   ########.fr       */
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

int	count_delim(t_phrase **phrase)
{
	t_phrase	*temp;
	int 		count;
	
	count = 0;
	temp = *phrase;
	while (temp != NULL)
	{
		if (ft_strncmp(temp->str, "|", 10) == 0)
			count++;
		temp = temp->next;
	}
	return (count);
}

void	print_tab(char **tab, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		printf("in loop\n");
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

void	print_command(t_command **command, int size)
{
	t_command	*temp;

	temp = *command;
	while (temp != NULL)
	{
		print_tab(temp->value, size);
		temp = temp->next;
	}
}
