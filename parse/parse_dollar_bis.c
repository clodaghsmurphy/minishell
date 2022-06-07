/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_dollar_bis.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clmurphy <clmurphy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 16:46:43 by clmurphy          #+#    #+#             */
/*   Updated: 2022/06/04 12:19:43 by clmurphy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

int	quote_after_dollar(t_split **word, t_mshell *mshell, char *str, int *i)
{
	if (str[*i + 1] == 34 || str[*i + 1] == 39)
	{
		(*i)++;
		parse_quotes(word, mshell, str, i);
		return (1);
	}
	return (0);
}

int	define_quote_type(char	*str, int *i)
{
	int	type;

	type = 0;
	if (*i > 0)
	{
		if (str[*i - 1] == 34 || str[*i - 1] == 39)
			type = str[*i - 1];
	}
	return (type);
}

int	dollar_only(t_split **word, t_mshell *mshell, char *str, int *i)
{
	char	*new_word;

	(void)word;
	if ((str[*i] == '$' && is_delim_dollar(str, (*i) + 1) == 0))
	{
		new_word = ft_strdup("$");
		mshell->res = ft_strjoin_f2(mshell->res, new_word);
		free(new_word);
		(*i)++;
		return (1);
	}
	if (str[*i] == '$' && str[*i + 1] == '?')
	{
		new_word = ft_itoa(g_estatus);
		mshell->res = ft_strjoin_f2(mshell->res, new_word);
		*i += 2;
		free(new_word);
		return (1);
	}
	return (0);
}

int	parse_dollar_string(int *j, t_mshell *mshell, char *str, int *i)
{
	int	type;

	type = define_quote_type(str, i);
	mshell->j = *j;
	while (is_delim_dollar(str, *i))
	{
		(*i)++;
		if (not_quotes(type, str, i) == 1)
			break ;
		if (quotes_in_dstring(&type, mshell, str, i) == -1)
			return (-1);
		if (eq_in_dollar(&type, mshell, str, i) == 1)
			continue ;
		if (another_dollar(j, mshell, str, i) == 2)
			return (1);
	}
	if (str[*i] == 34 || str[*i] == 39)
		return (2);
	return (0);
}

int	not_quotes(int type, char *str, int *i)
{
	int	q_delim;

	if (type == 34)
		q_delim = 39;
	else if (type == 39)
		q_delim = 34;
	else
		q_delim = -1;
	if (str[*i] == type)
		return (1);
	if (q_delim != -1)
	{
		if (str[*i] == q_delim)
			return (1);
	}
	else if (q_delim == -1)
	{
		if (str[*i] == 34)
			return (1);
		if (str[*i] == 39)
			return (1);
	}
	return (0);
}
