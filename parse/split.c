/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clmurphy <clmurphy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 17:22:21 by clmurphy          #+#    #+#             */
/*   Updated: 2022/04/06 19:08:26 by clmurphy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	split_command(char *str, t_mshell *mshell)
{
	t_split		*word;
	int			i;
	int			quote;
	int			type;

	word = NULL;
	mshell->phrase = NULL;
	quote = 0;
	i = 0;
	while (str[i] != '\0')
	{
		while (str[i] != 32 && str[i] != '|' && str[i] != '\0')
		{
			if (str[i] == 44 || str[i] == 34)
			{
				quote = 1;
				type = str[i];
				i++;
				while (str[i] != type && str[i] != '\0')
				{
					split_lstadd_back(&word, split_lstnew(str[i]));
					i++;
				}
				print_split(&word);
				if (str[i] == '\0')
					printf("quote error\n");
				else
				{
					make_word(&word, mshell);
					i++;
					quote = 0;
				}
			}
			split_lstadd_back(&word, split_lstnew(str[i]));
			i++;
		}
		if (str[i] != 32 && str[i] != '|' && str[i] != '\0')
		{
			while (str[i] != 32)
			{
				if (str[i] == '|')
					break ;
				i++;
			}
			if (str[i] == '|')
				break ;
		}
		if (str[i] == '|')
		{
			if (str[i + 1] == '|')
			{
				printf("syntax error\n");
				return ;
			}
			else
			{
				i++;
				continue ;
			}
		}
		printf("str[i] is %d\n", str[i]);
		make_word(&word, mshell);
		i++;
	}
	print_phrase(&mshell->phrase);
}

void	make_word(t_split **word, t_mshell *mshell)
{
	int		size;
	t_split	*temp;
	int		i;
	char	*str;

	i = 0;
	temp = *word;
	size = split_lstsize(*word) + 1;
	str = malloc(sizeof(char) * size);
	while (temp != NULL)
	{
		str[i] = temp->c;
		i++;
		temp = temp->next;
	}
	str[i] = '\0';
	phrase_lstadd_back(&mshell->phrase, phrase_lstnew(str));
	if (*word)
	{
		ft_wordclear(word);
		*word = NULL;
	}
}
