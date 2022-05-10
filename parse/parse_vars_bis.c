/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_mshell->vars_bis.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clmurphy <clmurphy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 16:46:43 by clmurphy          #+#    #+#             */
/*   Updated: 2022/05/10 12:05:55 by clmurphy         ###   ########.fr       */
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
	if (i != 0)
	{
		if (str[*i - 1] == 34 || str[*i - 1] == 39)
			type = str[*i - 1];
	}
	return (type);
}

int	dollar_only(t_split **word, t_mshell *mshell, char *str, int *i)
{
	if ((str[*i] == '$' && is_delim_dollar(str, (*i) + 1) == 0))
	{
		mshell->res = ft_strjoin(mshell->res, ft_strdup("$"));
		(*i)++;
		return (1);
	}
	return (0);
}

int	parse_dollar_string(int *j, t_mshell *mshell, char *str, int *i)
{
	int	type;

	type = define_quote_type(str, i);
	mshell->j = j;
	while (is_delim_dollar(str, *i) && str[*i] != type)
	{
		(*i)++;
		if (quotes_in_dstring(&type, mshell, str, i) == -1)
			return (-1);
		if (eq_in_dollar(&type, mshell, str, i) == 1)
			continue ;
		if (another_dollar(j, mshell, str, i) == 1)
			continue ;
	}
	return (0);
}

int	quotes_in_dstring(int *type, t_mshell *mshell, char *str, int *i)
{
	int	*j;

	j = mshell->j;
	if (str[*i] == 34 || str[*i] == 39 && type == 0)
	{
		if (str[*i + 1] == '\0')
		{
			printf("quote error\n");
			mshell->q_error = 1;
			return (-1);
		}
		*type = str[*i];
		(*i)++;
		if (str[*i] == *type)
		{
			(*i)++;
			*type = 0;
		}
		while (str[*i] != *type && str[*i] != '\0')
		{
			if (str[*i] == '$')
			{
				mshell->var = is_in_env(mshell, \
				ft_strndup(str + *j, (*i - *j)));
				if (mshell->var != NULL)
				{
					mshell->res = ft_strjoin(mshell->res, mshell->var);
				}
				*j = *i;
				free(mshell->var);
				mshell->var = NULL;
				continue ;
			}
			(*i)++;
		}
	}
	return (0);
}

int	eq_in_dollar(int *type, t_mshell *mshell, char *str, int *i)
{
	int	*j;

	j = mshell->j;
	if (str[*i] == '=')
	{
		mshell->var = is_in_env(mshell, ft_strndup(str + *j, (*i - *j)));
		if (mshell->var != NULL)
			mshell->res = ft_strjoin(mshell->res, mshell->var);
		*j = (*i);
		while (is_delim_dollar(str, *i) && str[*i] != *type && str[*i] != '$')
			(*i)++;
		mshell->res = ft_strjoin(mshell->res, ft_strndup(str + *j, (*i - *j)));
		*j = (*i);
		free(mshell->var);
		mshell->var = NULL;
		if (str[*i] == '$')
			return (1);
	}
	return (0);
}

int another_dollar(int *j, t_mshell *mshell, char *str, int *i)
{
	if (str[*i] == '$')
	{
		mshell->var = is_in_env(mshell, ft_strndup(str + *j, (*i - *j)));
		if (mshell->var != NULL)
			mshell->res = ft_strjoin(mshell->res, mshell->var);
		*j = (*i);
		free(mshell->var);
		mshell->var = NULL;
		return (1);
	}
	return (0);
}
