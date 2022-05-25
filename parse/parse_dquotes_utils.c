/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_dquotes_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clmurphy <clmurphy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 11:31:01 by clmurphy          #+#    #+#             */
/*   Updated: 2022/05/25 10:45:19 by clmurphy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	dquote_eq(t_mshell *mshell, char *str, int *i)
{
	if (str[*i + 1] == '=' && str[*i] == '$')
	{
		(*i)++;
		(*i)++;
		mshell->res = ft_strjoin_f2(mshell->res, ft_strdup("$="));
		return (1);
	}
	return (0);
}

int	parse_dquote_string2(int type, t_mshell *mshell, char *str, int *i)
{
	int	j;

	j = mshell->j;
	while (str[*i] != type && is_delim_dollar(str, *i) == 1)
	{
		if (str[*i - 1] == '$' && type == 34)
		{
			while (str[*i] != type && str[*i] != '$' && \
			is_delim_dollar(str, *i) == 1)
			{
				if (dquote_is_digit(mshell, str, i) == 1)
					return (1);
				(*i)++;
			}
			make_var2(mshell, str, i);
			j = (*i);
			mshell->j = j;
			continue ;
		}
		(*i)++;
	}
	if (type == 39)
		mshell->res = ft_strjoin_f2(mshell->res, ft_strndup(str + j, (*i - j)));
	return (0);
}

void	make_var2(t_mshell *mshell, char *str, int *i)
{
	int	j;

	j = mshell->j;
	mshell->var = is_in_env(mshell, ft_strndup(str + j, (*i - j)));
	if (mshell->var != NULL)
		mshell->res = ft_strjoin_f2(mshell->res, mshell->var);
	free(mshell->var);
	mshell->var = NULL;
}

int	dquote_is_digit(t_mshell *mshell, char *str, int *i)
{
	int	j;

	j = mshell->j;
	if (ft_isdigit(str[*i]) && str[*i - 1] == '$')
	{
		(*i)++;
		mshell->var = is_in_env(mshell, \
		ft_strndup(str + j, (*i - j)));
		if (mshell->var != NULL)
			mshell->res = ft_strjoin_f2(mshell->res, mshell->var);
		else
		{
			free(mshell->var);
			mshell->var = NULL;
			return (1);
		}
	}
	return (0);
}
