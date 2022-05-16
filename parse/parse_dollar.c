/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_dollar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clmurphy <clmurphy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 15:56:42 by clmurphy          #+#    #+#             */
/*   Updated: 2022/05/16 17:25:18 by clmurphy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_dollar(t_split **word, t_mshell *mshell, char *str, int *i)
{
	int		j;
	int		type;
	int		res;

	j = *i;
	if (*word)
		mshell->res = ft_strjoin(mshell->res, make_word(word, mshell));
	if (quote_after_dollar(word, mshell, str, i) == 1)
		return ;
	if (dollar_only(word, mshell, str, i) == 1)
		return ;
	if (str[*i + 1] == '=')
	{
		(*i)++;
		(*i)++;
		mshell->res = ft_strjoin(mshell->res, ft_strdup("$="));
		return ;
	}
	number_after_dollar(mshell, str, i);
	res = parse_dollar_string(&j, mshell, str, i);
	if (res == 1)
		return ;
	else if (res == 2)
	{
		j = mshell->j;
		mshell->var = is_in_env(mshell, ft_strndup(str + j, (*i - j)));
		if (mshell->var != NULL)
		{
			mshell->res = ft_strjoin(mshell->res, mshell->var);
			return ;
		}
		else
		{
			free(mshell->var);
			mshell->var = NULL;
			parse_quotes(word, mshell, str, i);
			return ;
		}
	}
	mshell->var = is_in_env(mshell, ft_strndup(str + j, (*i - j)));
	if (mshell->var != NULL)
		mshell->res = ft_strjoin(mshell->res, mshell->var);
	else
	{
		free(mshell->var);
		mshell->var = NULL;
		return ;
	}
	free(mshell->var);
	mshell->var = NULL;
	return ;
}

int	quotes_in_dstring(int *type, t_mshell *mshell, char *str, int *i)
{
	int	j;

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
	}
	return (0);
}

int	number_after_dollar(t_mshell *mshell, char *str, int *i)
{
	int	j;

	j = *i;
	if (str[*i + 1] >= '0' && str[*i + 1] <= '9')
	{
		(*i)++;
		mshell->var = is_in_env(mshell, ft_strndup(str + j, (*i - j)));
		(*i)++;
		if (mshell->var != NULL)
			mshell->res = ft_strjoin(mshell->res, mshell->var);
		else
		{
			free(mshell->var);
			mshell->var = NULL;
			return (1);
		}
		return (1);
	}
	return (0);
}
