/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_vars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clmurphy <clmurphy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 17:34:17 by clmurphy          #+#    #+#             */
/*   Updated: 2022/04/21 14:46:10 by clmurphy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void parse_dollar(t_split **word, t_mshell *mshell, char *str, int *i)
{
	int j;

	j = *i;
	while (str[*i] != '\0' && str[*i] != '|' && str[*i] != ' ')
	{
		(*i)++;
	}
	if (str[*i] == '$')
	{
		phrase_lstadd_back(&mshell->phrase, phrase_lstnew(ft_strdup("$")));
		return;
	}
	is_in_env(mshell, ft_strndup(str, (*i - j)));
	return;
}

void parse_dollar_dquotes(t_split **word, t_mshell *mshell, char *str, int *i)
{
	int j;

	j = *i;
	(*i)++;
	while (str[*i] != 34 && str[*i] != '\0')
	{
		(*i)++;
	}
	is_in_env(mshell, ft_strndup(str, (*i - j)));
}

void is_in_env(t_mshell *mshell, char *str)
{
	int i;
	t_env *temp;

	temp = mshell->env;
	i = 0;
	while (temp != NULL)
	{
		if (ft_strncmp(str, temp->name, 100) == 0)
		{
			phrase_lstadd_back(&mshell->phrase, phrase_lstnew(temp->value));
			return;
		}
		temp = temp->next;
	}
	phrase_lstadd_back(&mshell->phrase, phrase_lstnew(str));
<<<<<<< HEAD
	return (0);
=======
	return;
}

char *ft_strndup(const char *s, int size)
{
	int s_len;
