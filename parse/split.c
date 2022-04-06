/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clmurphy <clmurphy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 17:22:21 by clmurphy          #+#    #+#             */
/*   Updated: 2022/04/06 12:04:49 by clmurphy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**split_command(char *str, t_mshell *mshell)
{
	t_split		*word;
	t_phrase	*phrase;
	int			i;
	int			quote;
	int			type;

	word = NULL;
	phrase = NULL;
	quote = 0;
	i = 0;
	while (str[i] != '\0')
	{
		while (str[i] != 32 && str[i] != '|')
		{
			if (str[i] == 44 || str[i] == 34)
			{
				quote == 1;
				type = str[i];
				while (str[i] != type && str[i] != '\0')
				{
					split_lstadd_back(&word, split_lstnew(str[i]));
					i++;
				}
				if (str[i] == '\0')
					printf("quote error\n");
				else
				{
					make_word(word, phrase);
					i++;
					quote = 0;
				}
			}
			split_lstadd_back(&word, split_lstnew(str[i]));
			i++;
		}
		make_word(word, phrase);
		i++;
	}
}

void	make_word(t_split *word, t_phrase *phrase)
{
	int		size;
	t_split	*temp;
	int		i;

	i = 0;
	temp = word;
	size = split_lstsize(word) + 1;
	phrase->str = malloc(sizeof(char) * size);
	while (temp ->next != NULL)
	{
		phrase->str[i] = temp->c;
		i++;
	}
}

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
		current = current->next;
		free(temp);
	}
	*lst = NULL;
}
