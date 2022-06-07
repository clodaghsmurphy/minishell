/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clmurphy <clmurphy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 17:22:21 by clmurphy          #+#    #+#             */
/*   Updated: 2022/06/04 12:14:15 by clmurphy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_string(t_split **word, t_mshell *mshell, char *str, int *i)
{
	while (is_delim(mshell, str, i) == 1)
	{
		if (str[*i] == 34 || str[*i] == 39)
		{
			parse_quotes(word, mshell, str, i);
			continue ;
		}
		if (str[*i] == '$' && mshell->hdoc_flag != 1)
		{
			parse_dollar(word, mshell, str, i);
			continue ;
		}
		split_lstadd_back(word, split_lstnew(str[*i]));
		(*i)++;
	}
	parse_string_bis(word, mshell, str, i);
	return (1);
}

void	parse_string_bis(t_split **word, t_mshell *mshell, char *str, int *i)
{
	char	*new_word;

	while (str[*i] == 32)
		(*i)++;
	new_word = make_word(word, mshell);
	if (new_word)
	{
		mshell->res = ft_strjoin_f2(mshell->res, new_word);
		free(new_word);
	}
	if (mshell->res)
		phrase_lstadd_back(&mshell->phrase, \
		phrase_lstnew(ft_strdup(mshell->res)));
	free(mshell->res);
	mshell->res = NULL;
}

int	is_delim(t_mshell *mshell, char *str, int *i)
{
	if (str[*i] == 32)
	{
		mshell->hdoc_flag = 0;
		return (0);
	}
	if (str[*i] == '|')
	{
		mshell->hdoc_flag = 0;
		return (0);
	}
	if (str[*i] == '\0')
	{
		mshell->hdoc_flag = 0;
		return (0);
	}
	if (str[*i] == '<')
	{	
		if (str[*i + 1] == '>')
			syntax_error(mshell);
		mshell->hdoc_flag = 0;
		return (0);
	}
	if (check_redirs(mshell, str, i) == 0)
		return (0);
	return (1);
}

void	parse_delimiter(t_mshell *mshell, char *str, int *i)
{
	t_split	*delimiter;
	int		flag;

	flag = 0;
	delimiter = NULL;
	if (str[*i] == 32)
	{
		while (str[*i] == 32)
			(*i)++;
	}
	flag = is_pipe(&delimiter, mshell, str, i);
	if (flag == -1)
		return ;
	else if (is_redir(str, i, mshell) == 1 || is_redir(str, i, mshell) == 2)
		flag = parse_redir(&delimiter, mshell, str, i);
	if (flag == 1)
		new_word_afte_pipe(&delimiter, mshell);
}
