/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clmurphy <clmurphy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 15:36:25 by clmurphy          #+#    #+#             */
/*   Updated: 2022/04/07 17:35:04 by clmurphy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_split	*split_lstnew(char c)
{
	t_split	*new;

	new = malloc(sizeof(t_split));
	if (!new)
		return (NULL);
	new->c = c;
	new->next = NULL;
	return (new);
}

void	split_lstadd_back(t_split **alst, t_split *new)
{
	t_split	*current;

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

int	split_lstsize(t_split *lst)
{
	t_split	*current;
	int		i;

	current = lst;
	i = 0;
	while (current != NULL)
	{
		i++;
		current = current->next;
	}
	return (i);
}

void	print_split(t_split **split)
{
	t_split	*temp;

	temp = *split;
	while (temp != NULL)
	{
		printf("%c\n", temp->c);
		temp = temp->next;
	}
}
