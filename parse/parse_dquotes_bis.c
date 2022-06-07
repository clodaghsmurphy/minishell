/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_dquotes_bis.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clmurphy <clmurphy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 12:05:08 by clmurphy          #+#    #+#             */
/*   Updated: 2022/06/04 12:12:12 by clmurphy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

int	eq_in_dquote(t_mshell *mshell, char *str, int *i)
{
	int	j;

	j = mshell->j;
	if (str[*i] == '=')
	{
		mshell->var = is_in_env(mshell, ft_strndup(str + j, (*i - j)));
		if (mshell->var != NULL)
			mshell->res = ft_strjoin_f2(mshell->res, mshell->var);
		mshell->j = (*i);
		return (1);
	}
	return (0);
}

int	check_dquote_error(char *str, int *i)
{
	if (str[*i] == '\0')
	{
		printf("quote error\n");
		return (1);
	}
	return (0);
}

int	check_dquote_in_env(int type, t_mshell *mshell, char *str, int *i)
{
	int	j;

	j = mshell->j;
	if (type == 34)
	{
		mshell->var = is_in_env(mshell, ft_strndup(str + j, (*i - j)));
		if (mshell->var != NULL)
			mshell->res = ft_strjoin_f2(mshell->res, mshell->var);
		else
			mshell->res = ft_strjoin_f2(mshell->res, ft_strdup(""));
	}
	else if (type == 39)
	{
		mshell->res = ft_strjoin_f2(mshell->res, mshell->var);
		(*i)++;
	}
	return (0);
}
