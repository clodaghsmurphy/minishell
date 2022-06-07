/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_string_bis.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clmurphy <clmurphy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 17:26:28 by clmurphy          #+#    #+#             */
/*   Updated: 2022/06/04 14:00:21 by clmurphy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

void	new_word_afte_pipe(t_split **delimiter, t_mshell *mshell)
{
	char	*new_word;

	new_word = make_word(delimiter, mshell);
	if (new_word)
	{
		phrase_lstadd_back(&mshell->phrase, \
		phrase_lstnew(ft_strdup(new_word)));
		free(new_word);
	}	
}

int	is_redir(char *str, int *i, t_mshell *mshell)
{
	if (ft_strncmp(str + *i, ">>", 2) == 0)
	{
		mshell->hdoc_flag = 0;
		if (str[*i + 2] == '<')
			syntax_error(mshell);
		if (str[*i + 2] == '>')
			syntax_error(mshell);
		return (2);
	}
	if (ft_strncmp(str + *i, "<<", 2) == 0)
	{
		if (str[*i + 2] == '>')
			syntax_error(mshell);
		if (str[*i + 2] == '<')
			syntax_error(mshell);
		mshell->hdoc_flag = 1;
		return (2);
	}
	if (is_redir2(str, i, mshell) == 1)
		return (1);
	return (0);
}

int	is_redir2(char *str, int *i, t_mshell *mshell)
{
	if (str[*i] == '>')
	{	
		if (str[*i + 1] == '<')
			syntax_error(mshell);
		return (1);
	}
	if (str[*i] == '<')
	{	
		if (str[*i + 1] == '>')
			syntax_error(mshell);
		return (1);
	}
	return (0);
}

int	check_redirs(t_mshell *mshell, char *str, int *i)
{
	if (str[*i] == '>')
	{	
		if (str[*i + 1] == '<')
			syntax_error(mshell);
		mshell->hdoc_flag = 0;
		return (0);
	}
	if (ft_strncmp(str + *i, ">>", 2) == 0)
	{
		if (str[*i + 2] == '>')
			syntax_error(mshell);
		if (str[*i + 2] == '<')
			syntax_error(mshell);
		mshell->hdoc_flag = 0;
		return (0);
	}
	if (check_redirs2(mshell, str, i) == 1)
		return (0);
	return (1);
}

int	check_redirs2(t_mshell *mshell, char *str, int *i)
{
	if (ft_strncmp(str + *i, "<<", 2) == 0)
	{
		if (str[*i + 2] == '>')
			syntax_error(mshell);
		if (str[*i + 2] == '<')
			syntax_error(mshell);
		mshell->hdoc_flag = 1;
		return (1);
	}
	return (0);
}
