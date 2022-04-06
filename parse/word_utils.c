/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clmurphy <clmurphy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 15:37:17 by clmurphy          #+#    #+#             */
/*   Updated: 2022/04/06 18:34:05 by clmurphy         ###   ########.fr       */
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

void	print_phrase(t_phrase **phrase)
{
	t_phrase	*temp;

	printf("in print phrase and str is %s\n", (*phrase)->str);
	temp = *phrase;
	while (temp != NULL)
	{
		printf("%s\n", temp->str);
		temp = temp->next;
	}
}
