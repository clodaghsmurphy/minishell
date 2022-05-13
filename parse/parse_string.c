/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clmurphy <clmurphy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 17:22:21 by clmurphy          #+#    #+#             */
/*   Updated: 2022/05/13 10:51:56 by clmurphy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_string(t_split **word, t_mshell *mshell, char *str, int *i)
{
	while (is_delim(str, i) == 1)
	{
		if (str[*i] == 34 || str[*i] == 39)
		{
			parse_quotes(word, mshell, str, i);
			continue ;
		}
		if (str[*i] == '$')
		{
			parse_dollar(word, mshell, str, i);
			continue ;
		}
		split_lstadd_back(word, split_lstnew(str[*i]));
		(*i)++;
	}
	if (*word)
		mshell->res = ft_strjoin(mshell->res, make_word(word, mshell));
	if (mshell->res)
		phrase_lstadd_back(&mshell->phrase, \
		phrase_lstnew(ft_strdup(mshell->res)));
	free(mshell->res);
	mshell->res = NULL;
	return (1);
}

int	is_delim(char *str, int *i)
{
	if (str[*i] == 32)
		return (0);
	if (str[*i] == '|')
		return (0);
	if (str[*i] == '\0')
		return (0);
	if (str[*i] == '>')
		return (0);
	if (str[*i] == '>')
		return (0);
	if (ft_strncmp(str + *i, ">>", 2) == 0)
		return (0);
	if (ft_strncmp(str + *i, "<<", 2) == 0)
		return (0);
	return (1);
}

void	parse_delimiter(t_split **word, t_mshell *mshell, char *str, int *i)
{
	t_split	*delimiter;
	int		flag;

	flag = 0;
	delimiter = NULL;
	if (str[*i] == '\0')
	{
		make_word(word, mshell);
		return ;
	}
	if (str[*i] == 32)
	{
		while (str[*i] == 32)
			(*i)++;
	}
	flag = is_pipe(&delimiter, mshell, str, i);
	if (flag == -1)
		return ;
	else if (is_redir(str, i) == 1 || is_redir(str, i) == 2)
		flag = parse_redir(&delimiter, mshell, str, i);
	make_word(word, mshell);
	if (flag == 1)
		make_word(&delimiter, mshell);
}

int	is_redir(char *str, int *i)
{
	if (ft_strncmp(str + *i, ">>", 2) == 0)
		return (2);
	if (ft_strncmp(str + *i, "<<", 2) == 0)
		return (2);
	if (str[*i] == '>')
		return (1);
	if (str[*i] == '<')
		return (1);
	return (0);
}
