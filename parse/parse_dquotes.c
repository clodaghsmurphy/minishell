/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_dquotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clmurphy <clmurphy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 11:37:04 by clmurphy          #+#    #+#             */
/*   Updated: 2022/06/03 17:46:20 by clmurphy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

int	dquotes_only(int type, t_mshell *mshell, char *str, int *i)
{
	if (str[*i] == 34 || str[*i] == 39)
	{
		if (str[*i] == type)
			mshell->res = ft_strjoin_f2(mshell->res, ft_strdup("$"));
		return (1);
	}
	return (0);
}

int	eq_start_dquote(t_mshell *mshell, char *str, int *i)
{
	if (str[*i] == '=')
	{
		(*i)++;
		mshell->res = ft_strjoin_f2(mshell->res, ft_strdup("$="));
		return (1);
	}
	return (0);
}

int	digit_in_dquote(t_mshell *mshell, char *str, int *i)
{
	int	j;

	j = mshell->j;
	if (str[*i] >= '0' && str[*i] <= '9')
	{
		(*i)++;
		mshell->var = is_in_env(mshell, ft_strndup(str + j, (*i - j)));
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

int	parse_dquote_string(int type, t_mshell *mshell, char *str, int *i)
{
	int		j;
	char	*new_word;

	new_word = NULL;
	if (dquote_eq(mshell, str, i) == 1)
		return (1);
	if (parse_dquote_string_bis(type, mshell, str, i) == 1)
		return (1);
	if (str[*i] == '$' && str[*i + 1] == '?' && type == 34)
	{
		new_word = ft_itoa(g_estatus);
		mshell->res = ft_strjoin_f2(mshell->res, new_word);
		free(new_word);
		*i += 2;
		return (1);
	}
	if (number_after_dollar(mshell, str, i) == 1)
		return (1);
	mshell->j = *i;
	j = mshell->j;
	if (parse_dquote_string2(type, mshell, str, i) == 1)
		return (1);
	return (0);
}

int	parse_dquote_string_bis(int type, t_mshell *mshell, char *str, int *i)
{
	char	*new_word;

	if (str[*i] == '$' && str[*i + 1] == type)
	{
		*i += 2;
		new_word = ft_strdup("$");
		mshell->res = ft_strjoin_f2(mshell->res, new_word);
		free(new_word);
		return (1);
	}
	return (0);
}
