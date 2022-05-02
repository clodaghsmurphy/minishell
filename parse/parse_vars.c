/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_vars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clmurphy <clmurphy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 17:34:17 by clmurphy          #+#    #+#             */
/*   Updated: 2022/05/02 18:14:26 by clmurphy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_dollar(t_split **word, t_mshell *mshell, char *str, int *i)
{
	int		j;
	int		type;
	char	*res;
	char	*var;

	res = NULL;
	j = *i;
	if (str[*i + 1] == 34 || str[*i + 1] == 39)
	{
		(*i)++;
		type = (*i);
		if (str[*i + 1] == type)
		{
			phrase_lstadd_back(&mshell->phrase, phrase_lstnew(ft_strdup("")));
			return ;
		}
		parse_quotes(word, mshell, str, i);
		return ;
	}
	if ((str[*i] == '$' && str[*i + 1] == '\0') || \
	(str[*i] == '$' && str[*i + 1] == ' ') || \
	(str[*i] == '$' && str[*i + 1] == '|'))
	{
		phrase_lstadd_back(&mshell->phrase, phrase_lstnew(ft_strdup("$")));
		(*i)++;
		return ;
	}
	while (str[*i] != '\0' && str[*i] != '|' && str[*i] != ' ')
	{
		(*i)++;
		if (str[*i] == '$')
		{
			var = is_in_env(mshell, ft_strndup(str + j, (*i - j)));
			if (var != NULL)
				res = ft_strjoin(res, var);
			else
				res = ft_strjoin(res, ft_strdup(""));
			if (str[*i] == '$')
			{
				j = (*i) + 1;
				continue ;
			}
			else
				break ;
		}	
	}
	res = is_in_env(mshell, ft_strndup(str + j, (*i - j)));
	phrase_lstadd_back(&mshell->phrase, phrase_lstnew(res));
	return ;
}

void	parse_dollar_dquotes(t_split **word, t_mshell *mshell, char *str, int *i)
{
	int		j;
	char	type;

	type = str[*i - 1];
	j = *i;
	(*i)++;
	if (str[*i] == 34 || str[*i] == 39)
	{
		phrase_lstadd_back(&mshell->phrase, phrase_lstnew(ft_strdup("$")));
		(*i)++;
		return ;
	}
	while (str[*i] != type && str[*i] != '\0')
	{
		(*i)++;
	}
	if (type == 34)
		is_in_env(mshell, ft_strndup(str + j, (*i - j)));
	else if (type == 39)
	{
		phrase_lstadd_back(&mshell->phrase, phrase_lstnew(ft_strndup(str + j, (*i - j))));
		(*i)++;
	}
	if (str[*i] == 34)
		(*i)++;
}

char	*is_in_env(t_mshell *mshell, char *str)
{
	int		i;
	t_env	*temp;
	char	*var;

	var = ft_strdup(str + 1);
	temp = mshell->env;
	i = 0;
	while (temp != NULL)
	{
		if (ft_strncmp(var, temp->name, 100) == 0)
		{
			free(str);
			free(var);
			return (temp->value);
		}
		temp = temp->next;
	}
	free(str);
	free(var);
	return (NULL);
}

char	*ft_strndup(const char *s, int size)
{
	int		s_len;
	char	*s_;
	char	*s2;
	int		i;

	i = 0;
	s_ = (char *)s;
	s_len = ft_strlen(s_);
	s2 = malloc(sizeof(char) * s_len + 1);
	if (!s2)
		return (NULL);
	while (s[i] && i < size)
	{
		s2[i] = s[i];
		i++;
		if (s[i] == '$')
			break ;
	}
	s2[i] = '\0';
	return (s2);
}
