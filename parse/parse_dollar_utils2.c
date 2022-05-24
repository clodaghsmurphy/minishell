/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_dollar_utils2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clmurphy <clmurphy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 10:17:16 by clmurphy          #+#    #+#             */
/*   Updated: 2022/05/24 15:43:09 by clmurphy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

int	eq_in_dollar(int *type, t_mshell *mshell, char *str, int *i)
{
	int	j;

	j = *i;
	if (str[*i] == '=')
	{
		mshell->var = is_in_env(mshell, ft_strndup(str + j, (*i - j)));
		if (mshell->var != NULL)
			mshell->res = ft_strjoin_f2(mshell->res, mshell->var);
		j = (*i);
		while (is_delim_dollar(str, *i) && str[*i] != *type && str[*i] != '$')
			(*i)++;
		mshell->res = ft_strjoin_f2(mshell->res, ft_strndup(str + j, (*i - j)));
		j = (*i);
		mshell->j = j;
		free(mshell->var);
		mshell->var = NULL;
		if (str[*i] == '$')
			return (1);
	}
	return (0);
}

int	another_dollar(int *j, t_mshell *mshell, char *str, int *i)
{
	if (str[*i] == '$')
	{
		mshell->var = is_in_env(mshell, ft_strndup(str + *j, (*i - *j)));
		if (mshell->var != NULL)
			mshell->res = ft_strjoin_f2(mshell->res, mshell->var);
		mshell->j = (*i);
		free(mshell->var);
		mshell->var = NULL;
		if (str[*i + 1] == '=')
		{
			(*i)++;
			(*i)++;
			mshell->res = ft_strjoin_f2(mshell->res, ft_strdup("$="));
			return (2);
		}
		return (1);
	}
	return (0);
}

int	parse_quotes_in_destring(int *type, t_mshell *mshell, char *str, int *i)
{
	int	j;

	j = mshell->j;
	while (str[*i] != *type && str[*i] != '\0')
	{
		if (str[*i] == '$')
		{
			mshell->var = is_in_env(mshell, \
			ft_strndup(str + j, (*i - j)));
			if (mshell->var != NULL)
			{
				mshell->res = ft_strjoin_f2(mshell->res, mshell->var);
			}
			j = *i;
			mshell->j = j;
			free(mshell->var);
			mshell->var = NULL;
			continue ;
		}
		(*i)++;
	}
	return (0);
}

int	eq_in_pdollar(t_mshell *mshell, char *str, int *i)
{
	if (str[*i + 1] == '=')
	{
		(*i)++;
		(*i)++;
		mshell->res = ft_strjoin_f2(mshell->res, ft_strdup("$="));
		return (1);
	}
	return (0);
}
