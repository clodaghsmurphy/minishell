/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_delim_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clmurphy <clmurphy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 16:24:32 by clmurphy          #+#    #+#             */
/*   Updated: 2022/05/30 17:07:52 by clmurphy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

int	is_pipe(t_split **delimiter, t_mshell *mshell, char *str, int *i)
{
	if (str[*i] == '|')
	{
		if (str[(*i) + 1] == '|')
		{
			syntax_error(mshell);
			(*i) += 2;
			return (-1);
		}
		if (str[(*i) + 1] == '\0')
		{
			syntax_error(mshell);
			(*i) += 1;
			return (-1);
		}
		split_lstadd_back(delimiter, split_lstnew(str[*i]));
		(*i)++;
		if (str[*i] == 32)
		{
			while (str[*i] == 32)
				(*i)++;
			if (end_of_string(delimiter, mshell, str, i) == -1)
				return (-1);
		}
	}
	return (1);
}

int	end_of_string(t_split **delimiter, t_mshell *mshell, char *str, int *i)
{
	if (str[*i] == '\0')
	{
		syntax_error(mshell);
		ft_wordclear(delimiter);
		return (-1);
	}
	return (0);
}

int	parse_redir(t_split **delimiter, t_mshell *mshell, char *str, int *i)
{
	if (is_redir(str, i, mshell) == 2)
	{
		split_lstadd_back(delimiter, split_lstnew(str[*i]));
		(*i)++;
		split_lstadd_back(delimiter, split_lstnew(str[*i]));
	}
	else
		split_lstadd_back(delimiter, split_lstnew(str[*i]));
	(*i)++;
	if (str[*i] == 32)
	{
		while (str[*i] == 32)
			(*i)++;
	}
	return (1);
}
