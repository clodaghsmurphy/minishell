/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hdoc_expand.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clmurphy <clmurphy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 13:31:13 by clmurphy          #+#    #+#             */
/*   Updated: 2022/06/01 13:38:44 by clmurphy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../includes/minishell.h"

char	*hdoc_expand(char *str, t_mshell *mshell)
{
	t_split	*word;
	char	*new_word;
	int		i;
	int		type;

	type = 0;
	mshell->j = 0;
	printf("Here and str is %s\n", str);
	while (str[i] != '\0')
	{
		if (str[i] == '$')
		{
			//new_word = make_word(&word, mshell);
			/* if (new_word)
				mshell->res = ft_strjoin_f2(mshell->res, new_word); */
			printf("str beofre quotes %s\n", str);
			parse_hdoc_quotes(mshell, str, &i);
			continue ;
		}
		split_lstadd_back(&word, split_lstnew(str[i]));
		i++;
	}
	parse_if_word(&word, mshell, str, &i);
	return (ft_strdup(mshell->res));
}

int	parse_hdoc_quotes(t_mshell *mshell, char *str, int *i)
{
	int	j;

	j = mshell->j;
	while (is_delim_dollar(str, *i) == 1)
	{
		while (str[*i] != 34 && str[*i] != 39 && str[*i + 1] != '$' && \
		is_delim_dollar(str, *i) == 1)
		{
			if (dquote_is_digit(mshell, str, i) == 1)
				return (1);
			(*i)++;
		}
		printf("str before makevat %s\n", str);
		make_var2(mshell, str, i);
		j = (*i);
		mshell->j = j;
		continue ;
	}
	(*i)++;
	return (0);
}
