/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clmurphy <clmurphy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 15:37:17 by clmurphy          #+#    #+#             */
/*   Updated: 2022/05/27 19:44:23 by clmurphy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_phrase	*phrase_lstnew(char *str)
{
	t_phrase	*new;

	new = malloc(sizeof(t_phrase));
	if (!new)
		return (NULL);
	new->str = str;
	new->next = NULL;
	return (new);
}

void	phrase_lstadd_back(t_phrase **alst, t_phrase *new)
{
	t_phrase	*current;

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

int	phrase_lstsize(t_phrase *lst)
{
	t_phrase	*current;
	int			i;

	if (lst == NULL)
		return (0);
	current = lst;
	i = 0;
	while (current != NULL && ft_strncmp(current->str, "|", 10) != 0)
	{
		i++;
		current = current->next;
	}
	return (i);
}

void	ft_wordclear(t_split **lst)
{
	t_split	*current;
	t_split	*temp;

	if (*lst == NULL)
		return ;
	current = *lst;
	while (current != NULL)
	{
		temp = current;
		temp->c = 0;
		current = current->next;
		free(temp);
	}
	*lst = NULL;
}

void	free_phrase(t_phrase **phrase)
{
	t_phrase	*current;
	t_phrase	*temp;

	if (*phrase == NULL)
		return ;
	current = *phrase;
	while (current != NULL)
	{
		temp = current;
		current = current->next;
		free(temp);
	}
	*phrase = NULL;
}
