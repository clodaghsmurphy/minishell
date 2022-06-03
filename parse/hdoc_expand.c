/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hdoc_expand.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clmurphy <clmurphy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 13:31:13 by clmurphy          #+#    #+#             */
/*   Updated: 2022/06/03 17:06:51 by clmurphy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

char	*hdoc_expand(char *str, t_mshell *mshell)
{
	int			i;
	int			len;
	char		*res;
	char		*s1;

	if (str == NULL)
		return (ft_strdup(""));
	i = 0;
	s1 = NULL;
	res = NULL;
	mshell->hdoc_flag = 0;
	mshell->word = NULL;
	mshell->phrase = NULL;
	mshell->hdoc_flag = 0;
	len = ft_strlen(str) - 1;
	s1 = ft_strndup2(str, len);
	while (s1[i] != '\0')
	{
		parse_string2(&mshell->word, mshell, s1, &i);
		if (s1[i - 1] == 32 && mshell->phrase)
			phrase_lstadd_back(&mshell->phrase, \
		phrase_lstnew(ft_strdup(" ")));
	}
	res = hdoc_expand2(str, s1, mshell);
	return (res);
}

char	*hdoc_expand2(char *str, char *s1, t_mshell *mshell)
{
	t_phrase	*temp;
	char		*res;

	free(str);
	res = NULL;
	temp = mshell->phrase;
	while (temp != NULL)
	{
		res = ft_strjoin_f2(res, temp->str);
		temp = temp->next;
	}
	free_phrase2(&mshell->phrase);
	if (res == NULL)
		res = ft_strdup("");
	free(s1);
	return (res);
}

int	parse_string2(t_split **word, t_mshell *mshell, char *str, int *i)
{
	while (is_delim(mshell, str, i) == 1 && str[*i] != '\n')
	{
		if (str[*i] == '$' && mshell->hdoc_flag != 1)
		{
			parse_dollar(word, mshell, str, i);
			continue ;
		}
		split_lstadd_back(word, split_lstnew(str[*i]));
		(*i)++;
	}
	parse_string_bis2(word, mshell, str, i);
	return (1);
}

void	parse_string_bis2(t_split **word, t_mshell *mshell, char *str, int *i)
{
	char	*new_word;

	while (str[*i] == 32)
		(*i)++;
	new_word = make_word(word, mshell);
	if (new_word)
	{
		mshell->res = ft_strjoin_f2(mshell->res, new_word);
		free(new_word);
	}
	if (mshell->res)
		phrase_lstadd_back(&mshell->phrase, \
		phrase_lstnew(ft_strdup(mshell->res)));
	free(mshell->res);
	mshell->res = NULL;
}
