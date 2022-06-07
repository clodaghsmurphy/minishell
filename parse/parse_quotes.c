/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clmurphy <clmurphy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 16:03:31 by clmurphy          #+#    #+#             */
/*   Updated: 2022/06/04 12:17:41 by clmurphy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

void	parse_quotes(t_split **word, t_mshell *mshell, char *str, int *i)
{
	int		type;

	if_word(word, mshell);
	type = str[*i];
	(*i)++;
	if (empty_quote(type, mshell, str, i) == 1)
		return ;
	if (str[*i] == '$')
		parse_dquote_string(type, mshell, str, i);
	if (quote_delim(type, mshell, str, i) == 1)
		return ;
	while (str[*i] != type && str[*i] != '\0')
	{
		if (type == 34)
		{
			if (dollar_in_quote_string(word, mshell, str, i) == 1)
			{
				parse_dollar_dquotes(type, mshell, str, i);
				continue ;
			}
		}
		split_lstadd_back(word, split_lstnew(str[*i]));
		(*i)++;
	}
	parse_if_word(word, mshell, str, i);
}

int	empty_quote(int type, t_mshell *mshell, char *str, int *i)
{
	if (str[*i] == type)
	{
		if (str[*i + 1] == 32)
			phrase_lstadd_back(&mshell->phrase, phrase_lstnew(ft_strdup("")));
		(*i)++;
		return (1);
	}
	return (0);
}

int	quote_error(t_split **word, t_mshell *mshell, char *str, int *i)
{
	(void)mshell;
	if (str[*i] == '\0')
	{
		printf("quote error\n");
		ft_wordclear(word);
		return (1);
	}
	return (0);
}

int	parse_if_word(t_split **word, t_mshell *mshell, char *str, int *i)
{
	char	*new_word;

	new_word = make_word(word, mshell);
	if (new_word)
	{
		mshell->res = ft_strjoin_f2(mshell->res, new_word);
		free(new_word);
	}
	if (str[*i] == '\0')
		return (0);
	(*i)++;
	if (str[*i] == 32)
	{
		parse_string_bis(word, mshell, str, i);
	}
	return (0);
}

int	dollar_in_quote_string(t_split **word, t_mshell *mshell, char *str, int *i)
{
	char	*new_word;

	if (str[*i] == '$')
	{	
		new_word = make_word(word, mshell);
		if (new_word)
		{
			mshell->res = ft_strjoin_f2(mshell->res, new_word);
			free(new_word);
		}
		return (1);
	}
	return (0);
}
