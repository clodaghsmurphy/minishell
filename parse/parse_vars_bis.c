/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_vars_bis.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clmurphy <clmurphy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 16:46:43 by clmurphy          #+#    #+#             */
/*   Updated: 2022/05/09 13:57:51 by clmurphy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

int	quote_after_dollar(t_split **word, t_mshell *mshell, char *str, int *i)
{
	if (str[*i + 1] == 34 || str[*i + 1] == 39)
	{
		(*i)++;
		if (str[*i + 1] == type)
			return ;
		parse_quotes(word, mshell, str, i);
		return (1) ;
	}
}
