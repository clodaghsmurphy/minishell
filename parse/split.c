/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clmurphy <clmurphy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 17:22:21 by clmurphy          #+#    #+#             */
/*   Updated: 2022/04/07 18:05:19 by clmurphy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	split_command(char *str, t_mshell *mshell)
{
	t_split		*word;
	int			i;

	word = NULL;
	mshell->phrase = NULL;
	i = 0;
	while (str[i] != '\0')
	{
		parse_delimiter(str, &i);
		parse_string(&word, mshell, str, &i);
		parse_delimiter(str, &i);
		print_split(&word);
		make_word(&word, mshell);
		//i++;
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
	if (!word)
		return ;
	temp = *word;
	size = split_lstsize(*word) + 1;
	str = malloc(sizeof(char) * size);
	while (temp != NULL)
	{
		str[i] = temp->c;
		printf("temp->c is %d\n", temp->c);
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

void	parse_quotes(t_split **word, t_mshell *mshell, char *str, int *i)
{
	int	type;

	if (str[*i] == 44 || str[*i] == 34)
	{
		type = str[*i];
		(*i)++;
		while (str[*i] != type && str[*i] != '\0')
		{
			split_lstadd_back(word, split_lstnew(str[*i]));
			(*i)++;
		}
		printf("word after quote\n");
		print_split(word);
		if (str[*i] == '\0')
		{
			printf("quote error\n");
			return ;
		}
		else
		{
			make_word(word, mshell);
			(*i)++;
		}
		if (str[*i] == 32)
		{
			printf("str[i] in quote is %c\n", str[*i - 1]);
			while (str[*i] == 32)
			(*i)++;
		}
	}
}

void	parse_string(t_split **word, t_mshell *mshell, char *str, int *i)
{
	while (str[*i] != 32 && str[*i] != '|' && str[*i] != '\0')
	{
		if (str[*i] == 44 || str[*i] == 34)
		{
			parse_quotes(word, mshell, str, i);
			printf("in parse quote\n");
			return ;
		}
		printf("after quote if and str[*i] is %c\n", str[*i]);
		split_lstadd_back(word, split_lstnew(str[*i]));
		(*i)++;
	}
}

void	parse_delimiter(char *str, int *i)
{
	if (str[*i] == '\0')
		return ;
	if (str[*i] == 32)
	{
		while (str[*i] == 32)
			(*i)++;
	}
	if (str[*i] == '|')
	{
		if (str[(*i) + 1] == '|')
		{
			printf("syntax error\n");
			return ;
		}
		(*i)++;
		if (str[*i] == 32)
		{
			while (str[*i] == 32)
			(*i)++;
		}
	}
}
