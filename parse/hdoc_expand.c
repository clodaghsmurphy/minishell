/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hdoc_expand.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clmurphy <clmurphy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 13:31:13 by clmurphy          #+#    #+#             */
/*   Updated: 2022/06/01 13:48:58 by clmurphy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

char	*hdoc_expand(char *str, t_mshell *mshell)
{
	t_split	*word;
	int		i;
	int		type;

	type = 0;
	while (str[i] != '\0')
	{
		if (dollar_in_quote_string(&word, mshell, str, &i) == 1)
		{
			parse_dollar_dquotes(type, mshell, str, &i);
			continue ;
		}
		split_lstadd_back(&word, split_lstnew(str[i]));
		i++;
	}
	parse_if_word(&word, mshell, str, &i);
	return (ft_strdup(mshell->res));
}
