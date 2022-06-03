/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_delim.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clmurphy <clmurphy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 14:40:16 by clmurphy          #+#    #+#             */
/*   Updated: 2022/06/03 15:07:45 by clmurphy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	quote_delim(int type, t_mshell *mshell, char *str, int *i)
{
	if (str[*i] == '|' && (str[*i + 1] == type || str[*i +1] == '\0' \
	|| str[*i + 1] == 32))
	{
		phrase_lstadd_back(&mshell->phrase, phrase_lstnew(ft_strdup("\"|\"")));
		if (str[*i + 1] == '\0')
			(*i)++;
		else
			*i += 2;
		return (1);
	}
	if (str[*i] == '<' && (str[*i + 1] == type || str[*i + 1] == '\0' \
	|| str[*i + 1] == 32))
	{
		phrase_lstadd_back(&mshell->phrase, phrase_lstnew(ft_strdup("\"<\"")));
		if (str[*i + 1] == '\0')
			(*i)++;
		else
			*i += 2;
		return (1);
	}
	if (quote_delim2(type, mshell, str, i) == 1)
		return (1);
	return (0);
}

int	quote_delim2(int type, t_mshell *mshell, char *str, int *i)
{
	if (str[*i] == '>' && (str[*i + 1] == type || str[*i + 1] == '\0' \
	|| str[*i + 1] == 32))
	{
		phrase_lstadd_back(&mshell->phrase, phrase_lstnew(ft_strdup("\">\"")));
		if (str[*i + 1] == '\0')
			(*i)++;
		else
			*i += 2;
		return (1);
	}
	if (str[*i + 1] != '\0')
	{
		if (quote_delim3(type, mshell, str, i) == 1)
			return (1);
	}
	return (0);
}

int	quote_delim3(int type, t_mshell *mshell, char *str, int *i)
{
	if (str[*i] == '>' && str[*i + 1] == '>')
	{
		(*i)++;
		phrase_lstadd_back(&mshell->phrase, phrase_lstnew(ft_strdup("\">>\"")));
		if (str[*i + 1] == '\0')
			(*i)++;
		else
			*i += 2;
		return (1);
	}
	if (str[*i] == '<' && str[*i + 1] == '<')
	{
		(*i)++;
		phrase_lstadd_back(&mshell->phrase, phrase_lstnew(ft_strdup("\"<<\"")));
		if (str[*i + 1] == '\0')
			(*i)++;
		else
			*i += 2;
		return (1);
	}
	return (0);
}

void	if_word(t_split **word, t_mshell *mshell, char *str, int *i)
{
	char	*new_word;

	if (*word)
	{
		new_word = make_word(word, mshell);
		if (new_word)
			mshell->res = ft_strjoin_f2(mshell->res, new_word);
		free(new_word);
	}
}